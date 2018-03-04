#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include "Parse.h"
#include "Encoder.h"
#include "Statement.h"

unsigned char Parse::tblCharType[256];

std::map<std::string, std::string>	mmPOC;	// Processor Option Command
std::map<std::string, std::string>	mmCondition;	// 比較条件

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

	// 条件コード
	mmCondition["xtlo"] = "xtlo";
	mmCondition["xylo"] = "xylo";
	mmCondition["clo"] = "clo";
	mmCondition["xolo"] = "xolo";
	mmCondition["llo"] = "llo";
	mmCondition["niv"] = "niv";
	mmCondition["xtlonys"] = "xtlonys";
	mmCondition["xylonys"] = "xylonys";
	mmCondition["xolonys"] = "xolonys";
	mmCondition["llonys"] = "llonys";

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

// トークンのリストを生成する
Parse::tTokenList Parse::makeTokenList()
{
	std::string	word;
	Parse::PosInfo	curp, nextp;
	tTokenList vTokenList;

	while (getToken(word, curp, nextp))
	{
		if (word != "\x20") {
			vTokenList.push_back(Tokenize(word, curp));
		}
	}

	return (vTokenList);
}

// トークンリストからステートメントリストへの変換
Parse::tStatementList Parse::makeStatementList(Parse::tTokenList &vTokenList)
{
	tStatementList			vStatementList;
	tTokenList::size_type	idx(0);
	Mnemonic::tParamDir		ecid(Mnemonic::tParamDir::eci_I_C);		// 初期値は'i'c

	// パラメータ指定方向の設定
	auto setCI = [&](std::string &k) {
		ecid = !k.compare("'c'i") ? Mnemonic::tParamDir::eci_C_I : Mnemonic::tParamDir::eci_I_C;
	};

	while (idx < vTokenList.size())
	{
		Token & tok = vTokenList[idx];

		// 初期状態からはパラメータの方向指示とニーモニックのみ受け付ける
		switch (tok.type)
		{
		case Token::eProcOption:
			if (tok.chkKeyword("'c'i") || tok.chkKeyword("'i'c"))
			{
				setCI(tok.str);
				idx++;
			}
			else if (tok.chkKeyword("kue"))
			{
				// パラメータ１つとってラベル処理
				idx+=2;
			}
			else if (tok.chkKeyword("xok"))
			{
				// パラメータ１つとってラベル処理
				idx += 2;
			}
			else if (tok.chkKeyword("nll"))
			{
				// パラメータ１つとってラベル処理
				idx += 2;
			}
			else if (tok.chkKeyword("l'"))
			{
				// パラメータ１つとってラベル処理
				idx += 2;
			}
			else
			{

			}
			break;
		case Token::eMnemonic: {
			// ニーモニック
			Mnemonic	*mne = Encoder::getMnemonic(tok.str);
			Mnemonic::tParamCount	count = mne->getParamCount();
			Statement	statement;
			bool bError(false);

			Statement::tParamMap	params;

			idx++;	// 次からパラメータ
			// 必要な数だけパラメータを集める
			for (Mnemonic::tParamCount cnt = 0; cnt < count; ++cnt)
			{
				Parameter	prm = makeParameter(vTokenList, idx);
				Mnemonic::tParamCount	pidx = mne->getParamIndex(cnt, ecid);

				if (mne->chkParamType(pidx, prm.type))
				{
					params[pidx] = prm;
				}
				else
				{
					bError = true;
					// 不正な形式のパラメータ
					break;
				}
			}

			// エラーがなければ'i'c順にパラメータを整えてステートメントにセット
			if (!bError)
			{
				statement.eci = ecid;
				statement.mnemonic = mne;

				// 各Mnemonicで定義されるePrmTypeの順に積みなおし
				for (Mnemonic::tParamCount cnt = 0; cnt < count; ++cnt)
				{
					statement.param.push_back(params[cnt]);
				}

				vStatementList.push_back(statement);
			}
		}	break;
		default:
			break;
		}
	}

	return(vStatementList);
}

