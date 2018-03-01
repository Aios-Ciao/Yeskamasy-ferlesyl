#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "Statement.h"

class Parse
{
private:
	enum CharType {
		eBlank,		// \t \x20		空白系文字
		eWord,		// a-zFRXV'-_	通常文字
		ePlus,		// +			記号
		eNum,		// 0-9			数字
		eDerefer,	// @			記号
		eComment,	// ;			コメント
		eBreak,		// \r \n		改行系文字
		eInvalid	// 不明
	};
	static unsigned char tblCharType[256];
	std::ifstream	ifs;

public:

	struct PosInfo {
		unsigned long nRow;			// 行番号
		unsigned long nColumn;		// 桁番号
		PosInfo(unsigned long row = 0, unsigned long col = 0) : nRow(row), nColumn(col) { };
		// 代入はデフォルトのコピーコンストラクタに任せる
	};

	struct Token {
		enum TokenType {
			eRegister,		// f0～f7
			eMnemonic,		// 命令名
			eNumeric,		// 数値
			eSymbol,		// ラベル候補
			eDereference,	// @
			eDisplacement,	// +
			eProcOption,	// 'c'iやnllといった大域に関わる処理
			eCondition,		// fi命令用の判断条件
			eUnknown		// 不明なもの
		};
		std::string	str;		// 文字列
		TokenType	type;		// 種別
		PosInfo		pos;		// 元ソースでの位置情報

		Token() :str(""), type(TokenType::eUnknown), pos() {};
		Token(std::string &token, PosInfo &_pos, TokenType _type = TokenType::eUnknown)
			: str(token), pos(_pos), type(_type) {};
	};


public:
	bool isProcOption(std::string &token);
	bool isRegister(std::string &token);
	bool isMnemonic(std::string &token);
	bool isNumeric(std::string &token);
	bool isCondition(std::string &token);
	bool isValidSymbol(std::string &token);

public:
	using tTokenList = std::vector<Token>;
	using tStatementList = std::vector<Statement>;
public:
	Parse(char *fname);
	~Parse();

	tTokenList makeTokenList();
	tStatementList makeStatementList(tTokenList &vTokenList);
private:
	// リーダーI/F
	bool getToken(std::string &token, PosInfo &tokenpos, PosInfo &nexttoken);
	Token Tokenize(std::string &token, PosInfo &tokenpos);
};
