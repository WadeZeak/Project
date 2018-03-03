/*

�ļ�����main.cpp
�ļ�����:ʵ�ֺ����������Ϸ

*/


#include <windows.h> //ͷ�ļ�

//ר�Ŵ������ֵ�ͷ�ļ� ���ļ� MCI(media control interface)
//��ý���豸�ӿڵ�ͷ�ļ�����ļ�
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib")//�ں�͸����ͼ�ĺ��� TransparentBlt


#include<time.h>
#include<stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define NUM 30

//ȫ�ֱ���
HBITMAP g_BackBmp, g_DragonBmp, g_FireBmp, g_EnemyBmp;//����ͼƬ
HDC g_hdc, g_memdc, g_bufdc;//�����豸 �����豸 �����豸
int g_DragonX;
int g_DragonY;
int g_bgoff;//����ƫ����
int g_FireNum = 0;//��������

DWORD g_tPre, g_tNow;//����
DWORD g_etPre, g_etNow;//����

DWORD g_mtPre,g_mtNow;




struct Fire
{
	int x;
	int y;//��������
	bool exist;//�����Ƿ����
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
	int nShowCmd) //������ 
{
	//MessageBox(NULL, L"HELLO WORLD", L"", MB_YESNO);
	//�1������
	//1.��Ҫʲô���ӵĴ���
	WNDCLASSEX wnd = { 0 }; //����һ������
	wnd.cbSize = sizeof(WNDCLASSEX);     //����Ӧ��ռ���ڴ�
	wnd.hInstance = hInstance;           //����ĵ�ǰʵ�����
	wnd.style = CS_HREDRAW | CS_VREDRAW; //������Ըı�ˮƽ�ʹ�ֱ����
	wnd.hbrBackground = (HBRUSH)5;		 //������ɫ
	wnd.hCursor = NULL;					 //�����ʽ  
	wnd.hIcon = NULL;					 //�����ͼ��
	wnd.cbClsExtra = 0;          //����ĸ����ڴ�
	wnd.cbWndExtra = 0;          //���ڵĸ����ڴ�
	wnd.lpszMenuName = NULL;	 //�˵�
	wnd.lpszClassName = L"�ж��ڿ���"; //���ڵ�������
	wnd.lpfnWndProc = WndProc;   //���ڵĹ��̺���

	//2.ע�ᴰ��
	RegisterClassEx(&wnd); //��鴰���Ƿ����

	//3.����
	HWND hWnd = CreateWindow(L"�ж��ڿ���", L"DragonWarDemo",
		WS_OVERLAPPEDWINDOW, 300, 200, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//4.��ʾ�͸���
	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	//ִ��ʧ��
	if (!GameInit(hWnd))
	{
		return -1;
	}


	//PlaySound(L"res/music.wav", //·��
	//	NULL, //���
	//	SND_FILENAME | SND_LOOP | SND_ASYNC);
	//SND_FILENAME ͨ���ļ���·��������(������Դ)
	//SND_LOOP ѭ������
	//SND_ASYNC �첽����(˳��ṹ)ִ�иú����������أ�����ִ�����µĴ���
	


	//��Ϣѭ��
	MSG msg = { 0 };
	while (msg.message != WM_QUIT) //ֻҪ�ͻ������˳������ָ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))//��Ϣ����ȥ�����Ϣ
		{
			//ջ��������?�����   �����������ð�? ����Ϸ
			TranslateMessage(&msg);  //������Ϣ  �����ֵ--->�ַ���Ϣ
			DispatchMessage(&msg);   //������Ϣ ���͸�ϵͳ 
		}
		else
		{
			g_mtNow = GetTickCount();
			g_tNow = GetTickCount();//��ȡ��ǰϵͳʱ��
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

//���ڵĹ��̺���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE://��괦����  
		//��������ƶ�
		g_DragonX = LOWORD(lParam);
		g_DragonY = HIWORD(lParam);
		break;


	case WM_CREATE:
		CreateList();
		break;
	case WM_LBUTTONDOWN://����������
		//�Ի����������г�ʼ��
		for (int i = 0; i < NUM; i++)
		{
			if (!fire[i].exist)//�������
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




//��Ϸ��ʼ��
//1������ͼƬ
//2����ʼ���ؼ�����
//3������ͼ��ʹ�õļ���(GDI�����弼��)
BOOL GameInit(HWND hWnd)
{
	srand((unsigned int)time(NULL));//���������
	//��ʼ��������Ļ�ͼ��ϵ
	g_hdc = GetDC(hWnd);//���ڵ��豸����
	g_memdc = CreateCompatibleDC(g_hdc);
	g_bufdc = CreateCompatibleDC(g_hdc);

	HBITMAP  bmp = CreateCompatibleBitmap(g_hdc, WINDOW_WIDTH,WINDOW_HEIGHT);


	//����ͼƬ
	g_BackBmp = (HBITMAP)LoadImage(NULL, L"res/bg.bmp", IMAGE_BITMAP, WINDOW_WIDTH, 
									WINDOW_HEIGHT, LR_LOADFROMFILE);
	g_DragonBmp = (HBITMAP)LoadImage(NULL, L"res/long00.bmp", IMAGE_BITMAP,
									284 , 206, LR_LOADFROMFILE);
	g_FireBmp = (HBITMAP)LoadImage(NULL, L"res/fire.bmp", IMAGE_BITMAP, 
										100, 34, LR_LOADFROMFILE);
	g_EnemyBmp = (HBITMAP)LoadImage(NULL, L"res/long005.bmp", IMAGE_BITMAP, 
										300, 300, LR_LOADFROMFILE);

	//1
	SelectObject(g_memdc, bmp);//����λͼ����g_memdc

	g_DragonX = WINDOW_WIDTH - 142;
	g_DragonY = 0;
	g_bgoff = 0;


	ShowCursor(false);//�������


//	INT G_bgoff=0;//����ƫ����


	return TRUE;
}


//��Ϸ�Ļ���
//͸����ͼ�����ַ���
//���ַ�
//ɫ�ʷ�	TransparntBlt()

VOID GamePaint(HWND hWnd)
{
	
	//����
	//2
	SelectObject(g_bufdc, g_BackBmp);//��ͼƬ����g_bufdc

	//3
	BitBlt(g_memdc, 0, 0, g_bgoff, WINDOW_HEIGHT, g_bufdc, WINDOW_WIDTH-g_bgoff, 0, SRCCOPY);//g_bufdc�е���������g_memdc
	BitBlt(g_memdc, g_bgoff, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_bufdc, 0, 0, SRCCOPY);

	if (++g_bgoff>=WINDOW_WIDTH)//��������
	{
		g_bgoff = 0;
	}


	//��
	//2
	SelectObject(g_bufdc, g_DragonBmp);
	//3	
	//BitBlt(g_memdc, 0, 0, 284, 206, g_bufdc, 0, 0, SRCCOPY);
	TransparentBlt(g_memdc, g_DragonX, g_DragonY, 142, 103, g_bufdc, 0, 0,284,206, RGB(255,255,255));



	//����
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
				//���ַ� ͸��������
				BitBlt(g_memdc, fire[i].x, fire[i].y, 50, 34, g_bufdc, 50, 0, SRCAND);//���
				BitBlt(g_memdc, fire[i].x, fire[i].y, 50, 34, g_bufdc, 0, 0, SRCPAINT);//����

				fire[i].x -= 10;//���������ƶ�
				if (fire[i].x <= 0)//���򳬹��߽�
				{
					g_FireNum--;//������������
					fire[i].exist = false;
				}
			}		
		}
	}
	
	//����

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
	BitBlt(g_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, g_memdc, 0, 0, SRCCOPY);//��g_memdc�е���������g_hdc

	g_tPre = GetTickCount();//��ȡ��ǰϵͳʱ��
}



//��Ϸ��Դ������

BOOL GameClearUp(HWND hWnd)
{
	return TRUE;

}




void CreateList()
{
	//pEnemy�ڲ�x,y����
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





//���� ���� ����

//�� ���� ����

//��һ������Χ�����ķ�Χ������ײ�������exist=false