#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_ata : public Mnemonic
{
private:
	enum {
		eSource,
		eTarget,
		eParamCount
	};
	const std::string name = "ata";

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("ata");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(ope_ata::eParamCount);
	}

	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		switch (idx)
		{
		case ope_ata::eSource:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptImmidiate:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
			case Parameter::ParamType::eptLabel:
				isOK = true;
				break;
			default:
				break;
			}
			break;
		case ope_ata::eTarget:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				// ƒŒƒWƒXƒ^‚©ƒƒ‚ƒŠŠÔÚ‚Ìê‡‚¾‚¯OK
				isOK = true;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		return(isOK);
	}

	std::string getName()
	{
		return (name);
	}

};

