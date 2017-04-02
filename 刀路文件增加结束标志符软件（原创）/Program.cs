using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace 刀路文件增加结束标志符
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n\n\n\n\n\n");
            Console.WriteLine("\t              _______刀路文件处理（WhisperHear制作）___");
            Console.WriteLine("\t             |                                       |");
            Console.WriteLine("\t             |                                       |");
            Console.WriteLine("\t             |         在每一行G代码的后面增加         |");
            Console.WriteLine("\t             |         结束字符标志#                  |");
            Console.WriteLine("\t             |         并将刀路文件转换为txt文件       |");
            Console.WriteLine("\t             |                                       |");
            Console.WriteLine("\t             |_______________________________________|");
            Console.WriteLine("请输入路径和文件名（例如：F:\\hello.nc）：");

            try
            {
                string strPath = Console.ReadLine();
                string[] str1 = File.ReadAllLines(@strPath, Encoding.Default);
                for (int i = 0; i < str1.Length; i++)
                {
                    char[] s = new char[str1[i].Length + 1];
                    for (int j = 0; j < str1[i].Length; j++)  //自己写的字符串转字符数组的算法，系统提供的靠不住
                    {
                        s[j] = str1[i][j];
                    }
                    s[str1[i].Length] = '#';
                    str1[i] = new string(s);
                }

                strPath = Path.GetDirectoryName(strPath) + '\\' + Path.GetFileNameWithoutExtension(strPath) + ".txt";

                File.WriteAllLines(@strPath, str1);

                Console.WriteLine("转换完成，请在当前目录下查找该文件。");
                Console.WriteLine("按任意键退出...");
                Console.ReadKey();
            }
            catch
            {
                Console.WriteLine("输入的路径有误！请重启程序！");
				Console.ReadKey();

            }
        }
    }
}
