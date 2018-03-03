#pragma once
#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_fi : public Mnemonic
{
private:
	enum ePrmType {
		eLeftValue,
		eRighttValue,
		eCondition,
		eParamCount
	};
	const std::string name = "fi";

	// 引数位置テーブル								0			1			2
	const ePrmType	tbl_prmidx[eParamCount] = { eLeftValue,	eRighttValue,eCondition };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("fi");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(eParamCount);
	}
	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// 範囲外

		// fiはパラメータ順は変わらない
		return(tbl_prmidx[idx]);
	}
	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		switch (idx)
		{
		case eLeftValue:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptImmidiate:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				isOK = true;
				break;
			default:
				break;
			}
			break;
		case eRighttValue:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptImmidiate:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				isOK = true;
				break;
			default:
				break;
			}
			break;
		case eCondition:
			if (type == Parameter::ParamType::eptCondition) {
				isOK = true;
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

