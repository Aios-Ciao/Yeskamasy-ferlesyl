#pragma once
#include <fstream>
#include <string>
#include <vector>
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
		eInvalid	// �s��
	};
	static unsigned char tblCharType[256];
	std::ifstream	ifs;

public:
	enum TokenType {
		eRegister,		// f0�`f7
		eMnemonic,		// ���ߖ�
		eNumeric,		// ���l
		eSymbol,		// ���x�����
		eDereference,	// @
		eDisplacement,	// +
		eProcOption,	// 'c'i��nll�Ƃ��������Ɋւ�鏈��
		eUnknown		// �s���Ȃ���
	};
	struct PosInfo {
		unsigned long nRow;			// �s�ԍ�
		unsigned long nColumn;		// ���ԍ�
		PosInfo(unsigned long row = 0, unsigned long col = 0) : nRow(row), nColumn(col) { };
		// ����̓f�t�H���g�̃R�s�[�R���X�g���N�^�ɔC����
	};

	struct Token {
		std::string	str;		// ������
		TokenType	type;		// ���
		PosInfo		pos;		// ���\�[�X�ł̈ʒu���

		Token() :str(""), type(TokenType::eUnknown), pos() {};
		Token(std::string &token, PosInfo &_pos, TokenType _type = TokenType::eUnknown)
			: str(token), pos(_pos), type(_type) {};
	};
public:
	bool isProcOption(std::string &token);
	bool isRegister(std::string &token);
	bool isMnemonic(std::string &token);
	bool isNumeric(std::string &token);
	bool isValidSymbol(std::string &token);

public:
	Parse(char *fname);
	~Parse();

	std::vector<Token> makeTokenList();
private:
	// ���[�_�[I/F
	bool getToken(std::string &token, PosInfo &tokenpos, PosInfo &nexttoken);
	Token Tokenize(std::string &token, PosInfo &tokenpos);
};
