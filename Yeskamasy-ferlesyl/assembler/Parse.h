#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Statement.h"
#include "Module.h"

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

public:

	struct PosInfo {
		unsigned long nRow;			// �s�ԍ�
		unsigned long nColumn;		// ���ԍ�
		PosInfo(unsigned long row = 0, unsigned long col = 0) : nRow(row), nColumn(col) { };
		// ����̓f�t�H���g�̃R�s�[�R���X�g���N�^�ɔC����

		// �g�[�N���̍s�A��ʒu�������������Ԃ� �uline(col)�v�̌`
		std::string toString() {
			return(std::to_string(nRow + 1) + "(" + std::to_string(nColumn + 1) + ")");
		}
	};

	struct Token {
		enum TokenType {
			eRegister,		// f0�`f7
			eMnemonic,		// ���ߖ�
			eNumeric,		// ���l
			eSymbol,		// ���x�����
			eDereference,	// @
			eDisplacement,	// +
			eProcOption,	// 'c'i��nll�Ƃ��������Ɋւ�鏈��
			eCondition,		// fi���ߗp�̔��f����
			eUnknown		// �s���Ȃ���
		};
		std::string	str;		// ������
		TokenType	type;		// ���
		PosInfo		pos;		// ���\�[�X�ł̈ʒu���

		Token() :str(""), type(TokenType::eUnknown), pos() {};
		Token(std::string &token, PosInfo &_pos, TokenType _type = TokenType::eUnknown)
			: str(token), pos(_pos), type(_type) {};
		bool chkKeyword(const char *ref) { return(!str.compare(ref)); };
	};

public:
	using tTokenList = std::vector<Token>;
	using tTokenIdx = tTokenList::size_type;

	using tLabelName = std::string;

	struct stLabelInfo {
		Statement::tStatementIndex	target;			// �T����_�X�e�[�g�����g�ԍ�
		enum SerchDir {
			esForward,
			esReverse
		}							dir;			// �T������
		bool						isExported;		// kue�ς݂�

		tTokenIdx		tokenidx;	/// ���x����`���߂̃g�[�N���ԍ�
		stLabelInfo(Statement::tStatementIndex baseidx = 0)
			:isExported(false), target(baseidx), dir(stLabelInfo::esForward) {};
		~stLabelInfo() {};
	};

	using tLabelMap = std::map<tLabelName, stLabelInfo>;

private:
	Parameter	makeParameter(Parse::tTokenList &list, Parse::tTokenList::size_type &top);

public:
	bool isProcOption(std::string &token);
	bool isRegister(std::string &token);
	bool isMnemonic(std::string &token);
	bool isNumeric(std::string &token);
	bool isCondition(std::string &token);
	bool isValidSymbol(std::string &token);

public:
	Parse();
	~Parse();

	tTokenList makeTokenList(std::string &);
	Statement::tStatementList makeStatementList(tTokenList &vTokenList, Module &mod);
private:
	// ���[�_�[I/F
	bool getToken(std::ifstream &ifs, std::string &token, PosInfo &tokenpos, PosInfo &nexttoken);
	Token Tokenize(std::string &token, PosInfo &tokenpos);
};
