#pragma once
#include <string>

// アセンブラ
class ladirvirelyl
{
public:
	ladirvirelyl(int argc, char *argv[]);
	~ladirvirelyl();

	void load(char *fname);

	std::string removeComment(std::string &buf);
	std::string skipBlank(std::string &buf);
};

