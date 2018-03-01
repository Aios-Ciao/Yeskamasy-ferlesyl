#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Mnemonic
{
public:
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

	// 指定番目のパラメータタイプチェック(パラメータの並びは'i'c：0がsrc、1がdest)
	virtual bool chkParamType(tParamCount idx, Parameter::ParamType type) = 0;
};
