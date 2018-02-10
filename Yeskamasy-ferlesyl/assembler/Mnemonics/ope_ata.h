#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_ata : public Mnemonic
{
public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("ata");

		return(bok);
	};
};
