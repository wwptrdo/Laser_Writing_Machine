using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.IO;             //添加串口的命名空间

namespace 激光雕刻兼写字机上位机程序
{
    public partial class programMain : Form
    {

        //增加一个线程用于改变某个控件状态
        Thread th;

        //定义一个标志，判断有没有接受到数据
        private bool receiveOkFlag = false;   //默认没有接收到数据

        //定义一个标志，判断打印文件内容还是一行G代码
        private bool oneLineFlag = true;   //默认是一行G代码

        //定义一个字符串数组存储要发送的数据
        private string[] sendStr;

        //构造函数
        public programMain()
        {
            InitializeComponent();
        }

        //主窗口加载时的准备
        private void programMain_Load(object sender, EventArgs e)
        {
            //提供串口选择（当可用设备插入时才可用）
            string[] portName = SerialPort.GetPortNames();  //获取当前计算机的所有可用串口
            for (int i = 0; i < portName.Length; i++)
            {
                this.cboCOM.Items.Add(portName[i]);       //赋值给comBox控件
                this.cboCOM.SelectedItem = portName[i];   //默认控件选择的是当前的值
            }

            //提供可选择的波特率
            this.cboBaudRate.Items.Add(300);
            this.cboBaudRate.Items.Add(600);
            this.cboBaudRate.Items.Add(1200);
            this.cboBaudRate.Items.Add(2400);
            this.cboBaudRate.Items.Add(4800);
            this.cboBaudRate.Items.Add(9600);
            this.cboBaudRate.Items.Add(19200);
            this.cboBaudRate.Items.Add(38400);
            this.cboBaudRate.Items.Add(43000);
            this.cboBaudRate.Items.Add(56000);
            this.cboBaudRate.Items.Add(57600);
            this.cboBaudRate.Items.Add(115200);
            this.cboBaudRate.SelectedItem = 9600;   //控件默认选择为9600

            //提供可供选择的校验位
            this.cboCheckBit.Items.Add("None");
            this.cboCheckBit.Items.Add("Even");
            this.cboCheckBit.Items.Add("Odd");
            this.cboCheckBit.Items.Add("Mark");
            this.cboCheckBit.Items.Add("Space");
            this.cboCheckBit.SelectedItem = "None"; //控件的默认选择为None

            //提供可供选择的数据位
            this.cboDataBit.Items.Add(6);
            this.cboDataBit.Items.Add(7);
            this.cboDataBit.Items.Add(8);
            this.cboDataBit.SelectedItem = 8;       //控件的默认选择是8

            //提供可供选择的停止位
            this.cboStopBit.Items.Add("None");
            this.cboStopBit.Items.Add("One");
            this.cboStopBit.Items.Add("OnePointFive");
            this.cboStopBit.Items.Add("Two");
            this.cboStopBit.SelectedItem = "One";       //控件默认选择的是1

            //其他控件的初始化设置
            ball.FillColor = System.Drawing.Color.SaddleBrown;  //初始化将球的颜色设置为棕色的
            OpenCOM.Visible = true;                             //初始化隐藏打开串口    
            CloseCOM.Visible = false;                           //初始化显示关闭串口

        }

        //点击打开串口控件按钮
        private void OpenCOM_Click(object sender, EventArgs e)
        {
            try
            {
                //注意：此处需要维护代码输入
                com.PortName = cboCOM.SelectedItem.ToString();   //设置串口名
                com.BaudRate = (int)cboBaudRate.SelectedItem;    //设置比特率
                com.DataBits = (int)cboDataBit.SelectedItem;     //设置数据位
                switch (cboCheckBit.SelectedItem.ToString())     //设置校验位
                {
                    case "None": com.Parity = Parity.None;
                        break;
                    case "Even": com.Parity = Parity.Even;
                        break;
                    case "Odd": com.Parity = Parity.Odd;
                        break;
                    case "Mark": com.Parity = Parity.Mark;
                        break;
                    case "Space": com.Parity = Parity.Space;
                        break;
                    default: MessageBox.Show("校验位设置出错！请重新选择");
                        break;
                }
                switch (cboStopBit.SelectedItem.ToString())      //设置停止位
                {
                    case "One": com.StopBits = StopBits.One;
                        break;
                    case "Two": com.StopBits = StopBits.Two;
                        break;
                    case "None": com.StopBits = StopBits.None;
                        break;
                    case "OnePointFive": com.StopBits = StopBits.OnePointFive;
                        break;
                    default: MessageBox.Show("停止位设置出错！请重新选择");
                        break;
                }
                com.Open();     //打开串口
                OpenCOM.Visible = false;                      //隐藏打开串口    
                CloseCOM.Visible = true;                      //显示关闭串口
                ball.FillColor = System.Drawing.Color.Red;    //将球的颜色设置为红色的
            }
            catch
            {
                MessageBox.Show("串口打开失败！（有可能是停止位设置出错！）\n问题未解决，请联系作者。。。");
            }
        }

