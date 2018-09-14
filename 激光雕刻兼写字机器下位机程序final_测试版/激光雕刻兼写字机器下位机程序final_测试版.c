/*
 * author: wwptrdudu <1348351139@qq.com>
 * github: https://github.com/wwptrdudu
 * tg: @wwptrdudu
 */


#include <reg52.h>
#include <math.h>

double x0 = 0, y0 = 0;    //起点坐标。表示当前激光所处的位置（定义的是全局变量，有风险。如果定义局部变量，需要二级指针，复杂些）
                          //令当前的激光的位置为(0, 0)点, 单片机复位需要手动调节激光位置到(0, 0)点	

double a, b;    		  //定义圆弧插补时的圆心（a, b）
							 
unsigned int Speed = 30;  //步进电机移动的速度, 初始化为30。 注意调速范围在delay函数中设置(当前是1~300)

double Length = 0.075;    //基本的步进长度（精度）, 设置为0.15mm(正好2拍), 为减少bug，设定为一次运动2拍

int moveFlag = 0;         //定义一个标志，判断是不是执行电机操作

sbit Laser = P3^7;        //定义激光打开的针脚

unsigned int xFlag = 7;   //标记X轴步进电机走到了第几拍, 初始值为第一拍
unsigned int yFlag = 6;   //标记Y轴步进电机走到了第几拍, 初始值为第一拍
		   
sbit Xa = P1^0;
sbit Xa_ = P1^1;
sbit Xb = P1^2;
sbit Xb_ = P1^3;

sbit Ya = P0^0;
sbit Ya_ = P0^1;
sbit Yb = P0^2;
sbit Yb_ = P0^3;


//串口的初始化 
void SerInit()
{	
	//对串行口控制寄存器(SCON)进行设置   
	SM0 = 0;           
	SM1 = 1;    //使串行口工作在方式一 
	REN = 1;    //允许接收数据  
	
	//对T1定时器设置
	TMOD = 0x20;  //T1的工作在方式二（对TMOD寄存器设置）	   
	TH1 = 0xfd;
	TL1 = 0xfd;   //设定比特率为9600
	TR1 = 1;      //启动定时器T1	
}


