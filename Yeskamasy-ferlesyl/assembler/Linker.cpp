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
bool Linker::Link(Module::tModuleList &vModules)
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

	// 各ステートメントのパラメータに対してアドレス(モジュールIDとステートメントインデックス)解決
	for (Module::tModuleList::iterator mod = vModules.begin(); mod != vModules.end(); ++mod) {
		Symbol::tSymbolAry &syms = mod->vSymbols;
		std::map<std::string, Symbol *> mSymbols;

		// 一旦モジュール内のシンボルをハッシュに変換する
		for (Symbol::tSymbolAry::iterator sym = syms.begin(); sym != syms.end(); ++sym) {
			mSymbols[sym->name] = &(*sym);
		}

		for (Statement::tStatementList::iterator statement = mod->vStatements.begin(); statement != mod->vStatements.end(); ++statement) {
			for (Parameter::tParamList::iterator param = statement->param.begin(); param != statement->param.end(); ++param) {
				// パラメータがラベルならばそのシンボルのアドレスをロードする
				if (param->type == Parameter::eptLabel) {
					if (mSymbols.count(param->label) > 0) {
						param->localaddr = lk::tAddressHalf(mSymbols[param->label]->idx);
						param->modid = mSymbols[param->label]->modid;
					}
					else {
						std::cerr << "シンボルが見つかりませんでした。" << param->label << std::endl;
						break;
					}
				}
			}
		}
	}

	return(true);
}

