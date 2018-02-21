#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_ata : public Mnemonic
{
	const std::string name = "ata";

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("ata");

		return(bok);
	};

	std::string getName()
	{
		return (name);
	}

};