void delay() //步进电机调速
{	
	unsigned int x, j;       //脉冲频率中的延时函数中的变量
	for(j = 250; j >= Speed; j--)   //设置调速范围，请设置j变量
		for(x = 0; x <= 114; x++);	
}
//控制X轴正转
void xPositiveTurn(double length)
{
	while (1)
	{
		switch (xFlag)
		{
			case 1:
				   Xa = 1; Xa_ = 0; Xb = 0; Xb_ = 0; //第一拍
				   length = length - 0.075;
				   xFlag = 2;
				   delay();
				   if (length <= 0)
				   {
					   //Xa = 0;
					   return;
				   }
				   break;
			case 2:	   
					Xa = 1; Xa_ = 0; Xb = 1; Xb_ = 0; //第二拍
					length = length - 0.075;
					xFlag = 3;
					delay();
					if (length <= 0)
					{
						//Xa = 0; Xb = 0;
					    return;
					}
					break;
			 case 3:
					Xa = 0; Xa_ = 0; Xb = 1; Xb_ = 0; //第三拍
					length = length - 0.075;
					xFlag = 4;
					delay();
					if (length <= 0)
					{
						//Xb = 0;
					    return;
					}
					break;
			 case 4:
					Xa = 0; Xa_ = 1; Xb = 1; Xb_ = 0; //第四拍
					length = length - 0.075;
					xFlag = 5;
					delay();
					if (length <= 0)
					{
						//Xa_ = 0; Xb = 0;
					    return;
					}
					break;
			 case 5:
					Xa = 0; Xa_ = 1; Xb = 0; Xb_ = 0; //第五拍
					length = length - 0.075;
					xFlag = 6;
					delay();
					if (length <= 0)
					{
					    //Xa_ = 0;
					    return;
					}
					break;
			 case 6:
					Xa = 0; Xa_ = 1; Xb = 0; Xb_ = 1; //第六拍
					length = length - 0.075;
					xFlag = 7;
					delay();
					if (length <= 0)
					{
						//Xa_ = 0; Xb_ = 0;
					    return;
					}  
					break;
			 case 7:
					Xa = 0; Xa_ = 0; Xb = 0; Xb_ = 1; //第七拍
					length = length - 0.075;
					xFlag = 8;
					delay();
					if (length <= 0)
					{
						//Xb_ = 0;
						return;
					}
					break;
			 case 8:
					Xa = 1; Xa_ = 0; Xb = 0; Xb_ = 1; //第八拍
					length = length - 0.075;
					xFlag = 1;
					delay();
					if (length <= 0)
					{
						//Xa = 0; Xb_ = 0;
					    return;
					}
					break;
		}
	}
}
//控制X轴反转
void xReversalTurn(double length)
{
	while (1)
	{
		switch (xFlag)
		{
			case 1:
				   Xa = 1; Xa_ = 0; Xb = 0; Xb_ = 1; //第一拍
				   length = length - 0.075;
				   xFlag = 8;
				   delay();
				   if (length <= 0)
				   {
					   //Xa = 0; Xb_ = 0;
				       return;
				   }
				   break;
			case 8:
				   Xa = 0; Xa_ = 0; Xb = 0; Xb_ = 1; //第二拍
				   length = length - 0.075;
				   xFlag = 7;
				   delay();
				   if (length <= 0)
				   {
					   //Xb_ = 0;
				       return;
				   }
				   break;
			case 7:
				   Xa = 0; Xa_ = 1; Xb = 0; Xb_ = 1; //第三拍
				   length = length - 0.075;
				   xFlag = 6;
				   delay();
				   if (length <= 0)
				   {
				       //Xa_ = 0; Xb_ = 0;
				       return;
				   }
				   break;
			case 6:
				   Xa = 0; Xa_ = 1; Xb = 0; Xb_ = 0; //第四拍
				   length = length - 0.075;
				   xFlag = 5;
				   delay();
				   if (length <= 0)
				   {
					   //Xa_ = 0;
				       return;
				   }
				   break;
			case 5:
				   Xa = 0; Xa_ = 1; Xb = 1; Xb_ = 0; //第五拍
				   length = length - 0.075;
				   xFlag = 4;
				   delay();
				   if (length <= 0)
				   {
					   //Xa_ = 0; Xb = 0;
				       return;
				   }
				   break;
			case 4:
				   Xa = 0; Xa_ = 0; Xb = 1; Xb_ = 0; //第六拍
				   length = length - 0.075;
				   xFlag = 3;
				   delay();
			       if (length <= 0)
				   {
						//Xb = 0;
				        return;
				   }
				   break;
			case 3:
				   Xa = 1; Xa_ = 0; Xb = 1; Xb_ = 0; //第七拍
				   length = length - 0.075;
				   xFlag = 2;
				   delay();
				   if (length <= 0)
				   {
					   //Xa = 0; Xb = 0;
				       return;
				   }
				   break;
			case 2:
				   Xa = 1; Xa_ = 0; Xb = 0; Xb_ = 0; //第八拍
				   length = length - 0.075;
				   xFlag = 1;
				   delay();
				   if (length <= 0)
				   {
				       //Xa = 0;
				       return; 
				   }
				   break;
		}
	}
}
//控制Y轴正转
void yPositiveTurn(double length)
{
	while (1)
	{
		switch (yFlag)
		{
			case 1:
				   Ya = 1; Ya_ = 0; Yb = 0; Yb_ = 0; //第一拍
				   length = length - 0.075;
				   yFlag = 2;
				   delay();
				   if (length <= 0)
				   {
					   //Ya = 0;
					   return;
				   }
				   break;
			case 2:	   
					Ya = 1; Ya_ = 0; Yb = 1; Yb_ = 0; //第二拍
					length = length - 0.075;
					yFlag = 3;
					delay();
					if (length <= 0)
					{
						//Ya = 0; Yb = 0;
					    return;
					}
					break;
			 case 3:
					Ya = 0; Ya_ = 0; Yb = 1; Yb_ = 0; //第三拍
					length = length - 0.075;
					yFlag = 4;
					delay();
					if (length <= 0)
					{
						//Yb = 0;
					    return;
					}
					break;
			 case 4:
					Ya = 0; Ya_ = 1; Yb = 1; Yb_ = 0; //第四拍
					length = length - 0.075;
					yFlag = 5;
					delay();
					if (length <= 0)
					{
						//Ya_ = 0; Yb = 0;
					    return;
					}
					break;
			 case 5:
					Ya = 0; Ya_ = 1; Yb = 0; Yb_ = 0; //第五拍
					length = length - 0.075;
					yFlag = 6;
					delay();
					if (length <= 0)
					{
						//Ya_ = 0;
					    return;
					}
					break;
			 case 6:
					Ya = 0; Ya_ = 1; Yb = 0; Yb_ = 1; //第六拍
					length = length - 0.075;
					yFlag = 7;
					delay();
					if (length <= 0)
					{
						//Ya_ = 0; Yb_ = 0;
					    return;
					}
					break;
			 case 7:
					Ya = 0; Ya_ = 0; Yb = 0; Yb_ = 1; //第七拍
					length = length - 0.075;
					yFlag = 8;
					delay();
					if (length <= 0)
					{
						//Yb_ = 0;
					    return;
					}
					break;
			 case 8:
					Ya = 1; Ya_ = 0; Yb = 0; Yb_ = 1; //第八拍
					length = length - 0.075;
					yFlag = 1;
					delay();
					if (length <= 0)
					{
						//Ya = 0; Yb_ = 0;
					    return;
					}
					break;
		}
	}
}
//控制Y轴反转
void yReversalTurn(double length)
{
	while (1)
	{
		switch (yFlag)
		{
			case 1:
				   Ya = 1; Ya_ = 0; Yb = 0; Yb_ = 1; //第一拍
				   length = length - 0.075;
				   yFlag = 8;
				   delay();
				   if (length <= 0)
				   {
				       //Ya = 0; Yb_ = 0;
				       return;
				   }
				   break;
			case 8:
				   Ya = 0; Ya_ = 0; Yb = 0; Yb_ = 1; //第二拍
				   length = length - 0.075;
				   yFlag = 7;
				   delay();
				   if (length <= 0)
				   {
					   //Yb_ = 0;
				       return;
				   }
				   break;
			case 7:
				   Ya = 0; Ya_ = 1; Yb = 0; Yb_ = 1; //第三拍
				   length = length - 0.075;
				   yFlag = 6;
				   delay();
				   if (length <= 0)
				   {
					   //Ya_ = 0; Yb_ = 0; 
				       return;
				   }
				   break;
			case 6:
				   Ya = 0; Ya_ = 1; Yb = 0; Yb_ = 0; //第四拍
				   length = length - 0.075;
				   yFlag = 5;
				   delay();
				   if (length <= 0)
				   {
				      // Ya_ = 0; 
				       return;
				   }
				   break;
			case 5:
				   Ya = 0; Ya_ = 1; Yb = 1; Yb_ = 0; //第五拍
				   length = length - 0.075;
				   yFlag = 4;
				   delay();
				   if (length <= 0)
				   {
				       //Ya_ = 0; Yb = 0;
				       return;
				   }
				   break;
			case 4:
				   Ya = 0; Ya_ = 0; Yb = 1; Yb_ = 0; //第六拍
				   length = length - 0.075;
				   yFlag = 3;
				   delay();
			       if (length <= 0)
				   {
						//Yb = 0;
				        return;
				   }
				   break;
			case 3:
				   Ya = 1; Ya_ = 0; Yb = 1; Yb_ = 0; //第七拍
				   length = length - 0.075;
				   yFlag = 2;
				   delay();
				   if (length <= 0)
				   {
						//Ya = 0; Yb = 0;
				        return;
				   }
				   break;
			case 2:
				   Ya = 1; Ya_ = 0; Yb = 0; Yb_ = 0; //第八拍
				   length = length - 0.075;
				   yFlag = 1;
				   delay();
				   if (length <= 0)
				   {
						//Ya = 0; 
						return;
				   }
				   break;
		}
	}
}
//单片机发送字符串给电脑，在电脑上显示信息（注意：需等待发送完毕，才能进行下一步操作，浪费时间!!!）
void printf(unsigned char *show)
{
	unsigned int i = 0;                 
	for (i = 0; show[i] != '\0'; i++)
	{
		SBUF = show[i];  
		while(!TI);     //直到发送结束
		TI = 0;         //软件清零
	}
} 
//快速定位算法
void quickPosition(double X, double Y)
{
	double xLength = 0, yLength = 0;       //定义步进电机需要移动的距离, xLength表示在x轴要移动的距离，ylength同xLength
	
	xLength = fabs(X - x0);
	yLength = fabs(Y - y0);
	
	if (X > x0)
		xPositiveTurn(xLength);     //向x轴正方向运动，参数是毫米
	else
		xReversalTurn(xLength);     //向x轴负方向运动，参数是毫米
	
	if (Y > y0)
		yPositiveTurn(yLength);     //向y轴正方向运动，参数是毫米
	else 
		yReversalTurn(yLength);     //向y轴负方向运动，参数是毫米

	x0 = X;     //更改起始位置的坐标
	y0 = Y;
}

