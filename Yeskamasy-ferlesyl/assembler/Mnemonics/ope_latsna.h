#pragma once
#include <string>
//#include "../Mnemonic.h"
#include "../imp_Instruction.h"

class ope_latsna : public imp_Instruction
{
private:
	enum ePrmType {
		eMulti,
		eTarget_ResultL,
		eResultH,
		eParamCount
	};
	const std::string name = "latsna";

	// 引数位置テーブル								0			1				2
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eMulti,	eTarget_ResultL, eResultH };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget_ResultL,	eResultH, eMulti };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("latsna");

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
		case eMulti:
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
		case eResultH:
			switch (type)
			{
			case Parameter::ParamType::eptRegister:
			case Parameter::ParamType::eptReg_Ofs_Imm:
			case Parameter::ParamType::eptReg_Ofs_Reg:
				isOK = true;
				break;
			default:
				break;
			}
			break;

		case eTarget_ResultL:
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
		regtype wk_m, wk_n;

		bSuccess &= proc.Read(wk_m.reg_u, prm[eTarget_ResultL]);
		bSuccess &= proc.Read(wk_n.reg_u, prm[eMulti]);

		int64_t wk_l = (int64_t)wk_m.reg_s * (int64_t)wk_n.reg_s;
		Ferlesexiayl::tRegister result_h = uint32_t(wk_l >> 32);
		Ferlesexiayl::tRegister result_l = uint32_t(wk_l & 0xFFFFFFFFul);

		bSuccess &= proc.Write(prm[eResultH], result_h);
		bSuccess &= proc.Write(prm[eTarget_ResultL], result_l);

		return(bSuccess);
	};
};

