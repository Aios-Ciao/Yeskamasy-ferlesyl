#pragma once
#include <string>

// �X�e�[�g�����g�̃p�����[�^
class Parameter
{
public:
	enum ParamType {
		eptImmidiate,		/// ���l				imm
		eptRegister,		/// ���W�X�^����		f0
		eptLabel,			/// ���x��				l'��nll�Œ�`�Axok�Œ�`�Q��
		eptCondition,		/// ���f����			fi�̃p�����[�^
		eptReg_Ofs_Imm,		/// ���l�I�t�Z�b�g�t�����W�X�^�Ԑ�			f0+imm@
		eptReg_Ofs_Reg,		/// ���W�X�^�I�t�Z�b�g�t�����W�X�^�Ԑ�		f0+f1@
//		eptReg_Idx_Imm,		/// ���l�C���f�b�N�X�t�����W�X�^�Ԑ�			f0:imm@
//		eptReg_Idx_Reg		/// ���W�X�^�C���f�b�N�X�t�����W�X�^�Ԑ�		f0:f1@
	};

	/// ���W�X�^��
	enum ParamRegName {
		ernF0, ernF1, ernF2, ernF3, ernF4, ernF5, ernF6, ernF7, ernXX
	};

	// �e�A�h���b�V���O���[�h�Ŏg�p����p�����[�^�����g�p����
	ParamType		type;	// �p�����[�^�̃A�h���b�V���O���[�h���
	uint32_t		imm;	// ���l�f�[�^
	ParamRegName	base;	// �x�[�X���W�X�^
	ParamRegName	dsp;	// �I�t�Z�b�g�܂��̓C���f�b�N�X�̃��W�X�^
	std::string		label;	// ���x��������
	std::string		cond;	// ��r����

public:
	Parameter(){};
	~Parameter() {};

};
