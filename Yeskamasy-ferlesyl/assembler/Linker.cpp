#include "Common.h"
#include "Linker.h"
#include <map>
#include <iostream>
#include <fstream>

using tKueSymbol = struct KuedSymbol{
	lk::tModuleID id;
	Statement::tStatementIndex idx;
	
	KuedSymbol() :id(0), idx(0) {};
	KuedSymbol(lk::tModuleID _id, Statement::tStatementIndex _idx)
		: id(_id), idx(_idx) {};
};
using mKueSymbols = std::map<std::string, tKueSymbol>;

/// リンク処理
bool Linker::Link(Module::tModuleList vModules)
{
	mKueSymbols symbols_kue;

	// 各モジュールでkueされたシンボルのかき集め処理
	for (Module::tModuleList::iterator mod = vModules.begin(); mod != vModules.end(); ++mod) {
		Symbol::tSymbolAry &syms = mod->vSymbols;

		for (Symbol::tSymbolAry::iterator sym = syms.begin(); sym != syms.end(); ++sym) {
			if (sym->celesol_kue) {
				tKueSymbol	symbol_pos(sym->modid, sym->idx);
				symbols_kue[sym->name] = symbol_pos;
			}
		}
	}

	// 各モジュールがxokするシンボルへの当てはめ
	for (Module::tModuleList::iterator mod = vModules.begin(); mod != vModules.end(); ++mod) {
		Symbol::tSymbolAry &syms = mod->vSymbols;

		for (Symbol::tSymbolAry::iterator sym = syms.begin(); sym != syms.end(); ++sym) {
			if (sym->req_xok) {
				if (symbols_kue.count(sym->name)) {
					sym->modid = symbols_kue[sym->name].id;
					sym->idx = symbols_kue[sym->name].idx;
				}
				else {
					// xokしたいシンボルが見つからなかった
					std::cerr << "リンクエラー: xok対象のラベルが未定義です ";
					std::cerr << "参照元：" << mod->getFilename() << " シンボル：" << sym->name << std::endl;
				}
				// 要求消化
				sym->req_xok = false;
				sym->celesol_xok = true;
			}
		}
	}

	return(true);
}

