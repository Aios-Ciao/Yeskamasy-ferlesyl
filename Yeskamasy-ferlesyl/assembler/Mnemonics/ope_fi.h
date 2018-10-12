#pragma once
#pragma once
#include <string>
//#include "../Mnemonic.h"
#include "../imp_Instruction.h"

class ope_fi : public imp_Instruction
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
	};

	// 命令の実行
	bool Execute(Proc &proc, Parameter::tParamList &prm, tParamDir d)
	{
		bool bSuccess(true);
		bool result;
		Ferlesexiayl::tRegister	work_L, work_R;

		bSuccess &= proc.Read(work_L, prm[eLeftValue]);
		bSuccess &= proc.Read(work_R, prm[eRighttValue]);

		switch (prm[eCondition].cond) {
		case Parameter::ecn_clo:
			result = (work_L == work_R);
			proc.setFlag(result);
			break;

		case Parameter::ecn_niv:
			result = (work_L != work_R);
			proc.setFlag(result);
			break;

		case Parameter::ecn_xtlo:
			work_L += 0x80000000u;
			work_R += 0x80000000u;
			/* not break */
		case Parameter::ecn_xtlonys:
			result = (work_L <= work_R);
			proc.setFlag(result);
			break;

		case Parameter::ecn_xolo:
			work_L += 0x80000000u;
			work_R += 0x80000000u;
			/* not break */
		case Parameter::ecn_xolonys:
			result = (work_L >= work_R);
			proc.setFlag(result);
			break;

		case Parameter::ecn_xylo:
			work_L += 0x80000000u;
			work_R += 0x80000000u;
			/* not break */
		case Parameter::ecn_xylonys:
			result = (work_L < work_R);
			proc.setFlag(result);
			break;

		case Parameter::ecn_llo:
			work_L += 0x80000000u;
			work_R += 0x80000000u;
			/* not break */
		case Parameter::ecn_llonys:
			result = (work_L > work_R);
			proc.setFlag(result);
			break;
		default:
			bSuccess = false;
			break;
		}

		return(bSuccess);
	};

};

