
#include<stdio.h>
#include<graphics.h>//ͼ�ο�easyX
#include<time.h>//time clock
#include<math.h>
#include<stdlib.h>//�ػ�����

#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
using namespace std;



//playsound() ֻ�ܷ�wav wav����������Դ�ļ�
//mciSendString() ���Բ����κ����͵�����  


#define PI 3.141592654
void drawDail(int h, int m, int s);
void mouceClickMsg();


int main()
{
	char arr[100];
	SYSTEMTIME sysTime;

	initgraph(640, 480);//�½�һ������ 640*480
	setbkmode(TRANSPARENT);
	settextstyle(30,0,"���Ĳ���");

	//settextcolor(RGB(230,50,180));
	//setbkcolor(LIGHTGRAY);//grey  gray
		
	//������


	//mciSendString("open Fade.mp3 alias bkmusic", 0, 0, 0);
	//mciSendString("play bkmusic repeat",0, 0, 0);



		//���̽���
	//1����ȡʱ��
	//while (1)
	//{
	//	GetLocalTime(&sysTime);//��ȡ��ǰʱ��
	//	sprintf(arr, "%d��%d��%d�� %dʱ%d��%d��", sysTime.wYear, sysTime.wMonth,
	//		sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	//	outtextxy(0, 0, arr);
	//	Sleep(1000);
	//}
	
	//����ÿ��ѭ��������ͼ��  ���µ�ͼ�񸲸�(����)�ɵ�ͼ����
	while (1)
	{
		loadimage(NULL, "1.jpg");
		setlinecolor(YELLOW);
		rectangle(500, 20, 630, 60);//���Ͻ� ���½ǵĵ�ȷ������
		outtextxy(520, 20, "�ػ�");


		rectangle(500, 200, 630, 240);
		outtextxy(520, 200, "��������");

		rectangle(500, 420, 630, 460);
		outtextxy(540, 420, "�˳�");

		GetLocalTime(&sysTime);//��ȡ��ǰʱ�� 
		drawDail(sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		 mouceClickMsg();
		Sleep(1000);//̫С ������
	
	//	cleardevice();//����
	}
	getchar();
	closegraph();
	return 0;
}


//������
void drawDail(int h,int m,int s)
{
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	circle(280, 240, 200);

	char arr[3];


	for (int i = 1; i <= 12; i++)//���̶�
	{
		sprintf(arr, "%d", i);
		outtextxy(280+(int)(190*sin(PI/6*i))-6, 240-(int)(190*cos(PI/6*i))-13, arr);
	}

	//��ʼ��ָ��  ʱ �� ��
	//��ɫ  ����  ��ϸ

	//�˴������Ƿ����ʱ���Լ�����Է����Ӱ��
	//ʱ��
	setlinecolor(RED);
	setlinestyle(PS_SOLID,7);//������
	line(280, 240, 280 + (int)(120 * sin(PI / 6 * h)), 240 - (int)(120 * cos(PI / 6 * h)));

		//����
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 3);
	line(280, 240, 280 + (int)(160 * sin(PI*m/30)), 240 - (int)(160 * cos(PI /30*m)));

	//����
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 1);
	line(280, 240, 280 + (int)(180 * sin(PI / 30*s)), 240 - (int)(180 * cos(PI / 30*s)));
	
}



void mouceClickMsg()
{
	if (MouseHit())//�����
	{
		MOUSEMSG mouceMsg = GetMouseMsg();
		switch (mouceMsg.uMsg)
		{
		case WM_LBUTTONDOWN://�������
			if (mouceMsg.x>500&&mouceMsg.x<630)
			{
				if (mouceMsg.y>20 && mouceMsg.y<60)
				{
					MessageBox(GetHWnd(), "200s��ػ�!!", "����", MB_OK);
					system("shutdown -s -t 200");
				}	
				else if (mouceMsg.y>200 && mouceMsg.y<240)
				{
					//��������
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

























