#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include "Parse.h"

unsigned char Parse::tblCharType[256];

std::map<std::string, std::string>	mmPOC;	// Processor Option Command
std::map<std::string, std::string>	mmReg;	// ���W�X�^
std::map<std::string, std::string>	mmOpe;	// ����

// �R���X�g���N�^
Parse::Parse(char *fname)
	: ifs( fname )
{
	// �����^�C�v�}�b�v������
	{
		// �g�p�\�ȕ�����ȊO�͕s���Ƃ��ď�����
		for (int idx = 0; idx < 255; idx++) {
			tblCharType[idx] = Parse::eInvalid;
		}

		// ����
		for (int idx = 0; idx < 10; idx++) {
			tblCharType['0' + idx] = Parse::eNum;
		}

		// �ʏ핶��
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

		// �󔒕���
		tblCharType['\x20'] = Parse::eBlank;
		tblCharType['\t'] = Parse::eBlank;

		// ���s�n����
		tblCharType['\r'] = Parse::eBreak;
		tblCharType['\n'] = Parse::eBreak;

		// �L��
		tblCharType['+'] = Parse::ePlus;
		tblCharType['@'] = Parse::eDerefer;

		// �R�����g�L��
		tblCharType[';'] = Parse::eComment;
	}

	// �v���Z�b�T�I�v�V�����R�}���h
	mmPOC.clear();
	mmPOC["'c'i"] = "'c'i";
	mmPOC["'i'c"] = "'i'c";
	mmPOC["l'"] = "l'";
	mmPOC["nll"] = "nll";
	mmPOC["kue"] = "kue";
	mmPOC["xok"] = "xok";

	// ���W�X�^
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

	// ����(�召�����͂���������ʂ���)
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
	mmOpe["xtlo"] = "xtlo";		// �����R�[�h
	mmOpe["xylo"] = "xylo";
	mmOpe["clo"] = "clo";
	mmOpe["xolo"] = "xolo";
	mmOpe["llo"] = "llo";
	mmOpe["niv"] = "niv";
	mmOpe["xtlonys"] = "xtlonys";
	mmOpe["xylonys"] = "xylonys";
	mmOpe["xolonys"] = "xolonys";
	mmOpe["llonys"] = "llonys";


	// �J���Ă��Ȃ���Όx��
	if (ifs.fail()) {
		std::cerr << "�t�@�C�����J���܂���ł���(" << std::string(fname) << ")" << std::endl;
	}
}

// �f�X�g���N�^
Parse::~Parse()
{
	ifs.close();
}

// 1�P��擾
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
		// �R�����g�������͉��s�ȊO�󔒂Ƃ��Ĉ���
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
			nexttoken.nRow++;			// ���̍s��
			nexttoken.nColumn = 0;
			bcommentskip = false;		// �s�R�����g�I��
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
			bcommentskip = true;	// �ȍ~�s��(���s)�܂ŃR�����g�Ƃ��ăX�L�b�v
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

// �v���v���Z�b�T�̖��߂�
bool Parse::isProcOption(std::string &token)
{
	return (mmPOC.count(token) > 0);
}

// ���W�X�^���ɓo�^�����邩
bool Parse::isRegister(std::string &token)
{
	return (mmReg.count(token) > 0);
}

// ���ߖ��Ƃ��ēo�^�����邩
bool Parse::isMnemonic(std::string &token)
{
	return (mmOpe.count(token) > 0);
}

// ���l������
bool Parse::isNumeric(std::string &token)
{
	// �����ȊO�̂��̂�������Ȃ������Ȃ琔�l������
	return (token.find_first_not_of("0123456789") == -1);
}

// ���x���A�V���{���Ƃ��ėL���ȕ����ō\������Ă��邩
bool Parse::isValidSymbol(std::string &token)
{
	bool bValid(false);

	// �L���ȕ����ō\������Ă��邱��
	if (token.find_first_not_of("pFftcxkqhRzmnrljwbVvdsgXiyuoea0123456789'-_") == -1) {
		// 1�����ڂ͐����ȊO�ł��邱��
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
		// ���x����������Ȃ����s���ȕ����񂩂�����Ȃ�
		tok.type = TokenType::eUnknown;
	}

	return(tok);
}

