#pragma once
#include <vector>
#include <map>
#include <string>
#include "Proc.h"
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	using tParamMap = std::map<Mnemonic::tParamCount, Parameter>;
	using tStatementList = std::vector<Statement>;
	using tStatementIndex = tStatementList::size_type;
public:
	Mnemonic				*mnemonic;		// ニーモニック
	Parameter::tParamList	param;			// ステートメントのパラメータ
	Mnemonic::tParamDir		eci;			// パラメータの格納順序
public:
	Statement();
	~Statement();
	bool operator()(Proc &);

	std::string ToString();
};

