
/**********************************************

�ļ�����:main.cpp
�ļ�����:ʵ��һ����׳���
���뻷��:VS2013&&EasyX

***********************************************/

//EasyXͼ�ν����     MFC Win32 Qt  duilib


#include<graphics.h>//ͼ�ο�ͷ�ļ�
/*
1��ͼ�ο��е���Ҫ����
	�򿪽���	�رս���
	���ñ���			
	setbkcolor(BLACK);//ѡ�񱳾���ɫ
	cleardevice();//ʹ��ѡ������ɫˢ�±���

2����ɫ
	�����У�MFC/Win32/Cocos2d/Unity3d/UE4  ��ɫͨ��
	2.1 ����һЩ�궨��    RED  GREEN BLACK �������
	2.2 RGB��ʽ  RGB(255,255,255)//������
	2.3 HSL��ʽ (��ҵɫ��ģʽ,������Ļ,������Ļ)ɫ��,���Ͷ�,���� 

3���ı�
	3.1 ��С�͸�ʽ
	3.2 ���ֱ���
	3.3 ������ɫ
	3.4 �������


4����Ƶ
	4.1 ��Ӷ�ý���豸�ӿڵ�ͷ�ļ���ӿ�
		#include<mmsystem.h>
		#pragma comment(lib,"winmm.lib")
	4.2
		mp3
		//mp3��ʽ
		//mciSendString(L"open ./music/���ĳ��.mp3 alias BGM",0, 0, 0);
		//mciSendString(L"play BGM repeat", 0, 0, 0);

		wav
		//wav��ʽ
		//PlaySound(L"./music/�㻹Ҫ������.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

5��ͼƬ
	��������ͼƬ���� IMAGE 
	����ͼƬ:
	���ͼƬ:
	


*/

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<time.h>

#include"resource.h"//��Դͷ�ļ�

#define PI 3.14159265
#define NUM 13

//�̻����ṹ��
struct Jet
{
	int x;
	int y;//����
	
	int hx;
	int hy;//���� high ���������߶ȵ�����  ���ֵ���̻�

	int height;//�̻��ĸ߶�

	bool shoot;//�Ƿ���Է���

	DWORD t1, t2, dt;//�����̻����������ٶ�
	IMAGE img[2];//1 ��  2��
	byte n : 1;//ͼƬ�±�  0 1 //λ�� 1bit  
}jet[NUM];



//�̻��ṹ��
struct Fire
{
	int x, y;//���Ͻ�����
	int cen_x, cen_y;//��������
	int width, height;//ͼƬ�Ŀ�͸�
	int r;//�뾶��С���
	int max_r;//���뾶

	int xy[240][240];//���ص�ļ���
	bool show;//�Ƿ�����
	bool  draw;//�Ƿ�������ص�
	DWORD t1, t2, dt;

}fire[NUM];







void welcome();
void Init(int i);
void Load();//����ͼƬ
void Chose(DWORD &t1);//ɸѡ�̻���
void shoot();
void Show(DWORD *pMem);

int main()
{

	initgraph(1200, 800);//�򿪽��� ����ĳ� ��

	welcome();
	DWORD t1 = timeGetTime();

	DWORD *pMem = GetImageBuffer();//��ȡ�Դ�

	//ѭ����ʼ��
	for (int i = 0; i < NUM; i++)
	{  
		Init(i);
	}
	Load();


	BeginBatchDraw();//��ʼ����
	while (!_kbhit())//�ж��Ƿ��м�����Ϣ
	{
		Chose(t1);
		shoot();
		Show(pMem);
		FlushBatchDraw();//���Դ�չʾ����
	}
	getchar();
	closegraph();//�رս���
	return 0;
}




void welcome()
{

	//��Ƶ�ļ�

	//wav��ʽ
	//�����Դ�ļ�
	//PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//mp3
	mciSendString(L"open ./music/���ĳ��.mp3 alias BGM", 0, 0, 0);
	mciSendString(L"play BGM repeat", 0, 0, 0);


	//����
	settextcolor(YELLOW);//����������ɫ	
	//��εõ�һ��Բ�Ĺ켣�ϵ�N������
	for (int i = 0; i < 50; i++)
	{
		//Բ��ԭ��(600,200) �뾶 180
		int x = 600 + (int)(sin(PI * 2 * i / 60) * 180);
		int y = 200 + (int)(cos(PI * 2 * i / 60) * 180);
		cleardevice();;//ˢ��,���û��ָ����ɫ,Ĭ��Ϊ��ɫ
		settextstyle(i, 0, L"����");//���������ʽ���С  �� ��  ����
		outtextxy(x - 200, y, L"ƽ��ҹ�����׸���");//��ָ����λ������ı�
		outtextxy(x + 50, y + 100, L"���XXXXXXX");
		Sleep(25);//�����ٶ�
	}


	getchar();//��ס

	//���������,����ڶ�����

	cleardevice();
	settextstyle(25, 0, L"����");
	outtextxy(400, 150, L"ãã�˺��У�");
	outtextxy(400, 200, L"����˸ô���ģ������˸÷����ģ�");
	outtextxy(400, 250, L"���ǣ����ڵȵ�����");
	outtextxy(400, 450, L"������������ң�");
	outtextxy(400, 500, L"������������ʱ��Ϊ�⣬");
	outtextxy(400, 550, L"�����ڷ�ǰ��������꣬");
	outtextxy(400, 600, L"���������ǽ�һ�γ�Ե");
	outtextxy(650, 700, L"--By ĳĳĳ");

}


