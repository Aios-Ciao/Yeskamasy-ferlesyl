#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_krz : public Mnemonic
{
private:
	enum {
		eSource,
		eTarget,
		eParamCount
	};
	const std::string name = "krz";
public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("krz");
		bok |= !token.compare("kRz");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(ope_krz::eParamCount);
	}

	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		switch (idx)
		{
		case ope_krz::eSource:
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
		case ope_krz::eTarget:
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

