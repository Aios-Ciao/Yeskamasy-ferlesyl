﻿#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_dtosna : public Mnemonic
{
private:
	enum ePrmType {
		eTarget,
		eAmount,
		eParamCount
	};
	const std::string name = "dtosna";

	// 引数位置テーブル								0			1
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eAmount,	eTarget };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget,	eAmount };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("dtosna");

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
		using regtype = union {
			Ferlesexiayl::tRegister	reg_u;
			int32_t	reg_s;
		};
		regtype wk_m;
		Ferlesexiayl::tRegister	amount;

		bSuccess &= proc.Read(wk_m.reg_u, prm[eTarget]);
		bSuccess &= proc.Read(amount, prm[eAmount]);

		int64_t wk_l = (int64_t)wk_m.reg_s;
		Ferlesexiayl::tRegister result = uint32_t(wk_l >> amount);

		bSuccess &= proc.Write(prm[eTarget], result);

		return(bSuccess);
	};
};

