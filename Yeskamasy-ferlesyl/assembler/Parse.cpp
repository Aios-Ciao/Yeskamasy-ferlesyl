#include <cstdio>
#include <iostream>
#include <fstream>
#include "Parse.h"

// �R���X�g���N�^
Parse::Parse(char *fname)
	: ifs( fname)
{
	// �����^�C�v�}�b�v������
	{
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
		tblCharType['\r'] = Parse::eBlank;
		tblCharType['\n'] = Parse::eBlank;
		tblCharType['\x20'] = Parse::eBlank;
		tblCharType['\t'] = Parse::eBlank;

		// �L��
		tblCharType['+'] = Parse::ePlus;
		tblCharType['@'] = Parse::eDerefer;

		// �R�����g�L��
		tblCharType[';'] = Parse::eComment;
	}
	// �J���Ă��Ȃ���ΏI��
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
size_t Parse::getToken(std::string &token)
{
	size_t pos(0);
	char	chr;
	bool next(true);
	unsigned char context;
	unsigned char type;

	token = "";

	chr = ifs.get();
	context = tblCharType[chr];
	ifs.unget();

	while (next && ifs.get(chr))
	{
		type = tblCharType[chr];
		switch (context) {
		case Parse::eBlank:
			if (type != context) {
				ifs.unget();
				token = "\x20";
				next = false;
			}
			break;
		case Parse::eNum:
			if (type != context) {
				ifs.unget();
				next = false;
			}
			else {
				token += chr;
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
		case Parse::eDerefer:
		case Parse::ePlus:
		case Parse::eComment:
			token = chr;
			next = false;
			break;
		default:
			break;
		}
		pos++;
	}

	return pos;
}

// �s���܂œǂݔ�΂�
size_t Parse::skipToBreak()
{
	size_t pos(0);
	char	chr;
	bool next(true);

	while (next && ifs.get(chr)) {

		switch (chr) {
		case '\r':
		case '\n':
			next = false;
			break;
		default:
			break;
		}
		pos++;
	}

	return pos;
}

