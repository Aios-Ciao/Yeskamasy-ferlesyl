#pragma once
#include <string>
#include "Module.h"

// アセンブラ
class ladirvirelyl
{
	Module::tModuleList	_modules;

public:
	ladirvirelyl(int argc, char *argv[]);
	~ladirvirelyl();

	void load(Module &module);
};

