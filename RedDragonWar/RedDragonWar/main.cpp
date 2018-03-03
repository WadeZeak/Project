/*

文件名：main.cpp
文件描述:实现横板的射击类游戏

*/


#include <windows.h> //头文件

//专门处理音乐的头文件 库文件 MCI(media control interface)
//多媒体设备接口的头文件与库文件
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib")//内涵透明贴图的函数 TransparentBlt


#include<time.h>
#include<stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NUM 30

//全局变量
HBITMAP g_BackBmp, g_DragonBmp, g_FireBmp, g_EnemyBmp;//四张图片
HDC g_hdc, g_memdc, g_bufdc;//窗口设备 兼容设备 缓冲设备
int g_DragonX;
int g_DragonY;
int g_bgoff;//背景偏移量
int g_FireNum = 0;//火球数量

DWORD g_tPre, g_tNow;//火球
DWORD g_etPre, g_etNow;//敌人

DWORD g_mtPre,g_mtNow;




struct Fire
{
	int x;
	int y;//火球坐标
	bool exist;//火球是否存在
}fire[NUM];

typedef struct Enemy
{
	int x;
	int y;
	struct  Enemy *pnext;
}ENEMY;


ENEMY *pEnemy = NULL;



void EnemyMove();
void CreateList();
void AddEnemyNode();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL GameInit(HWND hWnd);
VOID GamePaint(HWND hWnd);
BOOL GameClearUp(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE prehInstance,
	LPSTR lpCmdLine,
	int nShowCmd) //主函数 
{
	//MessageBox(NULL, L"HELLO WORLD", L"", MB_YESNO);
	//搭建1个窗口
	//1.需要什么样子的窗口
	WNDCLASSEX wnd = { 0 }; //定义一个窗口
	wnd.cbSize = sizeof(WNDCLASSEX);     //窗口应该占用内存
	wnd.hInstance = hInstance;           //程序的当前实例句柄
	wnd.style = CS_HREDRAW | CS_VREDRAW; //窗体可以改变水平和垂直方向
	wnd.hbrBackground = (HBRUSH)5;		 //背景颜色
	wnd.hCursor = NULL;					 //鼠标样式  
	wnd.hIcon = NULL;					 //程序的图标
	wnd.cbClsExtra = 0;          //程序的附加内存
	wnd.cbWndExtra = 0;          //窗口的附加内存
	wnd.lpszMenuName = NULL;	 //菜单
	wnd.lpszClassName = L"感恩节快乐"; //窗口的类名称
	wnd.lpfnWndProc = WndProc;   //窗口的过程函数

	//2.注册窗口
	RegisterClassEx(&wnd); //检查窗口是否可用

	//3.创建
	HWND hWnd = CreateWindow(L"感恩节快乐", L"DragonWarDemo",
		WS_OVERLAPPEDWINDOW, 300, 200, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//4.显示和更新
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//执行失败
	if (!GameInit(hWnd))
	{
		return -1;
	}


	//PlaySound(L"res/music.wav", //路径
	//	NULL, //句柄
	//	SND_FILENAME | SND_LOOP | SND_ASYNC);
	//SND_FILENAME 通过文件的路径来播放(播放资源)
	//SND_LOOP 循环播放
	//SND_ASYNC 异步播放(顺序结构)执行该函数立即返回，继续执行以下的代码
	


	//消息循环
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) //只要客户发出退出程序的指令
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))//消息队列去获得消息
		{
			//栈在哪里用?代码块   队列在哪里用啊? 打游戏
			TranslateMessage(&msg);  //翻译消息  虚拟键值--->字符消息
			DispatchMessage(&msg);   //发送消息 发送给系统 
		}
		else
		{
			g_mtNow = GetTickCount();
			g_tNow = GetTickCount();//获取当前系统时间
			if (g_tNow-g_tPre>=10)
			{
				GamePaint(hWnd);
			}

			if (g_mtNow-g_mtPre>5)
			{
				EnemyMove();
				g_mtPre = g_mtNow;
			}
		
		}
	}

	return 0;
}

//窗口的过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE://鼠标处理函数  
		//龙随鼠标移动
		g_DragonX = LOWORD(lParam);
		g_DragonY = HIWORD(lParam);
		break;


	case WM_CREATE:
		CreateList();
		break;
	case WM_LBUTTONDOWN://点下鼠标左键
		//对火球的数组进行初始化
		for (int i = 0; i < NUM; i++)
		{
			if (!fire[i].exist)//火球存在
			{
				fire[i].x = g_DragonX+10;
				fire[i].y = g_DragonY+30;
				fire[i].exist = true;
				g_FireNum++;
				break;
			}
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}




