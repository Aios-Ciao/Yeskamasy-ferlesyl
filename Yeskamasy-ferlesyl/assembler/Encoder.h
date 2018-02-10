#pragma once
#include <string>
#include <vector>
#include "Mnemonic.h"

// エンコーダー
class Encoder
{
private:
	static std::vector<Mnemonic*>	vMnemonics;
public:
	Encoder();
	~Encoder();
	static bool isMnemonic(std::string &token);

};