        //点击关闭串口控件按钮
        private void CloseCOM_Click(object sender, EventArgs e)
        {
            try
            {
                com.Close();           //关闭串口
                OpenCOM.Visible = true;          //隐藏打开串口    
                CloseCOM.Visible = false;        //显示关闭串口
                ball.FillColor = System.Drawing.Color.SaddleBrown;  //将球的颜色设置为棕色的
                ReceiveText.Clear();   //清除当前串口的内容
            }
            catch
            {
                MessageBox.Show("关闭串口失败！未知错误！");
            }
        }

        //点击打开激光的按钮
        private void OpenLaser_Click(object sender, EventArgs e)
        {
            if (receiveOkFlag == true)   //判断可不可以发送
            {
                SendData("M03#");   //发送这一行字符串
            }
            else
            {
                if (ball.BorderColor == System.Drawing.Color.Black)
                {
                    MessageBox.Show("串口没有打开，请打开串口继续操作...");
                }
                else
                {
                    MessageBox.Show("机器正在运作，请稍后...");
                }
            }
        }

        //点击关闭激光的按钮
        private void CloseLaser_Click(object sender, EventArgs e)
        {
            if (receiveOkFlag == true)   //判断可不可以发送
            {
                SendData("M05#");   //发送这一行字符串
            }
            else
            {
                if (ball.BorderColor == System.Drawing.Color.Black)
                {
                    MessageBox.Show("串口没有打开，请打开串口继续操作...");
                }
                else
                {
                    MessageBox.Show("机器正在运作，请稍后...");
                }
            }
        }



        private void Increase_Y_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Y轴增加了");
        }