//游戏初始化
//1、加载图片
//2、初始化关键变量
//3、绘制图形使用的技术(GDI三缓冲技术)
BOOL GameInit(HWND hWnd)
{
	srand((unsigned int)time(NULL));//随机数种子
	//初始化三缓冲的绘图体系
	g_hdc = GetDC(hWnd);//窗口的设备环境
	g_memdc = CreateCompatibleDC(g_hdc);
	g_bufdc = CreateCompatibleDC(g_hdc);

	HBITMAP  bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH,WINDOW_HEIGHT);


	//加载图片
	g_BackBmp = (HBITMAP)LoadImage(NULL, L"res/bg.bmp", IMAGE_BITMAP, WINDOW_WIDTH, 
									WINDOW_HEIGHT, LR_LOADFROMFILE);
	g_DragonBmp = (HBITMAP)LoadImage(NULL, L"res/long00.bmp", IMAGE_BITMAP,
									284 , 206, LR_LOADFROMFILE);
	g_FireBmp = (HBITMAP)LoadImage(NULL, L"res/fire.bmp", IMAGE_BITMAP, 
										100, 34, LR_LOADFROMFILE);
	g_EnemyBmp = (HBITMAP)LoadImage(NULL, L"res/long005.bmp", IMAGE_BITMAP, 
										300, 300, LR_LOADFROMFILE);

	//1
	SelectObject(g_memdc, bmp);//将空位图放入g_memdc

	g_DragonX = WINDOW_WIDTH - 142;
	g_DragonY = 0;
	g_bgoff = 0;


	ShowCursor(false);//隐藏鼠标


//	INT G_bgoff=0;//背景偏移量


	return TRUE;
}


//游戏的绘制
//透明贴图的两种方法
//遮罩法
//色彩法	TransparntBlt()

VOID GamePaint(HWND hWnd)
{
	
	//背景
	//2
	SelectObject(g_bufdc, g_BackBmp);//将图片贴到g_bufdc

	//3
	BitBlt(g_memdc, 0, 0, g_bgoff, WINDOW_HEIGHT, g_bufdc, WINDOW_WIDTH-g_bgoff, 0, SRCCOPY);//g_bufdc中的内容贴到g_memdc
	BitBlt(g_memdc, g_bgoff, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_bufdc, 0, 0, SRCCOPY);

	if (++g_bgoff>=WINDOW_WIDTH)//超过窗口
	{
		g_bgoff = 0;
	}


	//龙
	//2
	SelectObject(g_bufdc, g_DragonBmp);
	//3	
	//BitBlt(g_memdc, 0, 0, 284, 206, g_bufdc, 0, 0, SRCCOPY);
	TransparentBlt(g_memdc, g_DragonX, g_DragonY, 142, 103, g_bufdc, 0, 0,284,206, RGB(255,255,255));



	//火球
	//2
	SelectObject(g_bufdc, g_FireBmp);
	//3
	//BitBlt(g_memdc, 300, 0, 100, 34, g_bufdc, 0, 0, SRCCOPY);

	if (g_FireNum!=0)
	{
		for (int  i = 0; i < NUM; i++)
		{
			if (fire[i].exist)
			{
				//遮罩法 透明化背景
				BitBlt(g_memdc, fire[i].x, fire[i].y, 50, 34, g_bufdc, 50, 0, SRCAND);//打底
				BitBlt(g_memdc, fire[i].x, fire[i].y, 50, 34, g_bufdc, 0, 0, SRCPAINT);//覆盖

				fire[i].x -= 10;//火球向左移动
				if (fire[i].x <= 0)//火球超过边界
				{
					g_FireNum--;//火球数量减少
					fire[i].exist = false;
				}
			}		
		}
	}
	
	//敌人

	g_etNow=GetTickCount();
	if (g_etNow-g_etPre>1000)//1000ms
	{
		AddEnemyNode();
		g_etPre = g_etNow;
	}

	//2
	SelectObject(g_bufdc, g_EnemyBmp);

	ENEMY *pTemp = pEnemy->pnext;
	while (pTemp!=NULL)
	{		
		TransparentBlt(g_memdc, pTemp->x, pTemp->y, 100, 100, 
							g_bufdc, 0, 0, 300,300,RGB(0,255,0));
	
		pTemp = pTemp->pnext;
	}


	//3
	//BitBlt(g_memdc, 0, 300, 300, 300, g_bufdc, 0, 0, SRCCOPY);

	
	//4
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_memdc, 0, 0, SRCCOPY);//将g_memdc中的内容铁道g_hdc

	g_tPre = GetTickCount();//获取当前系统时间
}



//游戏资源的清理

BOOL GameClearUp(HWND hWnd)
{
	return TRUE;

}




void CreateList()
{
	//pEnemy内部x,y不用
	pEnemy = (ENEMY *)malloc(sizeof(ENEMY));
	pEnemy ->pnext= NULL;

	g_mtPre=g_etPre = GetTickCount();

}




void AddEnemyNode()
{

	ENEMY *pNew = (ENEMY*)malloc(sizeof(ENEMY));
	pNew->x = 0;
	pNew->y = rand() % (WINDOW_HEIGHT - 100);
	pNew->pnext = pEnemy->pnext;//NULL
	pEnemy->pnext = pNew;

}


void EnemyMove()
{
	ENEMY *pTemp = pEnemy->pnext;

	while (pTemp!=NULL)
	{

		pTemp->x++;
		pTemp = pTemp->pnext;

	}

}





//火球 数组 便利

//龙 链表 遍历

//摸一个火球范围和龙的范围出现碰撞，火球的exist=false