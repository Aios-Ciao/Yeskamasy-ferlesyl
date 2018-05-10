#pragma once
#include <vector>
#include <map>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	using tParamList = std::vector<Parameter>;
	using tParamMap = std::map<Mnemonic::tParamCount, Parameter>;
	using tStatementList = std::vector<Statement>;
	using tStatementIndex = tStatementList::size_type;
public:
	Mnemonic				*mnemonic;		// ニーモニック
	tParamList				param;			// ステートメントのパラメータ
	Mnemonic::tParamDir		eci;			// パラメータの格納順序
public:
	Statement();
	~Statement();

	std::string ToString();
};

