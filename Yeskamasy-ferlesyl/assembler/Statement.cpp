#include <vector>
#include <string>
#include "Statement.h"

Statement::Statement()
	: mnemonic(nullptr)
{

}

Statement::~Statement()
{

}

// ステートメントの実行
void Statement::Execute()
{
//	mnemonic->Execute(param);
}

// ステートメントの機械語コードへの変換
void Statement::Encode()
{

}

// １ステートメントを逆アセしたように文字列に直す
std::string Statement::ToString()
{
	std::string statement;

	return( statement );
}

