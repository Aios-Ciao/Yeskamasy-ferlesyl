namespace interpreter
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.ファイルToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.デバッグToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tctlEditor = new System.Windows.Forms.TabControl();
            this.tbpDebug = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.splitContainer3 = new System.Windows.Forms.SplitContainer();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.lstLabelSymbol = new System.Windows.Forms.ListBox();
            this.txtStatementList = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.txtDebugConsole = new System.Windows.Forms.TextBox();
            this.splitContainer4 = new System.Windows.Forms.SplitContainer();
            this.dgvRegisters = new System.Windows.Forms.DataGridView();
            this.clRegister = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.clRegValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.dgvMemView = new System.Windows.Forms.DataGridView();
            this.clAddr = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.値 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tbpEdit = new System.Windows.Forms.TabPage();
            this.txtSourceCode = new System.Windows.Forms.TextBox();
            this.splitContainer5 = new System.Windows.Forms.SplitContainer();
            this.txtEditConsole = new System.Windows.Forms.TextBox();
            this.menuStrip1.SuspendLayout();
            this.tctlEditor.SuspendLayout();
            this.tbpDebug.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).BeginInit();
            this.splitContainer3.Panel1.SuspendLayout();
            this.splitContainer3.Panel2.SuspendLayout();
            this.splitContainer3.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).BeginInit();
            this.splitContainer4.Panel1.SuspendLayout();
            this.splitContainer4.Panel2.SuspendLayout();
            this.splitContainer4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMemView)).BeginInit();
            this.tbpEdit.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).BeginInit();
            this.splitContainer5.Panel1.SuspendLayout();
            this.splitContainer5.Panel2.SuspendLayout();
            this.splitContainer5.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ファイルToolStripMenuItem,
            this.デバッグToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(745, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // ファイルToolStripMenuItem
            // 
            this.ファイルToolStripMenuItem.Name = "ファイルToolStripMenuItem";
            this.ファイルToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.ファイルToolStripMenuItem.Text = "ファイル";
            // 
            // デバッグToolStripMenuItem
            // 
            this.デバッグToolStripMenuItem.Name = "デバッグToolStripMenuItem";
            this.デバッグToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
            this.デバッグToolStripMenuItem.Text = "デバッグ";
            // 
            // tctlEditor
            // 
            this.tctlEditor.Controls.Add(this.tbpEdit);
            this.tctlEditor.Controls.Add(this.tbpDebug);
            this.tctlEditor.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tctlEditor.Location = new System.Drawing.Point(0, 24);
            this.tctlEditor.Name = "tctlEditor";
            this.tctlEditor.SelectedIndex = 0;
            this.tctlEditor.Size = new System.Drawing.Size(745, 502);
            this.tctlEditor.TabIndex = 1;
            // 
            // tbpDebug
            // 
            this.tbpDebug.Controls.Add(this.splitContainer1);
            this.tbpDebug.Location = new System.Drawing.Point(4, 22);
            this.tbpDebug.Name = "tbpDebug";
            this.tbpDebug.Padding = new System.Windows.Forms.Padding(3);
            this.tbpDebug.Size = new System.Drawing.Size(737, 476);
            this.tbpDebug.TabIndex = 0;
            this.tbpDebug.Text = "Debug";
            this.tbpDebug.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer4);
            this.splitContainer1.Size = new System.Drawing.Size(731, 470);
            this.splitContainer1.SplitterDistance = 544;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer2
            // 
            this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.splitContainer3);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.tableLayoutPanel2);
            this.splitContainer2.Size = new System.Drawing.Size(544, 470);
            this.splitContainer2.SplitterDistance = 349;
            this.splitContainer2.TabIndex = 0;
            // 
            // splitContainer3
            // 
            this.splitContainer3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer3.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer3.Location = new System.Drawing.Point(0, 0);
            this.splitContainer3.Name = "splitContainer3";
            // 
            // splitContainer3.Panel1
            // 
            this.splitContainer3.Panel1.Controls.Add(this.tableLayoutPanel1);
            // 
            // splitContainer3.Panel2
            // 
            this.splitContainer3.Panel2.Controls.Add(this.txtStatementList);
            this.splitContainer3.Size = new System.Drawing.Size(540, 345);
            this.splitContainer3.SplitterDistance = 130;
            this.splitContainer3.TabIndex = 0;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.lstLabelSymbol, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(130, 345);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "ラベル一覧";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lstLabelSymbol
            // 
            this.lstLabelSymbol.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstLabelSymbol.Font = new System.Drawing.Font("ＭＳ ゴシック", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.lstLabelSymbol.FormattingEnabled = true;
            this.lstLabelSymbol.ItemHeight = 12;
            this.lstLabelSymbol.Location = new System.Drawing.Point(3, 23);
            this.lstLabelSymbol.Name = "lstLabelSymbol";
            this.lstLabelSymbol.Size = new System.Drawing.Size(124, 319);
            this.lstLabelSymbol.TabIndex = 1;
            // 
            // txtStatementList
            // 
            this.txtStatementList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtStatementList.Font = new System.Drawing.Font("ＭＳ ゴシック", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.txtStatementList.Location = new System.Drawing.Point(0, 0);
            this.txtStatementList.Multiline = true;
            this.txtStatementList.Name = "txtStatementList";
            this.txtStatementList.Size = new System.Drawing.Size(406, 345);
            this.txtStatementList.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.AutoSize = true;
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.txtDebugConsole, 0, 1);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(540, 113);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // txtDebugConsole
            // 
            this.txtDebugConsole.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtDebugConsole.Location = new System.Drawing.Point(3, 3);
            this.txtDebugConsole.Multiline = true;
            this.txtDebugConsole.Name = "txtDebugConsole";
            this.txtDebugConsole.Size = new System.Drawing.Size(534, 107);
            this.txtDebugConsole.TabIndex = 0;
            this.txtDebugConsole.Text = ">";
            // 
            // splitContainer4
            // 
            this.splitContainer4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer4.Location = new System.Drawing.Point(0, 0);
            this.splitContainer4.Name = "splitContainer4";
            this.splitContainer4.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer4.Panel1
            // 
            this.splitContainer4.Panel1.Controls.Add(this.dgvRegisters);
            // 
            // splitContainer4.Panel2
            // 
            this.splitContainer4.Panel2.Controls.Add(this.dgvMemView);
            this.splitContainer4.Size = new System.Drawing.Size(179, 466);
            this.splitContainer4.SplitterDistance = 294;
            this.splitContainer4.TabIndex = 0;
            // 
            // dgvRegisters
            // 
            this.dgvRegisters.AllowUserToAddRows = false;
            this.dgvRegisters.AllowUserToDeleteRows = false;
            this.dgvRegisters.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvRegisters.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.clRegister,
            this.clRegValue});
            this.dgvRegisters.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvRegisters.Enabled = false;
            this.dgvRegisters.Location = new System.Drawing.Point(0, 0);
            this.dgvRegisters.MultiSelect = false;
            this.dgvRegisters.Name = "dgvRegisters";
            this.dgvRegisters.RowHeadersVisible = false;
            this.dgvRegisters.RowTemplate.Height = 21;
            this.dgvRegisters.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dgvRegisters.Size = new System.Drawing.Size(179, 294);
            this.dgvRegisters.TabIndex = 0;
            // 
            // clRegister
            // 
            this.clRegister.HeaderText = "レジスタ";
            this.clRegister.Name = "clRegister";
            this.clRegister.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            this.clRegister.Width = 80;
            // 
            // clRegValue
            // 
            this.clRegValue.HeaderText = "データ";
            this.clRegValue.Name = "clRegValue";
            this.clRegValue.Resizable = System.Windows.Forms.DataGridViewTriState.False;
            // 
            // dgvMemView
            // 
            this.dgvMemView.AllowUserToAddRows = false;
            this.dgvMemView.AllowUserToDeleteRows = false;
            this.dgvMemView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvMemView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.clAddr,
            this.値});
            this.dgvMemView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvMemView.Location = new System.Drawing.Point(0, 0);
            this.dgvMemView.Name = "dgvMemView";
            this.dgvMemView.RowHeadersVisible = false;
            this.dgvMemView.RowTemplate.Height = 21;
            this.dgvMemView.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dgvMemView.Size = new System.Drawing.Size(179, 168);
            this.dgvMemView.TabIndex = 0;
            // 
            // clAddr
            // 
            this.clAddr.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.None;
            this.clAddr.Frozen = true;
            this.clAddr.HeaderText = "アドレス";
            this.clAddr.Name = "clAddr";
            this.clAddr.ReadOnly = true;
            this.clAddr.Width = 80;
            // 
            // 値
            // 
            this.値.Frozen = true;
            this.値.HeaderText = "データ";
            this.値.Name = "値";
            // 
            // tbpEdit
            // 
            this.tbpEdit.Controls.Add(this.splitContainer5);
            this.tbpEdit.Location = new System.Drawing.Point(4, 22);
            this.tbpEdit.Name = "tbpEdit";
            this.tbpEdit.Padding = new System.Windows.Forms.Padding(3);
            this.tbpEdit.Size = new System.Drawing.Size(737, 476);
            this.tbpEdit.TabIndex = 1;
            this.tbpEdit.Text = "Edit";
            this.tbpEdit.UseVisualStyleBackColor = true;
            // 
            // txtSourceCode
            // 
            this.txtSourceCode.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtSourceCode.Location = new System.Drawing.Point(0, 0);
            this.txtSourceCode.Multiline = true;
            this.txtSourceCode.Name = "txtSourceCode";
            this.txtSourceCode.Size = new System.Drawing.Size(731, 323);
            this.txtSourceCode.TabIndex = 0;
            // 
            // splitContainer5
            // 
            this.splitContainer5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer5.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer5.Location = new System.Drawing.Point(3, 3);
            this.splitContainer5.Name = "splitContainer5";
            this.splitContainer5.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer5.Panel1
            // 
            this.splitContainer5.Panel1.Controls.Add(this.txtSourceCode);
            // 
            // splitContainer5.Panel2
            // 
            this.splitContainer5.Panel2.Controls.Add(this.txtEditConsole);
            this.splitContainer5.Size = new System.Drawing.Size(731, 470);
            this.splitContainer5.SplitterDistance = 323;
            this.splitContainer5.TabIndex = 1;
            // 
            // txtEditConsole
            // 
            this.txtEditConsole.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtEditConsole.Location = new System.Drawing.Point(0, 0);
            this.txtEditConsole.Multiline = true;
            this.txtEditConsole.Name = "txtEditConsole";
            this.txtEditConsole.Size = new System.Drawing.Size(731, 143);
            this.txtEditConsole.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(745, 526);
            this.Controls.Add(this.tctlEditor);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Yeskamasy-ferlesyl";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tctlEditor.ResumeLayout(false);
            this.tbpDebug.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.splitContainer3.Panel1.ResumeLayout(false);
            this.splitContainer3.Panel2.ResumeLayout(false);
            this.splitContainer3.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer3)).EndInit();
            this.splitContainer3.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.splitContainer4.Panel1.ResumeLayout(false);
            this.splitContainer4.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer4)).EndInit();
            this.splitContainer4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvRegisters)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvMemView)).EndInit();
            this.tbpEdit.ResumeLayout(false);
            this.splitContainer5.Panel1.ResumeLayout(false);
            this.splitContainer5.Panel1.PerformLayout();
            this.splitContainer5.Panel2.ResumeLayout(false);
            this.splitContainer5.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer5)).EndInit();
            this.splitContainer5.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem ファイルToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem デバッグToolStripMenuItem;
        private System.Windows.Forms.TabControl tctlEditor;
        private System.Windows.Forms.TabPage tbpDebug;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.SplitContainer splitContainer3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox lstLabelSymbol;
        private System.Windows.Forms.TextBox txtStatementList;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TextBox txtDebugConsole;
        private System.Windows.Forms.DataGridView dgvMemView;
        private System.Windows.Forms.TabPage tbpEdit;
        private System.Windows.Forms.SplitContainer splitContainer4;
        private System.Windows.Forms.DataGridView dgvRegisters;
        private System.Windows.Forms.DataGridViewTextBoxColumn clRegister;
        private System.Windows.Forms.DataGridViewTextBoxColumn clRegValue;
        private System.Windows.Forms.DataGridViewTextBoxColumn clAddr;
        private System.Windows.Forms.DataGridViewTextBoxColumn 値;
        private System.Windows.Forms.SplitContainer splitContainer5;
        private System.Windows.Forms.TextBox txtSourceCode;
        private System.Windows.Forms.TextBox txtEditConsole;
    }
}

