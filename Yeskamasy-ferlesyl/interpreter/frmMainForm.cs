using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace interpreter
{
    public enum ETokenType
    {
        ttUndefined,        // 未定義
        ttNumeric,          // 数値
        ttLabel,            // ラベル
        ttPlus = '+',       // オフセット計算の +
        ttAt = '@',         // 間接参照の @
        ttQuat = '\'',      // 方向定義の '
       
        tt_Mnemonic = 0x100, // ニーモニック識別子
        tt_krz,             // mov
        tt_ata,             // add
        tt_nta,             // sub
        tt_lat,             // mul
    //  tt_kak,             // div
        tt_ada,             // and
        tt_ekc,             // or
        tt_nac,             // not
        tt_dal,             // xnor
        tt_dto,             // shr (論理右シフト)
        tt_dro,             // shl (左シフト)
    //  tt_                 //      (算術右シフト)
        tt_malkrz,          // 条件付きmov
        tt_fi,              // 条件判断→フラグセット
        tt__xtlo,           // 条件 <=    (符号あり判断)
        tt__xylo,           // 条件 <
        tt__clo,            // 条件 ==
        tt__xolo,           // 条件 >=
        tt__llo,            // 条件 >
        tt__niv,            // 条件 !=
        tt__xtlonys,        // 条件 <=    (符号なし判断)
        tt__xylonys,        // 条件 <
        tt__xolonys,        // 条件 >=
        tt__llonys,         // 条件 >
        tt_inj,             // shift
        tt_fen,             // nop

    };

    public class Tokens
    {
        public long         SrcLine;        // ソースコード上の行番号位置
        public long         SrcColm;        // ソースコード上の桁位置
        public string       Token;          // トークン文字列
        public ETokenType   Type;           // トークン種別

    };

    public partial class frmMainForm : Form
    {
        public frmMainForm()
        {
            InitializeComponent();
        }

        private void miToMnemonic_Click(object sender, EventArgs e)
        {
            string buf;
            List<Tokens> saTokens;


            buf = txtSourceCode.Text;

            // ここで成型
            saTokens = Tokenize(buf);

            // 再度並べ替え
            buf = "";
            long lindx = -1;
            bool spOut = false;
            foreach( Tokens token in saTokens)
            {
                // 行が変わったら行番号を出力
                if (lindx != token.SrcLine)
                {
                    // 初回は出さない
                    if( lindx != -1)
                    {
                        buf += "\r\n";
                        spOut = false;
                    }
                    lindx = token.SrcLine;
                    buf += lindx.ToString("0000") + " | ";
                }
                // トークンをブランク区切りで出力
                if (spOut)
                {
                    buf += "\x20";
                }
                buf += token.Token;
                spOut = true;
            }

            txtStatementList.Text = buf;

            tbpDebug.Select();
            tctlEditor.SelectTab(tbpDebug.Name);
        }


        // トークン化
        List<Tokens> Tokenize(string sSrc)
        {
            var saTokens = new List<Tokens> ();             // 分割されたトークンリスト
            var saLines = new List<string>();               // コメントが除去された１行ずつ文字列リスト


            // コメントと改行文字を1文字の空白へ置き換え
            {
                char[] sep = { '\n', '\r' };
                string[] saSrc = sSrc.Split(sep);         // 改行文字でスライス
                foreach (string sLine in saSrc)
                {
                    if (sLine.Length == 0) continue;           // 空行スキップ
                    int posdeli = sLine.IndexOf(';');           // 各行のコメントを除去

                    if (posdeli < 0)
                    {
                        // 見つからなかった
                        saLines.Add(sLine);
                    }
                    else
                    {
                        // １文字の空白文字として置換する
                        saLines.Add(sLine.Substring(0, posdeli));
                    }
                }
            }

            // 空白区切りごとに切り出し
            int lindex = 0;                         // 行番号
            foreach (string sLine in saLines)
            {
                if (sLine.Length == 0) continue;               // 空行スキップ

                char[] sep = { '\x20', '\t' };
                string[] saSepStr = sLine.Split(sep);      // 空白文字でスライス

                // 文字があればリストに積む
                foreach (string tkn in saSepStr)
                {
                    if( tkn != "" )
                    {
                        Tokens token = new Tokens();
                        token.Token = tkn;
                        token.SrcLine = lindex + 1;
                        saTokens.Add(token);
                    }
                }

                ++lindex;
            }

            return( saTokens );
        }
    }


}

/*
aaa bbb ccc
a b c d ;agwio
1 2 3 4 
agw0
 
*/

