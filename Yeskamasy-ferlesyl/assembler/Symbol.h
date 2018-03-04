#pragma once
#include <vector>
#include <string>
#include <map>
#include "Common.h"
#include "Module.h"

/// ���x���Ǘ�
class Symbol
{
public:
	struct stSymbolInfo {
		bool				isExported;		// kue�ς݂�
		lk::tAddressHalf	address;		// ���W���[�����A�h���X

		stSymbolInfo(lk::tAddressHalf addr = 0) :isExported(false), address(addr) {};
		~stSymbolInfo() {};
	};

	using tSymbolMap = std::map<std::string, stSymbolInfo>;
	tSymbolMap		mSymbols;			// �V���{���Ƃ��̃A�h���X���

public:
	// ���x���̓o�^
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

	// �V���{�������݂��邩
	bool chkExistSymbol(std::string &name) { return(mSymbols.count(name) > 0); };

	// �V���{����kue
	bool kueSymbol(std::string &name)
	{
		bool bSuccessed(false);

		if (chkExistSymbol(name)) {
			mSymbols[name].isExported = true;
			bSuccessed = true;
		}

		return(bSuccessed);
	}

	// �V���{����kue�ς݂�
	bool chkKueSymbol(std::string &name)
	{
		bool bKue(false);

		if (chkExistSymbol(name)) {
			bKue = mSymbols[name].isExported;
		}

		return(bKue);
	}

	// �V���{���̃A�h���X�擾
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