//直线插补算法
void linearInterpolation(double X, double Y)
{
	double slope;                      //定义终点的斜率（固定的值）
	double slopeTemp = 0;              //定义动点斜率，用于和终点的斜率进行比较, 初值为0
	double xTemp = x0, yTemp = y0;     //定义动点坐标，其初值等于起始位置的坐标
	
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	
	//如果终点和起点相同,停止
	if (X == x0 && Y == y0)
	{
		return;
	}
	//如果终点和起点是平行线(即斜率是0或无穷大)
	if (X - x0 == 0 || Y - y0 == 0)
	{
		quickPosition(X, Y);  //用快速定位的方式移动
		return;
	}
	
	//如果起点和终点构成斜线
	if (X - x0 == 0)
	{
		//printf("ERROR! (In the linearInterpolation)");
		return ;
	}
	slope =(Y - y0) / (X - x0);   //求得直线斜率
	N = (fabs(X - x0) + fabs(Y - y0)) / Length;   //一步定为0.6毫米，共需要走N步。
	
	
	if (slope > 0 && X > x0 && Y > y0)       //判断该直线是否和第一象限的类似
	{
		while (i < N)
		{
			if (xTemp == x0 && yTemp == y0)  //如果动点在起始位置上
			{
				xPositiveTurn(Length);        //规定x轴向正方向移动一个基本步进长度
				xTemp = xTemp + Length;        //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;        //步数加一
			}
			if (slopeTemp == slope)                    //动点斜率等于终点斜率，即动点在该直线上
			{
				xPositiveTurn(Length);        //规定x轴向正方向移动一个基本步进长度
				xTemp = xTemp + Length;        //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp < slope)           //动点在该直线之下
			{
				yPositiveTurn(Length);       //y轴增加一个步进距离
				yTemp = yTemp + Length;      //动点纵坐标增加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp > slope)                               //动点斜率等于终点斜率，即动点在该直线上
			{
				xPositiveTurn(Length);       //x轴向正方向移动一个基本步进长度
				xTemp = xTemp + Length;      //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}				
		}		
	}	
	if (slope < 0 && X < x0 && Y > y0) //判断该直线是否和第二象限的类似（与第一象限算法有差异）
	{
		while (i < N)
		{
			if (xTemp == x0 && yTemp == y0)   //如果动点在起始位置
			{
				xReversalTurn(Length);        //规定x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;       //动点横坐标减一个步进长度
				yPositiveTurn(Length);        //y轴增加一个步进距离
				yTemp = yTemp + Length;       //动点纵坐标增加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i = i + 2;
			}
			if (slopeTemp == slope)                              //动点斜率等于终点斜率，即动点在该直线上
			{
				xReversalTurn(Length);        //规定x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;       //动点横坐标减一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp < slope)                               //动点在该直线之下
			{	
				xReversalTurn(Length);       //x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;      //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp > slope)                               //动点在该直线之上
			{
				yPositiveTurn(Length);       //y轴增加一个步进距离
				yTemp = yTemp + Length;      //动点纵坐标增加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率	
				i++;
			}				
		}	
	}
	if (slope > 0 && X < x0 && Y < y0) //类似于第三象限
	{
		while (i < N)
		{
			if (xTemp == x0 && yTemp == y0)  //如果动点在起始位置上
			{
				xReversalTurn(Length);       //x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;      //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp < slope) //动点在直线上方
			{
				yReversalTurn(Length);  //向Y轴负方向移动距离
				yTemp = yTemp - Length;
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp == slope)  //动点位于直线
			{
				xReversalTurn(Length);       //x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;      //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp > slope)  //动点在直线下方
			{
				xReversalTurn(Length);       //x轴向负方向移动一个基本步进长度
				xTemp = xTemp - Length;      //动点横坐标加一个步进长度
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}	
		}	
	}
	if (slope < 0 && X > x0 && Y < y0)  //类似于第四象限
	{
		while (i < N)
		{
			if (xTemp == x0 && yTemp == y0) //动点在起始位置
			{
				xPositiveTurn(Length);  //向x轴正方向走一步
				xTemp = xTemp + Length;
				yReversalTurn(Length);  //向Y轴负方向移动距离
				yTemp = yTemp - Length;
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i = i + 2;
			}
			if (slopeTemp == slope)
			{
				xPositiveTurn(Length);  //向x轴正方向走一步
				xTemp = xTemp + Length;
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp > slope)
			{
				yReversalTurn(Length);  //向Y轴负方向移动一步
				yTemp = yTemp - Length;
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}
			if (slopeTemp < slope)
			{
				xPositiveTurn(Length);  //向x轴正方向走一步
				xTemp = xTemp + Length;
				slopeTemp = (yTemp - y0) / (xTemp - x0);  //更新动点和起始坐标的斜率
				i++;
			}		
		}	
	}
	x0 = X;                      //更改起始位置的坐标, 令程序结束
	y0 = Y;
	return;                      
}
//类似第一象限逆时针圆弧插补子程序
void sub1(double x1, double y1, double x2, double y2)  //(x1, y1)-->(x2, y2)
{
	//注意圆心坐标（a, b）已经在父程序中确定
	
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：-x方向的进给，2：+y方向的进给，3：-x和+y都进给）
	
		
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.6毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F - 2*Length*xTemp + Length*Length + 2*a*Length;  //如果要按-x方向进给，偏差数为F1
		F2 = F + 2*Length*yTemp + Length*Length - 2*b*Length;  //如果要按+y方向进给，偏差数为F2
		F3 = F - 2*Length*xTemp + 2*Length*yTemp + 2*a*Length - 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xReversalTurn(Length);  //向X轴负方向移动一步
				xTemp = xTemp - Length;
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加1
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;   
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加1
			}
			
		}		
	}	
}
//类似第二象限逆时针圆弧插补子程序
void sub2(double x1, double y1, double x2, double y2) //（x1，y1）---> (x2, y2)
{
	//注意圆心坐标（a, b）已经在父程序中确定
	
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：-x方向的进给，2：-y方向的进给，3：-x和-y都进给）
	
		
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.6毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F - 2*Length*xTemp + Length*Length + 2*a*Length;  //如果要按-x方向进给，偏差数为F1
		F2 = F - 2*Length*yTemp + Length*Length + 2*b*Length;  //如果要按-y方向进给，偏差数为F2
		F3 = F - 2*Length*xTemp - 2*Length*yTemp + 2*a*Length + 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xReversalTurn(Length);  //向X轴负方向移动一步
				xTemp = xTemp - Length;
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;     
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}
			
		}		
	}	
}
//类似第三象限逆时针圆弧插补子程序
void sub3(double x1, double y1, double x2, double y2) //起点（x1，y1）到终点（x2, y2）
{
	//注意圆心坐标（a, b）已经在父程序中确定
	
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：+x方向的进给，2：-y方向的进给，3：+x和-y都进给）
	
		
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.6毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F + 2*Length*xTemp + Length*Length - 2*a*Length;  //如果要按+x方向进给，偏差数为F1
		F2 = F - 2*Length*yTemp + Length*Length + 2*b*Length;  //如果要按-y方向进给，偏差数为F2
		F3 = F + 2*Length*xTemp - 2*Length*yTemp - 2*a*Length + 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;    
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yReversalTurn(Length);       //向-y轴移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;     
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yReversalTurn(Length);       //向-y轴移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}
			
		}		
	}	
	
}
//类似第四象限逆时针圆弧插补子程序
void sub4(double x1, double y1, double x2, double y2)
{

	//注意圆心坐标（a, b）已经在父程序中确定
		
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：+x方向的进给，2：+y方向的进给，3：+x和+y都进给）
	
	
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.15毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F + 2*Length*xTemp + Length*Length - 2*a*Length;  //如果要按+x方向进给，偏差数为F1
		F2 = F + 2*Length*yTemp + Length*Length - 2*b*Length;  //如果要按+y方向进给，偏差数为F2
		F3 = F + 2*Length*xTemp + 2*Length*yTemp - 2*a*Length - 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;    
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;  
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;      
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;  
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}			
		}		
	}
}
//逆时针圆弧插补(用的是最小偏差法)
void circularInterpolation_N(double X, double Y) //(X, Y)为终点坐标, (x0, y0)为起点坐标, （a，b）为圆心
{
    //注意圆心（a, b）已经在全局变量中定义并在父程序中赋值
	
	double r;        //定义半径r，其值为起点到原心（a, b）的距离
	
	r = sqrt((x0-a)*(x0-a) + (y0-b)*(y0-b));  //求得半径
	
	//起点在第一象限（包括x轴正半轴，不包括y轴正半轴）
	if (x0 > a && y0 >= b)   
	{
		if (X >= a && Y > b)  //终点在第一象限（包括y轴正半轴，不包括x轴正半轴）
		{
			if (X >= x0)
			{		
				if (X == x0 || Y >= y0 )
				{
					//printf("ERROR 1! The coordinate is wrong!");
					return;
				}
				sub1(x0, y0, a, (b+r));
				sub2(a, (b+r), (a-r), b);
				sub3((a-r), b, a, (b-r));
				sub4(a, (b-r), (a+r), b);
				sub1((a+r), b, X, Y);
			}
			if (X < x0)
			{
				if (Y <= y0)
				{
					//printf("ERROR 2! The coordinate is wrong!");
					return;
				}
				sub1(x0, y0, X, Y);  
			}		
		}
		if (X < a && Y >= b) //终点在第二象限
		{
			sub1(x0, y0, a, (b+r));
			sub2(a, (b+r), X, Y);
		}
		if (X <= a && Y < b)  //终点在第三象限
		{
			sub1(x0, y0, a, (b+r));  
			sub2(a, (b+r), (a-r), b);  
			sub3((a-r), b, X, Y);		
		}
		if (X > a && Y <= b)  //终点在第四象限
		{
			sub1(x0, y0, a, (b+r));
			sub2(a, (b+r), (a-r), b);
			sub3((a-r), b, a, (b-r));
			sub4(a, (b-r), X, Y);
		}
	}
	//起点在第二象限（包括y轴正半轴，不包括x轴负半轴）
	if (x0 <= a && y0 > b)
	{
		if (X < a && Y >= b) //终点在第二象限
		{
			if (Y >= y0)
			{
				if (Y == y0 || X <= x0)
				{
					//printf("ERROR 3! The coordinate is wrong!");
					return;
				}
				sub2(x0, y0, (a-r), b);
				sub3((a-r), b, a, (b-r));
				sub4(a, (b-r), (a+r), b);
				sub1((a+r), b, a, (b+r));
				sub2(a, (b+r), X, Y);
			}
			if (Y < y0)
			{
				if (X >= x0)
				{
					//printf("ERROR 4! The coordinate is wrong!");
					return;
				}
				sub2(x0, y0, X, Y);  
			}
		}
		if (X <= a && Y < b)  //终点在第三象限
		{
			sub2(x0, y0, (a-r), b);
			sub3((a-r), b, X, Y);
		}
		if (X > a && Y <= b)  //终点在第四象限
		{
			sub2(x0, y0, (a-r), b);
			sub3((a-r), b, a, (b-r));
			sub4(a, (b-r), X, Y);
		}
		if (X >= a && Y > b)  //终点在第一象限（包括y轴正半轴，不包括x轴正半轴）
		{
			sub2(x0, y0, (a-r), b);
			sub3((a-r), b, a, (b-r));
			sub4(a, (b-r), (a+r), b);
			sub1((a+r), b, X, Y);
		}		
	}
	//起点在第三象限（包括x轴负半轴，不包括Y轴负半轴）
	if (x0 < a && y0 <= b)
	{
		if (X <= a && Y < b)  //终点在第三象限
		{
			if (X <= x0)
			{
				if (X == x0 || Y <= y0)
				{
					//printf("ERROR 5! The coordinate is wrong!");
					return;
				}
				sub3(x0, y0, a, (b-r));
				sub4(a, (b-r), (a+r), b);
				sub1((a+r), b, a, (b+r));
				sub2(a, (b+r), (a-r), b);
				sub3((a-r), b, X, Y);			
			}
			if (X > x0)
			{
				if (Y >= y0)
				{
					//printf("ERROR 6! The coordinate is wrong!");
					return;
				}
				sub3(x0, y0, X, Y);
			}
		}
		if (X > a && Y <= b)  //终点在第四象限
		{
			sub3(x0, y0, a, (b-r));
			sub4(a, (b-r), X, Y);
		}
		if (X >= a && Y > b)  //终点在第一象限（包括y轴正半轴，不包括x轴正半轴）
		{
			sub3(x0, y0, a, (b-r));
			sub4(a, (b-r), (a+r), b);
			sub1((a+r), b, X, Y);
		}
		if (X < a && Y >= b) //终点在第二象限
		{
			sub3(x0, y0, a, (b-r));
			sub4(a, (b-r), (a+r), b);
			sub1((a+r), b, a, (b+r));
			sub2(a, (b+r), X, Y);
		}	
	}
	//起点在第四象限（包括Y轴负半轴，不包括x轴正半轴）
	if (x0 >= a && y0 < b)
	{
		if (X > a && Y <= b)  //终点在第四象限
		{
			if (Y <= y0)
			{
				if (Y == y0 || X >= x0)
				{
					//printf("ERROR 7! The coordinate is wrong!");
					return;
				}
				sub4(x0, y0, (a+r), b);
				sub1((a+r), b, a, (b+r));
				sub2(a, (b+r), (a-r), b);
				sub3((a-r), b, a, (b-r));
				sub4(a, (b-r), X, Y);
			}
			if (Y > y0)
			{
				if (X <= x0)
				{
					//printf("ERROR 8! The coordinate is wrong!");
					return;
				}
				sub4(x0, y0, X, Y);
			}
		}
		if (X >= a && Y > b)  //终点在第一象限（包括y轴正半轴，不包括x轴正半轴）
		{
			sub4(x0, y0, (a+r), b);
			sub1((a+r), b, X, Y);
		}
		if (X < a && Y >= b)  //终点在第二象限
		{
			sub4(x0, y0, (a+r), b);
			sub1((a+r), b, a, (b+r));
			sub2(a, (b+r), X, Y);
		}	
		if (X <= a && Y < b)  //终点在第三象限
		{
			sub4(x0, y0, (a+r), b);
			sub1((a+r), b, a, (b+r));
			sub2(a, (b+r), (a-r), b);
			sub3((a-r), b, X, Y);		
		}		
	}
	x0 = X;    //更新起点位置
	y0 = Y;
} 
//类似 第一象限 顺时针 圆弧插补子程序
void sub5(double x1, double y1, double x2, double y2)
{
	//注意圆心坐标（a, b）已经在父程序中确定
		
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：+x方向的进给，2：+y方向的进给，3：+x和+y都进给）
	
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.15毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F + 2*Length*xTemp + Length*Length - 2*a*Length;  //如果要按+x方向进给，偏差数为F1
		F2 = F - 2*Length*yTemp + Length*Length + 2*b*Length;  //如果要按-y方向进给，偏差数为F2
		F3 = F + 2*Length*xTemp - 2*Length*yTemp - 2*a*Length + 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;    
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yReversalTurn(Length);       //向-y轴移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;     
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yReversalTurn(Length);       //向-y轴移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}
			
		}		
	}	
}
//类似 第二象限 顺时针 圆弧插补子程序
void sub6(double x1, double y1, double x2, double y2)
{

	//注意圆心坐标（a, b）已经在父程序中确定
		
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：+x方向的进给，2：+y方向的进给，3：+x和+y都进给）
	
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.15毫米，共需要走N步。

	while (i < N)
	{
		F1 = F + 2*Length*xTemp + Length*Length - 2*a*Length;  //如果要按+x方向进给，偏差数为F1
		F2 = F + 2*Length*yTemp + Length*Length - 2*b*Length;  //如果要按+y方向进给，偏差数为F2
		F3 = F + 2*Length*xTemp + 2*Length*yTemp - 2*a*Length - 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;    
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;  
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;      
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xPositiveTurn(Length);       //向+x轴移动一步
				xTemp = xTemp + Length;
				yPositiveTurn(Length);       //向+y轴移动一步
				yTemp = yTemp + Length;  
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}			
		}		
	}
}
//类似 第三象限 顺时针 圆弧插补子程序
void sub7(double x1, double y1, double x2, double y2)  //(x1, y1)-->(x2, y2)
{
	//注意圆心坐标（a, b）已经在父程序中确定
	
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：-x方向的进给，2：+y方向的进给，3：-x和+y都进给）
		
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.15毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F - 2*Length*xTemp + Length*Length + 2*a*Length;  //如果要按-x方向进给，偏差数为F1
		F2 = F + 2*Length*yTemp + Length*Length - 2*b*Length;  //如果要按+y方向进给，偏差数为F2
		F3 = F - 2*Length*xTemp + 2*Length*yTemp + 2*a*Length - 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xReversalTurn(Length);  //向X轴负方向移动一步
				xTemp = xTemp - Length;
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加1
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;   
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yPositiveTurn(Length);       //向y轴正方向移动一步
				yTemp = yTemp + Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加1
			}
			
		}		
	}	
}
//类似 第四象限 顺时针 圆弧插补子程序
void sub8(double x1, double y1, double x2, double y2) //（x1，y1）---> (x2, y2)
{
	//注意圆心坐标（a, b）已经在父程序中确定
	
	double xTemp = x1, yTemp = y1;  //定义动点(xTemp, yTemp), 初值为起始位置
	double N;                       //定义N为起始位置到终点两个步进电机一共要走的步数，定义每一步2拍，即精度为0.15毫米
	double i = 0;                   //定义变量i，表示两个步进电机一经走了i步, 初始化为0
	double F = 0;        //定义偏差数，即动点距离圆弧的差值，(偏差函数F= x^2+y^2-R^2), 由于开始时动点在圆弧上，故F初值为0
	double F1, F2, F3;   //三种不同方式的进给，所求的偏差数（1：-x方向的进给，2：-y方向的进给，3：-x和-y都进给）
		
	N = (fabs(x2 - x1) + fabs(y2 - y1)) / Length;   //一步定为0.15毫米，共需要走N步。
	
	while (i < N)
	{
		F1 = F - 2*Length*xTemp + Length*Length + 2*a*Length;  //如果要按-x方向进给，偏差数为F1
		F2 = F - 2*Length*yTemp + Length*Length + 2*b*Length;  //如果要按-y方向进给，偏差数为F2
		F3 = F - 2*Length*xTemp - 2*Length*yTemp + 2*a*Length + 2*b*Length + 2*Length*Length;
	
		if (fabs(F1) < fabs(F2))
		{
			if (fabs(F1) < fabs(F3))  //即F1最小, 用方式1
			{
				xReversalTurn(Length);  //向X轴负方向移动一步
				xTemp = xTemp - Length;
				F = F1;   //更新偏差数
				i++;      //已走的步数加1
			}
			else                     //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}	
		}
		else
		{
			if (fabs(F2) < fabs(F3))  //F2最小，用方式2
			{
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;     
				F = F2;
				i++;			
			}
			else                   //F3最小，用方式3
			{
				xReversalTurn(Length);       //向X轴负方向移动一步
				xTemp = xTemp - Length;
				yReversalTurn(Length);       //向y轴负方向移动一步
				yTemp = yTemp - Length;    
				F = F3;       //更新偏差数
				i = i + 2;    //已走的步数加2
			}
			
		}		
	}	
}

