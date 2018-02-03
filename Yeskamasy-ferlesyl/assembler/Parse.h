#pragma once
#include <fstream>
#include <string>
class Parse
{
private:
	enum CharType {
		eBlank,		// \t \x20		�󔒌n����
		eWord,		// a-zFRXV'-_	�ʏ핶��
		ePlus,		// +			�L��
		eNum,		// 0-9			����
		eDerefer,	// @			�L��
		eComment,	// ;			�R�����g
		eBreak,		// \r \n		���s�n����
		eUnknown	// �s��
	};
	static unsigned char tblCharType[256];
	std::ifstream	ifs;

public:
	struct PosInfo {
		unsigned long nRow;			// �s�ԍ�
		unsigned long nColumn;		// ���ԍ�
		PosInfo(unsigned long row = 0, unsigned long col = 0) : nRow(row), nColumn(col) { };
		// ����̓f�t�H���g�̃R�s�[�R���X�g���N�^�ɔC����
	};

public:
	Parse(char *fname);
	~Parse();
	
	// ���[�_�[I/F
	bool getToken(std::string &token, PosInfo &tokenpos, PosInfo &nexttoken);
};