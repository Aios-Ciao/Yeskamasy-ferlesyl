#pragma once
#include <string>
//#include "../Mnemonic.h"
#include "../imp_Instruction.h"

class ope_dro : public imp_Instruction
{
private:
	enum ePrmType {
		eTarget,
		eAmount,
		eParamCount
	};
	const std::string name = "dro";

	// 引数位置テーブル								0			1
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eAmount,	eTarget };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget,	eAmount };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("dro");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(eParamCount);
	}

	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// 範囲外

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
		case eAmount:
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
		case eTarget:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				// レジスタかメモリ間接の場合だけOK
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

	// 命令の実行
	bool Execute(Proc &proc, Parameter::tParamList &prm, tParamDir d)
	{
		bool bSuccess(true);
		Ferlesexiayl::tRegister value, amount;

		bSuccess &= proc.Read(value, prm[eTarget]);
		bSuccess &= proc.Read(amount, prm[eAmount]);

		value = (amount >= 32) ? 0 : value << amount;

		bSuccess = proc.Write(prm[eTarget], value);

		return(bSuccess);
	};
};

