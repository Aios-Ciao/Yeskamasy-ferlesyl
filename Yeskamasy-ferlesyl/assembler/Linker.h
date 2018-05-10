#pragma once
#include "Common.h"
#include "Module.h"

class Linker {
public:
	static bool Link(Module::tModuleList mods);
};

