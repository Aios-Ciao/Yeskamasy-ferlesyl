#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_inj : public Mnemonic
{
private:
	enum ePrmType {
		eSource,
		eDestSrc,
		eTarget,
		eParamCount
	};
	const std::string name = "inj";

	// �����ʒu�e�[�u��								0			1		2
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eSource,	eDestSrc, eTarget };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget,	eDestSrc, eSource };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("inj");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(eParamCount);
	}
	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// �͈͊O

		switch (d)
		{
		case Mnemonic::eci_C_I:
			return(tbl_prmidx_ci[idx]);
			break;
		case Mnemonic::eci_I_C:
		default:
			return(tbl_prmidx_ic[idx]);
			break;
		}
	}

	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		switch (idx)
		{
		case eSource:
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
		case eDestSrc:
		case eTarget:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				// ���W�X�^���������Ԑڂ̏ꍇ����OK
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
