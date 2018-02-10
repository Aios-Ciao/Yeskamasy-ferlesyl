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
	vector<Parse::Token> vTokenList = prs.makeTokenList();
	unsigned long	lastlinenum(0);
	string line = "";

	for (vector<Parse::Token>::iterator it = vTokenList.begin(); it != vTokenList.end(); it++)
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
		case Parse::eNumeric:		line += "Num";	break;
		case Parse::eDereference:	line += "Der";	break;
		case Parse::eDisplacement:	line += "Dsp";	break;
		case Parse::eMnemonic:		line += "Mne";	break;
		case Parse::eProcOption:	line += "Opt";	break;
		case Parse::eSymbol:		line += "Sym";	break;
		case Parse::eRegister:		line += "Reg";	break;
		default:
		case Parse::eUnknown:		line += "???";	break;
		}
		line += ">";

	}
	std::cout << (++lastlinenum) << " : " << line;
	std::cout << std::endl;

	std::cout << "done." << std::endl;
	(void)getchar();
}