void  Init(int i)
{

	srand((unsigned int)time(NULL));

	int r[NUM] = { 120, 133, 125, 138, 156, 140, 148, 155, 132, 128,142,136,149 };
	int x[NUM] = { 120, 120, 110, 117, 93, 105, 110, 108, 116, 117, 104, 112, 118 };
	int y[NUM] = { 120, 120, 85, 120, 120, 103, 105, 107, 116, 118, 116, 107, 96 };


	//��ʼ���̻���
	jet[i].x = 0;
	jet[i].y = 0;
	jet[i].hx = 0;
	jet[i].hy = 0;
	jet[i].height = 0;
	jet[i].t1 = timeGetTime();
	jet[i].dt = rand() % 10;
	jet[i].n = 0;
	jet[i].shoot = false;

	//��ʼ���̻�
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




void Load()//����ͼƬ
{
	

	//�����̻�
	IMAGE fm;
	IMAGE gm;
	loadimage(&fm, L"./image/flower.jpg");

	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);//ÿһ���̻�
		for (int a = 0; a < 240; a++)
		{
			for (int b = 0; b < 240; b++)
			{
				fire[i].xy[a][b] = getpixel(a, b);//��ȡÿһ�����ص�
			}
		}
	}


	//�����̻���
	IMAGE jm;//�̻���ͼƬ
	loadimage(&jm, L"./image/shoot.jpg");

	//jm�ﱣ����һ����ͼƬ  �ָ�ͼƬ
	for (int i = 0; i < NUM; i++)
	{		
		SetWorkingImage(&jm);//���ù�����ͼƬ
		int n = rand() % 5;

		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL);//Ϊ�գ������ղŵĹ�������



}




void Chose(DWORD &t1)//ɸѡ�̻���
{

	DWORD t2 = timeGetTime();

	if (t2-t1>100)//���Ʒ���Ƶ��
	{
		int n = rand() % 20;//�������
		if (n<NUM&&jet[n].shoot==false&&fire[n].show==false)
		{
			jet[n].x = rand() % 1200;
			jet[n].y = rand() % 100+600;//����λ��
			jet[n].hx = jet[n].x ;
			jet[n].hy = rand()%400;//��ըλ��
			jet[n].height = jet[n].y-jet[n].hy;//�����߶�
			jet[n].shoot = true;//����
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}

		t1 = t2;
	}

}

//�̻�������

void shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		jet[i].t2 = timeGetTime();
		if (jet[i].t2-jet[i].t1>jet[i].dt&&jet[i].shoot==1)//ÿ���̻��������Ƶ��
		{
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//���̻���
			
				if (jet[i].y>jet[i].hy)
				{
					jet[i].n++;//���������Ч��
					jet[i].y -= 5;
				}
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//���̻���

				////�̻���������ߴ�,����
				if (jet[i].y<=jet[i].hy)
				{
					putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);//���̻���
					
					//���̻�������ߴ����긳���̻�
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



void Show(DWORD *pMem)//�Դ�ָ�� ���� ���������е����ص�ļ���
{

	int drt[16] = { 5, 5, 5, 5, 5, 5, 25, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		// ���ӱ�ը�뾶�������̻�������ʱ����������Ч��
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
		
	
		// ����ú��ڻ��ɱ�ը�����ݵ�ǰ��ը�뾶���̻�����ɫֵ�ӽ���ɫ�Ĳ������

		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a+=0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r*cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r*sin(a));

				if (x1>0&&x1<fire[i].width&&y1>0&&y1<fire[i].height)
				{
					//���ص����ɫ
					int b = fire[i].xy[x1][y1] & 0xff;
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (fire[i].xy[x1][y1] >> 16);


					int xx = (int)(fire[i].x + fire[i].r*cos(a));
					int yy = (int)(fire[i].y - fire[i].r*sin(a));

					if (r>0x20 && g>0x20 && b>0x20 && xx>0 && xx<1200 && yy>0 && yy>800)
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);//����ÿ�����ص����ɫ
					
				}
			
			}
			fire[i].draw = false;
		}
	}

	
}















