
/**********************************************

文件名称:main.cpp
文件描述:实现一个表白程序
编译环境:VS2013&&EasyX

***********************************************/

//EasyX图形界面库     MFC Win32 Qt  duilib


#include<graphics.h>//图形库头文件
/*
1、图形库中的重要函数
	打开界面	关闭界面
	设置背景			
	setbkcolor(BLACK);//选择背景颜色
	cleardevice();//使用选定的颜色刷新背景

2、颜色
	程序中，MFC/Win32/Cocos2d/Unity3d/UE4  颜色通用
	2.1 会有一些宏定义    RED  GREEN BLACK 诸如此类
	2.2 RGB格式  RGB(255,255,255)//红绿蓝
	2.3 HSL格式 (工业色彩模式,电脑屏幕,电视屏幕)色相,饱和度,亮度 

3、文本
	3.1 大小和格式
	3.2 文字背景
	3.3 文字颜色
	3.4 输出文字


4、音频
	4.1 添加多媒体设备接口的头文件与接口
		#include<mmsystem.h>
		#pragma comment(lib,"winmm.lib")
	4.2
		mp3
		//mp3格式
		//mciSendString(L"open ./music/爱的翅膀.mp3 alias BGM",0, 0, 0);
		//mciSendString(L"play BGM repeat", 0, 0, 0);

		wav
		//wav格式
		//PlaySound(L"./music/你还要我怎样.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

5、图片
	用来保存图片的类 IMAGE 
	加载图片:
	输出图片:
	


*/

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<time.h>

#include"resource.h"//资源头文件

#define PI 3.14159265
#define NUM 13

//烟花弹结构体
struct Jet
{
	int x;
	int y;//坐标
	
	int hx;
	int hy;//坐标 high 上升的最大高度的坐标  最后赋值给烟花

	int height;//烟花的高度

	bool shoot;//是否可以发射

	DWORD t1, t2, dt;//控制烟花弹的上升速度
	IMAGE img[2];//1 亮  2暗
	byte n : 1;//图片下标  0 1 //位段 1bit  
}jet[NUM];



//烟花结构体
struct Fire
{
	int x, y;//左上角坐标
	int cen_x, cen_y;//中心坐标
	int width, height;//图片的宽和高
	int r;//半径从小变大
	int max_r;//最大半径

	int xy[240][240];//像素点的集合
	bool show;//是否绽放
	bool  draw;//是否输出像素点
	DWORD t1, t2, dt;

}fire[NUM];







void welcome();
void Init(int i);
void Load();//加载图片
void Chose(DWORD &t1);//筛选烟花弹
void shoot();
void Show(DWORD *pMem);

int main()
{

	initgraph(1200, 800);//打开界面 界面的长 宽

	welcome();
	DWORD t1 = timeGetTime();

	DWORD *pMem = GetImageBuffer();//获取显存

	//循环初始化
	for (int i = 0; i < NUM; i++)
	{  
		Init(i);
	}
	Load();


	BeginBatchDraw();//开始绘制
	while (!_kbhit())//判断是否有键盘消息
	{
		Chose(t1);
		shoot();
		Show(pMem);
		FlushBatchDraw();//把显存展示出来
	}
	getchar();
	closegraph();//关闭界面
	return 0;
}




void welcome()
{

	//音频文件

	//wav格式
	//添加资源文件
	//PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//mp3
	mciSendString(L"open ./music/爱的翅膀.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM repeat", 0, 0, 0);


	//文字
	settextcolor(YELLOW);//设置字体颜色	
	//如何得到一个圆的轨迹上的N个坐标
	for (int i = 0; i < 50; i++)
	{
		//圆的原点(600,200) 半径 180
		int x = 600 + (int)(sin(PI * 2 * i / 60) * 180);
		int y = 200 + (int)(cos(PI * 2 * i / 60) * 180);
		cleardevice();;//刷新,如果没有指定颜色,默认为黑色
		settextstyle(i, 0, L"楷体");//设置字体格式与大小  长 宽  字体
		outtextxy(x - 200, y, L"平安夜，谨献给：");//在指定的位置输出文本
		outtextxy(x + 50, y + 100, L"最爱的XXXXXXX");
		Sleep(25);//放慢速度
	}


	getchar();//卡住

	//按下任意键,进入第二界面

	cleardevice();
	settextstyle(25, 0, L"楷体");
	outtextxy(400, 150, L"茫茫人海中，");
	outtextxy(400, 200, L"错过了该错过的，放弃了该放弃的，");
	outtextxy(400, 250, L"于是，终于等到了你");
	outtextxy(400, 450, L"如何让你遇见我，");
	outtextxy(400, 500, L"在我最美丽的时刻为这，");
	outtextxy(400, 550, L"我已在佛前求了五百年，");
	outtextxy(400, 600, L"求他让我们结一段尘缘");
	outtextxy(650, 700, L"--By 某某某");

}


