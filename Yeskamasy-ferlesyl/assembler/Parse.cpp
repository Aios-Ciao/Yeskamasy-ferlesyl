#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include "Parse.h"

unsigned char Parse::tblCharType[256];

std::map<std::string, std::string>	mmPOC;	// Processor Option Command
std::map<std::string, std::string>	mmReg;	// レジスタ
std::map<std::string, std::string>	mmOpe;	// 命令

// コンストラクタ
Parse::Parse(char *fname)
	: ifs( fname )
{
	// 文字タイプマップ初期化
	{
		// 使用可能な文字種以外は不正として初期化
		for (int idx = 0; idx < 255; idx++) {
			tblCharType[idx] = Parse::eInvalid;
		}

		// 数字
		for (int idx = 0; idx < 10; idx++) {
			tblCharType['0' + idx] = Parse::eNum;
		}

		// 通常文字
		for (int idx = 'a'; idx <= 'z'; idx++) {
			tblCharType[idx] = Parse::eWord;
		}
		tblCharType['F'] = Parse::eWord;
		tblCharType['R'] = Parse::eWord;
		tblCharType['V'] = Parse::eWord;
		tblCharType['X'] = Parse::eWord;
		tblCharType['\''] = Parse::eWord;
		tblCharType['-'] = Parse::eWord;
		tblCharType['_'] = Parse::eWord;

		// 空白文字
		tblCharType['\x20'] = Parse::eBlank;
		tblCharType['\t'] = Parse::eBlank;

		// 改行系文字
		tblCharType['\r'] = Parse::eBreak;
		tblCharType['\n'] = Parse::eBreak;

		// 記号
		tblCharType['+'] = Parse::ePlus;
		tblCharType['@'] = Parse::eDerefer;

		// コメント記号
		tblCharType[';'] = Parse::eComment;
	}

	// プロセッサオプションコマンド
	mmPOC.clear();
	mmPOC["'c'i"] = "'c'i";
	mmPOC["'i'c"] = "'i'c";
	mmPOC["l'"] = "l'";
	mmPOC["nll"] = "nll";
	mmPOC["kue"] = "kue";
	mmPOC["xok"] = "xok";

	// レジスタ
	mmReg.clear();
	mmReg["f0"] = "f0";
	mmReg["f1"] = "f1";
	mmReg["f2"] = "f2";
	mmReg["f3"] = "f3";
	mmReg["f4"] = "f4";
	mmReg["f5"] = "f5";
	mmReg["f6"] = "f6";
	mmReg["f7"] = "xx";
	mmReg["xx"] = "xx";

	// 命令(大小文字はいちおう区別する)
	mmOpe.clear();
	mmOpe["krz"] = "krz";			mmOpe["kRz"] = "krz";
	mmOpe["malkrz"] = "malkrz";		mmOpe["malkRz"] = "malkrz";
	mmOpe["fen"] = "fen";
	mmOpe["inj"] = "inj";
	mmOpe["ata"] = "ata";
	mmOpe["nta"] = "nta";
	mmOpe["lat"] = "lat";
	mmOpe["latsna"] = "latsna";
//	mmOpe["kak"] = "kak";
	mmOpe["ada"] = "ada";
	mmOpe["ekc"] = "ekc";
	mmOpe["nac"] = "nac";
	mmOpe["dal"] = "dal";
	mmOpe["dto"] = "dto";
	mmOpe["dtosna"] = "dtosna";
	mmOpe["dro"] = "dro";			mmOpe["dRo"] = "dro";

	mmOpe["fi"] = "fi";
	mmOpe["xtlo"] = "xtlo";		// 条件コード
	mmOpe["xylo"] = "xylo";
	mmOpe["clo"] = "clo";
	mmOpe["xolo"] = "xolo";
	mmOpe["llo"] = "llo";
	mmOpe["niv"] = "niv";
	mmOpe["xtlonys"] = "xtlonys";
	mmOpe["xylonys"] = "xylonys";
	mmOpe["xolonys"] = "xolonys";
	mmOpe["llonys"] = "llonys";


	// 開けていなければ警告
	if (ifs.fail()) {
		std::cerr << "ファイルが開けませんでした(" << std::string(fname) << ")" << std::endl;
	}
}

