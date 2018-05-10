#pragma once
#include <string>
#include <vector>
#include "Mnemonic.h"

// エンコーダー
class Mnemonics
{
private:
	using tMnemonics = std::vector<Mnemonic*>;
	static tMnemonics vMnemonics;
public:
	Mnemonics();
	~Mnemonics();
	static bool isMnemonic(std::string &token);
	static Mnemonic *getMnemonic(std::string &ope);
};