//顺时针圆弧插补(用的是最小偏差法)
void circularInterpolation_S(double X, double Y) //(X, Y)为终点坐标, (x0, y0)为起点坐标, （a，b）为圆心
{
    //注意圆心（a, b）已经在全局变量中定义并在父程序中赋值
	
	double r;        //定义半径r，其值为起点到原心（a, b）的距离
	
	r = sqrt((x0-a)*(x0-a) + (y0-b)*(y0-b));  //求得半径
	
	//起点在第一象限（不包括x轴正半轴，包括y轴正半轴）
	if (x0 >= a && y0 > b)   
	{
		if (X > a && Y >= b)  //终点在第一象限（不包括y轴正半轴，包括x轴正半轴）
		{
			if (X >= x0)
			{		
				if (X == x0 || Y >= y0 )
				{
					//printf("ERROR 1! The coordinate is wrong!");
					return;
				}
				sub5(x0, y0, X, Y);
			}
			if (X < x0)
			{
				if (Y <= y0)
				{
					//printf("ERROR 2! The coordinate is wrong!");
					return;
				}
				sub5(x0, y0, (a+r), b);
				sub8((a+r), b, a, (b-r));
				sub7(a, (b-r), (a-r), b);
				sub6((a-r), b, a, (b+r));
				sub5(a, (b+r), X, Y);
			}		
		}
		if (X >= a && Y < b)  //终点在第四象限
		{
			sub5(x0, y0, (a+r), b);
			sub8((a+r), b, X, Y);
		}
		if (X < a && Y <= b)  //终点在第三象限
		{
			sub5(x0, y0, (a+r), b);
			sub8((a+r), b, a, (b-r));
			sub7(a, (b-r), X, Y);
		}
		if (X <= a && Y > b)  //终点在第二象限
		{
			sub5(x0, y0, (a+r), b);
			sub8((a+r), b, a, (b-r));
			sub7(a, (b-r), (a-r), b);
			sub6((a-r), b, X, Y);
		}	
	}
	//起点在第二象限（不包括y轴正半轴，包括x轴负半轴）
	if (x0 < a && y0 >= b)
	{
		if (X <= a && Y > b) //终点在第二象限
		{
			if (Y >= y0)
			{
				if (Y == y0 || X <= x0)
				{
					//printf("ERROR 3! The coordinate is wrong!");
					return;
				}
				sub6(x0, y0, X, Y);
			}
			if (Y < y0)
			{
				if (X >= x0)
				{
					//printf("ERROR 4! The coordinate is wrong!");
					return;
				}
				sub6(x0, y0, a, (b+r));
				sub5(a, (b+r), (a+r), b);
				sub8((a+r), b, a, (b-r));
				sub7(a, (b-r), (a-r), b);
				sub6((a-r), b, X, Y);
			}
		}
		if (X > a && Y >= b)  //终点在第一象限
		{
			sub6(x0, y0, a, (b+r));
			sub5(a, (b+r), X, Y);
		}
		if (X >= a && Y < b)  //终点在第四象限
		{
			sub6(x0, y0, a, (b+r));
			sub5(a, (b+r), (a+r), b);
			sub8((a+r), b, X, Y);	
		}
		if (X < a && Y <= b)  //终点在第三象限
		{
			sub6(x0, y0, a, (b+r));
			sub5(a, (b+r), (a+r), b);
			sub8((a+r), b, a, (b-r));
			sub7(a, (b-r), X, Y);			
		}		
	}	
	//起点在第三象限（不包括x轴负半轴，包括Y轴负半轴）
	if (x0 <= a && y0 < b)
	{
		if (X < a && Y <= b)  //终点在第三象限
		{
			if (X <= x0)
			{
				if (X == x0 || Y <= y0)
				{
					//printf("ERROR 5! The coordinate is wrong!");
					return;
				}
				sub7(x0, y0, X, Y);			
			}
			if (X > x0)
			{
				if (Y >= y0)
				{
					//printf("ERROR 6! The coordinate is wrong!");
					return;
				}
				sub7(x0, y0, (a-r), b);
				sub6((a-r), b, a, (b+r));
				sub5(a, (b+r), (a+r), b);
				sub8((a+r), b, a, (b-r));
				sub7(a, (b-r), X, Y);
			}
		}
		if (X <= a && Y > b)   //终点在第二象限
		{
			sub7(x0, y0, (a-r), b);
			sub6((a-r), b, X, Y);
		}
		if (X > a && Y >= b)   //终点在第一象限
		{
			sub7(x0, y0, (a-r), b);
			sub6((a-r), b, a, (b+r));
			sub5(a, (b+r), X, Y);
		}
		if (X >= a && Y < b)   //终点在第四象限
		{
			sub7(x0, y0, (a-r), b);
			sub6((a-r), b, a, (b+r));
			sub5(a, (b+r), (a+r), b);
			sub8((a+r), b, X, Y);
		}	
	}
	//起点在第四象限（不包括Y轴负半轴，包括x轴正半轴）
	if (x0 > a && y0 <= b)
	{
		if (X >= a && Y < b)  //终点在第四象限
		{
			if (Y <= y0)
			{
				if (Y == y0 || X >= x0)
				{
					//printf("ERROR 7! The coordinate is wrong!");
					return;
				}
				sub8(x0, y0, X, Y);
			}
			if (Y > y0)
			{
				if (X <= x0)
				{
					//printf("ERROR 8! The coordinate is wrong!");
					return;
				}
				sub8(x0, y0, a, (b-r));
				sub7(a, (b-r), (a-r), b);
				sub6((a-r), b, a, (b+r));
				sub5(a, (b+r), (a+r), b);
				sub8((a+r), b, X, Y);
			}
		}
		if (X < a && Y <= b)  //终点在第三象限
		{
			sub8(x0, y0, a, (b-r));
			sub7(a, (b-r), X, Y);
		}
		if (X <= a && Y > b)  //终点在第二象限
		{
			sub8(x0, y0, a, (b-r));
			sub7(a, (b-r), (a-r), b);
			sub6((a-r), b, X, Y);
		}
		if (X > a && Y >= b)  //终点在第一象限
		{
			sub8(x0, y0, a, (b-r));
			sub7(a, (b-r), (a-r), b);
			sub6((a-r), b, a, (b+r));
			sub5(a, (b+r), X, Y);
		}		
	}
	x0 = X;    //更新起点位置
	y0 = Y;
} 

