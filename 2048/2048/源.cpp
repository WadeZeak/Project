#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>//图标



int map[4][4] ;


void playgame();
void pfun();
void draw();
int gameover();



void pfun(int *a, int *b, int *c, int *d)
{
		int arr[] = { *a, *b, *c, *d };


		for (int i = 0,k=4; i < k; )
		{
		//	所有的0移动到后面
			if (!arr[i])
			{
				for (int j = i; j < k-1; j++)
				{
					arr[j] = arr[j + 1];
				}
				arr[k-1] = 0;
				k--;
			}
			else
			{
				i++;
			}
				
		}


		
		//将相同的数字进行相加
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 2; i++)
			{
				if (arr[i] == arr[i + 1])
				{
					arr[i] += arr[i + 1];
					for (int k = i; k <2; k++)
					{
						arr[k] = arr[k + 1];
					}
					arr[3] = 0;

				}
			}
		}
		

		*a=arr[0];
		*b=arr[1];
		*c=arr[2];
		*d=arr[3];
}


void playgame()
{
	switch (getch())//获取用户输入
	{
	case 'W':
	case 'w':
		for (int i = 0; i < 4; i++)
			pfun(&map[i][0], &map[i][1], &map[i][2], &map[i][3]);

		break;
	case 'A':
	case 'a':
		for (int i = 0; i < 4; i++)
			pfun(&map[0][i], &map[1][i], &map[2][i], &map[3][i]);

		break;
	case 'S':
	case 's':
		for (int i = 0; i < 4; i++)
			pfun(&map[i][3], &map[i][2], &map[i][1], &map[i][0]);

		break;
	case 'D':
	case 'd':
		for (int i = 0; i < 4; i++)
			pfun(&map[3][i], &map[2][i], &map[1][i], &map[0][i]);

		break;
	default:
		break;
	}

}




void draw(IMAGE *img)//绘制界面
{
	//每次都需要重新贴图
	putimage(0, 0, img);//贴图
	setlinecolor(WHITE);//线条颜色
	for (int i = 0; i < 4; i++)
	{
		line(160 * i, 0, 160 * i, 640);//竖线
		line(0, 160 * i, 640, 160 * i);//横线
	}
	char arr[10];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			//图形库不能直接使用 printf outtextxy
			//先把数组转换成字符串 sprintf
			sprintf(arr, "%d", map[i][j]);
			outtextxy(160 * i + 50, 160 * j + 50, arr);//在指定位置输出字符串
		}
	}
}

int gameover()
{

	//赢

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] >= 2048)
			{
				MessageBox(0, "Win", "恭喜", MB_OK);
							return  1;
			}
			
		}
	}


	//四周有相等的数字就可以继续游戏
	for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						//判断周围是否有重复部分
						if ((i + 1 < 4 && map[i][j] == map[i + 1][j]) || (j + 1 < 4 && map[i][j] == map[i][j + 1]))
						{
							//标记游戏还可以继续
							//变量标记
							return -1;
						}
					}
				}

	for (int i = 0; i < 3; i++)
	{
		if (map[i][3]==map[i+1][3]||map[3][i]==map[3][i+1])//最右边  最下面
		{
			return -1;
		}
	}

	//是否满掉
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <4 ; j++)
		{
			if (map[i][j]==0)
			{
				return -1;
			}
		}
	}


	return 0;//游戏结束

}

int main()
{
	
	initgraph(640, 640);//窗口大小
	IMAGE img;

	//字体颜色
	settextcolor(WHITE);//
	settextstyle(30, 0, "黑体");//字体格式
	setbkcolor(TRANSPARENT);//去掉文字黑边
	loadimage(&img, "背景.jpg", 640, 640);//加载素材


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = 0;
		}
	}
	


	srand((unsigned)time(NULL));
	
	int i, j;
	int flag;//判断输赢


	while (1)
	{
		do
		{
			i = rand() % 4;//行
			j = rand() % 4;//列		
		} while (map[i][j] != 0);

		map[i][j] = rand() % 2 * 2 + 2;//2或4

		draw(&img);
		playgame();

		flag = gameover();
		if (flag==1)
		{
			MessageBox(0, "Win", "恭喜", MB_OK);
			break; 
			
		}
		else if (flag==0)
		{
			MessageBox(0, "Lose", "what a pity!!", MB_OK);
			break;
		}
		
	}
	
	getchar();
	closegraph();

	return 0;


}