void  Init(int i)
{

	srand((unsigned int)time(NULL));

	int r[NUM] = { 120, 133, 125, 138, 156, 140, 148, 155, 132, 128,142,136,149 };
	int x[NUM] = { 120, 120, 110, 117, 93, 105, 110, 108, 116, 117, 104, 112, 118 };
	int y[NUM] = { 120, 120, 85, 120, 120, 103, 105, 107, 116, 118, 116, 107, 96 };


	//初始化烟花弹
	jet[i].x = 0;
	jet[i].y = 0;
	jet[i].hx = 0;
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;

	//初始化烟花
	fire[i].x = 0;
	fire[i].y = 0;
	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].max_r = r[i];
	fire[i].cen_x = x[i];
	fire[i].cen_y = 0;
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();
	fire[i].r = 0;
}




void Load()//加载图片
{
	

	//加载烟花
	IMAGE fm;
	IMAGE gm;
	loadimage(&fm, L"./image/flower.jpg");

	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);//每一个烟花
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);//获取每一个像素点
			}
		}
	}


	//加载烟花弹
	IMAGE jm;//烟花弹图片
	loadimage(&jm, L"./image/shoot.jpg");

	//jm里保存了一整张图片  分割图片
	for (int i = 0; i < NUM; i++)
	{		
		SetWorkingImage(&jm);//设置工作的图片
		int n = rand() % 5;

		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);//为空，放弃刚才的工作区域



}




void Chose(DWORD &t1)//筛选烟花弹
{

	DWORD t2 = timeGetTime();

	if (t2-t1>100)//控制发射频率
	{
		int n = rand() % 20;//随机发射
		if (n<NUM&&jet[n].shoot==false&&fire[n].show==false)
		{
			jet[n].x = rand() % 1200;
			jet[n].y = rand() % 100+600;//发射位置
			jet[n].hx = jet[n].x ;
			jet[n].hy = rand()%400;//爆炸位置
			jet[n].height = jet[n].y-jet[n].hy;//上升高度
			jet[n].shoot = true;//发射
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}

		t1 = t2;
	}

}

//烟花弹上升

void shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2-jet[i].t1>jet[i].dt&&jet[i].shoot==1)//每个烟花弹发射的频率
		{
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//贴烟花弹
			
				if (jet[i].y>jet[i].hy)
				{
					jet[i].n++;//明暗交替的效果
					jet[i].y -= 5;
				}
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//贴烟花弹

				////烟花弹升到最高处,擦除
				if (jet[i].y<=jet[i].hy)
				{
					putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//贴烟花弹
					
					//将烟花弹的最高处坐标赋给烟花
					fire[i].x = jet[i].hx+10;
					fire[i].y = jet[i].hy;
					fire[i].show = true;
					jet[i].shoot = false;
				}
				
				
				jet[i].t1 = jet[i].t2;
			}
		}
	}
}



void Show(DWORD *pMem)//显存指针 像素 这里面所有的像素点的集合
{

	int drt[16] = { 5, 5, 5, 5, 5, 5, 25, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		// 增加爆炸半径，绽放烟花，增加时间间隔做变速效果
		if (fire[i].t2-fire[i].t1>fire[i].dt&&fire[i].show==true)
		{
			if (fire[i].r<fire[i].max_r)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}
	
			if (fire[i].r >= fire[i].max_r - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
	   	}
		
	
		// 如果该号炮花可爆炸，根据当前爆炸半径画烟花，颜色值接近黑色的不输出。

		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a+=0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r*cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r*sin(a));

				if (x1>0&&x1<fire[i].width&&y1>0&&y1<fire[i].height)
				{
					//像素点的颜色
					int b = fire[i].xy[x1][y1] & 0xff;
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (fire[i].xy[x1][y1] >> 16);


					int xx = (int)(fire[i].x + fire[i].r*cos(a));
					int yy = (int)(fire[i].y - fire[i].r*sin(a));

					if (r>0x20 && g>0x20 && b>0x20 && xx>0 && xx<1200 && yy>0 && yy>800)
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);//绘制每个像素点的颜色
					
				}
			
			}
			fire[i].draw = false;
		}
	}

	
}















