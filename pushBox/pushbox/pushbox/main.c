#include<stdio.h>
#include<conio.h>

int map[7][10] = {
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{0,1,0,0,0,0,1,1,1},
		{1,1,0,1,1,1,0,0,0,1},
		{1,0,5,0,4,0,0,4,0,1},
		{1,0,3,3,1,0,4,0,1,1},
		{1,1,3,3,1,0,0,0,1,0},
		{0,1,1,1,1,1,1,1,1,0}};

void DrawMap();
void PlayGame();

int main()
{
	while (1)
	{
		system("cls");
		DrawMap();
		PlayGame();
	}
	
	getchar();
	return 0;
}


void DrawMap()//地图
{

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//printf("%d ",map[i][j]);

			switch (map[i][j])
			{
			case 0:
				printf(" ");
				break;
			case 1://墙
				printf("■");
				break;
			case  3://目标
				printf("☆");
				break;
			case 4://箱子
				printf("□");
				break;
			case 5://人
				printf("♀");
				break;
			case 8://人+目的地重合
				printf("♀");
				break;
			case 7://箱子+目的地重合
				printf("★");
				break;
			}
			
		}
		printf("\n");
	}

}


//玩游戏
void PlayGame()
{

	char ch;
	int r,c;//人的行和列
	int i, j;
	//时刻的得到人的下标
	for ( i = 0; i < 7; i++)
	{
		for ( j = 0; j < 10; j++)
		{
			if (map[i][j]==5||map[i][j]==8)//人或者人与目的地重合
			{
				r = i;//得到人的下标
				c = j;
				break;
			}
		}
		if (map[i][j] == 5||map[i][j] == 8)
			break;
	}

	ch = getch();
	//getchar 接受字符 显示回文 按下回车的时候结束
	//getch 接受字符 不显示回文 直接接受

	switch (ch)
	{
	case 'W'://按 上 不一定能走 
	case 'w'://能走的话处理  不能走啥也不干
	case 72:// 键值    上

		//人的前面是空地或者是目的地
		if (map[r-1][c]==0||map[r-1][c]==3)//简化后的代码   0-->5 3-->8   
		{
			map[r - 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//人的前面是箱子  不一定 箱子的前面是什么
		{
			if (map[r - 2][c] == 0 || map[r - 2][c]==3)//判断箱子的前面是什么
			{
				map[r - 2][c] += 4;
		
				map[r - 1][c] += 1;
				//-4+5

				map[r][c] -= 3;
			}
		}

		//人的前面是空地
		//if (map[r-1][c]==0)//人的前面是空地
		//{
		//	map[r - 1][c] = 5;//人往前走 前面的元素变成了5

		//	//if (map[r][c]==8)//人原来的位置是目的地
		//	//	map[r][c] = 3;//人走之后变成目的地
		//	//else
		//	//	map[r][c] = 0;//人走之后，人原来的位置变成空地

		//	map[r][c] -= 5;
		//}
		//else if (map[r-1][c]==3)//人的前面是目的地
		//{
		//	map[i - 1][r] = 8;
		//	map[r][c] -=5;
		//}

		break;




	case 'S':
	case 's':
	case 80:// 下

		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)//简化后的代码   0-->5 3-->8   
		{
			map[r + 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r + 1][c] == 4 || map[r +1][c] == 7)
		{
			if (map[r + 2][c] == 0 || map[r + 2][c] == 3)
			{
				map[r + 2][c] += 4;
				map[r + 1][c] += 1;
				map[r][c] -= 3;
			}
		}
		break;




	case 'A':
	case 'a':
	case 75://左
		if (map[r ][c-1] == 0 || map[r][c-1] == 3)//简化后的代码   0-->5 3-->8   
		{
			map[r][c-1] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r ][c-1] == 4 || map[r][c-1] == 7)//人的前面是箱子  不一定 箱子的前面是什么
		{
			if (map[r][c-2] == 0 || map[r - 2][c] == 3)//判断箱子的前面是什么
			{
				map[r][c-2] += 4;
				map[r][c-1] += 1;
				map[r][c] -= 3;
			}
		}


		break;
	case 'D':
	case 'd':
	case 77://右
		if (map[r ][c+1] == 0 || map[r][c+1] == 3)
		{
			map[r ][c+1] += 5; 
			map[r][c] -= 5;
		}
		else if (map[r ][c+1] == 4 || map[r ][c+1] == 7)
		{
			if (map[r][c+2] == 0 || map[r][c+2] == 3)
			{
				map[r][c+2] += 4;
				map[r ][c+1] += 1;
				map[r][c] -= 3;
			}
		}
		break;


	}


}




