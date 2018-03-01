#pragma once
#include <vector>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	using tParamList = std::vector<Parameter>;
public:
	Mnemonic		*mnemonic;		// �j�[���j�b�N
	tParamList		param;			// �X�e�[�g�����g�̃p�����[�^

public:
	Statement();
	~Statement();

	void Execute();	// �X�e�[�g�����g�̎��s
	void Encode();	// �@�B��R�[�h�ւ̕ϊ�

	std::string ToString();
};

