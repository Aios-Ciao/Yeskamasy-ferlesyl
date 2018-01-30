#include <iostream>
#include <fstream>
#include <string>
#include "ladirvirelyl.h"


ladirvirelyl::ladirvirelyl(int argc, char *argv[])
{
	load(argv[1]);
}

ladirvirelyl::~ladirvirelyl()
{

}

void ladirvirelyl::load(char *fname)
{
	std::ifstream	ifs(fname);

	// �J���Ă��Ȃ���ΏI��
	if (ifs.fail()) {
		std::cerr << "�t�@�C�����J���܂���ł���(" << std::string(fname) << ")" << std::endl;
		return;
	}

	std::string linebuf;
	unsigned long	lidx(0);

	while (getline(ifs, linebuf))
	{
		lidx++;
		std::cout << lidx << ":" << linebuf << std::endl;
	}

	(void)getchar();
}
