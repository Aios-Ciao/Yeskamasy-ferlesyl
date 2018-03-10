#pragma once
//#include <vector>
#include <string>
#include <list>
#include <map>
#include "Common.h"

/// ラベル管理
class Symbol
{
public:
	using tSymbolName = std::string;
	using tSymbolList = std::list<Symbol::tSymbolName>;



private:
//	tSymbolMap		mSymbols;			// モジュール内定義シンボル
public:
	//// ラベルの登録
	//bool regSymbol(std::string &name, stLabelInfo &info)
	//{
	//	bool bExisted(true);

	//	if (!chkExistSymbol(name)) {

	//		mSymbols[name] = info;
	//		bExisted = false;
	//	}

	//	return(bExisted);
	//};

	//// シンボルが存在するか
	//bool chkExistSymbol(std::string &name)
	//{
	//	return(mSymbols.count(name) > 0);
	//};

	//// シンボルのkue
	//bool kueSymbol(std::string &name)
	//{
	//	bool bSuccessed(false);

	//	if (chkExistSymbol(name)) {
	//		mSymbols[name].isExported = true;
	//		bSuccessed = true;
	//	}

	//	return(bSuccessed);
	//}

	//// シンボルがkue済みか
	//bool chkKueSymbol(std::string &name)
	//{
	//	bool bKue(false);

	//	if (chkExistSymbol(name)) {
	//		bKue = mSymbols[name].isExported;
	//	}

	//	return(bKue);
	//}
};

