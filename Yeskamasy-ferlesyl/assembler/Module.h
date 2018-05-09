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
	using tModuleList = std::vector<Module>;
	using tStatementIdxList = std::vector<Statement::tStatementIndex>;

private:
	static lk::tModuleID	id_base;			// �����グ�p
	lk::tModuleID			id;
	lk::tModuleName			filename;
	lk::tAddressHalf		loadaddress;		// ���W���[���̊�_�A�h���X(���16bit)

public:
	Statement::tStatementList	vStatements;	/// �X�e�[�g�����g�Q
	tStatementIdxList			vLabelRefStateIdx;	/// �������ׂ����x�����p�����[�^�Ƃ��Ă��X�e�[�g�����g�̃C���f�b�N�X���X�g
	Symbol::tSymbolAry			vSymbols;		/// ���W���[���Œ�`����郉�x���ꗗ

public:
	Module(std::string &name);
	~Module() {};

	lk::tModuleID	getID() { return(id); };
	std::string		getFilename() { return(filename); };
};

