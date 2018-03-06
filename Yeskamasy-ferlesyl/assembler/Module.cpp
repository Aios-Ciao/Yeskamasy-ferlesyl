#include "Module.h"

Module::tModuleID	Module::id_base = 0;

Module::Module(std::string &name)
	:filename(name), loadaddress(0)
{
	id = id_base;
	id_base++;
};
