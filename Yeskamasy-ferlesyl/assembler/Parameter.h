#pragma once
#include <string>
#include "Common.h"

// �X�e�[�g�����g�̃p�����[�^
class Parameter
{
public:
	enum ParamType {
		eptInvalid,			/// �s���ȃp�����[�^
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

	/// ��r����
	enum ParamCondName {
		ecn_clo,
		ecn_xtlo,
		ecn_xtlonys,
		ecn_xolo,
		ecn_niv,
		ecn_xylo,
		ecn_xylonys,
		ecn_llo,
		ecn_llonys
	};

	// �e�A�h���b�V���O���[�h�Ŏg�p����p�����[�^�����g�p����
	ParamType		type;	// �p�����[�^�̃A�h���b�V���O���[�h���
	uint32_t		imm;	// ���l�f�[�^
	ParamRegName	base;	// �x�[�X���W�X�^
	ParamRegName	dsp;	// �I�t�Z�b�g�܂��̓C���f�b�N�X�̃��W�X�^
	std::string		label;	// ���x��������
	std::string		cond;	// ��r����

	lk::tAddressHalf	localaddr;	// �Q�Ɛ�(���W���[������)�A�h���X
	lk::tModuleID		modid;		// �Q�Ɛ惂�W���[��ID

public:
	Parameter() :type(eptInvalid), imm(0), base(ernF0), dsp(ernF0), label(""), cond(""), localaddr(0), modid(0) {};
	~Parameter() {};

public:
	static bool isValidRegName(std::string &name) {
		if (!name.compare("xx")) return(true);
		if ((name.length() == 2)
			&& ((name[0] == 'f')
				&& (('0' <= name[1]) && (name[1] <= '7')))) {
			// 2�����ŁA1�����ڂ�f�A����0�`7�Ȃ�OK
			return(true);
		}
		return(false);
	}
	static ParamRegName	fromRegName(std::string &name) {
		if (!name.compare("xx")) return(ernXX);
		if (!name.compare("f0")) return(ernF0);
		if (!name.compare("f1")) return(ernF1);
		if (!name.compare("f2")) return(ernF2);
		if (!name.compare("f3")) return(ernF3);
		if (!name.compare("f4")) return(ernF4);
		if (!name.compare("f5")) return(ernF5);
		if (!name.compare("f6")) return(ernF6);
		if (!name.compare("f7")) return(ernF7);
		return(ernXX);		// �_�~�[
	};
	static ParamCondName fromCondStr(std::string &cond) {
		if (!cond.compare("clo")) return(ecn_clo);
		if (!cond.compare("xtlo")) return(ecn_xtlo);
		if (!cond.compare("xtlonys")) return(ecn_xtlonys);
		if (!cond.compare("xolo")) return(ecn_xolo);
		if (!cond.compare("niv")) return(ecn_niv);
		if (!cond.compare("xylo")) return(ecn_xylo);
		if (!cond.compare("xylonys")) return(ecn_xylonys);
		if (!cond.compare("llo")) return(ecn_llo);
		if (!cond.compare("llonys")) return(ecn_llonys);
		return(ecn_niv);	// �_�~�[
	};
};
