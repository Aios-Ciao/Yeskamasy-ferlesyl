#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ladirvirelyl.h"
#include "Parse.h"
#include "Mnemonics.h"
#include "Module.h"
#include "Linker.h"
#include "Sequencer.h"

using namespace std;
static Mnemonics mne;


ladirvirelyl::ladirvirelyl(int argc, char *argv[])
{
	int nfiles = argc;
	Sequencer	*seq;

	// 引数無しでは何もしない
	if (nfiles == 0) {
		return;
	}

	for (int i = 1; i < nfiles; ++i) {
		std::string		fname(argv[i]);
		Module	mod(fname);

		_modules.push_back(mod);
	}

	// 各モジュールの読み込み
	for (Module::tModuleList::iterator mod = _modules.begin(); mod != _modules.end(); ++mod) {
		load(*mod);
	}

	// モジュール間のリンク
	Linker::Link(_modules);
	seq = new Sequencer(_modules);

	seq->Run();

	delete seq;
}

ladirvirelyl::~ladirvirelyl()
{
}

void ladirvirelyl::load(Module &_module)
{
	Parse	prs;
	Parse::tTokenList vTokenList = prs.makeTokenList(_module.getFilename());
	Statement::tStatementList	vStatements = prs.makeStatementList(vTokenList, _module);

	unsigned long	lastlinenum(0);
	string line = "";
	for (Parse::tTokenList::iterator it = vTokenList.begin(); it != vTokenList.end(); it++)
	{
		if (lastlinenum != it->pos.nRow)
		{
			lastlinenum = it->pos.nRow;
			std::cout << it->pos.nRow << " : " << line;
			std::cout << endl;
			line = "";
		}
		line += "<" + it->str + ",";
		switch (it->type)
		{
		case Parse::Token::eNumeric:		line += "Num";	break;
		case Parse::Token::eDereference:	line += "Der";	break;
		case Parse::Token::eDisplacement:	line += "Dsp";	break;
		case Parse::Token::eMnemonic:		line += "Mne";	break;
		case Parse::Token::eProcOption:	line += "Opt";	break;
		case Parse::Token::eSymbol:		line += "Sym";	break;
		case Parse::Token::eCondition:		line += "Cnd";	break;
		case Parse::Token::eRegister:		line += "Reg";	break;
		default:
		case Parse::Token::eUnknown:		line += "???";	break;
		}
		line += ">";

	}
	std::cout << (++lastlinenum) << " : " << line;
	std::cout << std::endl;

	std::cout << "done." << std::endl;
	(void)getchar();
}
