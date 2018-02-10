#include <string>
#include "Encoder.h"
#include "Mnemonic.h"
#include "Mnemonics/ope_fen.h"
#include "Mnemonics/ope_krz.h"
#include "Mnemonics/ope_inj.h"
using namespace std;

std::vector<Mnemonic*>	Encoder::vMnemonics;

Encoder::Encoder()
{
	vMnemonics.push_back(new ope_fen());
	vMnemonics.push_back(new ope_krz());
	vMnemonics.push_back(new ope_inj());
}

Encoder::~Encoder()
{
	for (std::vector<Mnemonic *>::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		delete *it;
	}
}

bool Encoder::isMnemonic(std::string &token)
{
	bool bIsMnemonic(false);

	for (std::vector<Mnemonic *>::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		if ((*it)->chkApplicable(token)) {
			bIsMnemonic = true;
			break;
		}
	}

	return (bIsMnemonic);
}
