#pragma once
#include <vector>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	using tParamList = std::vector<Parameter>;
public:
	Mnemonic				*mnemonic;		// ニーモニック
	tParamList				param;			// ステートメントのパラメータ
	Mnemonic::tParamDir		eci;			// パラメータの格納順序
public:
	Statement();
	~Statement();

	void Execute();	// ステートメントの実行
	void Encode();	// 機械語コードへの変換

	std::string ToString();
};

