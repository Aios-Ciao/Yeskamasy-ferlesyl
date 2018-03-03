#include <string>
#include "Encoder.h"
#include "Mnemonic.h"
#include "Mnemonics/ope_fen.h"
#include "Mnemonics/ope_krz.h"
#include "Mnemonics/ope_inj.h"
#include "Mnemonics/ope_ata.h"
#include "Mnemonics/ope_nta.h"
#include "Mnemonics/ope_fi.h"
#include "Mnemonics/ope_malkrz.h"
using namespace std;

Encoder::tMnemonics	Encoder::vMnemonics;

Encoder::Encoder()
{
	vMnemonics.push_back(new ope_fen());
	vMnemonics.push_back(new ope_krz());
	vMnemonics.push_back(new ope_inj());
	vMnemonics.push_back(new ope_ata());
	vMnemonics.push_back(new ope_nta());
	vMnemonics.push_back(new ope_fi());
	vMnemonics.push_back(new ope_malkrz());
}

Encoder::~Encoder()
{
	for (tMnemonics::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		delete *it;
	}
}

bool Encoder::isMnemonic(std::string &token)
{
	bool bIsMnemonic(false);

	for (tMnemonics::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		if ((*it)->chkApplicable(token)) {
			bIsMnemonic = true;
			break;
		}
	}

	return (bIsMnemonic);
}

Mnemonic * Encoder::getMnemonic(std::string &ope)
{
	Mnemonic *pOpe(nullptr);

	for (tMnemonics::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		// ˆ—‚Å‚«‚éƒAƒCƒeƒ€‚ð•Ô‚·
		if ((*it)->chkApplicable(ope)) {
			pOpe = *it;
			break;
		}
	}
	return(pOpe);
}

