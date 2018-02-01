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
	
	while (prs.getToken(token))
	{
		// トークン区切りの処理
		if (token == " ") {
			continue;
		}
		// コメントの処理
		if (token == ";") {
			prs.skipToBreak();
			continue;
		}

		std::cout << token << " ";
	}

	std::cout << "done." << std::endl;
	(void)getchar();
}
