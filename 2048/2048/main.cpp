//#include<stdio.h>
//#include<graphics.h>
//#include<stdlib.h>
//#include<time.h>
//#include<conio.h>
//#include<windows.h>//图标
//
//
////函数区
//void Init();//初始化
//void draw(IMAGE *img,int map[][4]);
//void deletemap(int *a, int *b, int *c, int d);
//
//int map[4][4] = {0};
//
//void Init()
//{
//	
//	int i, j, k;//k标记元素
//	srand((unsigned)time(NULL));
//	initgraph(640, 480);//窗口大小
//
//	IMAGE img;
//	loadimage(&img, "背景.jpg", 640, 640);//加载素材
//
//	//字体颜色
//	settextcolor(RGB(254, 110, 110));//
//	settextstyle(30, 0, "黑体");//字体格式
//	setbkcolor(TRANSPARENT);//去掉文字黑边
//	k = 0;
//
//	while (k!=-1)
//	{
//
//		do
//		{
//			i = rand() % 4;//行
//			j = rand() % 4;//列
//			map[i][j] = rand() % 2 * 2 + 2;//2或4
//		} while (map[i][j]==0);	
//		
//		
//		draw(&img, map);
//
//		//两个相邻的数字是否一样
//		//一样 相加
//
//		switch (getch())//获取用户输入
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
//				//判断周围是否有重复部分
//				if ((i + 1 < 4 && map[i][j] == map[i + 1][j]) || (j + 1 < 4 && map[i][j] == map[i][j + 1]))
//				{
//					//标记游戏还可以继续
//					//变量标记
//					k = 0;//游戏继续
//				}
//			}
//		}
//
//		if (k == -1)
//		{
//			//推出游戏
//			draw(&img, map);
//			MessageBox(0, "Lose", "what a pity!!", MB_OK);
//			break;
//		}
//
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 4; j++)
//			{
//				if (map[i][j] >= 2048)//通关
//				{
//					draw(&img, map);
//					MessageBox(0, "Win", "恭喜", MB_OK);
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
//void draw(IMAGE *img,int map[][4])//绘制界面
//{
//
//	putimage(0, 0, img);//贴图
//
//	setlinecolor(WHITE);//线条颜色
//
//	for (int i = 0; i < 4; i++)
//	{
//		line(160*i, 0,160*i,640);//竖线
//		line(0,160*i,640,160*i);//横线
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
//			//图形库不能直接使用 printf outtextxy
//			//先把数组转换成字符串 sprintf
//			sprintf(arr, "%d", map[i][j]);
//			outtextxy(160 * i+50, 160 * j+50, arr);//在指定位置输出字符串
//		}
//	}
//
//
//
//}
//
//void deletemap(int *a, int *b, int *c, int *d)//对列操作
//{
//
//	int arr[4] = { *a, *b, *c, *d };
//	int k = 0;//0的个数
//
//
//	for (int i = 0; i < 4; i++)
//	{
//		//排除中间0
//		if (!arr[i])
//			k++;
//	}
//
//	int j;
//	for (int i = 0; i <4- k; i++)//4-k个元素不为0
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
//	//相同元素相加
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
//					arr[n] = arr[n - 1];//往后移动
//			
//				}
//				arr[n] = 0;
//			}
//		}
//	}
//	//查找是否有大于2048的数字
//
//	
//
//
//	//处理完成后
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
