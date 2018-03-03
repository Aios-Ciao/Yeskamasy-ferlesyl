#pragma once
#include <string>
#include <vector>
#include "Mnemonic.h"

// エンコーダー
class Encoder
{
private:
	using tMnemonics = std::vector<Mnemonic*>;
	static tMnemonics vMnemonics;
public:
	Encoder();
	~Encoder();
	static bool isMnemonic(std::string &token);
	static Mnemonic *getMnemonic(std::string &ope);
};
