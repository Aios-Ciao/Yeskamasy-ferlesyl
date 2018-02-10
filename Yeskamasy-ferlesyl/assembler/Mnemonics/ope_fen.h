#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fen : public Mnemonic
{
public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("fen");

		return(bok);
	};
};

