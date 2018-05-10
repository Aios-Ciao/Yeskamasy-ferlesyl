#pragma once
#include "Common.h"
#include <map>

// メモリ
class Setistafar
{
	std::map<lk::tAddressFull, uint8_t>	_memory;
public:
	void init() {
		_memory.clear();
	}

};

// cpu
class Ferlesexiayl
{
	using tRegister = uint32_t;		/// レジスタタイプ
	using tFlags = union {			/// ステータスレジスタ
		uint16_t	word;
		struct {
			uint16_t	F	: 1;	/// フラグ(条件命令の成立状況)
			uint16_t		  : 3;
			uint16_t	C : 1;		/// キャリーフラグ
			uint16_t	Z : 1;		/// ゼロフラグ
			uint16_t	OF : 1;		/// オーバーフローフラグ
			uint16_t	 : 1;

			uint16_t	IPL : 4;	/// 処理レベル(0:最低 15:最高)
			uint16_t : 3;
			uint16_t	I : 1;		/// 割込み許可(0:禁止 1:許可)
		} bits;
	};
public:
	tRegister	f0, f1, f2, f3, f5, xx;		/// firjal
	tFlags		flg;

	void init() {
		f0 = f1 = f2 = f3 = 0xFFFFFFFFul;
		f5 = 0x6D7AA0F8;
		xx = 0x14830000;
		flg.word = 0x0000u;
	}
};

// 処理機クラス
// 外部から制御するためのクラス
class Proc
{
	Setistafar		setistafar;
	Ferlesexiayl	firjal;

public:
	Proc() {
		reset();
	}
	void reset() {
		setistafar.init();	// メモリ
		firjal.init();		// レジスタ
	}
};

