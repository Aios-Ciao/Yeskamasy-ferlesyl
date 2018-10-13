#include <string>
#include "Mnemonics.h"
#include "Mnemonic.h"
#include "Mnemonics/ope_fen.h"
#include "Mnemonics/ope_krz.h"
#include "Mnemonics/ope_krz8i.h"
#include "Mnemonics/ope_krz8c.h"
#include "Mnemonics/ope_krz16i.h"
#include "Mnemonics/ope_krz16c.h"
#include "Mnemonics/ope_inj.h"
#include "Mnemonics/ope_ata.h"
#include "Mnemonics/ope_nta.h"
#include "Mnemonics/ope_lat.h"
#include "Mnemonics/ope_latsna.h"
#include "Mnemonics/ope_ada.h"
#include "Mnemonics/ope_ekc.h"
#include "Mnemonics/ope_nac.h"
#include "Mnemonics/ope_dal.h"
#include "Mnemonics/ope_dto.h"
#include "Mnemonics/ope_dtosna.h"
#include "Mnemonics/ope_dro.h"
#include "Mnemonics/ope_fi.h"
#include "Mnemonics/ope_malkrz.h"
using namespace std;

Mnemonics::tMnemonics	Mnemonics::vMnemonics;

Mnemonics::Mnemonics()
{
	vMnemonics.push_back(new ope_fen());
	vMnemonics.push_back(new ope_krz());
	vMnemonics.push_back(new ope_krz8i());
	vMnemonics.push_back(new ope_krz8c());
	vMnemonics.push_back(new ope_krz16i());
	vMnemonics.push_back(new ope_krz16c());
	vMnemonics.push_back(new ope_inj());
	vMnemonics.push_back(new ope_ata());
	vMnemonics.push_back(new ope_nta());
	vMnemonics.push_back(new ope_lat());
	vMnemonics.push_back(new ope_latsna());
	vMnemonics.push_back(new ope_ada());
	vMnemonics.push_back(new ope_ekc());
	vMnemonics.push_back(new ope_nac());
	vMnemonics.push_back(new ope_dal());
	vMnemonics.push_back(new ope_dto());
	vMnemonics.push_back(new ope_dtosna());
	vMnemonics.push_back(new ope_dro());
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

