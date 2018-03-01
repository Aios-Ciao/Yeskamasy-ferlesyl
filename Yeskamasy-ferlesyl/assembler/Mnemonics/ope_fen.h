#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fen : public Mnemonic
{
private:
	enum {
		eParamCount
	};
	const std::string	name = "fen";

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("fen");

		return(bok);
	};
	tParamCount getParamCount()
	{
		return(ope_fen::eParamCount);
	}
	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		return(isOK);
	}
	std::string getName()
	{
		return (name);
	}
};