        private void Decrease_Y_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Y轴减少了");
        }

        private void Increase_X_Click(object sender, EventArgs e)
        {
            MessageBox.Show("X轴增加了。");
        }

        private void Decrease_X_Click(object sender, EventArgs e)
        {
            MessageBox.Show("X轴减少了。");
        }

        private void Increase_Z_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Z轴增加了。");
        }

        private void Decrease_Z_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Z轴减少了。");
        }




        private void cboCOM_SelectedIndexChanged(object sender, EventArgs e)
        {
            //MessageBox.Show(cboCOM.SelectedItem.ToString());
        }

        private void cboBaudRate_SelectedIndexChanged(object sender, EventArgs e)
        {
            //ReceiveText.AppendText(cboBaudRate.SelectedItem.ToString());
        }

        private void cboCheckBit_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cboDataBit_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void cboStopBit_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void SendText_TextChanged(object sender, EventArgs e)
        {
            //string tempStr = SendText.Text;
            //sendStr = Encoding.Default.GetString();
        }





        //处理接收到数据这个事件
        private void com_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            #region  线程部分（已注释掉）
            //打印一行G代码
            //if (oneLineFlag == true)
            //{
            //    showEndFlag = false; //表示正在显示东西，不要乱动控件

            //    if (th == null)  //如果线程不存在
            //    {
            //        try
            //        {
            //            CreateNewThread();  //创建新线程,显示来自下位机的数据
            //        }
            //        catch
            //        {
            //            MessageBox.Show("创建新线程失败，请重试！(Error1)");
            //        }
            //    }
            //    if (th != null)       //如果线程已经存在
            //    {
            //        th.Abort();       //结束这个线程
            //        try
            //        {
            //            CreateNewThread();  //创建新线程，显示来自下位机的数据
            //        }
            //        catch
            //        {
            //            MessageBox.Show("创建新线程失败，请重试！(Error2)");
            //        }
            //    }
            //}
            ////如果打印多行G代码
            //if (oneLineFlag == false)
            //{
            //    ReceiveText.Text = "正在雕刻，请稍后...";
            //    showEndFlag = true;
            //}
            #endregion
            receiveOkFlag = true;  //表示接受到数据

            th = new Thread(ChangeShow);  //新线程调用方法

            Control.CheckForIllegalCrossThreadCalls = false;  //取消跨线程的访问

            th.Start();   //标记这个线程准备就绪了，可以随时被执行。具体什么时候执行这个线程，由cpu决定
            
        }
        
        //改变显示框中的内容
        private void ChangeShow()
        {
            ReceiveText.Text = "已完成操作，请发送G代码..."; 
        }

        #region 线程和委托部分函数（已注释掉）
        ////创建一个新线程
        //private void CreateNewThread()
        //{
        //    th = new Thread(Calldelegate);  //新线程调用委托方法
        //    //将线程设置为后台线程
        //    th.IsBackground = true;
        //    //取消跨线程的访问
        //    Control.CheckForIllegalCrossThreadCalls = false;
        //    //标记这个线程准备就绪了，可以随时被执行。具体什么时候执行这个线程，由cpu决定
        //    th.Start();
        //}

        ////声明委托
        //public delegate void ShowReceived_dl();

        ////新线程入口（调用委托）
        //private void Calldelegate()
        //{
        //    this.BeginInvoke(new ShowReceived_dl(Received));
        //}

        ////接收数据具体处理情况
        //private void Received()
        //{
        //    //当接受到数据的时候，把接受的数据显示到文本框中
        //    try
        //    {
        //        byte[] buffer = new byte[com.ReadBufferSize];   //开辟一个缓存空间（字节数组）
        //        com.Read(buffer, 0, buffer.Length);            //将从串口接受的数据放到缓存空间中
        //        string readStr = Encoding.Default.GetString(buffer);    //转码并将字节数组转换为字符串

        //        ReceiveText.AppendText(readStr);     //将字符串显示到文本框中

        //        th.Abort(); //关闭线程

        //        showEndFlag = true;   //显示内容结束，可以点击其他控件了
        //    }
        //    catch
        //    {
        //        ReceiveText.Text = "接收数据出错！！";
        //    }
        //}
        #endregion

        //当点击发送按钮的时候
        private void Send_Click(object sender, EventArgs e)
        {
            if (receiveOkFlag == false)
            {
                MessageBox.Show("机器正在运作，请稍后...");
            }
            //发送一行数据模式
            if (oneLineFlag == true && receiveOkFlag == true)  
            {
                string oneStr = SendText.Text;
                SendData(oneStr);                   //发送这一行字符串
            }
            //发送多行数据模式
            if (oneLineFlag == false && receiveOkFlag == true)
            {
                for (int i = 0; i < sendStr.Length; i++)
                {
                    lblSendedLine.Text = "已发送" + Convert.ToString(i + 1) + "行";
                    SendText.Text = sendStr[i];
                    while(receiveOkFlag == false);  //如果没有接收到数据，一直等待
                    if (sendStr[i] == "G0 Z2#")     //排除”文字转G代码“生成G代码个别类型
                    {
                        SendData("M05#");
                    }
                    else if (sendStr[i] == "G1 Z-1#")
                    {
                        SendData("M03#");
                    }
                    else if (sendStr[i] == "G1F30.000000#")  //排除“Inkscape软件”生成G代码个别类型
                    {
                        SendData("F30.00#");
                    }
                    //else if ((i + 5) > sendStr.Length)  //排除文字（同上）
                    //{
                    //    if (sendStr[i] == sendStr[i + 1] && sendStr[i] == sendStr[i + 2])
                    //    {
                    //        SendData("M05#" + " " + sendStr[i]);
                    //        break;
                    //    }
                    //}
                    else if (sendStr[i] == "M107#")   //排除“位图转G代码专用软件”G代码生成个别类型
                    {
                        SendData("M05#");
                    }
                    else if (sendStr[i] == "M106#")
                    {
                        SendData("M03#");
                    }
                    else
                    {
                        SendData(sendStr[i]);
                    }
                }
            }
        }

        //发送数据的基本插件
        private void SendData(string str)
        {
            //发送一个字符串
            receiveOkFlag = false;
            ReceiveText.Text = "正在处理G代码...";
            try
            {
                com.Write(str);
            }
            catch
            {
                MessageBox.Show("发送数据出错！ERROR!");
            }
        }

        //当点击确定按钮的时候
        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                string strPath = tbxpath.Text;        //用于保存路径
                sendStr = File.ReadAllLines(@strPath, Encoding.Default);  //将文件的内容复制到字符串数组中
                //for (int i = 0; i < sendStr.Length; i++)
                //{
                //    SendText.AppendText(sendStr[i] + '\n');
                //}
                SendText.Text = "已加载文件内容...";
                lblLine.Text = Convert.ToString(sendStr.Length) + "行";
                oneLineFlag = false;    //标志当前打印的是文件内容
            }
            catch
            {
                MessageBox.Show("您输入的路劲有错误，请重新输入！");
                tbxpath.Clear();
            }
        }

        //当点击“ X ”要关闭这个程序的时候
        private void programMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (th != null)   //判断后台线程有没有关闭
            {
                th.Abort();     //如果没有关闭，则关闭这个线程
            }
            if (ball.FillColor == System.Drawing.Color.Red) //如果还没有关闭串口，则关闭
            {
                try
                {
                    com.Close();
                }
                catch
                {
                    MessageBox.Show("错误！串口无法关闭！");
                }
            }
        }

    }
}
