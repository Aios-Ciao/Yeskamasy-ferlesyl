#pragma once
#include <string>
#include <map>
#include <vector>
#include "Common.h"
#include "Statement.h"
#include "Symbol.h"

// �A�Z���u�����郂�W���[���̊Ǘ�
class Module
{
public:
						
	/// �p�����[�^��������v�����郉�x���̈ʒu���
	struct stLabelRef {
		Parameter	*target;	// ���Ƃŏ����ւ���ׂ��p�����[�^�ւ̃|�C���^
		Symbol		*symbol;	// 
	};

private:
	static lk::tModuleID	id_base;			// �����グ�p
	lk::tModuleID			id;
	lk::tModuleName			filename;
	lk::tAddressHalf		loadaddress;		// ���W���[���̊�_�A�h���X(���16bit)

	Statement::tStatementList	vStatements;	// �X�e�[�g�����g�Q

public:
	using tModuleList = std::vector<Module*>;

public:
	Module(std::string &name);
	~Module() {};

	lk::tModuleID	getID() { return(id); };
	std::string		getFilename() { return(filename); };
};