// トークンリストの指定した位置からパラメータとして使える単位で１つ取得する
Parameter	Parse::makeParameter(Parse::tTokenList &vTokList, Parse::tTokenList::size_type &top)
{
	Parameter	param;

	if (top >= vTokList.size()) return(param);
	Token & tok = vTokList[top];

	switch (tok.type)
	{
	case Token::eCondition:
		// 比較条件が来たらコンディションで確定
		param.type = Parameter::eptCondition;
		param.cond = Parameter::fromCondStr(tok.str);
		top++;
		break;
	case Token::eNumeric:
		// 数値が来たらイミディエイト確定
		param.type = Parameter::eptImmidiate;
		param.imm = std::stoul(tok.str);
		top++;
		break;
	case Token::eSymbol:
		// ラベルが来たらラベル指定確定(アドレス解決必要)
		param.type = Parameter::eptLabel;
		param.label = tok.str;
		top++;
		break;
	case Token::eRegister:
		if ((top + 1) < vTokList.size())
		{
			// リストの最後でない場合修飾をチェック
			switch (vTokList[top+1].type)
			{
			case Token::eDereference:	// @
				// レジスタ間接(オフセットなど無し)確定
				param.type = Parameter::eptReg_Ofs_Imm;
				param.base = Parameter::fromRegName(tok.str);
				param.imm = 0;	// オフセット0の間接参照として扱う
				top += 2;
				break;
			case Token::eDisplacement:	// +
				// + reg/imm @ で3つ先まで必要
				if (((top + 3) < vTokList.size()) && (vTokList[top + 3].type == Token::eDereference))
				{
					// リストの最後でなければ残りもチェック
					if (vTokList[top + 2].type == Token::eRegister) {
						// reg + reg @
						param.type = Parameter::eptReg_Ofs_Reg;
						param.base = Parameter::fromRegName(tok.str);
						param.dsp = Parameter::fromRegName(vTokList[top + 2].str);
					}
					else if (vTokList[top + 2].type == Token::eNumeric) {
						// reg + imm @
						param.type = Parameter::eptReg_Ofs_Imm;
						param.base = Parameter::fromRegName(tok.str);
						param.imm = std::stoul(vTokList[top + 2].str);
					}
					top += 4;
				}
				break;
			default:
				// ラストならばレジスタ直接に決定
				param.type = Parameter::eptRegister;
				param.base = Parameter::fromRegName(tok.str);
				top++;
				break;
			}
		}
		else
		{
			// ラストならばレジスタ直接に決定
			param.type = Parameter::eptRegister;
			param.base = Parameter::fromRegName(tok.str);
			top++;
		}
		break;
	default:
		break;
	}

	return(param);
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
	return (Parameter::isValidRegName(token));
}

// 命令名として登録があるか
bool Parse::isMnemonic(std::string &token)
{
//	return (mmOpe.count(token) > 0);
	return (Encoder::isMnemonic(token));
}

// 数値文字列か
bool Parse::isNumeric(std::string &token)
{
	// 数字以外のものが見つからなかったなら数値文字列
	return (token.find_first_not_of("0123456789") == -1);
}

// 比較条件か
bool Parse::isCondition(std::string &token)
{
	return(mmCondition.count(token) > 0);
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
		tok.type = Parse::Token::eProcOption;
	}
	else if (isRegister(token)) {
		tok.type = Parse::Token::eRegister;
	}
	else if (isNumeric(token)) {
		tok.type = Parse::Token::eNumeric;
	}
	else if (isMnemonic(token)) {
		tok.type = Parse::Token::eMnemonic;
	}
	else if (!token.compare("+")) {
		tok.type = Parse::Token::eDisplacement;
	}
	else if (!token.compare("@")) {
		tok.type = Parse::Token::eDereference;
	}
	else if (isCondition(token)) {
		tok.type = Parse::Token::eCondition;
	}
	else if (isValidSymbol(token)) {
		tok.type = Parse::Token::eSymbol;
	}
	else {
		tok.type = Parse::Token::eUnknown;
	}

	return(tok);
}

