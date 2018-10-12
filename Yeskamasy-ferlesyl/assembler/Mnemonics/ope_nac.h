#pragma once
#include <string>
//#include "../Mnemonic.h"
#include "../imp_Instruction.h"

class ope_nac : public imp_Instruction
{
private:
	enum ePrmType {
		eTarget,
		eParamCount
	};
	const std::string name = "nac";

	// 引数位置テーブル								0
	const ePrmType	tbl_prmidx[eParamCount] = { eTarget };

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("nac");

		return(bok);
	};

	tParamCount getParamCount()
	{
		return(eParamCount);
	}

	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// 範囲外

		return(tbl_prmidx[idx]);
	}

	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

		switch (idx)
		{
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
		Ferlesexiayl::tRegister work;

		bSuccess &= proc.Read(work, prm[eTarget]);
		work ^= 0xFFFFFFFFu;
		bSuccess = proc.Write(prm[eTarget], work);

		return(bSuccess);
	};
};

