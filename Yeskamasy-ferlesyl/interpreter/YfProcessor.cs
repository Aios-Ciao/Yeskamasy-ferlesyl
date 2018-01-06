using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace interpreter
{
    /// <summary>
    ///     メモリ管理
    /// </summary>
    class YfMemory
    {
        Dictionary<ulong, byte> memory;      // アドレス→値

        public YfMemory()
        {
            this.memory = new Dictionary<ulong, byte>();

            Reset();
        }

        ~YfMemory()
        {
        }




        /// <summary>
        ///     メモリ内容の消去
        /// </summary>
        public void Reset()
        {
            this.memory.Clear();
        }

        /// <summary>
        ///     メモリの内容を取得する
        /// </summary>
        /// <param name="addr">基点アドレス</param>
        /// <returns>指定アドレスからの32bit値</returns>
        public ulong Read(ulong addr)
        {
            Random r = new Random();
            byte[] rdata = new byte[4];
            ulong retval;

            // 全既に書き込みをしているかチェック
            if (memory.ContainsKey(addr + 0) && memory.ContainsKey(addr + 1)
                && memory.ContainsKey(addr + 2) && memory.ContainsKey(addr + 3))
            {
                retval = memory[addr];
            }
            else
            {
                // 未初期化領域へのアクセス
                r.NextBytes(rdata);
                retval = BitConverter.ToUInt32(rdata, 0);
            }

            return retval;
        }

        /// <summary>
        ///     メモリへのデータ書き込み
        /// </summary>
        /// <param name="addr">書き込み先のアドレス</param>
        /// <param name="value">書きこむ値</param>
        public void Write(ulong addr, ulong value)
        {
            byte[] data = new byte[4];

            data[0] = (byte)((value & 0x000000FF) >> 0);
            data[1] = (byte)((value & 0x0000FF00) >> 8);
            data[2] = (byte)((value & 0x00FF0000) >> 16);
            data[3] = (byte)((value & 0xFF000000) >> 24);

            memory[addr + 0] = data[0];
            memory[addr + 1] = data[1];
            memory[addr + 2] = data[2];
            memory[addr + 3] = data[3];
        }
    }

    class Registers
    {
        private ulong f0;       // 引数1 / 戻り値
        private ulong f1;
        private ulong f2;
        private ulong f3;
        private ulong f4;
        private ulong f5;       // リターンアドレス
        private ulong f6;
        private ulong xx;       // プログラムカウンタ

        private bool flag;       // コンディション


        /// <summary>
        /// 各種アクセサ
        /// </summary>
        public ulong F0
        {
            set { this.f0 = value; }
            get { return this.f0; }
        }
        public ulong F1
        {
            set { this.f1 = value; }
            get { return this.f1; }
        }
        public ulong F2
        {
            set { this.f2 = value; }
            get { return this.f2; }
        }
        public ulong F3
        {
            set { this.f3 = value; }
            get { return this.f3; }
        }
        public ulong F4
        {
            set { this.f4 = value; }
            get { return this.f4; }
        }
        public ulong F5
        {
            set { this.f5 = value; }
            get { return this.f5; }
        }
        public ulong F6
        {
            set { this.f6 = value; }
            get { return this.f6; }
        }
        public ulong XX
        {
            set { this.xx = value; }
            get { return this.xx; }
        }

        public bool Flag
        {
            set { this.flag = value; }
            get { return this.flag; }
        }

        /// <summary>
        ///  コンストラクタ
        /// </summary>
        public Registers()
        {
            this.Reset();
        }

        // 初期状態へリセット
        public void Reset()
        {
            F0 = 0x00000000;
            F1 = 0x00000000;
            F2 = 0x00000000;
            F3 = 0x00000000;
            F4 = 0x00000000;
            F5 = 0x6d7aa0f8;
            F6 = 0x00000000;
            XX = 0x14830000;
            Flag = false;
        }
    };


    struct MOpeland
    {
        /// <summary>
        ///     引数の情報
        /// </summary>
        public enum efParamType
        {
            efImmidiate,            // 即値
            efDirectReg,            // レジスタ値
            efLabel,                // ラベル値
            efReserved,             // 予約
            efRegDispImm,           // レジスタ＋即値 間接参照
            efRegDispReg,           // レジスタ＋レジスタ 間接参照
            efLabelDispImm,         // ラベル＋即値 間接参照【拡張】
            efLabelDispReg          // ラベル＋レジスタ 間接参照【拡張】
        };

        /// <summary>
        ///     引数レジスタ番号
        /// </summary>
        public enum efRegName
        {
            efRegF0,
            efRegF1,
            efRegF2,
            efRegF3,
            efRegF4,
            efRegF5,
            efRegF6,
            efRegXX
        };

        efParamType addrtype;       // アドレッシングモード
        efRegName basereg;          // ベースレジスタ
        efRegName offsetreg;        // オフセットレジスタ
        ulong immidiate;                // 即値
        ulong label;                // ラベル値( TODO:いずれインデックス引きしたい)

        public efParamType Type
        {
            set { this.addrtype = value; }
            get { return this.addrtype; }
        }

        public efRegName BaseReg
        {
            set { this.basereg = value; }
            get { return this.basereg; }
        }
        public efRegName OffsetReg
        {
            set { this.offsetreg = value; }
            get { return this.offsetreg; }
        }
        public ulong Immidiate
        {
            set { this.immidiate = value; }
            get { return this.immidiate; }
        }
        public ulong Label
        {
            set { this.label = value; }
            get { return this.label; }
        }

    };

    // プロセッサ
    partial class YfProcessor
    {
        protected Registers firjal;     // 各種レジスタ
        YfMemory setistafar;

        // プロセッサの初期化
        YfProcessor()
        {
            firjal = new Registers();
            setistafar = new YfMemory();

            this.firjal.Reset();
            this.setistafar.Reset();

        }


        /// <summary>
        /// レジスタの内容読み出し
        /// </summary>
        /// <param name="reg">レジスタ番号</param>
        /// <returns></returns>
        private ulong RegRead(MOpeland.efRegName reg)
        {
            ulong retval = 0;

            // レジスタ管理のclassではなく、オペランド側の名前として、ここで解決
            switch (reg)
            {
                case MOpeland.efRegName.efRegF0: retval = firjal.F0; break;
                case MOpeland.efRegName.efRegF1: retval = firjal.F1; break;
                case MOpeland.efRegName.efRegF2: retval = firjal.F2; break;
                case MOpeland.efRegName.efRegF3: retval = firjal.F3; break;
                case MOpeland.efRegName.efRegF4: retval = firjal.F4; break;
                case MOpeland.efRegName.efRegF5: retval = firjal.F5; break;
                case MOpeland.efRegName.efRegF6: retval = firjal.F6; break;
                case MOpeland.efRegName.efRegXX: retval = firjal.XX; break;
                default:
                    // 例外スローしたい
                    break;
            }

            return retval;
        }

        /// <summary>
        /// レジスタへの値の書きこみ
        /// </summary>
        /// <param name="reg">レジスタ番号</param>
        /// <param name="value">書きこむ値</param>
        private void RegWrite(MOpeland.efRegName reg, ulong value)
        {
            switch (reg)
            {
                case MOpeland.efRegName.efRegF0: firjal.F0 = value; break;
                case MOpeland.efRegName.efRegF1: firjal.F1 = value; break;
                case MOpeland.efRegName.efRegF2: firjal.F2 = value; break;
                case MOpeland.efRegName.efRegF3: firjal.F3 = value; break;
                case MOpeland.efRegName.efRegF4: firjal.F4 = value; break;
                case MOpeland.efRegName.efRegF5: firjal.F5 = value; break;
                case MOpeland.efRegName.efRegF6: firjal.F6 = value; break;
                case MOpeland.efRegName.efRegXX: firjal.XX = value; break;
                default:
                    // 例外スローしたい
                    break;
            }
        }

        /// <summary>
        ///     アドレッシングモードを解決して値を読みだす
        /// </summary>
        /// <param name="addr">アドレスオペランド</param>
        /// <returns>読み出した値</returns>
        public ulong Load(MOpeland addr)
        {
            ulong retval = 0;
            ulong address = 0;

            switch (addr.Type)
            {
                case MOpeland.efParamType.efImmidiate:
                    retval = addr.Immidiate;
                    break;
                case MOpeland.efParamType.efDirectReg:
                    retval = RegRead(addr.BaseReg);
                    break;
                case MOpeland.efParamType.efLabel:
                    retval = addr.Label;                // TODO:ラベル処理未実装
                    break;
                case MOpeland.efParamType.efRegDispImm:
                    address = RegRead(addr.BaseReg) + addr.Immidiate;
                    retval = setistafar.Read(address);
                    break;
                case MOpeland.efParamType.efRegDispReg:
                    address = RegRead(addr.BaseReg) + RegRead(addr.OffsetReg);
                    retval = setistafar.Read(address);
                    break;
                case MOpeland.efParamType.efLabelDispImm:       // 拡張
                    address = addr.Label + addr.Immidiate;
                    retval = setistafar.Read(address);
                    break;
                case MOpeland.efParamType.efLabelDispReg:       // 拡張
                    address = addr.Label + RegRead(addr.BaseReg);
                    retval = setistafar.Read(address);
                    break;
                default:
                case MOpeland.efParamType.efReserved:
                    // 例外を投げたい
                    break;
            }

            return retval;
        }

        /// <summary>
        ///     アドレッシングモードを解決して値を書きこむ
        /// </summary>
        /// <param name="addr">アドレスオペランド</param>
        /// <param name="val"></param>
        public void Store(MOpeland addr, ulong val)
        {
            ulong address = 0;

            switch (addr.Type)
            {
                case MOpeland.efParamType.efDirectReg:
                    // レジスタへの格納
                    RegWrite(addr.BaseReg, val);
                    break;
                case MOpeland.efParamType.efRegDispImm:
                    // 即値修飾レジスタ間接参照で格納
                    address = RegRead(addr.BaseReg) + addr.Immidiate;
                    setistafar.Write(address,val);
                    break;
                case MOpeland.efParamType.efRegDispReg:
                    // レジスタ修飾レジスタ間接参照で格納
                    address = RegRead(addr.BaseReg) + RegRead(addr.OffsetReg);
                    setistafar.Write(address, val);
                    break;
                case MOpeland.efParamType.efLabelDispImm:       // 拡張
                    // 即値修飾ラベル間接参照で格納
                    address = addr.Label + addr.Immidiate;
                    setistafar.Write(address, val);
                    break;
                case MOpeland.efParamType.efLabelDispReg:       // 拡張
                    // レジスタ修飾ラベル間接参照で格納
                    address = addr.Label + RegRead(addr.BaseReg);
                    setistafar.Write(address, val);
                    break;
                default:
                case MOpeland.efParamType.efReserved:
                case MOpeland.efParamType.efImmidiate:          // 即値に対して値の代入は不可
                case MOpeland.efParamType.efLabel:              // ラベルそのものへの代入は不可
                    // 例外を投げたい
                    break;
            }

        }




    }



}
