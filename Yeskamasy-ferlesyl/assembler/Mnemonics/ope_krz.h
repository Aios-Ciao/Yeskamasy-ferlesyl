#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_krz : public Mnemonic
{
public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("krz");
		bok |= !token.compare("kRz");

		return(bok);
	};
};

