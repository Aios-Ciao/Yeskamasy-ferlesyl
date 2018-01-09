using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace interpreter
{
    partial class YfProcessor
    {
        /// <summary>
        /// NOP
        /// </summary>
        public void Op_fen()
        {

        }

        /// <summary>
        /// データ転送
        /// </summary>
        /// <param name="target"></param>
        /// <param name="src"></param>
        public void Op_krz(MOpeland target, MOpeland src)
        {
            uint temp;

            temp = Load(src);

            Store(target, temp);
        }

        /// <summary>
        /// フラグ条件付きデータ転送
        /// </summary>
        /// <param name="target"></param>
        /// <param name="src"></param>
        public void Op_malkrz(MOpeland target, MOpeland src)
        {
            uint temp;

            temp = Load(src);

            // フラグがセットされている場合のみ転送
            if(firjal.Flag)
            {
                Store(target, temp);
            }

        }

        /// <summary>
        /// 加算命令
        /// </summary>
        /// <param name="target">加算する対象</param>
        /// <param name="value">加算する値</param>
        public void Op_ata(MOpeland target, MOpeland value)
        {
            uint temp;

            temp = Load(target);
            temp += Load(value);
            Store(target, temp);
        }

        /// <summary>
        /// 減算命令
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_nta(MOpeland target, MOpeland value)
        {
            uint temp;

            temp = Load(target);
            temp -= Load(value);
            Store(target, temp);
        }

        /// <summary>
        /// ビットAND
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_ada(MOpeland target, MOpeland value)
        {
            uint temp;

            temp = Load(target);
            temp &= Load(value);
            Store(target, temp);
        }

        /// <summary>
        /// ビットOR
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_ekc(MOpeland target, MOpeland value)
        {
            uint temp;

            temp = Load(target);
            temp |= Load(value);
            Store(target, temp);
        }

        /// <summary>
        /// ビット反転
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_nac(MOpeland target)
        {
            uint temp;

            temp = Load(target);
            temp = ~temp;
            Store(target, temp);
        }

        /// <summary>
        /// ビットXNOR
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_dal(MOpeland target, MOpeland value)
        {
            uint temp;

            temp = Load(target);
            temp ^= Load(value);
            temp = ~temp;
            Store(target, temp);
        }

        /// <summary>
        /// 論理右シフト
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_dto(MOpeland target, MOpeland value)
        {
            uint temp;
            int shift;

            temp = Load(target);
            shift = (int)Load(value);
            temp = temp >> shift;
            Store(target, temp);
        }

        /// <summary>
        /// 算術右シフト
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_dtosna(MOpeland target, MOpeland value)
        {
            int temp;
            int shift;

            temp = (int)Load(target);
            shift = (int)Load(value);
            temp = temp >> shift;
            Store(target, (uint)temp);
        }

        /// <summary>
        /// 左シフト
        /// </summary>
        /// <param name="target"></param>
        /// <param name="value"></param>
        public void Op_dro(MOpeland target, MOpeland value)
        {
            uint temp;
            int shift;

            temp = Load(target);
            shift = (int)Load(value);
            temp = temp << shift;
            Store(target, temp);
        }

        /// <summary>
        /// 符号なし乗算
        /// </summary>
        /// <param name="mulcand">被乗数</param>
        /// <param name="muler">乗数</param>
        /// <param name="dest_h">結果格納上位32bit</param>
        /// <param name="dest_l">結果格納下位32bit</param>
        public void Op_lat(MOpeland mulcand, MOpeland muler, MOpeland dest_h, MOpeland dest_l)
        {
            ulong answer;
            ulong m1, m2;
            uint uh, ul;

            m1 = (ulong)Load(mulcand);
            m2 = (ulong)Load(muler);
            answer = m1 * m2;       // 符号なし演算

            uh = (uint)((answer >> 32) & 0xFFFFFFFF);
            ul = (uint)(answer & 0xFFFFFFFF);

            Store(dest_h, uh);
            Store(dest_l, ul);
        }

        /// <summary>
        /// 符号付き乗算
        /// </summary>
        /// <param name="mulcand"></param>
        /// <param name="muler"></param>
        /// <param name="dest_h"></param>
        /// <param name="dest_l"></param>
        public void Op_latsna(MOpeland mulcand, MOpeland muler, MOpeland dest_h, MOpeland dest_l)
        {
            ulong answer;
            long m1, m2;
            uint r1, r2;

            m1 = (long)Load(mulcand);
            m2 = (long)Load(muler);
            answer = (ulong)(m1 * m2);       // 符号付き演算

            r1 = (uint)((answer >> 32) & 0xFFFFFFFF);
            r2 = (uint)(answer & 0xFFFFFFFF);

            Store(dest_h, r1);
            Store(dest_l, r2);
        }

        /// <summary>
        /// 除算(未定義)
        /// </summary>
        /// <param name="divend">被除数</param>
        /// <param name="divor">除数</param>
        public void Op_kak(MOpeland divend, MOpeland divor)
        {
            // 例外スローしたい
        }

        /// <summary>
        /// 条件比較命令
        /// </summary>
        /// <param name="lvalue">左</param>
        /// <param name="rvalue">右</param>
        /// <param name="cond">条件</param>
        public void Op_fi(MOpeland lvalue, MOpeland rvalue, MOpeland.EfCondition cond)
        {
            uint ul, ur;
            int sl, sr;
            bool result = false;

            ul = Load(lvalue); sl = (int)ul;
            ur = Load(rvalue); sr = (int)ur;

            switch (cond)
            {
                case MOpeland.EfCondition.efCond_clo:       // 同値
                    result = (ul == ur);
                    break;
                case MOpeland.EfCondition.efCond_niv:       // 不等
                    result = (ul != ur);
                    break;
                case MOpeland.EfCondition.efCond_xolonys:   // 符号なし以上
                    result = (ul >= ur);
                    break;
                case MOpeland.EfCondition.efCond_xtlonys:   // 符号なし以下
                    result = (ul <= ur);
                    break;
                case MOpeland.EfCondition.efCond_xylonys:   // 符号なし未満
                    result = (ul < ur);
                    break;
                case MOpeland.EfCondition.efCond_llonys:    // 符号なし超過
                    result = (ul > ur);
                    break;
                case MOpeland.EfCondition.efCond_xylo:      // 符号あり未満
                    result = (sl < sr);
                    break;
                case MOpeland.EfCondition.efCond_llo:       // 符号あり超過
                    result = (sl > sr);
                    break;
                case MOpeland.EfCondition.efCond_xtlo:      // 符号あり以下
                    result = (sl <= sr);
                    break;
                case MOpeland.EfCondition.efCond_xolo:      // 符号あり以上
                    result = (sl >= sr);
                    break;
                default:
                    break;
            }

            // 判定結果をフラグに反映
            firjal.Flag = result;
        }

        /// <summary>
        /// 二重移動
        /// </summary>
        /// <param name="dest"></param>
        /// <param name="srcdest"></param>
        /// <param name="src"></param>
        public void Op_inj(MOpeland dest, MOpeland srcdest, MOpeland src)
        {
            uint temp1, temp2;

            temp1 = Load(srcdest);
            temp2 = Load(src);

            Store(dest, temp1);
            Store(srcdest, temp2);
        }
    }
}
