//#include<stdio.h>
//#include<graphics.h>
//#include<stdlib.h>
//#include<time.h>
//#include<conio.h>
//#include<windows.h>//ͼ��
//
//
////������
//void Init();//��ʼ��
//void draw(IMAGE *img,int map[][4]);
//void deletemap(int *a, int *b, int *c, int d);
//
//int map[4][4] = {0};
//
//void Init()
//{
//	
//	int i, j, k;//k���Ԫ��
//	srand((unsigned)time(NULL));
//	initgraph(640, 480);//���ڴ�С
//
//	IMAGE img;
//	loadimage(&img, "����.jpg", 640, 640);//�����ز�
//
//	//������ɫ
//	settextcolor(RGB(254, 110, 110));//
//	settextstyle(30, 0, "����");//�����ʽ
//	setbkcolor(TRANSPARENT);//ȥ�����ֺڱ�
//	k = 0;
//
//	while (k!=-1)
//	{
//
//		do
//		{
//			i = rand() % 4;//��
//			j = rand() % 4;//��
//			map[i][j] = rand() % 2 * 2 + 2;//2��4
//		} while (map[i][j]==0);	
//		
//		
//		draw(&img, map);
//
//		//�������ڵ������Ƿ�һ��
//		//һ�� ���
//
//		switch (getch())//��ȡ�û�����
//		{
//		case 'W':
//		case 'w':
//			for (int i = 0; i < 4; i++)
//				delete(&map[i][0], &map[i][1], &map[i][2], &map[i][3]);
//
//			break;
//		case 'A':
//		case 'a':
//			for (int i = 0; i < 4; i++)
//				delete(&map[0][i], &map[1][i], &map[2][i], &map[3][i]);
//
//			break;
//		case 'S':
//		case 's':
//			for (int i = 0; i < 4; i++)
//				delete(&map[i][3], &map[i][2], &map[i][1], &map[i][0]);
//
//			break;
//		case 'D':
//		case 'd':
//			for (int i = 0; i < 4; i++)
//				delete(&map[3][i], &map[2][i], &map[1][i], &map[0][i]);
//
//			break;
//		default:
//			break;
//		}
//
//		k = -1;
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				//�ж���Χ�Ƿ����ظ�����
//				if ((i + 1 < 4 && map[i][j] == map[i + 1][j]) || (j + 1 < 4 && map[i][j] == map[i][j + 1]))
//				{
//					//�����Ϸ�����Լ���
//					//�������
//					k = 0;//��Ϸ����
//				}
//			}
//		}
//
//		if (k == -1)
//		{
//			//�Ƴ���Ϸ
//			draw(&img, map);
//			MessageBox(0, "Lose", "what a pity!!", MB_OK);
//			break;
//		}
//
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				if (map[i][j] >= 2048)//ͨ��
//				{
//					draw(&img, map);
//					MessageBox(0, "Win", "��ϲ", MB_OK);
//					return;
//				}
//
//			}
//		}
//
//	}
//
//
//}
//
//
//
//void draw(IMAGE *img,int map[][4])//���ƽ���
//{
//
//	putimage(0, 0, img);//��ͼ
//
//	setlinecolor(WHITE);//������ɫ
//
//	for (int i = 0; i < 4; i++)
//	{
//		line(160*i, 0,160*i,640);//����
//		line(0,160*i,640,160*i);//����
//	}
//
//	char arr[10];
//
//
//
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j= 0; j < 4; j++)
//		{
//		
//			//ͼ�οⲻ��ֱ��ʹ�� printf outtextxy
//			//�Ȱ�����ת�����ַ��� sprintf
//			sprintf(arr, "%d", map[i][j]);
//			outtextxy(160 * i+50, 160 * j+50, arr);//��ָ��λ������ַ���
//		}
//	}
//
//
//
//}
//
//void deletemap(int *a, int *b, int *c, int *d)//���в���
//{
//
//	int arr[4] = { *a, *b, *c, *d };
//	int k = 0;//0�ĸ���
//
//
//	for (int i = 0; i < 4; i++)
//	{
//		//�ų��м�0
//		if (!arr[i])
//			k++;
//	}
//
//	int j;
//	for (int i = 0; i <4- k; i++)//4-k��Ԫ�ز�Ϊ0
//	{
//		if (!arr[i])
//		{
//			j = i + 1;
//			while (!arr[j])
//			{
//				j++;
//			}
//			arr[i] = arr[j];
//			arr[j] = 0;
//		}
//	}
//
//
//	//��ͬԪ�����
//	for (int i = 0; i < 4-k; i++)
//	{
//		for (int m= 0; m< 4-k; m++)
//		{
//			int n;
//			if (arr[m]==arr[m+1])
//			{
//				arr[m] *= 2;
//				for ( n = m+1; n < 3; n++)
//				{
//					arr[n] = arr[n - 1];//�����ƶ�
//			
//				}
//				arr[n] = 0;
//			}
//		}
//	}
//	//�����Ƿ��д���2048������
//
//	
//
//
//	//������ɺ�
//	*a = arr[0];
//	*b = arr[1];
//	*c = arr[2];
//	*d = arr[3];
//}
//
//
//int main()
//{
//	HWND hwnd = GetConsoleWindow();
//	SendMessage(hwnd, WM_SETICON,ICON_SMALL, (LPARAM)LoadIcon(GetModuleHandle(NULL),MAKEINTRESOURCE(101)));
//
//
//	Init();
//	getchar();
//	closegraph();
//
//	return 0;
//}
//
//
