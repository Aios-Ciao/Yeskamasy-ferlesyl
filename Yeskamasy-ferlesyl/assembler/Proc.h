#pragma once
#include "Common.h"
#include "Parameter.h"
#include <map>

// メモリ
class Setistafar
{
	std::map<lk::tAddressFull, uint8_t>	_memory;
public:
	void init() {
		_memory.clear();
		write(0x6D7AA0F8, 0xBDA574B8);
	};

	// 指定アドレスから4byte読み出し
	uint32_t	read(lk::tAddressFull addr) {
		union {
			uint32_t	dword;
			uint8_t		byte[4];
		} work;
		uint32_t value(0);

		// 連続領域読み出し
		for (int ofs = 0; ofs < 4; ofs++) {
			if (_memory.count(addr + ofs) > 0) {
				work.byte[3 - ofs] = _memory[addr + ofs];
			}
			else {
				work.byte[3 - ofs] = 0;
			}
		}
		value = work.dword;

		return value;
	};
	// 指定アドレスから4byte書き込み
	void write(lk::tAddressFull addr, uint32_t value) {
		union {
			uint32_t	dword;
			uint8_t		byte[4];
		} work;

		// 連続領域書き込み
		work.dword = value;
		for (int ofs = 0; ofs < 4; ofs++) {
			_memory[addr + ofs] = work.byte[3 - ofs];
		}

	}
};

// cpu
class Ferlesexiayl
{
public:
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
	};

	tRegister &refReg(Parameter::ParamRegName reg) {
		tRegister dummy(0);

		switch (reg) {
		case Parameter::ernF0:	return(f0);
		case Parameter::ernF1:	return(f1);
		case Parameter::ernF2:	return(f2);
		case Parameter::ernF3:	return(f3);
		case Parameter::ernF5:	return(f5);
		case Parameter::ernXX:	return(xx);
		case Parameter::ernF7:	return(xx);
		default:
			break;
		}

		return dummy;
	};
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
	};
	void reset() {
		setistafar.init();	// メモリ
		firjal.init();		// レジスタ
	};
	void setFlag(bool value) {
		firjal.flg.bits.F = value;
	};
	bool chkFlag() {
		return(firjal.flg.bits.F);
	};

	// for interpretor
	Ferlesexiayl::tRegister getNX() {
		return firjal.xx;
	};
	void setNX(Ferlesexiayl::tRegister addr) {
		firjal.xx = addr;
	}
	Ferlesexiayl::tRegister getReg(Parameter::ParamRegName reg) {
		return firjal.refReg(reg);
	}
	Ferlesexiayl::tRegister getMem(Ferlesexiayl::tRegister addr) {
		return setistafar.read(addr);
	}

	Ferlesexiayl::tRegister &Read(Parameter &opeland) {
		Ferlesexiayl::tRegister value(0);
		Ferlesexiayl::tRegister addr(0);

		switch (opeland.type) {
		case Parameter::ParamType::eptImmidiate:
			value = opeland.imm;
			break;
		case Parameter::ParamType::eptRegister:
			value = firjal.refReg(opeland.base);
			break;
		case Parameter::ParamType::eptReg_Ofs_Imm:
			addr = firjal.refReg(opeland.base) + opeland.imm;
			value = setistafar.read(addr);
			break;
		case Parameter::ParamType::eptReg_Ofs_Reg:
			addr = firjal.refReg(opeland.base) + firjal.refReg(opeland.dsp);
			value = setistafar.read(addr);
			break;
		case Parameter::ParamType::eptLabel:
			value = (opeland.modid << 16) | opeland.localaddr;
			break;
		default:
			break;
		}

		return( value );
	};

	bool Write(Parameter &opeland, Ferlesexiayl::tRegister value) {

		bool bSuccess(true);
		Ferlesexiayl::tRegister addr(0);

		switch (opeland.type) {
		case Parameter::ParamType::eptRegister:
			firjal.refReg(opeland.base) = value;
			break;
		case Parameter::ParamType::eptReg_Ofs_Imm:
			addr = firjal.refReg(opeland.base) + opeland.imm;
			setistafar.write(addr, value);
			break;
		case Parameter::ParamType::eptReg_Ofs_Reg:
			addr = firjal.refReg(opeland.base) + firjal.refReg(opeland.dsp);
			setistafar.write(addr, value);
			break;
		default:
			bSuccess = false;
			break;
		}

		return(bSuccess);
	};
};

