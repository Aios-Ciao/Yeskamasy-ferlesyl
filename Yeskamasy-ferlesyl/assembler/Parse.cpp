#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>
#include "Parse.h"
#include "Encoder.h"
#include "Statement.h"
#include "Module.h"

unsigned char Parse::tblCharType[256];

std::map<std::string, std::string>	mmPOC;	// Processor Option Command
std::map<std::string, std::string>	mmCondition;	// ��r����


// �R���X�g���N�^
Parse::Parse()
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

}

// �f�X�g���N�^
Parse::~Parse()
{
}

// �g�[�N���̃��X�g�𐶐�����
Parse::tTokenList Parse::makeTokenList(std::string &fname)
{
	std::string	word;
	Parse::PosInfo	curp, nextp;
	tTokenList vTokenList;
	std::ifstream	ifs(fname);

	// �J���Ă��Ȃ���Όx��
	if (ifs.fail()) {
		std::cerr << "�t�@�C�����J���܂���ł���(" << std::string(fname) << ")" << std::endl;
	}

	while (getToken(ifs, word, curp, nextp))
	{
		if (word != "\x20") {
			vTokenList.push_back(Tokenize(word, curp));
		}
	}
	ifs.close();

	return (vTokenList);
}

// �g�[�N�����X�g����X�e�[�g�����g���X�g�ւ̕ϊ�
Statement::tStatementList Parse::makeStatementList(Parse::tTokenList &vTokenList, Module &mod)
{

	Statement::tStatementList	&vStatementList = mod.vStatements;
	tTokenList::size_type	idx(0);
	Mnemonic::tParamDir		ecid(Mnemonic::tParamDir::eci_I_C);		// �����l��'i'c

	// �p�����[�^�w������̐ݒ�
	auto setCI = [&](std::string &k) {
		ecid = !k.compare("'c'i") ? Mnemonic::tParamDir::eci_C_I : Mnemonic::tParamDir::eci_I_C;
	};

	tLabelMap	msymbol;		// nll�܂���l'�Œ�`�����V���{��
	Symbol::tSymbolList	kuereqlist;		// kue���ׂ��V���{�����X�g
	Symbol::tSymbolList xokreqlist;		// xok���ׂ��V���{�����X�g

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
				if ((idx + 1) <= vTokenList.size()) {
					Symbol::tSymbolName	symbol = vTokenList[idx + 1].str;
					kuereqlist.push_back(symbol);
					idx += 2;
				}
				else {
					std::cerr << "�\���G���[: ���x��������܂��� " << tok.pos.toString() << std::endl;
					break;
				}
			}
			else if (tok.chkKeyword("xok"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				if ((idx + 1) <= vTokenList.size()) {
					Symbol::tSymbolName	symbol = vTokenList[idx + 1].str;
					xokreqlist.push_back(symbol);
					idx += 2;
				}
				else {
					std::cerr << "�\���G���[: ���x��������܂��� " << tok.pos.toString() << std::endl;
					break;
				}
			}
			else if (tok.chkKeyword("nll"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				if (idx + 1 <= vTokenList.size()) {
					tLabelName	symbol = vTokenList[idx + 1].str;

					// ���o�^�Ȃ�
					if (msymbol.count(symbol) > 0) {
						// ���x�����d����`
						std::cerr << "�f�[�^�G���[�F���x�������d��`����܂�:" << symbol << " " << tok.pos.toString() << std::endl;
						break;
					}
					else {
						stLabelInfo	si;

						si.target = vStatementList.size();			// ���݂̃X�e�[�g�����g�ʒu
						si.dir = stLabelInfo::esForward;			// ���̕��֒T��
						si.isExported = false;						// �����J
						si.tokenidx = idx;

						msymbol[symbol] = si;
					}
					idx += 2;
				}
				else {
					// nll �����ŏI�����
					std::cerr << "�\���G���[: ���x��������܂��� " << tok.pos.toString() << std::endl;
				}
			}
			else if (tok.chkKeyword("l'"))
			{
				// �p�����[�^�P�Ƃ��ă��x������
				if (idx + 1 <= vTokenList.size()) {
					tLabelName	symbol = vTokenList[idx + 1].str;

					// ���o�^�Ȃ�
					if (msymbol.count(symbol) == 0) {
						stLabelInfo	si;

						si.target = vStatementList.size();			// ���݂̃X�e�[�g�����g�ʒu
						si.dir = stLabelInfo::esReverse;			// �O�̕��֒T��
						si.isExported = false;						// �����J
						si.tokenidx = idx;

						msymbol[symbol] = si;
					}
					else {
						// ���x�����d����`
						std::cerr << "�f�[�^�G���[�F���x�������d��`����܂�:" << symbol << " " << tok.pos.toString() << std::endl;
					}
					idx += 2;
				}
				else {
					// l' �����ŏI�����
					std::cerr << "�\���G���[: ���x��������܂��� " << tok.pos.toString() << std::endl;
				}
			}
			else
			{
				// �s���ȃI�v�V����
				std::cerr << "�\���G���[: �s���ȃg�[�N���ł� " << tok.str << " " << tok.pos.toString() << std::endl;
			}
			break;
		case Token::eMnemonic: {
			// �j�[���j�b�N
			Mnemonic	*mne = Encoder::getMnemonic(tok.str);
			Mnemonic::tParamCount	count = mne->getParamCount();
			Statement	statement;
			bool bError(false);
			bool bLabelReference(false);

			Statement::tParamMap	params;

			idx++;	// ������p�����[�^
					// �K�v�Ȑ������p�����[�^���W�߂�
			for (Mnemonic::tParamCount cnt = 0; cnt < count; ++cnt)
			{
				Statement::tStatementIndex base = idx;		// �p�����[�^��
				Parameter	prm = makeParameter(vTokenList, idx);
				Mnemonic::tParamCount	pidx = mne->getParamIndex(cnt, ecid);

				if (mne->chkParamType(pidx, prm.type))
				{
					// �K�؂ȃp�����[�^
					params[pidx] = prm;

					// �p�����[�^�����x���Ȃ�΃X�e�[�g�����gIdx���T����
					if (prm.type == prm.eptLabel) {
						bLabelReference = true;
					}
				}
				else
				{
					bError = true;
					// �s���Ȍ`���̃p�����[�^
					{
						std::cerr << "�\���G���[: �s���ȃg�[�N���ł� ";
						std::cerr << vTokenList[base].str << " " << vTokenList[base].pos.toString() << std::endl;
					}
					break;
				}
			}

			// ���x���̏ꍇ�A���Ƃ̃����N�̂��߃X�e�[�g�����g�̃C���f�b�N�X���T����
			if (bLabelReference) {
				mod.vLabelRefStateIdx.push_back(idx);
			}

			// �G���[���Ȃ����'i'c���Ƀp�����[�^�𐮂��ăX�e�[�g�����g�ɃZ�b�g
			if (!bError)
			{
				statement.eci = ecid;
				statement.mnemonic = mne;

				// �eMnemonic�Œ�`�����ePrmType�̏��ɐς݂Ȃ���
				for (Mnemonic::tParamCount cnt = 0; cnt < count; ++cnt)
				{
					statement.param.push_back(params[cnt]);
				}

				vStatementList.push_back(statement);
			}
		}	break;
		default:
			// �s���ȃI�v�V����
			std::cerr << "�\���G���[: �s���ȃg�[�N���ł� " << tok.str << " " << tok.pos.toString() << std::endl;
			break;
		}
	}
	
	// ���x���̃X�e�[�g�����g����t��
	for (tLabelMap::iterator it = msymbol.begin(); it != msymbol.end(); ++it)
	{
		stLabelInfo si = it->second;

		if (si.dir == si.esForward) {	// nll
			// ����������΃��x����`�G���[
			if (vStatementList.size() <= si.target) {
				std::cerr << "�\���G���[: �s���Ȉʒu�ł� ";
				std::cerr << vTokenList[si.tokenidx].pos.toString() << std::endl;
			}
			else {
				// ���탉�x����`
			}
		}
		else {	// l'
			// �O��������΃��x����`�G���[
			if (si.target == 0) {
				std::cerr << "�\���G���[: �s���Ȉʒu�ł� ";
				std::cerr << vTokenList[si.tokenidx].pos.toString() << std::endl;
			}
			else {
				// ���탉�x����`
				it->second.target--;		// ������肾���ǂЂƂO�̃X�e�[�g�����g���w������
			}
		}
	}

	// kue�v�����X�g�̏���
	for (Symbol::tSymbolList::iterator it = kuereqlist.begin(); it != kuereqlist.end(); ++it)
	{
		if (msymbol.count(*it) > 0) {
			msymbol[*it].isExported = true;
		}
		else {
			// ����`�V���{����kue�v��
			std::cerr << "�f�[�^�G���[: �Ώۂ̃��x��������`�ł� ";
			std::cerr << *it << std::endl;
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
bool Parse::getToken(std::ifstream &ifs, std::string &token, Parse::PosInfo &tokenpos, Parse::PosInfo &nexttoken)
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

