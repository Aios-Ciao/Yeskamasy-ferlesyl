#pragma once
//#include <vector>
#include <string>
#include <list>
#include <map>
#include "Common.h"

/// ���x���Ǘ�
class Symbol
{
public:
	using tSymbolName = std::string;
	using tSymbolList = std::list<Symbol::tSymbolName>;



private:
//	tSymbolMap		mSymbols;			// ���W���[������`�V���{��
public:
	//// ���x���̓o�^
	//bool regSymbol(std::string &name, stLabelInfo &info)
	//{
	//	bool bExisted(true);

	//	if (!chkExistSymbol(name)) {

	//		mSymbols[name] = info;
	//		bExisted = false;
	//	}

	//	return(bExisted);
	//};

	//// �V���{�������݂��邩
	//bool chkExistSymbol(std::string &name)
	//{
	//	return(mSymbols.count(name) > 0);
	//};

	//// �V���{����kue
	//bool kueSymbol(std::string &name)
	//{
	//	bool bSuccessed(false);

	//	if (chkExistSymbol(name)) {
	//		mSymbols[name].isExported = true;
	//		bSuccessed = true;
	//	}

	//	return(bSuccessed);
	//}

	//// �V���{����kue�ς݂�
	//bool chkKueSymbol(std::string &name)
	//{
	//	bool bKue(false);

	//	if (chkExistSymbol(name)) {
	//		bKue = mSymbols[name].isExported;
	//	}

	//	return(bKue);
	//}
};

