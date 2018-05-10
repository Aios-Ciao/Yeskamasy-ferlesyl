#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fen : public Mnemonic
{
private:
	enum ePrmType {
		eParamCount
	};
	const std::string	name = "fen";

	// 引数位置テーブルは無し

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
	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// 範囲外

		return(0);
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

