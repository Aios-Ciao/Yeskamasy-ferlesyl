#pragma once
#include <string>
#include "../Proc.h"
//#include "../Mnemonic.h"
//#include "../Opecode.h"
#include "../imp_Instruction.h"

class ope_fen : public imp_Instruction
{
private:
	enum ePrmType {
		eParamCount
	};
	const std::string	name = "fen";

	// 引数位置テーブルは無し

public:
	bool chkApplicable(std::string &token)
	{
		bool bok(false);

		bok |= !token.compare("fen");

		return(bok);
	};
	tParamCount getParamCount()
	{
		return(ope_fen::eParamCount);
	}
	tParamCount	getParamIndex(tParamCount idx, tParamDir d)
	{
		if (idx >= eParamCount) return(-1);	// 範囲外

		return(0);
	}
	bool chkParamType(tParamCount idx, Parameter::ParamType type)
	{
		bool isOK(false);

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

		return(bSuccess);
	};

	bool Encode(Parameter::tParamList &prm, Opecode::tCodeBytes &bytes) { return false; };
};

