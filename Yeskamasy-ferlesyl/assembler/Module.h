#pragma once
#include <string>
#include <map>
#include <vector>
#include "Common.h"
#include "Statement.h"
#include "Symbol.h"

// アセンブルするモジュールの管理
class Module
{
public:
						
	/// パラメータが解決を要求するラベルの位置情報
	struct stLabelRef {
		Parameter	*target;	// あとで書き替えるべきパラメータへのポインタ
		Symbol		*symbol;	// 
	};

private:
	static lk::tModuleID	id_base;			// 数え上げ用
	lk::tModuleID			id;
	lk::tModuleName			filename;
	lk::tAddressHalf		loadaddress;		// モジュールの基点アドレス(上位16bit)

	Statement::tStatementList	vStatements;	// ステートメント群

public:
	using tModuleList = std::vector<Module*>;

public:
	Module(std::string &name);
	~Module() {};

	lk::tModuleID	getID() { return(id); };
	std::string		getFilename() { return(filename); };
};

