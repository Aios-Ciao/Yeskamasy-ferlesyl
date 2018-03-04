#pragma once
#include <vector>
#include <string>
#include <map>
#include "Common.h"
#include "Module.h"

/// ラベル管理
class Symbol
{
public:
	struct stSymbolInfo {
		bool				isExported;		// kue済みか
		lk::tAddressHalf	address;		// モジュール内アドレス

		stSymbolInfo(lk::tAddressHalf addr = 0) :isExported(false), address(addr) {};
		~stSymbolInfo() {};
	};

	using tSymbolMap = std::map<std::string, stSymbolInfo>;
	tSymbolMap		mSymbols;			// シンボルとそのアドレス情報

public:
	// ラベルの登録
	bool regSymbol(std::string &name, lk::tAddressHalf addr)
	{
		bool bExisted(true);
		stSymbolInfo	symbol(addr);

		if (!chkExistSymbol(name)) {

			mSymbols[name] = symbol;
			bExisted = false;
		}

		return(bExisted);
	};

	// シンボルが存在するか
	bool chkExistSymbol(std::string &name) { return(mSymbols.count(name) > 0); };

	// シンボルのkue
	bool kueSymbol(std::string &name)
	{
		bool bSuccessed(false);

		if (chkExistSymbol(name)) {
			mSymbols[name].isExported = true;
			bSuccessed = true;
		}

		return(bSuccessed);
	}

	// シンボルがkue済みか
	bool chkKueSymbol(std::string &name)
	{
		bool bKue(false);

		if (chkExistSymbol(name)) {
			bKue = mSymbols[name].isExported;
		}

		return(bKue);
	}

	// シンボルのアドレス取得
	lk::tAddressFull	getAddress(std::string &name)
	{
		lk::tAddressFull	addr(0);

		if (chkExistSymbol(name)) {
			if (mSymbols[name].isExported) {
				addr = mSymbols[name].address;
			}
		}

		return(addr);
	}

};

