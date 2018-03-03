#include"letter.h"




int main()
{
	srand((unsigned)time(NULL));//随机数种子 
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//生成窗口
	Interface();
	playGame();


	getchar(); 
	closegraph();
	return 0;
}

void Interface()
{
	
	loadimage(&bkImg, L"res/111.jpg",640,480);
	putimage(0, 0, &bkImg);//从指定的位置贴图

	setbkmode(TRANSPARENT);
	settextstyle(50, 0, L"华文彩云");
	settextcolor(YELLOW);
	outtextxy(160, 200, L"打字练习系统");
	
	settextstyle(20, 0, L"宋体");
	outtextxy(250, 280, L"◆版本 V2.3.1");
	outtextxy(250, 300 ,L"◆作者:+_+");
	settextstyle(15, 0, L"宋体");

	//多媒体设备接口 句柄 设备
	//打开设备(类 单声道 多声道) 播放设备 录制设备(采样率 数据块 对齐单位) 设置设备 
	mciSendString(L"open res/Fade.mp3 alias music",NULL,0,NULL);
	mciSendString(L"play music repeat", NULL, 0, NULL);

	int colorR = 255, colorG = 0;
	int speed = 5;
	while (!kbhit())//kbhit() 接受键盘输入,返回true,否则返回false
	{
		settextcolor(RGB(colorR, colorG, 0));
		outtextxy(50, 350, L"请按任意键继续.......");
		colorR-=speed;
		colorG+=speed;
		if (colorG>255||colorR<0)
			speed = -speed;
		Sleep(20);
	}
	
}

void playGame()
{
	cleardevice();
	settextstyle(30, 0, L"宋体");

	DWORD timePre, timeNow;//决定添加链表的速度
	//int tarLetter, keyLetter;
//	int letterX, letterY;


	char keyLetter;
	LETTER *pTmp = NULL;
	CreateList();

	timePre = GetTickCount();
	while (1)
	{


		timeNow = GetTickCount();
		if (timeNow-timePre>500)
		{
			AddLetterNode();
			timePre = timeNow;
		}
		Sleep(50);
		pTmp = pLetter->pNext;
		cleardevice();

		while (pTmp!=NULL)
		{
			outtextxy(pTmp->x, pTmp->y, pTmp->chr);
			pTmp->y += 1;
			pTmp=pTmp->pNext;
		}
		if (kbhit())
		{
			keyLetter = getch();
			LETTER *ptmp = pLetter->pNext;
			LETTER *ppre = pLetter;
			while (ptmp!=NULL)
			{
				if (ptmp->chr==keyLetter||ptmp->chr+32==keyLetter)//大小写均可
				{
					ppre->pNext = ptmp->pNext;
					free(ptmp);
					break;
				}
				else if (ptmp->y>WINDOW_HEIGHT)
				{
					ppre->pNext = ptmp->pNext;
					free(ptmp);
					ptmp = ppre->pNext;
				}
				else
				{
					ppre = ppre->pNext;
					ptmp = ptmp->pNext;
				}
				
			}
		}
		
	}

	getchar();

}


void CreateList()
{
	pLetter = (LETTER *)malloc(sizeof(LETTER));
	pLetter->pNext = NULL;

}


void AddLetterNode()
{
	LETTER *pTmp = NULL;
	LETTER *pNew = NULL;

	pTmp = pLetter;
	while (pTmp->pNext!=NULL)
	{
		pTmp=pTmp->pNext;
	}

	pNew = (LETTER *)malloc(sizeof(LETTER));
	pNew->chr = rand() % 26 + 65;
	pNew->x = rand() % (WINDOW_WIDTH - 60) + 30;
	pNew->y = 0;
	pNew->pNext = NULL;
	pTmp->pNext = pNew;
}











