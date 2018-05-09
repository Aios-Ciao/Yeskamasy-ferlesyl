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
	using tModuleList = std::vector<Module>;
	using tStatementIdxList = std::vector<Statement::tStatementIndex>;

private:
	static lk::tModuleID	id_base;			// 数え上げ用
	lk::tModuleID			id;
	lk::tModuleName			filename;
	lk::tAddressHalf		loadaddress;		// モジュールの基点アドレス(上位16bit)

public:
	Statement::tStatementList	vStatements;	/// ステートメント群
	tStatementIdxList			vLabelRefStateIdx;	/// 解決すべきラベルをパラメータとしてもつステートメントのインデックスリスト
	Symbol::tSymbolAry			vSymbols;		/// モジュールで定義されるラベル一覧

public:
	Module(std::string &name);
	~Module() {};

	lk::tModuleID	getID() { return(id); };
	std::string		getFilename() { return(filename); };
};

