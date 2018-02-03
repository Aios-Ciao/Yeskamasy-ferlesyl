#pragma once
#include <fstream>
#include <string>
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
		eUnknown	// 不明
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

public:
	Parse(char *fname);
	~Parse();
	
	// リーダーI/F
	bool getToken(std::string &token, PosInfo &tokenpos, PosInfo &nexttoken);
};