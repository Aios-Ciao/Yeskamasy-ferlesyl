#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fen : public Mnemonic
{
	const std::string	name = "fen";

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("fen");

		return(bok);
	};

	std::string getName()
	{
		return (name);
	}
};

