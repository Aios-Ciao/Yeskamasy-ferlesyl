#pragma once
#include <vector>
#include <string>
#include <list>
#include "Common.h"
#include "Statement.h"

/// ラベル管理
class Symbol
{
public:
	using tSymbolName = std::string;
	using tSymbolList = std::list<Symbol::tSymbolName>;
	using tSymbolAry = std::vector<Symbol>;

	tSymbolName					name;			/// シンボル名
	bool						celesol_kue;	/// kueされたシンボル
	bool						celesol_xok;	/// xokで追加されたシンボル
	bool						req_xok;		/// xokを要求するシンボル
	lk::tModuleID				modid;			/// モジュールID
	Statement::tStatementIndex	idx;			/// モジュール内ステートメントIndex
//	lk::tAddressHalf			addr;			/// モジュール内アドレス(キャッシュ的な位置づけ)

	// コンストラクタ
	// 最低限シンボルテキストは引数に必要
	Symbol(tSymbolName _name, bool c_kue = false, bool r_xok = false, bool c_xok = false, lk::tModuleID mid = 0, Statement::tStatementIndex sidx = 0)
		: name(_name), celesol_kue(c_kue), celesol_xok(c_xok), req_xok(r_xok), modid(mid), idx(sidx)
	{

	};

};

