#pragma once
#include <vector>
#include <map>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	using tParamList = std::vector<Parameter>;
	using tParamMap = std::map<Mnemonic::tParamCount, Parameter>;
	using tStatementList = std::vector<Statement>;
	using tStatementIndex = tStatementList::size_type;
public:
	Mnemonic				*mnemonic;		// �j�[���j�b�N
	tParamList				param;			// �X�e�[�g�����g�̃p�����[�^
	Mnemonic::tParamDir		eci;			// �p�����[�^�̊i�[����
public:
	Statement();
	~Statement();

	std::string ToString();
};

