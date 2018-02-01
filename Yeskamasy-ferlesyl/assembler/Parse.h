#pragma once
#include <fstream>
#include <string>
class Parse
{
	enum CharType {
		eBlank,		// \t \n \x20	空白系文字
		eWord,		// a-zFRXV'-_	通常文字
		ePlus,		// +			記号
		eNum,		// 0-9			数字
		eDerefer,	// @			記号
		eComment,	// ;			コメント
		eUnknown	// 不明
	};
	unsigned char tblCharType[256];
	std::ifstream	ifs;
public:
	Parse(char *fname);
	~Parse();
	
	// リーダーI/F
	size_t getToken(std::string &token);

	// 行末までスキップ
	size_t	skipToBreak();
};