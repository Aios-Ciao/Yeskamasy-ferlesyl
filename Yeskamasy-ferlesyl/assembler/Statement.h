#pragma once
#include <vector>
#include <string>
#include "Mnemonic.h"
#include "Parameter.h"

class Statement
{
public:
	Mnemonic					*mnemonic;		// �j�[���j�b�N
	std::vector<Parameter>		param;			// �X�e�[�g�����g�̃p�����[�^

public:
	Statement();
	~Statement();

	std::string ToString();
};

