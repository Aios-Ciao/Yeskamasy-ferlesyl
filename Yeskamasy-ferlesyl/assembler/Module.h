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
public:
	using tModuleID = uint8_t;				// モジュール番号
private:
	static tModuleID	id_base;			// 数え上げ用
	tModuleID			id;
	std::string			filename;
	lk::tAddressHalf	loadaddress;		// モジュールの基点アドレス(上位16bit)

	Parse::tStatementList	vStatements;	// ステートメント群
	Symbol					_Symbols;		// シンボル群

public:
	using tModuleList = std::vector<Module*>;

public:
	Module(std::string &name);
	~Module() {};

	tModuleID	getID() { return(id); };
	std::string		getFilename() { return(filename); };
};

