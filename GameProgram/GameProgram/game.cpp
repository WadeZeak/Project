
#include<stdio.h>
#include<Windows.h>
#include<tchar.h>
#pragma comment(lib,"winmm.lib")



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE L"windows游戏编程入门,动作技能"
#define NUM 7

HDC g_hdc=NULL,g_mdc=NULL;//全局设备环境句柄 全局内存句柄
HBITMAP g_sPrite[NUM];//声明位图数组来存储每一张人物图片
DWORD g_tPre =0,g_tNow = 0;//记录上次绘图的时间//记录本准备绘图的时间
int g_iNum = 0;//记录目前显示的图片编号


//声明全局函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam);//窗口回掉函数 消息处理
BOOL Init_Game(HWND hwnd);//游戏初始化
VOID Paint_Game(HWND hwnd);//绘图
BOOL ClearUp_Game(HWND hwnd);//清理资源

int main(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof(WNDCLASS);//设置结构体大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;//设置窗口样式
	wndClass.lpfnWndProc = WndProc;//设置只指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;//窗口类附加内存,一般为情况下为0即可
	wndClass.cbWndExtra = 0;//窗口附内存，依然取0
	wndClass.hInstance = hInstance;//包含窗口过程的程序实例句柄
	wndClass.hIcon = (HICON)::LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//指定窗口类的光标句柄
	
	
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;//用一个空终止的字符,制定窗口菜单名称
	wndClass.lpszClassName = L"GameGDI";


	//注册窗口
	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}

	//创建窗口

	HWND hwnd = CreateWindow(L"GameGDI", WINDOW_TITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//显示更新
	MoveWindow(hwnd,250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, TRUE);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	//初始化游戏
	if (!Init_Game(hwnd))
	{
		MessageBox(hwnd, L"游戏初始化失败", L"错误", 0);
		return false;
	}

	//PlaySound(L"仙剑.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);


	//消息循环
	MSG msg = { 0 };
	while (msg.message!=WM_QUIT)//使用消息循环，如果不是WM_QUIT,继续循环
	{
		if (PeekMessage(&msg,0,0,0,PM_REMOVE))//将虚拟键消息转换为字符消息
		{
			TranslateMessage(&msg);//
			DispatchMessage(&msg);
		}
		else
		{
			g_tNow = GetTickCount();
			if (g_tNow-g_tPre>100)
			{
				Paint_Game(hwnd);
			}
		}
	}

	getchar();
	//窗口注销
	UnregisterClass(L"GameGDI",hInstance);


	return 0;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam)//窗口回掉函数
{

	switch (message)
	{
	case WM_DESTROY://窗口销毁消息
		ClearUp_Game(hwnd);//退出前，清理资源
		PostQuitMessage(0);//向系统表明有终止请求
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, IParam);
		break;
	}
	return 0;
}



BOOL Init_Game(HWND hwnd)//游戏初始化
{
	g_hdc = GetDC(hwnd);
	wchar_t filename[20];

	//加载每一个人物

	for (int i = 0; i < NUM; i++)
	{
		memset(filename, 0, sizeof(filename));
		swprintf_s(filename, L"%d.bmp", i);
		g_sPrite[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);

	}

	g_mdc = CreateCompatibleDC(g_hdc);//建立兼容设备的内存DC
	Paint_Game(hwnd);

	g_tPre = GetTickCount();
	return true;

}

VOID Paint_Game(HWND hwnd)//绘图
{

	if (g_iNum==NUM+1)//判断是否超过最大图片编号,最大为10
	{
		g_iNum = 00;
		SelectObject(g_mdc, g_sPrite[g_iNum]);

		//把图片按编号铁道
		BitBlt(g_hdc, 0, 0, 800, 600, g_hdc, 0, 0, SRCCOPY);
		g_iNum++;
	}
}


BOOL ClearUp_Game(HWND hwnd)//清理资源
{

	//释放资源对象
	for (int i = 0; i < NUM; i++)
	{

		DeleteObject(g_sPrite[i]);

	}

	DeleteDC(g_hdc);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}