#pragma once
#include <vector>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	Mnemonic					*mnemonic;		// ニーモニック
	std::vector<Parameter>		param;			// ステートメントのパラメータ

public:
	Statement();
	~Statement();

	std::string ToString();
};

