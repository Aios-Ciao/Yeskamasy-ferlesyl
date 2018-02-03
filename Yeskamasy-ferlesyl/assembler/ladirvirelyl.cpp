#include <iostream>
#include <fstream>
#include <string>
#include "ladirvirelyl.h"
#include "Parse.h"

using namespace std;

ladirvirelyl::ladirvirelyl(int argc, char *argv[])
{
	load(argv[1]);
}

ladirvirelyl::~ladirvirelyl()
{

}

void ladirvirelyl::load(char *fname)
{
	string token;
	Parse	prs(fname);
	Parse::PosInfo	curp, nextp;
	unsigned long	lastlinenum(0);
	string line = "";
	
	while (prs.getToken(token, curp, nextp))
	{
		if (token == "\x20") continue;

		if (lastlinenum != curp.nRow)
		{
			lastlinenum = curp.nRow;
			std::cout << curp.nRow << " : " << line;
			std::cout << endl;
			line = "";
		}
		line += "<" + token + ">";
	}
	std::cout << curp.nRow << " : " << line;
	std::cout << std::endl;

	std::cout << "done." << std::endl;
	(void)getchar();
}
