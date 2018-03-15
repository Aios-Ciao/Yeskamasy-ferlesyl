#pragma once
#include <vector>
#include <string>
#include <list>
#include "Common.h"
#include "Statement.h"

/// ���x���Ǘ�
class Symbol
{
public:
	using tSymbolName = std::string;
	using tSymbolList = std::list<Symbol::tSymbolName>;
	using tSymbolAry = std::vector<Symbol>;

	tSymbolName					name;			/// �V���{����
	bool						celesol_kue;	/// kue���ꂽ�V���{��
	bool						celesol_xok;	/// xok�Œǉ����ꂽ�V���{��
	bool						req_xok;		/// xok��v������V���{��
	lk::tModuleID				modid;			/// ���W���[��ID
	Statement::tStatementIndex	idx;			/// ���W���[�����X�e�[�g�����gIndex
//	lk::tAddressHalf			addr;			/// ���W���[�����A�h���X(�L���b�V���I�Ȉʒu�Â�)

	// �R���X�g���N�^
	// �Œ���V���{���e�L�X�g�͈����ɕK�v
	Symbol(tSymbolName _name, bool c_kue = false, bool r_xok = false, bool c_xok = false, lk::tModuleID mid = 0, Statement::tStatementIndex sidx = 0)
		: name(_name), celesol_kue(c_kue), celesol_xok(c_xok), req_xok(r_xok), modid(mid), idx(sidx)
	{

	};

};

