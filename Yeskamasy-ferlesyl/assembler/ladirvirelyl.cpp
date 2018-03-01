#include <iostream>
#include <fstream>
#include <string>
#include "ladirvirelyl.h"
#include "Parse.h"
#include "Encoder.h"

using namespace std;

static Encoder	enc;

ladirvirelyl::ladirvirelyl(int argc, char *argv[])
{
	load(argv[1]);
}

ladirvirelyl::~ladirvirelyl()
{

}

void ladirvirelyl::load(char *fname)
{
	Parse	prs(fname);
	Parse::tTokenList vTokenList = prs.makeTokenList();
	unsigned long	lastlinenum(0);
	string line = "";

	Parse::tStatementList	vStatements = prs.makeStatementList(vTokenList);

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
