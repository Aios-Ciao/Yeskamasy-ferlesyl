#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Mnemonic
{
public:
	using tParamCount = uint16_t;
public:
	// �j�[���j�b�N�������ł���Ȃ�true
	virtual bool chkApplicable(std::string &token) = 0;

	// �j�[���j�b�N������̎擾
	virtual std::string getName() = 0;

	// ���߂̎��s
//	virtual void Execute(std::vector<Parameter> &param) = 0;

	// �o�C�g�R�[�h�ւ̕ϊ�
//	virtual unsigned char Encode(std::vector<Parameter> &param) = 0;

	// �p�����[�^���擾
	virtual tParamCount getParamCount() = 0;

	// �w��Ԗڂ̃p�����[�^�^�C�v�`�F�b�N(�p�����[�^�̕��т�'i'c�F0��src�A1��dest)
	virtual bool chkParamType(tParamCount idx, Parameter::ParamType type) = 0;
};