//接受G代码初始化
void initReceive()
{
	//printf("Please sent one GCode!(Adding # at the end of the GCode!!)\n");
	moveFlag = 0;   //取消运动标志。
	printf("#");  //发送一个“#”表示可以接受数据。
}
//判断字符是不是数字字符
int isDigit(char temp)
{
	switch (temp)
	{
		case '0': return 1; break;
		case '1': return 1; break;
		case '2': return 1; break;
		case '3': return 1; break;
		case '4': return 1; break;
		case '5': return 1; break;
		case '6': return 1; break;
		case '7': return 1; break;
		case '8': return 1; break;
		case '9': return 1; break;
		default: return 0;
	}
	return 0;
}
//判断字符是不是命令字符
int isChar(char temp)
{
	switch (temp)
	{
		case 'G': return 1; break;
		case 'M': return 1; break;
		case 'X': return 1; break;
		case 'Y': return 1; break;
		case 'F': return 1; break;
		case 'I': return 1; break;
		case 'J': return 1; break;
		default: return 0;
	}
	return 0;
}

//读取G后面的数字字符保存到float型变量figure中，并且使i的下一个字符为G、M、X或Y
void readNumber(unsigned char *gCode, unsigned int *i, double *figure)   
{
	double num, power;   
    int sign; 
	
	(*i)++;    //先自加一次，让i指向第一个数字字符
	if (isChar(gCode[*i]) != 1 && gCode[*i] != '\0')
	{
		sign = (gCode[*i] == '-')? -1:1;

		if (gCode[*i] == '+' || gCode[*i] == '-')
			(*i)++;

		for (num = 0; isDigit(gCode[*i]) == 1; (*i)++)
			num = 10.0 * num + (gCode[*i] - '0');

		if (gCode[*i] == '.')
			(*i)++;

		for (power = 1.0; isDigit(gCode[*i]) == 1; (*i)++)
		{
			num = 10.0 * num + (gCode[*i] - '0');
			power = power * 10;			
		}

		num = sign * num / power;
		*figure = num;
		
		while (isChar(gCode[*i]) != 1 && gCode[*i] != '\0' )
		{
			(*i)++;   //解决遇到空格的状态
		}
		(*i)--;  //保证i的下一个字符为G、M、X、Y或F
	}
	else
	{
		//printf("ERROR! In the readNumber\n");
		return;
	}
}
//接收G代码（注意最后一个字符必须接收到'#'，否则出现bug）
void receiveGCode(unsigned char *gCode)
{
	unsigned int i = 0;        //循环变量
	
	while(1)
	{
		while (!RI);     //等待产生计算机发送完毕一个字符，产生中断信号
		RI = 0;          //消除中断信号
		gCode[i] = SBUF;
		if (gCode[i] == '#')  //如果检测到计算机发送完毕的信号，停止接收
		{
			break;
		}
		i++;
	}	
	gCode[i] = '\0';                 //字符串结束符
	//if (i >= 49)
	//	printf("Error! Low storage space!\n");
	//else
	//{ 
		//"成功信息"反馈显示到上位机
	//	printf("The GCode has been sent successfully!\n");     //此函数需自己编写，在电脑上位机程序中显示
	//	printf("Just received content is \n");
	//	printf(gCode);
	//	printf("\n\n");
	//}
}

