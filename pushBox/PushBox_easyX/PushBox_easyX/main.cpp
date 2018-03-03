#include<graphics.h>
#include<conio.h>
#include<mmsyscom.h>
#pragma comment(lib,"winmm.lib")

int map[7][10] = {
		{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
		{ 0, 1, 0, 0, 0, 0, 0, 0,1 },
		{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 5, 0, 4, 0, 0, 4, 0, 1 },
		{ 1, 0, 3, 3, 1, 0, 4, 0, 1, 1 },
		{ 1, 1, 3, 3, 1, 0, 0, 0, 1, 0 },
		{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 } };

void DrawMap();
void PlayGame();


IMAGE backImg, wallImg, blankImg, boxImg, darkImg, endImg, peoImg;

int main()
{
	initgraph(700, 1000);
	mciSendString(L"open ./image/你还要我怎样.mp3 alias backmusic",0,0,0 );
	mciSendString(L"play backmusic repeat",0,0,0);

	//加载图片
	loadimage(&backImg, L"./image/background.jpg", 700, 1000);
	loadimage(&wallImg, L"./image/wall.jpg", 100, 100);
	loadimage(&blankImg, L"./image/blank.jpg", 100, 100);
	loadimage(&boxImg, L"./image/box.jpg", 100, 100);
	loadimage(&darkImg, L"./image/dark.jpg", 100, 100);
	loadimage(&endImg, L"./image/end.jpg", 100, 100);
	loadimage(&peoImg, L"./image/people.jpg", 100, 100);

	while (1)
	{		
		 DrawMap();
		PlayGame();
	}

	getch();
	closegraph();
	return 0;

}


void DrawMap()//地图
{
	//防止闪屏
	BeginBatchDraw();
	cleardevice();

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (map[i][j])
			{
			case 0:
				putimage(i * 100, j * 100, &blankImg);
				break;
			case 1://墙
				putimage(i * 100, j * 100, &wallImg);

				break;
			case  3://目标
				putimage(i * 100, j * 100, &endImg);

				break;
			case 4://箱子
				putimage(i * 100, j * 100, &boxImg);

				break;
			case 5://人
				putimage(i * 100, j * 100, &peoImg);
				break;
			case 8://人+目的地重合
				putimage(i * 100, j * 100, &darkImg);
				break;
			case 7://箱子+目的地重合
				putimage(i * 100, j * 100, &peoImg);
				break;
			}
			
		}	
	}
	EndBatchDraw();
}



//左右跟上下颠倒
void PlayGame()
{

	char ch;
	int r, c;//人的行和列
	int i, j;
	//时刻的得到人的下标
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)//人或者人与目的地重合
			{
				r = i;//得到人的下标
				c = j;
				break;
			}
		}
		if (map[i][j] == 5 || map[i][j] == 8)
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

		if (map[r][c - 1] == 0 || map[r][c - 1] == 3)//简化后的代码   0-->5 3-->8   
		{
			map[r][c - 1] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)//人的前面是箱子  不一定 箱子的前面是什么
		{
			if (map[r][c - 2] == 0 || map[r - 2][c] == 3)//判断箱子的前面是什么
			{
				map[r][c - 2] += 4;
				map[r][c - 1] += 1;
				map[r][c] -= 5;
			}
		}

		break;
	case 'S':
	case 's':
	case 80:// 下

		if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
		{
			map[r][c + 1] += 5;
			map[r][c] -= 5;
		}
		else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
		{
			if (map[r][c + 2] == 0 || map[r][c + 2] == 3)
			{
				map[r][c + 2] += 4;
				map[r][c + 1] += 1;
				map[r][c] -= 5;
			}
		}
		break;

	case 'A':
	case 'a':
	case 75://左

		//人的前面是空地或者是目的地
		if (map[r - 1][c] == 0 || map[r - 1][c] == 3)//简化后的代码   0-->5 3-->8   
		{
			map[r - 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//人的前面是箱子  不一定 箱子的前面是什么
		{
			if (map[r - 2][c] == 0 || map[r - 2][c] == 3)//判断箱子的前面是什么
			{
				map[r - 2][c] += 4;

				map[r - 1][c] += 1;
				//-4+5

				map[r][c] -= 5;
			}
		}

		

		break;
	case 'D':
	case 'd':
	case 77://右

		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)//简化后的代码   0-->5 3-->8   
		{
			map[r + 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
		{
			if (map[r + 2][c] == 0 || map[r + 2][c] == 3)
			{
				map[r + 2][c] += 4;
				map[r + 1][c] += 1;
				map[r][c] -= 5;
			}
		}


		
		break;


	}


}





