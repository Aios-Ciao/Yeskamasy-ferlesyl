#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Mnemonic
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
	virtual bool chkApplicable(std::string &token) = 0;

	// ニーモニック文字列の取得
	virtual std::string getName() = 0;

	// 命令の実行
//	virtual void Execute(std::vector<Parameter> &param) = 0;

	// バイトコードへの変換
//	virtual unsigned char Encode(std::vector<Parameter> &param) = 0;

	// パラメータ数取得
	virtual tParamCount getParamCount() = 0;

	// 'c'i/'i'c指定によるパラメータの並びのマップ解決
	virtual tParamCount	getParamIndex(tParamCount idx, tParamDir d = eci_I_C) = 0;

	// 指定番目のパラメータタイプチェック(パラメータの並びは'i'c：0がsrc、1がdest)
	virtual bool chkParamType(tParamCount idx, Parameter::ParamType type) = 0;
};
