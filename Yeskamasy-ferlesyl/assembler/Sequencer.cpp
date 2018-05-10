#include <iostream>
#include "Sequencer.h"

bool Sequencer::Step()
{
	bool bSuccessed(false);
	lk::tModuleID	cur_idx_module(idx_module);
	Statement::tStatementIndex	cur_idx_statement(idx_statement);

	idx_statement++;
	if(cur_idx_statement < _modules[idx_module].vStatements.size()) {
		// 仮に逆アセ表示としておく
		std::cout << _modules[idx_module][cur_idx_statement].ToString() << std::endl;
		bSuccessed = true;
	}

	return(bSuccessed);
}

