#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_krz : public Mnemonic
{
	const std::string name = "krz";
public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("krz");
		bok |= !token.compare("kRz");

		return(bok);
	};

	std::string getName()
	{
		return (name);
	}

};

