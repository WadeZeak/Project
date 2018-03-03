
#include<Windows.h>
#include<time.h>
#include<stdlib.h>

#include<mmsyscom.h>
#pragma comment(lib, "WINMM.LIB")


//窗口弹出6部曲
//1、创建win32工程
//2、注册窗口
//3、窗口处理机制
//4、创建窗口
//5、显示窗口
//6、消息循环

#define NumofColum  25


typedef struct charList
{
	TCHAR ch;
	struct charList *prev, *next;
} CharList;



typedef struct tagcharColum
{
	struct charList *head, *cur;//头节点   本节点
	int x, y;//坐标
	int  iStrNum;//记录总共显示的字符数量
	int iShowLen;//用来显示记录需显示的个数
}charQueue;


//用来保存所有需要显示的字符
struct showChar
{
	TCHAR myChar[60];
	int iNum;
}charArr[7]={//戴望舒《雨巷》
		{ TEXT("撑着油纸伞,独自彷徨在悠长,悠长又寂寥的雨巷"),23 },
		{ TEXT("我希望逢着,一个丁香一样的,结着愁怨的姑娘"), 21 },
		{ TEXT("她是有丁香一样的颜色,丁香一样的芬芳,丁香一样的忧愁"),26},
		{ TEXT("在雨中哀怨,哀怨又彷徨"), 11 },
		{ TEXT("她彷徨在这寂寥的雨巷,撑着油纸伞,像我一样,像我一样地,默默彳亍着,冷漠,凄清,又惆怅"), 43},
		{ TEXT("像梦一般的凄婉迷茫,像梦中飘过,一枝丁香的"), 21 },
		{ TEXT("她静默地远了,远了,到了颓圮的篱墙,走尽这雨巷"), 21 }
};



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM Param);


int WINAPI WinMain(HINSTANCE hInstance,//实例句柄
	HINSTANCE hPrevInstance,//上一个实例句柄
	PSTR szCMDline,//命令行
	int iCMDshow)//显示方式
{

	//unicode多字节编码 2字节
	//窗口注册


	//TCHAR多字节 
	TCHAR szClassName[] = L"love";
	MSG msg;

	 WNDCLASS wndClass;//窗口类
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = NULL;
	wndClass.hIcon = NULL;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szClassName;

	PlaySound(L"方圆几里.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);//播放音乐
	if (!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("注册失败"), TEXT("错误信息"),0);
		return -1; 
	}

	//创建窗口
	HWND hwnd =CreateWindow(szClassName, NULL, WS_POPUP | WS_THICKFRAME, 0, 0,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL,
		hInstance, NULL);

	PlaySound(L"方圆几里.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//播放音乐

	//时间种子 伪随机
	srand((unsigned int)time(NULL));
	
	//显示窗口
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);
	ShowCursor(FALSE);
	

	//消息处理
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


//一切形参都是拷贝
void CreateQueue(charQueue* cc, int cyScreen, int x)
{
	cc->head = NULL;
	cc->iShowLen = 1;
	cc->x = x;
	cc->y = rand() % 10 ? rand() % cyScreen : 0;//0在屏幕边界显示 ； 1--9 在其他地方随机显示
	int NumTmp = rand() % 7;//显示的字符串的编号
	cc->iStrNum = charArr[NumTmp].iNum;//字符个数
	
	CharList *front;

	cc->head = cc->cur = front = (CharList *)
				calloc(cc->iStrNum, sizeof(CharList));//连续的内存空间



	//双向寻循环链表 
	//将每一串字符构造成循环链表
	int i = 0;
	for ( i = 0; i <cc->iStrNum-1; i++)
	{
		cc->cur->prev = front;
		cc->cur->ch = charArr[NumTmp].myChar[i];
		front = cc->cur++;
		front->next = cc->cur;
	}

	//到最后
	cc->cur->prev = front;
	cc->cur->ch = charArr[NumTmp].myChar[i];
	cc->cur->next = cc->head;
	cc->head->prev = cc->cur;//首尾相连
	cc->cur = cc->head;//回到头部

}





LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
	WPARAM wParam, LPARAM Param)
{
	HDC hdc;//设备句柄 

	//static 提高生命周期
	static HDC hdcMem;//内存句柄
	static HBITMAP	hBitmap;//位图句柄
	static charQueue *AllChar;//队列字符
	HFONT hFont;//字体
	static int cxScreen, cyScreen;//屏幕大小
	static int iFrontWidth = 20, iFrontHeight = 20;//字体大小
	int i, j, y, greenToblack;
	charQueue *ccElem;//每一列字符串
	charList * temp;//每一个字符

	switch (message)
	{
	case WM_CREATE:
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		SetTimer(hwnd, 1, 70, NULL);//设置定时器  id为1 周期70ms

		hdc = GetDC(hwnd);
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, cxScreen, cyScreen);
		SelectObject(hdcMem, hBitmap);
		ReleaseDC(hwnd, hdc);

		hFont = CreateFont(iFrontHeight, iFrontWidth, 0/*角度*/, 0, FW_BOLD, 0, 0, 0,
			DEFAULT_CHARSET/*字符集*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY, FIXED_PITCH | FF_SWISS, NULL
			);
		
		SelectObject(hdcMem, hFont);
		DeleteObject(hFont);

		SetBkMode(hdcMem, TRANSPARENT);//将背景设为透明

		AllChar = (charQueue*)calloc(NumofColum, sizeof(charQueue));

		for (i = 0; i < NumofColum; i++)
		{
			CreateQueue(AllChar + i, cyScreen,( 50 * i + 20));
		}
		return 0;

	case WM_TIMER: 
		hdc = GetDC(hwnd);
		PatBlt(hdcMem, 0, 0, cxScreen, cyScreen, BLACKNESS);//将内存设备映像为黑色
		for ( i = 0; i < NumofColum; i++)
		{
			ccElem = AllChar + 1;
			temp = ccElem->head;
			SetTextColor(hdcMem, RGB(255, 255, 255));
			TextOut(hdcMem, ccElem->x, ccElem->y, (LPCWSTR)&temp->ch, 1);

			y = ccElem->y;
			greenToblack = 0;
			ccElem->head = ccElem->head->next;
			temp = temp->prev; 
			//遍历整个显示列,将这个显示列里的字符从下往上显示
			for ( j = 1; j < ccElem->iShowLen; j++)
			{
				SetTextColor(hdcMem, RGB(0, int(255 - j*greenToblack++), 0));
				TextOut(hdcMem, ccElem->x, ccElem->y, &temp->ch, 1);
				temp = temp->prev;
			}

			if (ccElem->iShowLen<ccElem->iStrNum)
			{
				ccElem->iShowLen++;
			}


			ccElem->y += iFrontHeight;
			if (ccElem->y - ccElem->iStrNum*iFrontHeight>cyScreen)
			{
				free(ccElem->cur);
				CreateQueue(ccElem, cyScreen, 128 * i + 17);
			}
		}
		hdc = GetDC(hwnd);
		BitBlt(hdc, 0, 0, cxScreen, cyScreen, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_RBUTTONDOWN:
		KillTimer(hwnd, 1);
		return 0;
	case WM_RBUTTONUP:
		SetTimer(hwnd, 1, 70, NULL);
		return 0;
		//处理善后工作
	case WM_KEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_DESTROY:
		KillTimer(hwnd, 1);
		DeleteObject(hBitmap);
		DeleteDC(hdcMem);
		for (i = 0; i<NumofColum; i++)
		{
			free((ccElem + i)->cur);
		}
		free(ccElem);
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hwnd, message,	wParam, Param);//windows默认消息处理函数
}










