// デストラクタ
Parse::~Parse()
{
	ifs.close();
}

// 1単語取得
bool Parse::getToken(std::string &token, Parse::PosInfo &tokenpos, Parse::PosInfo &nexttoken)
{
	char chr;
	bool next(true);
	bool bcommentskip(false);
	unsigned char context;
	unsigned char type;

	token = "";
	tokenpos = nexttoken;

	chr = ifs.get();
	if (chr == -1 )	// eof
	{
		return(false);
	}
	ifs.unget();

	context = tblCharType[chr];

	while (next && ifs.get(chr))
	{
		nexttoken.nColumn++;

		type = tblCharType[chr];
		// コメント処理中は改行以外空白として扱う
		if (bcommentskip) {
			if (type != eBreak)
			{
				type = eComment;
			}
		}

		switch (context) {
		case Parse::eNum:
			switch (type) {
			case Parse::eNum:
				token += chr;
				break;
			default:
				ifs.unget();
				next = false;
				break;
			}
			break;
		case Parse::eWord:
			switch (type) {
			case Parse::eWord:
			case Parse::eNum:
				token += chr;
				break;
			default:
				ifs.unget();
				next = false;
			}
			break;
		case Parse::eBreak:
			token = "\x20";
			nexttoken.nRow++;			// 次の行へ
			nexttoken.nColumn = 0;
			bcommentskip = false;		// 行コメント終了
			next = false;
			break;
		case Parse::eBlank:
			if (type != context) {
				ifs.unget();
				token = "\x20";
				next = false;
			}
			break;
		case Parse::eComment:		// ;
			if (type == eBreak)
			{
				ifs.unget();
				token = "\x20";
				next = false;
			}
			bcommentskip = true;	// 以降行末(改行)までコメントとしてスキップ
			break;
		case Parse::eDerefer:		// @
		case Parse::ePlus:			// +
			token = chr;
			next = false;
			break;
		default:
			return(false);
			break;
		}
	}

	return (!ifs.eof());
}

// プリプロセッサの命令か
bool Parse::isProcOption(std::string &token)
{
	return (mmPOC.count(token) > 0);
}

// レジスタ名に登録があるか
bool Parse::isRegister(std::string &token)
{
	return (mmReg.count(token) > 0);
}

// 命令名として登録があるか
bool Parse::isMnemonic(std::string &token)
{
	return (mmOpe.count(token) > 0);
}

// 数値文字列か
bool Parse::isNumeric(std::string &token)
{
	// 数字以外のものが見つからなかったなら数値文字列
	return (token.find_first_not_of("0123456789") == -1);
}

// ラベル、シンボルとして有効な文字で構成されているか
bool Parse::isValidSymbol(std::string &token)
{
	bool bValid(false);

	// 有効な文字で構成されていること
	if (token.find_first_not_of("pFftcxkqhRzmnrljwbVvdsgXiyuoea0123456789'-_") == -1) {
		// 1文字目は数字以外であること
		if ((token[0] < '0') || ('9' < token[0])) {
			bValid = true;
		}
	}

	return (bValid);
}

Parse::Token Parse::Tokenize(std::string &token, Parse::PosInfo &tokenpos)
{
	Token tok(token, tokenpos);

	if (isProcOption(token)) {
		tok.type = TokenType::eProcOption;
	}
	else if (isRegister(token)) {
		tok.type = TokenType::eRegister;
	}
	else if (isNumeric(token)) {
		tok.type = TokenType::eNumeric;
	}
	else if (isMnemonic(token)) {
		tok.type = TokenType::eMnemonic;
	}
	else if (!token.compare("+")) {
		tok.type = TokenType::eDisplacement;
	}
	else if (!token.compare("@")) {
		tok.type = TokenType::eDereference;
	}
	else if (isValidSymbol(token)) {
		tok.type = TokenType::eSymbol;
	}
	else {
		// ラベルかもしれないし不正な文字列かもしれない
		tok.type = TokenType::eUnknown;
	}

	return(tok);
}

