
#include<Windows.h>
#include<time.h>
#include<stdlib.h>

#include<mmsyscom.h>
#pragma comment(lib, "WINMM.LIB")


//���ڵ���6����
//1������win32����
//2��ע�ᴰ��
//3�����ڴ������
//4����������
//5����ʾ����
//6����Ϣѭ��

#define NumofColum  25


typedef struct charList
{
	TCHAR ch;
	struct charList *prev, *next;
} CharList;



typedef struct tagcharColum
{
	struct charList *head, *cur;//ͷ�ڵ�   ���ڵ�
	int x, y;//����
	int  iStrNum;//��¼�ܹ���ʾ���ַ�����
	int iShowLen;//������ʾ��¼����ʾ�ĸ���
}charQueue;


//��������������Ҫ��ʾ���ַ�
struct showChar
{
	TCHAR myChar[60];
	int iNum;
}charArr[7]={//�����桶���
		{ TEXT("������ֽɡ,�����������Ƴ�,�Ƴ��ּ��ȵ�����"),23 },
		{ TEXT("��ϣ������,һ������һ����,���ų�Թ�Ĺ���"), 21 },
		{ TEXT("�����ж���һ������ɫ,����һ���ķҷ�,����һ�����ǳ�"),26},
		{ TEXT("�����а�Թ,��Թ������"), 11 },
		{ TEXT("������������ȵ�����,������ֽɡ,����һ��,����һ����,ĬĬ��ء��,��Į,����,�����"), 43},
		{ TEXT("����һ���������ã,������Ʈ��,һ֦�����"), 21 },
		{ TEXT("����Ĭ��Զ��,Զ��,�������ܵ���ǽ,�߾�������"), 21 }
};



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM Param);


int WINAPI WinMain(HINSTANCE hInstance,//ʵ�����
	HINSTANCE hPrevInstance,//��һ��ʵ�����
	PSTR szCMDline,//������
	int iCMDshow)//��ʾ��ʽ
{

	//unicode���ֽڱ��� 2�ֽ�
	//����ע��


	//TCHAR���ֽ� 
	TCHAR szClassName[] = L"love";
	MSG msg;

	 WNDCLASS wndClass;//������
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

	PlaySound(L"��Բ����.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);//��������
	if (!RegisterClass(&wndClass))
	{
		MessageBox(NULL, TEXT("ע��ʧ��"), TEXT("������Ϣ"),0);
		return -1; 
	}

	//��������
	HWND hwnd =CreateWindow(szClassName, NULL, WS_POPUP | WS_THICKFRAME, 0, 0,
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL,
		hInstance, NULL);

	PlaySound(L"��Բ����.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//��������

	//ʱ������ α���
	srand((unsigned int)time(NULL));
	
	//��ʾ����
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hwnd);
	ShowCursor(FALSE);
	

	//��Ϣ����
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


//һ���βζ��ǿ���
void CreateQueue(charQueue* cc, int cyScreen, int x)
{
	cc->head = NULL;
	cc->iShowLen = 1;
	cc->x = x;
	cc->y = rand() % 10 ? rand() % cyScreen : 0;//0����Ļ�߽���ʾ �� 1--9 �������ط������ʾ
	int NumTmp = rand() % 7;//��ʾ���ַ����ı��
	cc->iStrNum = charArr[NumTmp].iNum;//�ַ�����
	
	CharList *front;

	cc->head = cc->cur = front = (CharList *)
				calloc(cc->iStrNum, sizeof(CharList));//�������ڴ�ռ�



	//˫��Ѱѭ������ 
	//��ÿһ���ַ������ѭ������
	int i = 0;
	for ( i = 0; i <cc->iStrNum-1; i++)
	{
		cc->cur->prev = front;
		cc->cur->ch = charArr[NumTmp].myChar[i];
		front = cc->cur++;
		front->next = cc->cur;
	}

	//�����
	cc->cur->prev = front;
	cc->cur->ch = charArr[NumTmp].myChar[i];
	cc->cur->next = cc->head;
	cc->head->prev = cc->cur;//��β����
	cc->cur = cc->head;//�ص�ͷ��

}





LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
	WPARAM wParam, LPARAM Param)
{
	HDC hdc;//�豸��� 

	//static �����������
	static HDC hdcMem;//�ڴ���
	static HBITMAP	hBitmap;//λͼ���
	static charQueue *AllChar;//�����ַ�
	HFONT hFont;//����
	static int cxScreen, cyScreen;//��Ļ��С
	static int iFrontWidth = 20, iFrontHeight = 20;//�����С
	int i, j, y, greenToblack;
	charQueue *ccElem;//ÿһ���ַ���
	charList * temp;//ÿһ���ַ�

	switch (message)
	{
	case WM_CREATE:
		cxScreen = GetSystemMetrics(SM_CXSCREEN);
		cyScreen = GetSystemMetrics(SM_CYSCREEN);
		SetTimer(hwnd, 1, 70, NULL);//���ö�ʱ��  idΪ1 ����70ms

		hdc = GetDC(hwnd);
		hdcMem = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, cxScreen, cyScreen);
		SelectObject(hdcMem, hBitmap);
		ReleaseDC(hwnd, hdc);

		hFont = CreateFont(iFrontHeight, iFrontWidth, 0/*�Ƕ�*/, 0, FW_BOLD, 0, 0, 0,
			DEFAULT_CHARSET/*�ַ���*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DRAFT_QUALITY, FIXED_PITCH | FF_SWISS, NULL
			);
		
		SelectObject(hdcMem, hFont);
		DeleteObject(hFont);

		SetBkMode(hdcMem, TRANSPARENT);//��������Ϊ͸��

		AllChar = (charQueue*)calloc(NumofColum, sizeof(charQueue));

		for (i = 0; i < NumofColum; i++)
		{
			CreateQueue(AllChar + i, cyScreen,( 50 * i + 20));
		}
		return 0;

	case WM_TIMER: 
		hdc = GetDC(hwnd);
		PatBlt(hdcMem, 0, 0, cxScreen, cyScreen, BLACKNESS);//���ڴ��豸ӳ��Ϊ��ɫ
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
			//����������ʾ��,�������ʾ������ַ�����������ʾ
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
		//�����ƺ���
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

	return DefWindowProc(hwnd, message,	wParam, Param);//windowsĬ����Ϣ������
}










































