#pragma once
#include <string>

class Mnemonic
{
public:
	virtual bool chkApplicable(std::string &token) = 0;		// �j�[���j�b�N�������ł���Ȃ�true
};
