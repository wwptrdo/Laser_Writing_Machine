namespace 激光雕刻兼写字机上位机程序
{
    partial class programMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.Increase_Y = new System.Windows.Forms.Button();
            this.Decrease_X = new System.Windows.Forms.Button();
            this.Increase_X = new System.Windows.Forms.Button();
            this.Decrease_Y = new System.Windows.Forms.Button();
            this.Increase_Z = new System.Windows.Forms.Button();
            this.Decrease_Z = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.OpenLaser = new System.Windows.Forms.Button();
            this.CloseLaser = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.cboCOM = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.cboBaudRate = new System.Windows.Forms.ComboBox();
            this.cboCheckBit = new System.Windows.Forms.ComboBox();
            this.cboDataBit = new System.Windows.Forms.ComboBox();
            this.cboStopBit = new System.Windows.Forms.ComboBox();
            this.OpenCOM = new System.Windows.Forms.Button();
            this.CloseCOM = new System.Windows.Forms.Button();
            this.ReceiveText = new System.Windows.Forms.TextBox();
            this.shapeContainer1 = new Microsoft.VisualBasic.PowerPacks.ShapeContainer();
            this.lineShape3 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.ball = new Microsoft.VisualBasic.PowerPacks.OvalShape();
            this.lineShape2 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.lineShape1 = new Microsoft.VisualBasic.PowerPacks.LineShape();
            this.label10 = new System.Windows.Forms.Label();
            this.SendText = new System.Windows.Forms.TextBox();
            this.Send = new System.Windows.Forms.Button();
            this.com = new System.IO.Ports.SerialPort(this.components);
            this.label11 = new System.Windows.Forms.Label();
            this.tbxpath = new System.Windows.Forms.TextBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.lblLine = new System.Windows.Forms.Label();
            this.lblSendedLine = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(544, 25);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(159, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "显示下位机反馈信息：";
            // 
            // Increase_Y
            // 
            this.Increase_Y.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Increase_Y.Location = new System.Drawing.Point(125, 359);
            this.Increase_Y.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Increase_Y.Name = "Increase_Y";
            this.Increase_Y.Size = new System.Drawing.Size(100, 41);
            this.Increase_Y.TabIndex = 2;
            this.Increase_Y.Text = "Y轴+";
            this.Increase_Y.UseVisualStyleBackColor = true;
            this.Increase_Y.Click += new System.EventHandler(this.Increase_Y_Click);
            // 
            // Decrease_X
            // 
            this.Decrease_X.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Decrease_X.Location = new System.Drawing.Point(19, 399);
            this.Decrease_X.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Decrease_X.Name = "Decrease_X";
            this.Decrease_X.Size = new System.Drawing.Size(100, 41);
            this.Decrease_X.TabIndex = 3;
            this.Decrease_X.Text = "X轴- ";
            this.Decrease_X.UseVisualStyleBackColor = true;
            this.Decrease_X.Click += new System.EventHandler(this.Decrease_X_Click);
            // 
            // Increase_X
            // 
            this.Increase_X.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Increase_X.Location = new System.Drawing.Point(233, 399);
            this.Increase_X.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Increase_X.Name = "Increase_X";
            this.Increase_X.Size = new System.Drawing.Size(100, 41);
            this.Increase_X.TabIndex = 4;
            this.Increase_X.Text = "X轴+";
            this.Increase_X.UseVisualStyleBackColor = true;
            this.Increase_X.Click += new System.EventHandler(this.Increase_X_Click);
            // 
            // Decrease_Y
            // 
            this.Decrease_Y.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Decrease_Y.Location = new System.Drawing.Point(127, 441);
            this.Decrease_Y.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Decrease_Y.Name = "Decrease_Y";
            this.Decrease_Y.Size = new System.Drawing.Size(100, 41);
            this.Decrease_Y.TabIndex = 5;
            this.Decrease_Y.Text = "Y轴-";
            this.Decrease_Y.UseVisualStyleBackColor = true;
            this.Decrease_Y.Click += new System.EventHandler(this.Decrease_Y_Click);
            // 
            // Increase_Z
            // 
            this.Increase_Z.BackColor = System.Drawing.Color.Gainsboro;
            this.Increase_Z.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Increase_Z.Location = new System.Drawing.Point(376, 359);
            this.Increase_Z.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Increase_Z.Name = "Increase_Z";
            this.Increase_Z.Size = new System.Drawing.Size(100, 41);
            this.Increase_Z.TabIndex = 6;
            this.Increase_Z.Text = "Z轴+";
            this.Increase_Z.UseVisualStyleBackColor = false;
            this.Increase_Z.Click += new System.EventHandler(this.Increase_Z_Click);
            // 
            // Decrease_Z
            // 
            this.Decrease_Z.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Decrease_Z.Location = new System.Drawing.Point(376, 441);
            this.Decrease_Z.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Decrease_Z.Name = "Decrease_Z";
            this.Decrease_Z.Size = new System.Drawing.Size(100, 41);
            this.Decrease_Z.TabIndex = 7;
            this.Decrease_Z.Text = "Z轴-";
            this.Decrease_Z.UseVisualStyleBackColor = true;
            this.Decrease_Z.Click += new System.EventHandler(this.Decrease_Z_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(355, 329);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(148, 20);
            this.label2.TabIndex = 8;
            this.label2.Text = "调节Z轴(单位毫米)：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(16, 329);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(188, 20);
            this.label3.TabIndex = 9;
            this.label3.Text = "调节X轴和Y轴(单位毫米)：";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(125, 408);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(99, 25);
            this.textBox1.TabIndex = 10;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(376, 408);
            this.textBox2.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(99, 25);
            this.textBox2.TabIndex = 11;
            // 
            // OpenLaser
            // 
            this.OpenLaser.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.OpenLaser.Location = new System.Drawing.Point(127, 559);
            this.OpenLaser.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.OpenLaser.Name = "OpenLaser";
            this.OpenLaser.Size = new System.Drawing.Size(100, 48);
            this.OpenLaser.TabIndex = 12;
            this.OpenLaser.Text = "激光打开";
            this.OpenLaser.UseVisualStyleBackColor = true;
            this.OpenLaser.Click += new System.EventHandler(this.OpenLaser_Click);
            // 
            // CloseLaser
            // 
            this.CloseLaser.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CloseLaser.Location = new System.Drawing.Point(313, 559);
            this.CloseLaser.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.CloseLaser.Name = "CloseLaser";
            this.CloseLaser.Size = new System.Drawing.Size(100, 48);
            this.CloseLaser.TabIndex = 13;
            this.CloseLaser.Text = "激光关闭";
            this.CloseLaser.UseVisualStyleBackColor = true;
            this.CloseLaser.Click += new System.EventHandler(this.CloseLaser_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(20, 528);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(112, 15);
            this.label4.TabIndex = 14;
            this.label4.Text = "测试激光状态：";
            // 
            // cboCOM
            // 
            this.cboCOM.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboCOM.FormattingEnabled = true;
            this.cboCOM.Location = new System.Drawing.Point(83, 15);
            this.cboCOM.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboCOM.Name = "cboCOM";
            this.cboCOM.Size = new System.Drawing.Size(160, 28);
            this.cboCOM.TabIndex = 15;
            this.cboCOM.SelectedIndexChanged += new System.EventHandler(this.cboCOM_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(20, 15);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(54, 20);
            this.label5.TabIndex = 16;
            this.label5.Text = "串口：";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(16, 56);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(69, 20);
            this.label6.TabIndex = 17;
            this.label6.Text = "波特率：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(16, 91);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 20);
            this.label7.TabIndex = 18;
            this.label7.Text = "校验位：";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(16, 131);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 20);
            this.label8.TabIndex = 19;
            this.label8.Text = "数据位：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.Location = new System.Drawing.Point(16, 176);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(69, 20);
            this.label9.TabIndex = 20;
            this.label9.Text = "停止位：";
            // 
            // cboBaudRate
            // 
            this.cboBaudRate.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboBaudRate.FormattingEnabled = true;
            this.cboBaudRate.Location = new System.Drawing.Point(83, 52);
            this.cboBaudRate.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboBaudRate.Name = "cboBaudRate";
            this.cboBaudRate.Size = new System.Drawing.Size(160, 28);
            this.cboBaudRate.TabIndex = 21;
            this.cboBaudRate.Text = "9600";
            this.cboBaudRate.SelectedIndexChanged += new System.EventHandler(this.cboBaudRate_SelectedIndexChanged);
            // 
            // cboCheckBit
            // 
            this.cboCheckBit.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboCheckBit.FormattingEnabled = true;
            this.cboCheckBit.Location = new System.Drawing.Point(83, 91);
            this.cboCheckBit.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboCheckBit.Name = "cboCheckBit";
            this.cboCheckBit.Size = new System.Drawing.Size(160, 28);
            this.cboCheckBit.TabIndex = 22;
            this.cboCheckBit.Text = "None";
            this.cboCheckBit.SelectedIndexChanged += new System.EventHandler(this.cboCheckBit_SelectedIndexChanged);
            // 
            // cboDataBit
            // 
            this.cboDataBit.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboDataBit.FormattingEnabled = true;
            this.cboDataBit.Location = new System.Drawing.Point(83, 131);
            this.cboDataBit.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboDataBit.Name = "cboDataBit";
            this.cboDataBit.Size = new System.Drawing.Size(160, 28);
            this.cboDataBit.TabIndex = 23;
            this.cboDataBit.Text = "8";
            this.cboDataBit.SelectedIndexChanged += new System.EventHandler(this.cboDataBit_SelectedIndexChanged);
            // 
            // cboStopBit
            // 
            this.cboStopBit.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cboStopBit.FormattingEnabled = true;
            this.cboStopBit.Location = new System.Drawing.Point(83, 176);
            this.cboStopBit.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.cboStopBit.Name = "cboStopBit";
            this.cboStopBit.Size = new System.Drawing.Size(160, 28);
            this.cboStopBit.TabIndex = 24;
            this.cboStopBit.Text = "1";
            this.cboStopBit.SelectedIndexChanged += new System.EventHandler(this.cboStopBit_SelectedIndexChanged);
            // 
            // OpenCOM
            // 
            this.OpenCOM.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.OpenCOM.Location = new System.Drawing.Point(127, 225);
            this.OpenCOM.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.OpenCOM.Name = "OpenCOM";
            this.OpenCOM.Size = new System.Drawing.Size(117, 61);
            this.OpenCOM.TabIndex = 25;
            this.OpenCOM.Text = "打开串口";
            this.OpenCOM.UseVisualStyleBackColor = true;
            this.OpenCOM.Click += new System.EventHandler(this.OpenCOM_Click);
            // 
            // CloseCOM
            // 
            this.CloseCOM.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.CloseCOM.Location = new System.Drawing.Point(125, 225);
            this.CloseCOM.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.CloseCOM.Name = "CloseCOM";
            this.CloseCOM.Size = new System.Drawing.Size(119, 61);
            this.CloseCOM.TabIndex = 26;
            this.CloseCOM.Text = "关闭串口";
            this.CloseCOM.UseVisualStyleBackColor = true;
            this.CloseCOM.Visible = false;
            this.CloseCOM.Click += new System.EventHandler(this.CloseCOM_Click);
            // 
            // ReceiveText
            // 
            this.ReceiveText.BackColor = System.Drawing.Color.White;
            this.ReceiveText.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReceiveText.Location = new System.Drawing.Point(556, 53);
            this.ReceiveText.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.ReceiveText.Multiline = true;
            this.ReceiveText.Name = "ReceiveText";
            this.ReceiveText.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.ReceiveText.Size = new System.Drawing.Size(525, 229);
            this.ReceiveText.TabIndex = 27;
            // 
            // shapeContainer1
            // 
            this.shapeContainer1.Location = new System.Drawing.Point(0, 0);
            this.shapeContainer1.Margin = new System.Windows.Forms.Padding(0);
            this.shapeContainer1.Name = "shapeContainer1";
            this.shapeContainer1.Shapes.AddRange(new Microsoft.VisualBasic.PowerPacks.Shape[] {
            this.lineShape3,
            this.ball,
            this.lineShape2,
            this.lineShape1});
            this.shapeContainer1.Size = new System.Drawing.Size(1083, 769);
            this.shapeContainer1.TabIndex = 28;
            this.shapeContainer1.TabStop = false;
            // 
            // lineShape3
            // 
            this.lineShape3.Name = "lineShape3";
            this.lineShape3.X1 = -8;
            this.lineShape3.X2 = 516;
            this.lineShape3.Y1 = 508;
            this.lineShape3.Y2 = 510;
            // 
            // ball
            // 
            this.ball.BackColor = System.Drawing.Color.Lime;
            this.ball.BackStyle = Microsoft.VisualBasic.PowerPacks.BackStyle.Opaque;
            this.ball.BorderColor = System.Drawing.Color.Black;
            this.ball.FillColor = System.Drawing.Color.SaddleBrown;
            this.ball.FillStyle = Microsoft.VisualBasic.PowerPacks.FillStyle.Solid;
            this.ball.Location = new System.Drawing.Point(52, 244);
            this.ball.Name = "ball";
            this.ball.Size = new System.Drawing.Size(30, 30);
            // 
            // lineShape2
            // 
            this.lineShape2.Name = "lineShape2";
            this.lineShape2.X1 = 516;
            this.lineShape2.X2 = 518;
            this.lineShape2.Y1 = -2;
            this.lineShape2.Y2 = 770;
            // 
            // lineShape1
            // 
            this.lineShape1.Name = "lineShape1";
            this.lineShape1.X1 = -2;
            this.lineShape1.X2 = 1080;
            this.lineShape1.Y1 = 314;
            this.lineShape1.Y2 = 316;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label10.Location = new System.Drawing.Point(544, 329);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(320, 20);
            this.label10.TabIndex = 29;
            this.label10.Text = "要发送到下位机的数据（可发送多行G代码）：";
            // 
            // SendText
            // 
            this.SendText.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SendText.Location = new System.Drawing.Point(548, 359);
            this.SendText.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.SendText.Multiline = true;
            this.SendText.Name = "SendText";
            this.SendText.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.SendText.Size = new System.Drawing.Size(533, 249);
            this.SendText.TabIndex = 30;
            this.SendText.TextChanged += new System.EventHandler(this.SendText_TextChanged);
            // 
            // Send
            // 
            this.Send.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Send.Location = new System.Drawing.Point(943, 638);
            this.Send.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Send.Name = "Send";
            this.Send.Size = new System.Drawing.Size(132, 85);
            this.Send.TabIndex = 31;
            this.Send.Text = "发送：";
            this.Send.UseVisualStyleBackColor = true;
            this.Send.Click += new System.EventHandler(this.Send_Click);
            // 
            // com
            // 
            this.com.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.com_DataReceived);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label11.Location = new System.Drawing.Point(544, 638);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(342, 20);
            this.label11.TabIndex = 32;
            this.label11.Text = "请输入要雕刻的文件路径：（例如：F:\\hello.txt）";
            // 
            // tbxpath
            // 
            this.tbxpath.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbxpath.Location = new System.Drawing.Point(548, 674);
            this.tbxpath.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.tbxpath.Name = "tbxpath";
            this.tbxpath.Size = new System.Drawing.Size(181, 27);
            this.tbxpath.TabIndex = 33;
            // 
            // btnOK
            // 
            this.btnOK.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnOK.Location = new System.Drawing.Point(776, 671);
            this.btnOK.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(84, 29);
            this.btnOK.TabIndex = 34;
            this.btnOK.Text = "确定";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // lblLine
            // 
            this.lblLine.AutoSize = true;
            this.lblLine.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblLine.Location = new System.Drawing.Point(544, 712);
            this.lblLine.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblLine.Name = "lblLine";
            this.lblLine.Size = new System.Drawing.Size(66, 20);
            this.lblLine.TabIndex = 35;
            this.lblLine.Text = "一共   行";
            // 
            // lblSendedLine
            // 
            this.lblSendedLine.AutoSize = true;
            this.lblSendedLine.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSendedLine.Location = new System.Drawing.Point(640, 712);
            this.lblSendedLine.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSendedLine.Name = "lblSendedLine";
            this.lblSendedLine.Size = new System.Drawing.Size(81, 20);
            this.lblSendedLine.TabIndex = 36;
            this.lblSendedLine.Text = "已发送   行";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label12.Location = new System.Drawing.Point(4, 644);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(442, 100);
            this.label12.TabIndex = 37;
            this.label12.Text = "注意：(1)本程序仅为调试版本，为保证程序稳定，使用单线程，\n         所以在雕刻时，出现卡顿现象，属正常现象(代码未修复)\n      (2)本程序串口" +
                "部分开启已是默认值，更改无效（代码未修复）\n      (3)调节轴部分不可用。（代码未添加）\n      (4)本程序仅实现最基本功能。;";
            // 
            // programMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.SkyBlue;
            this.ClientSize = new System.Drawing.Size(1083, 769);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.lblSendedLine);
            this.Controls.Add(this.lblLine);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.tbxpath);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.Send);
            this.Controls.Add(this.SendText);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.ReceiveText);
            this.Controls.Add(this.CloseCOM);
            this.Controls.Add(this.OpenCOM);
            this.Controls.Add(this.cboStopBit);
            this.Controls.Add(this.cboDataBit);
            this.Controls.Add(this.cboCheckBit);
            this.Controls.Add(this.cboBaudRate);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.cboCOM);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.CloseLaser);
            this.Controls.Add(this.OpenLaser);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Decrease_Z);
            this.Controls.Add(this.Increase_Z);
            this.Controls.Add(this.Decrease_Y);
            this.Controls.Add(this.Increase_X);
            this.Controls.Add(this.Decrease_X);
            this.Controls.Add(this.Increase_Y);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.shapeContainer1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "programMain";
            this.Text = "激光雕刻兼写字机上位机程序（侧耳倾听 制作）";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.programMain_FormClosing);
            this.Load += new System.EventHandler(this.programMain_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button Increase_Y;
        private System.Windows.Forms.Button Decrease_X;
        private System.Windows.Forms.Button Increase_X;
        private System.Windows.Forms.Button Decrease_Y;
        private System.Windows.Forms.Button Increase_Z;
        private System.Windows.Forms.Button Decrease_Z;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button OpenLaser;
        private System.Windows.Forms.Button CloseLaser;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboCOM;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox cboBaudRate;
        private System.Windows.Forms.ComboBox cboCheckBit;
        private System.Windows.Forms.ComboBox cboDataBit;
        private System.Windows.Forms.ComboBox cboStopBit;
        private System.Windows.Forms.Button OpenCOM;
        private System.Windows.Forms.Button CloseCOM;
        private System.Windows.Forms.TextBox ReceiveText;
        private Microsoft.VisualBasic.PowerPacks.ShapeContainer shapeContainer1;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape1;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape2;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox SendText;
        private System.Windows.Forms.Button Send;
        private Microsoft.VisualBasic.PowerPacks.OvalShape ball;
        private System.IO.Ports.SerialPort com;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox tbxpath;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label lblLine;
        private System.Windows.Forms.Label lblSendedLine;
        private Microsoft.VisualBasic.PowerPacks.LineShape lineShape3;
        private System.Windows.Forms.Label label12;
       
    }
}

