
#include<stdio.h>
#include<graphics.h>//图形库easyX
#include<time.h>//time clock
#include<math.h>
#include<stdlib.h>//关机命令

#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
using namespace std;



//playsound() 只能放wav wav可以用于资源文件
//mciSendString() 可以播放任何类型的音乐  


#define PI 3.141592654
void drawDail(int h, int m, int s);
void mouceClickMsg();


int main()
{
	char arr[100];
	SYSTEMTIME sysTime;

	initgraph(640, 480);//新建一个窗口 640*480
	setbkmode(TRANSPARENT);
	settextstyle(30,0,"华文彩云");

	//settextcolor(RGB(230,50,180));
	//setbkcolor(LIGHTGRAY);//grey  gray
		
	//放音乐


	//mciSendString("open Fade.mp3 alias bkmusic", 0, 0, 0);
	//mciSendString("play bkmusic repeat",0, 0, 0);



		//表盘界面
	//1、获取时间
	//while (1)
	//{
	//	GetLocalTime(&sysTime);//获取当前时间
	//	sprintf(arr, "%d年%d月%d日 %d时%d分%d秒", sysTime.wYear, sysTime.wMonth,
	//		sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	//	outtextxy(0, 0, arr);
	//	Sleep(1000);
	//}
	
	//覆盖每次循环产生的图像  将新的图像覆盖(贴到)旧的图像上
	while (1)
	{
		loadimage(NULL, "1.jpg");
		setlinecolor(YELLOW);
		rectangle(500, 20, 630, 60);//左上角 右下角的点确定方框
		outtextxy(520, 20, "关机");


		rectangle(500, 200, 630, 240);
		outtextxy(520, 200, "播放音乐");

		rectangle(500, 420, 630, 460);
		outtextxy(540, 420, "退出");

		GetLocalTime(&sysTime);//获取当前时间 
		drawDail(sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		 mouceClickMsg();
		Sleep(1000);//太小 会闪屏
	
	//	cleardevice();//清屏
	}
	getchar();
	closegraph();
	return 0;
}


//画表盘
void drawDail(int h,int m,int s)
{
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	circle(280, 240, 200);

	char arr[3];


	for (int i = 1; i <= 12; i++)//画刻度
	{
		sprintf(arr, "%d", i);
		outtextxy(280+(int)(190*sin(PI/6*i))-6, 240-(int)(190*cos(PI/6*i))-13, arr);
	}

	//开始画指针  时 分 秒
	//颜色  长度  粗细

	//此处不考虑分针对时针以及秒针对分针的影响
	//时针
	setlinecolor(RED);
	setlinestyle(PS_SOLID,7);//粗线条
	line(280, 240, 280 + (int)(120 * sin(PI / 6 * h)), 240 - (int)(120 * cos(PI / 6 * h)));

		//分针
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 3);
	line(280, 240, 280 + (int)(160 * sin(PI*m/30)), 240 - (int)(160 * cos(PI /30*m)));

	//秒针
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 1);
	line(280, 240, 280 + (int)(180 * sin(PI / 30*s)), 240 - (int)(180 * cos(PI / 30*s)));
	
}



void mouceClickMsg()
{
	if (MouseHit())//鼠标点击
	{
		MOUSEMSG mouceMsg = GetMouseMsg();
		switch (mouceMsg.uMsg)
		{
		case WM_LBUTTONDOWN://左键按下
			if (mouceMsg.x>500&&mouceMsg.x<630)
			{
				if (mouceMsg.y>20 && mouceMsg.y<60)
				{
					MessageBox(GetHWnd(), "200s后关机!!", "提醒", MB_OK);
					system("shutdown -s -t 200");
				}	
				else if (mouceMsg.y>200 && mouceMsg.y<240)
				{
					//播放音乐
					mciSendString("open Fade.mp3 alias bkmusic", 0, 0, 0);
					mciSendString("play bkmusic repeat", 0, 0, 0);

				}
				else if (mouceMsg.y>420 && mouceMsg.y<460)
				{
					closegraph();
					exit(0);
				}
				
			}
			
			
		default:
			break;
		}
	}
}

























