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
            string[] saSrc;

            buf = txtSourceCode.Text;

            // ここで成型
            saSrc = buf.Split('\n');
            buf = Tokenize(saSrc);


            txtStatementList.Text = buf;

            tbpDebug.Select();
            tctlEditor.SelectTab(tbpDebug.Name);
        }

        // コメント除去
        string Tokenize(string [] saSrc)
        {
            string sResult = "";

            foreach( string sLine in saSrc )
            {
                int posdeli = sLine.IndexOf(';');

                // コメント開始文字以降を除去
                if( posdeli < 0 )
                {
                    // 見つからなかった
                    sResult += sLine + " ";
                }
                else
                {
                    // １文字の空白文字として置換する
                    sResult += sLine.Substring(0, posdeli) + " ";
                }
            }

            return( sResult );
        }
    }


}
