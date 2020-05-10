# 激光雕刻写字机器人
关键字：laser、sculpture、writing、C#、STC12c5a60s2

# 效果展示图片
图1（效果图）：

![效果图1](https://github.com/WhisperHear/Laser_Writing_Machine/blob/master/图片展示/running.jpg)

图2 (效果图)：

![效果图2](https://github.com/WhisperHear/Laser_Writing_Machine/blob/master/图片展示/demo.jpg)

图3 （上位机图片）：

![效果图2](https://github.com/WhisperHear/Laser_Writing_Machine/blob/master/图片展示/上位机图片.JPG)

图4 （刀路文件添加结束符程序图）：

![效果图2](https://github.com/WhisperHear/Laser_Writing_Machine/blob/master/图片展示/nc_files_change.jpg)

# 使用说明
## 一、需要的硬件部分：
#### 1、木质机架
#### 2、51单片机（STC12c5a60s2）开发板（带串口通信线）
#### 3、两个l298n步进机驱动
#### 4、两个2相4线步进电机 （带滑竿，距为3mm，步距角为18度，混合式）
#### 5、 250毫瓦的激光模组
#### 6、一个继电器
#### 7、电源部分
#### 8、杜邦线等其他部分

## 二、接线：
#### 所有的阵脚定义都在C源文件进行了说明，请按照源文件的注释说明进行接线。

#### （此处电路图丢失了喵~，大家只好看源码了呢~，过段时间在补充吧^.^）

## 三、下载下位机程序到单片机中
#### 请将下位机文件夹中的“激光雕刻兼写字机器下位机程序final测试版/激光雕刻兼写字机器下位机程序final_测试版.hex”文件下载到单片机中。

## 四、测试上位机程序
#### 说明：记得把单片机的串口连接到电脑上，如果串口驱动程序安装，上位机程序会自动检测该下位机串口。

## 五、开始激光写字
#### （0）确保上面的工作完成！
#### （1）生成刀路文件：首先用G代码生成软件，生成想要写的字的G代码文件（刀路文件）。
#### （2）处理刀路文件：打开刀路文件增加结束符标识软件，按照软件提示说明对步骤1中生成的刀路文件进行处理。
#### （3）打开上位机程序：首先打开串口。然后右下方选择刚刚处理过的刀路文件，点击发送即可开始打印。

# 原理介绍：
#### 简介：
该机器主要是建立一个二维的坐标系，通过数控机床的G代码作为改变坐标的介质。G代码中包括终点坐标和激光的移动方式（或者激光的关闭），激光的当前位置为起始坐标，当上位机程序（电脑）发送一行G代码到下位机（单片机）时，下位机程序解析出终点坐标和激光的移动方式，然后激光按照指定的路径开始移动，即可划出一条激光灼烧的路径。

#### 实现的G代码：
1、“G00  X10  Y10 ” 表示快速移动。即让激光从起始位置快速移动到终点坐标（10,10）点。2、 “G01   X20   Y20”表示直线插补。即让激光从现在的 位置以直线的方式移动到终点位置（20,   20）点。3、  “G02   X30   Y30”表示顺时针圆弧插补。即让激光从现在的位置以顺时针圆弧的方式移动到终点位置（30,    30）点。4、 “G03   X40   Y40”表示逆时针圆弧插补。即让激光从现在的位置以逆时针圆弧的方式移动到终点位置（40,    40）点。5、“M05 ”   表示关闭激光 。    （上位机中处理“Z2”也是关闭激光）6、 “M03”    表示打开激光 。    （上位机中处理“Z-1”是打开激光）7、 “F30”      表示移动速度。即激光的移动速度设置为30

#### 原理图：
![效果图2](https://github.com/WhisperHear/Laser_Writing_Machine/blob/master/图片展示/principle.png)


# Contact me 
#### If you have any questions, please contact me.
#### QQ: 1348351139
#### e-mail: wwptrdudu@gmail.com ; 1348351139@qq.com


