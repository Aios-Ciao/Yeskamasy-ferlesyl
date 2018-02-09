#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fen : public Mnemonic
{
public:
	std::string getMnemonicName() { return("fen"); };
	bool chkApplicable(std::string &token) { return(token == "fen"); };
};

