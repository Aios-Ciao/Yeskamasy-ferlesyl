#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_inj : public Mnemonic
{
	const std::string name = "inj";

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("inj");

		return(bok);
	};

	std::string getName()
	{
		return (name);
	}

};
