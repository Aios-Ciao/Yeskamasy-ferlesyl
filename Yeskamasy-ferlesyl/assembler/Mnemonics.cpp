#include <string>
#include "Mnemonics.h"
#include "Mnemonic.h"
#include "Mnemonics/ope_fen.h"
#include "Mnemonics/ope_krz.h"
#include "Mnemonics/ope_inj.h"
#include "Mnemonics/ope_ata.h"
#include "Mnemonics/ope_nta.h"
#include "Mnemonics/ope_fi.h"
#include "Mnemonics/ope_malkrz.h"
using namespace std;

Mnemonics::tMnemonics	Mnemonics::vMnemonics;

Mnemonics::Mnemonics()
{
	vMnemonics.push_back(new ope_fen());
	vMnemonics.push_back(new ope_krz());
	vMnemonics.push_back(new ope_inj());
	vMnemonics.push_back(new ope_ata());
	vMnemonics.push_back(new ope_nta());
	vMnemonics.push_back(new ope_fi());
	vMnemonics.push_back(new ope_malkrz());
}

Mnemonics::~Mnemonics()
{
	for (tMnemonics::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		delete *it;
	}
}

bool Mnemonics::isMnemonic(std::string &token)
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

Mnemonic * Mnemonics::getMnemonic(std::string &ope)
{
	Mnemonic *pOpe(nullptr);

	for (tMnemonics::iterator it = vMnemonics.begin(); it != vMnemonics.end(); it++)
	{
		// 処理できるアイテムを返す
		if ((*it)->chkApplicable(ope)) {
			pOpe = *it;
			break;
		}
	}
	return(pOpe);
}

