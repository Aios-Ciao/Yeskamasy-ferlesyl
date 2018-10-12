#pragma once
#include <string>
#include <vector>
//#include "Proc.h"
#include "Parameter.h"
//#include "Opecode.h"
//#include "Common.h"
#include "Instruction.h"

class Proc;
class Instruction;

class Mnemonic : public Instruction
{
public:
	enum eCI {
		eci_I_C,		// 'i'c ope src destの順	(デフォルト)
		eci_C_I			// 'c'i ope dest srcの順
	};
	using tParamDir = eCI;
	using tParamCount = uint16_t;
public:
	// ニーモニックを処理できるならtrue
	virtual bool chkApplicable(std::string &token) { return false; };

	// ニーモニック文字列の取得
	virtual std::string getName() { return ""; };

	// 命令の実行
	virtual bool Execute(Proc &proc, Parameter::tParamList &prm, tParamDir d) { return false; };

	// バイトコードへの変換
//	virtual bool Encode(Parameter::tParamList &prm, Opecode::tCodeBytes &bytes) { return false; };

	// バイトコードのデータ長
//	virtual Opecode::tCodeLength CodeSize(Parameter::tParamList &prm, Opecode::tCodeBytes &bytes) { return 0; };

	// パラメータ数取得
	virtual tParamCount getParamCount() { return 0; };

	// 'c'i/'i'c指定によるパラメータの並びのマップ解決
	virtual tParamCount	getParamIndex(tParamCount idx, tParamDir d = eci_I_C) { return 0; };

	// 指定番目のパラメータタイプチェック(パラメータの並びは'i'c：0がsrc、1がdest)
	virtual bool chkParamType(tParamCount idx, Parameter::ParamType type) { return false; };
};
