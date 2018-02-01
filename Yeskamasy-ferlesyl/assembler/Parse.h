#pragma once
#include <fstream>
#include <string>
class Parse
{
	enum CharType {
		eBlank,		// \t \n \x20	�󔒌n����
		eWord,		// a-zFRXV'-_	�ʏ핶��
		ePlus,		// +			�L��
		eNum,		// 0-9			����
		eDerefer,	// @			�L��
		eComment,	// ;			�R�����g
		eUnknown	// �s��
	};
	unsigned char tblCharType[256];
	std::ifstream	ifs;
public:
	Parse(char *fname);
	~Parse();
	
	// ���[�_�[I/F
	size_t getToken(std::string &token);

	// �s���܂ŃX�L�b�v
	size_t	skipToBreak();
};