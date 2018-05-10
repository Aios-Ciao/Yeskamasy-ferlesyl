#pragma once
#include <string>
#include "Common.h"

// ステートメントのパラメータ
class Parameter
{
public:
	enum ParamType {
		eptInvalid,			/// 不正なパラメータ
		eptImmidiate,		/// 即値				imm
		eptRegister,		/// レジスタ直接		f0
		eptLabel,			/// ラベル				l'かnllで定義、xokで定義参照
		eptCondition,		/// 判断条件			fiのパラメータ
		eptReg_Ofs_Imm,		/// 即値オフセット付きレジスタ間接			f0+imm@
		eptReg_Ofs_Reg,		/// レジスタオフセット付きレジスタ間接		f0+f1@
//		eptReg_Idx_Imm,		/// 即値インデックス付きレジスタ間接			f0:imm@
//		eptReg_Idx_Reg		/// レジスタインデックス付きレジスタ間接		f0:f1@
	};

	/// レジスタ名
	enum ParamRegName {
		ernF0, ernF1, ernF2, ernF3, ernF4, ernF5, ernF6, ernF7, ernXX
	};

	/// 比較条件
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

	// 各アドレッシングモードで使用するパラメータだけ使用する
	ParamType		type;	// パラメータのアドレッシングモード種別
	uint32_t		imm;	// 即値データ
	ParamRegName	base;	// ベースレジスタ
	ParamRegName	dsp;	// オフセットまたはインデックスのレジスタ
	std::string		label;	// ラベル文字列
	std::string		cond;	// 比較条件

	lk::tAddressHalf	localaddr;	// 参照先(モジュール内の)アドレス
	lk::tModuleID		modid;		// 参照先モジュールID

public:
	Parameter() :type(eptInvalid), imm(0), base(ernF0), dsp(ernF0), label(""), cond(""), localaddr(0), modid(0) {};
	~Parameter() {};

public:
	static bool isValidRegName(std::string &name) {
		if (!name.compare("xx")) return(true);
		if ((name.length() == 2)
			&& ((name[0] == 'f')
				&& (('0' <= name[1]) && (name[1] <= '7')))) {
			// 2文字で、1文字目がf、かつ0～7ならOK
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
		return(ernXX);		// ダミー
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
		return(ecn_niv);	// ダミー
	};
	static std::string RegNameFrom(ParamRegName fx) {
		switch (fx) {
		case ernF0:	return("f0");
		case ernF1:	return("f1");
		case ernF2:	return("f2");
		case ernF3:	return("f3");
		case ernF4:	return("f4");
		case ernF5:	return("f5");
		case ernF6:	return("f6");
		case ernF7:	return("f7");
		case ernXX:	return("xx");
		default:	return("??");
		}
		return "??";
	};
};
