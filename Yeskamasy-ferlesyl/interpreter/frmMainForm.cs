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

            buf = txtSourceCode.Text;

            // ここで成型

            txtStatementList.Text = buf;

            tbpDebug.Select();
            tctlEditor.SelectTab(tbpDebug.Name);
        }
    }
}
