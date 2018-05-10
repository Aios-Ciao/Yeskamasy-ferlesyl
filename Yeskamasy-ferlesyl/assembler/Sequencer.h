#pragma once
#include "Module.h"
#include "Proc.h"

// ステートメントシーケンサ
class Sequencer
{
	Module::tModuleList	&_modules;
	lk::tModuleID	idx_module;
	Statement::tStatementIndex	idx_statement;
	Proc	processor;

public:
	Sequencer(Module::tModuleList& modules)
		: _modules(modules), idx_module(0), idx_statement(0)
	{

	}

	~Sequencer() {};

	bool Step();
};