//解释G代码
void explainGCode(unsigned char *gCode, unsigned int *GCommand, double *X, double *Y, double *I, double *J)
{
	unsigned int i;
	double figure;       //保存命令字符后面的数字
	unsigned int num;   //用于保存figure的整型部分, 判断G命令和M命令的类型
	unsigned char temp;          //用于临时保存命令字符
	
	for (i = 0; gCode[i] != '\0'; i++)
	{
		temp = gCode[i];
		if (isChar(temp) != 1)
		{
			//printf("Error! In the explainGCode.\n");
			return;
		}
		readNumber(gCode, &i, &figure);  //读取G后面的数字保存到figure中，并使i的下一个字符为G、M、X或Y
		num = (unsigned int)figure;      //类型转换
		switch (temp)
		{
			case 'G':
					
					switch(num)
					{
						case 0: *GCommand = 0; moveFlag = 1; break;  //给G命令标志变量赋值（快速定位）
						case 1: *GCommand = 1; moveFlag = 1; break;  //直线插补
						case 2: *GCommand = 2; moveFlag = 1; break;  //顺时针圆弧插补 
						case 3: *GCommand = 3; moveFlag = 1; break;  //逆时针圆弧插补
						case 90: break;   //printf("Now working in Absolute size\n"); 
						case 21: break;   //printf("Now working in English unit\n");                    //注意此程序要改为公制编程
						default: break;  //printf("ERROR! Now the machine does not support the G gCode!\n");
					}
					break;
			case 'M':                                 //M命令为激光控制命令
					moveFlag = 0;  //取消运动标志
					switch (num)
					{
						case 5: Laser = 1; break;       //M05关闭激光 (此处为低电位有效)
						case 3: Laser = 0; break;       //M03打开激光
						case 2: break;   //printf("END\n");       //G02程序结束
						default: break; //printf("ERROR! Now the machine does not support the M GCode!\n");
					}
					break;
			case 'X':
					*X = figure;    //设定x轴坐标
					break;
			case 'Y':
					*Y = figure;    //设定y轴坐标
					break;
			case 'I':
					*I = figure;    //设定圆弧起点到圆心的x轴增量
					break;
			case 'J':
					*J = figure;    //设定圆弧起点到圆心的y轴增量
					break;
			case 'F':
					moveFlag = 0;   //取消运动标志
					Speed = num;    //设定速度（此版本为测试版本，速度不可控）
					break;
			default: break;   //printf("ERROR!(Please debug the explainGCode completely!)\n");					
		}
	}
}

