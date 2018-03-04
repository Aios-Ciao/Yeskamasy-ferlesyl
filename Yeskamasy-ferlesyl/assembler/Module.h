#pragma once
#include <string>
#include <map>
#include <vector>
#include "Common.h"
#include "Parse.h"
#include "Symbol.h"

// �A�Z���u�����郂�W���[���̊Ǘ�
class Module
{

private:
	std::string			filename;
	lk::tAddressHalf	loadaddress;		// ���W���[���̊�_�A�h���X(���16bit)

	Parse::tStatementList	vStatements;	// �X�e�[�g�����g�Q
	Symbol					_Symbols;		// �V���{���Q

public:
	using tModuleList = std::vector<Module*>;

public:
	Module(std::string &name) :filename(name), loadaddress(0) {};
	~Module() {};

	std::string		getFilename() { return(filename); };
};

