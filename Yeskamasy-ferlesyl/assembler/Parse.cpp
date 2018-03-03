#include <cstdio>
#include <iostream>
#include <fstream>
#include <map>
#include "Parse.h"
#include "Encoder.h"
#include "Statement.h"

unsigned char Parse::tblCharType[256];

std::map<std::string, std::string>	mmPOC;	// Processor Option Command
std::map<std::string, std::string>	mmCondition;	// ��r����

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

	// �����R�[�h
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

// �g�[�N���̃��X�g�𐶐�����
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

// �g�[�N�����X�g����X�e�[�g�����g���X�g�ւ̕ϊ�
Parse::tStatementList Parse::makeStatementList(Parse::tTokenList &vTokenList)
{
	tStatementList			vStatementList;
	tTokenList::size_type	idx(0);
	Mnemonic::tParamDir		ecid(Mnemonic::tParamDir::eci_I_C);		// �����l��'i'c

	// �p�����[�^�w������̐ݒ�
	auto setCI = [&](std::string &k) {
		ecid = !k.compare("'c'i") ? Mnemonic::tParamDir::eci_C_I : Mnemonic::tParamDir::eci_I_C;
	};

	while (idx < vTokenList.size())
	{
		Token & tok = vTokenList[idx];

		// ������Ԃ���̓p�����[�^�̕����w���ƃj�[���j�b�N�̂ݎ󂯕t����
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
				// �p�����[�^�P�Ƃ��ă��x������
				idx+=2;
			}
			else if (tok.chkKeyword("xok"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				idx += 2;
			}
			else if (tok.chkKeyword("nll"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				idx += 2;
			}
			else if (tok.chkKeyword("l'"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				idx += 2;
			}
			else
			{

			}
			break;
		case Token::eMnemonic: {
			// �j�[���j�b�N
			Mnemonic	*mne = Encoder::getMnemonic(tok.str);
			Mnemonic::tParamCount	count = mne->getParamCount();
			Statement	statement;

			statement.eci = ecid;
			statement.mnemonic = mne;
			idx++;	// ������p�����[�^
			// �K�v�Ȑ������p�����[�^���W�߂�
			for (Mnemonic::tParamCount cnt = 0; cnt < count; ++cnt)
			{
				Parameter	prm = makeParameter(vTokenList, idx);
				Mnemonic::tParamCount	pidx = mne->getParamIndex(cnt, ecid);

				if (mne->chkParamType(pidx, prm.type))
				{
					statement.param.push_back(prm);
				}
				else
				{
					// �s���Ȍ`���̃p�����[�^
					break;
				}
			}
			vStatementList.push_back(statement);
		}	break;
		default:
			break;
		}
	}

	return(vStatementList);
}

// �g�[�N�����X�g�̎w�肵���ʒu����p�����[�^�Ƃ��Ďg����P�ʂłP�擾����
Parameter	Parse::makeParameter(Parse::tTokenList &vTokList, Parse::tTokenList::size_type &top)
{
	Parameter	param;

	if (top >= vTokList.size()) return(param);
	Token & tok = vTokList[top];

	switch (tok.type)
	{
	case Token::eCondition:
		// ��r������������R���f�B�V�����Ŋm��
		param.type = Parameter::eptCondition;
		param.cond = Parameter::fromCondStr(tok.str);
		top++;
		break;
	case Token::eNumeric:
		// ���l��������C�~�f�B�G�C�g�m��
		param.type = Parameter::eptImmidiate;
		param.imm = std::stoul(tok.str);
		top++;
		break;
	case Token::eSymbol:
		// ���x���������烉�x���w��m��(�A�h���X�����K�v)
		param.type = Parameter::eptLabel;
		param.label = tok.str;
		top++;
		break;
	case Token::eRegister:
		if ((top + 1) < vTokList.size())
		{
			// ���X�g�̍Ō�łȂ��ꍇ�C�����`�F�b�N
			switch (vTokList[top+1].type)
			{
			case Token::eDereference:	// @
				// ���W�X�^�Ԑ�(�I�t�Z�b�g�Ȃǖ���)�m��
				param.type = Parameter::eptReg_Ofs_Imm;
				param.base = Parameter::fromRegName(tok.str);
				param.imm = 0;	// �I�t�Z�b�g0�̊ԐڎQ�ƂƂ��Ĉ���
				top += 2;
				break;
			case Token::eDisplacement:	// +
				// + reg/imm @ ��3��܂ŕK�v
				if (((top + 3) < vTokList.size()) && (vTokList[top + 3].type == Token::eDereference))
				{
					// ���X�g�̍Ō�łȂ���Ύc����`�F�b�N
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
				// ���X�g�Ȃ�΃��W�X�^���ڂɌ���
				param.type = Parameter::eptRegister;
				param.base = Parameter::fromRegName(tok.str);
				top++;
				break;
			}
		}
		else
		{
			// ���X�g�Ȃ�΃��W�X�^���ڂɌ���
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
	return (Parameter::isValidRegName(token));
}

// ���ߖ��Ƃ��ēo�^�����邩
bool Parse::isMnemonic(std::string &token)
{
//	return (mmOpe.count(token) > 0);
	return (Encoder::isMnemonic(token));
}

// ���l������
bool Parse::isNumeric(std::string &token)
{
	// �����ȊO�̂��̂�������Ȃ������Ȃ琔�l������
	return (token.find_first_not_of("0123456789") == -1);
}

// ��r������
bool Parse::isCondition(std::string &token)
{
	return(mmCondition.count(token) > 0);
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

