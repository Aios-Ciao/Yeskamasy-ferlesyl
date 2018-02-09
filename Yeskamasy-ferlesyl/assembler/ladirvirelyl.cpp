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
		line += "<" + it->str + "," + std::to_string(it->type) + ">";

	}
	std::cout << (++lastlinenum) << " : " << line;
	std::cout << std::endl;

	std::cout << "done." << std::endl;
	(void)getchar();
}
