#pragma once
#include <string>
#include <vector>
#include "Mnemonic.h"

// �G���R�[�_�[
class Encoder
{
private:
	static std::vector<Mnemonic*>	vMnemonics;
public:
	Encoder();
	~Encoder();
	static bool isMnemonic(std::string &token);

};
