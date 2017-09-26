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
    public partial class frmMainForm : Form
    {
        public frmMainForm()
        {
            InitializeComponent();
        }

        private void miToMnemonic_Click(object sender, EventArgs e)
        {
            string buf;
            List<string> saTokens;


            buf = txtSourceCode.Text;

            // ここで成型
            saTokens = Tokenize(buf);

            // 再度並べ替え
            buf = "";
            foreach( string token in saTokens)
            {
                buf += token + "\r\n";
            }

            txtStatementList.Text = buf;

            tbpDebug.Select();
            tctlEditor.SelectTab(tbpDebug.Name);
        }

        // トークン化
        List<string> Tokenize(string sSrc)
        {
            string[] saSrc = sSrc.Split('\n','\r');
            string sStream = "";
            var saTokens = new List<string> ();

            // コメントと改行文字を1文字の空白へ置き換え
            foreach ( string sLine in saSrc )
            {
                int posdeli = sLine.IndexOf(';');

                if( posdeli < 0 )
                {
                    // 見つからなかった
                    sStream += sLine + " ";
                }
                else
                {
                    // １文字の空白文字として置換する
                    sStream += sLine.Substring(0, posdeli) + " ";
                }
            }

            // 空白区切りで文字列配列に変換
            // todo:区切り条件を空白から文字種別に切り替える
            bool bWord = false;
            int posStart = 0, posDelim = 0;
            for ( posStart = posDelim = 0; posDelim < sStream.Length; ++posDelim )
            {

                // その文字が
                switch( sStream[posDelim] )
                {
                    // 空白文字ならば
                    case '\x20':
                    case '\t':
             //     case '\r':
                        if( bWord )
                        {
                            // 単語から空白へ → トークン切り出し
                            string token = sStream.Substring(posStart, posDelim - posStart);
                            saTokens.Add( token );

                            bWord = false;
                        }
                        break;
                    default:
                        if(!bWord)
                        {
                            posStart = posDelim;
                            bWord = true;
                        }
                        break;
                }
            }

            // 行末まで単語が続いていた場合の処理
            if( bWord )
            {
                // 残りすべてを取得
                string token = sStream.Substring(posStart);
                saTokens.Add(token);
            }

            return( saTokens );
        }
    }


}
