#include <iostream>
#include "Sequencer.h"
#include "Proc.h"

bool Sequencer::Step()
{
	bool bSuccessed(false);
	lk::tModuleID	cur_idx_module(idx_module);
	Statement::tStatementIndex	cur_idx_statement(idx_statement);

	idx_statement++;
	if(cur_idx_statement < _modules[idx_module].vStatements.size()) {
		_modules[idx_module][cur_idx_statement](processor);
		// 仮に逆アセ表示としておく
		std::cout << _modules[idx_module][cur_idx_statement].ToString() << std::endl;
		bSuccessed = true;
	}

	return(bSuccessed);
}

bool Sequencer::Run()
{
	lk::tModuleID	cur_idx_module;
	Statement::tStatementIndex	cur_idx_statement;
	lk::tAddressFull nx = 0x00000000;	// mod#0 statement#0

	bool b_loop(true);
	while (b_loop)
	{
		cur_idx_module = (nx >> 16) & 0x0000FFFF;
		cur_idx_statement = nx & 0x0000FFFF;
		set_nx(nx);
		std::cout << _modules[idx_module][cur_idx_statement].ToString() << std::endl;
		_modules[idx_module][cur_idx_statement](processor);
		nx = get_nx();
		switch (nx) {
		case 0xbda574b8:
			// 特定の条件時、処理終了
			if (get_fn(Parameter::ernF5) == 0x6d7aa0f8) {
				b_loop = false;
			}
			break;
		case 3126834864:	// 組み込み関数
		{
			lk::tAddressFull sp = get_fn(Parameter::ernF5);
			Ferlesexiayl::tRegister val = get_mem(sp + 4);

			std::cout << val << std::endl;

			lk::tAddressFull retaddr = get_mem(sp);
			set_nx(retaddr);
		}
			break;
		default:
			nx++;
			break;
		}
	}

	return true;
}

// 次に実行するアドレスを取得する(インタプリタ用)
lk::tAddressFull Sequencer::get_nx()
{
	return(processor.getNX());
}
// 次に実行するアドレスを設定する(インタプリタ用)
void Sequencer::set_nx(lk::tAddressFull new_addr)
{
	processor.setNX(new_addr);
}
// 任意のレジスタ値を読みだす
Ferlesexiayl::tRegister Sequencer::get_fn(Parameter::ParamRegName reg)
{
	return processor.getReg(reg);
}
// 任意のメモリアドレスから4byte値を読みだす
Ferlesexiayl::tRegister Sequencer::get_mem(lk::tAddressFull addr)
{
	return processor.getMem(addr);
}
