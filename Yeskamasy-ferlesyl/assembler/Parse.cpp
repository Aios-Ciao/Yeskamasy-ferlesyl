#include <cstdio>
#include <iostream>
#include <fstream>
#include "Parse.h"

unsigned char Parse::tblCharType[256];

// �R���X�g���N�^
Parse::Parse(char *fname)
	: ifs( fname )
{
	// �����^�C�v�}�b�v������
	{
		// �g�p�\�ȕ�����ȊO�͕s���Ƃ��ď�����
		for (int idx = 0; idx < 255; idx++) {
			tblCharType[idx] = Parse::eUnknown;
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

