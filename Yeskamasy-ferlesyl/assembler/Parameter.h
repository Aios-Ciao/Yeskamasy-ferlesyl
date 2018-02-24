#pragma once
#include <string>

// ステートメントのパラメータ
class Parameter
{
public:
	enum ParamType {
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

	// 各アドレッシングモードで使用するパラメータだけ使用する
	ParamType		type;	// パラメータのアドレッシングモード種別
	uint32_t		imm;	// 即値データ
	ParamRegName	base;	// ベースレジスタ
	ParamRegName	dsp;	// オフセットまたはインデックスのレジスタ
	std::string		label;	// ラベル文字列
	std::string		cond;	// 比較条件

public:
	Parameter(){};
	~Parameter() {};

};
