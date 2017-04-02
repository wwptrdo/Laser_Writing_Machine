using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace 激光雕刻兼写字机上位机程序
{
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new programMain());
        }
    }
}
