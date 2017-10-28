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
            memory[addr + 1] = data[0];
            memory[addr + 2] = data[0];
            memory[addr + 3] = data[0];
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

    // プロセッサ
    class YfProcessor
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

        public void Op_krz()
        {
            this.firjal.F0 = 0;
        }

    }



}