//执行G代码
void executeGCode(unsigned int GCommand, double X, double Y, double I, double J)
{

	//注意：激光的打开关闭，速度设定已经在解释G代码时完成, 即F命令，M命令已经完成
	
	//为圆弧插补子程序服务（根据起点坐标（x0, y0）和增量I，J确定圆心（a, b））
	
	if (moveFlag == 1)   //需要运动
	{
		a = x0 + I;
		b = y0 + J;
	
		switch (GCommand)
		{
			case 0: quickPosition(X, Y); break;                //快速定位
			case 1: linearInterpolation(X, Y); break;          //直线插补
			case 2: circularInterpolation_S(X, Y); break;      //顺时针圆弧插补 
			case 3: circularInterpolation_N(X, Y); break;      //逆时针圆弧插补
			default: return;  //printf("The GCommand is Error!\n");
		}
	}
}

//主程序
void main()
{
    idata unsigned char gCode[50];       //定义字符串数组用于临时保存从电脑接收的一行G代码
	
	idata unsigned int GCommand = 0;           //用来标志哪一种G命令（0: 快速定位， 1：直线插补， 2：顺时针圆弧插补， 3：逆时针圆弧插补）
	idata unsigned int laserFlag = 0;          //用来标志激光状态（1：打开， 0：关闭）,初始化为关闭
	
	idata double X, Y;                          //表示G代码中的坐标位置（即激光要移动的终点）
	idata double I, J;   					    //圆弧起点到圆心的增量坐标
	
	SerInit();  //串口初始化(循环检测的方法接受数据) 
	Laser = 1;  //激光初始化关闭（低电位有效）
	
	while(1)
	{
		initReceive();                         //接收G代码初始化
		receiveGCode(gCode);                   //接收G代码
		explainGCode(gCode, &GCommand, &X, &Y, &I, &J);     //解释G代码
		executeGCode(GCommand, X, Y, I, J);    //执行G代码
	}
}


