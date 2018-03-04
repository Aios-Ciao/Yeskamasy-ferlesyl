#pragma once
#include <string>
#include <map>
#include <vector>
#include "Common.h"
#include "Parse.h"
#include "Symbol.h"

// アセンブルするモジュールの管理
class Module
{

private:
	std::string			filename;
	lk::tAddressHalf	loadaddress;		// モジュールの基点アドレス(上位16bit)

	Parse::tStatementList	vStatements;	// ステートメント群
	Symbol					_Symbols;		// シンボル群

public:
	using tModuleList = std::vector<Module*>;

public:
	Module(std::string &name) :filename(name), loadaddress(0) {};
	~Module() {};

	std::string		getFilename() { return(filename); };
};

