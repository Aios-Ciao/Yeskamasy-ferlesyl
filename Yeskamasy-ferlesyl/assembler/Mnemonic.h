#pragma once
#include <string>

class Mnemonic
{
public:
	virtual bool chkApplicable(std::string &token) = 0;		// ニーモニックを処理できるならtrue
	virtual std::string getName() = 0;	// ニーモニック文字列の取得
};
