#pragma once
#include <string>
//#include "../Mnemonic.h"
#include "../imp_Instruction.h"

class ope_malkrz : public imp_Instruction
{
private:
	enum ePrmType {
		eSource,
		eTarget,
		eParamCount
	};
	const std::string name = "malkrz";

	// 引数位置テーブル								0			1
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eSource,	eTarget };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget,	eSource };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("malkrz");
		bok |= !token.compare("malkRz");

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

		// フラグセット時にkrz処理
		if (proc.chkFlag()) {
			Ferlesexiayl::tRegister	work;
			bSuccess &= proc.Read(work, prm[eSource]);
			bSuccess &= proc.Write(prm[eTarget], work);
		}

		return(bSuccess);
	};
};

