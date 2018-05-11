#pragma once
#include <string>
#include "../Mnemonic.h"

class ope_nta : public Mnemonic
{
private:
	enum ePrmType {
		eSource,
		eTarget,
		eParamCount
	};
	const std::string name = "nta";

	// 引数位置テーブル								0			1
	const ePrmType	tbl_prmidx_ic[eParamCount] = { eSource,	eTarget };
	const ePrmType	tbl_prmidx_ci[eParamCount] = { eTarget,	eSource };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("nta");

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
		bool bSuccess(false);

		bSuccess = true;

		return(bSuccess);
	};
};

