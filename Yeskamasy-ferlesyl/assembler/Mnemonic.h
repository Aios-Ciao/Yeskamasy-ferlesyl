#pragma once
#include <string>
#include <vector>
#include "Parameter.h"

class Mnemonic
{
public:
	enum eCI {
		eci_I_C,		// 'i'c ope src dest�̏�	(�f�t�H���g)
		eci_C_I			// 'c'i ope dest src�̏�
	};
	using tParamDir = eCI;
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

	// 'c'i/'i'c�w��ɂ��p�����[�^�̕��т̃}�b�v����
	virtual tParamCount	getParamIndex(tParamCount idx, tParamDir d = eci_I_C) = 0;

	// �w��Ԗڂ̃p�����[�^�^�C�v�`�F�b�N(�p�����[�^�̕��т�'i'c�F0��src�A1��dest)
	virtual bool chkParamType(tParamCount idx, Parameter::ParamType type) = 0;
};
