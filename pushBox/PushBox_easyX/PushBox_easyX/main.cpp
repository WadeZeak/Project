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
	mciSendString(L"open ./image/�㻹Ҫ������.mp3 alias backmusic",0,0,0 );
	mciSendString(L"play backmusic repeat",0,0,0);

	//����ͼƬ
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


void DrawMap()//��ͼ
{
	//��ֹ����
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
			case 1://ǽ
				putimage(i * 100, j * 100, &wallImg);

				break;
			case  3://Ŀ��
				putimage(i * 100, j * 100, &endImg);

				break;
			case 4://����
				putimage(i * 100, j * 100, &boxImg);

				break;
			case 5://��
				putimage(i * 100, j * 100, &peoImg);
				break;
			case 8://��+Ŀ�ĵ��غ�
				putimage(i * 100, j * 100, &darkImg);
				break;
			case 7://����+Ŀ�ĵ��غ�
				putimage(i * 100, j * 100, &peoImg);
				break;
			}
			
		}	
	}
	EndBatchDraw();
}



//���Ҹ����µߵ�
void PlayGame()
{

	char ch;
	int r, c;//�˵��к���
	int i, j;
	//ʱ�̵ĵõ��˵��±�
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (map[i][j] == 5 || map[i][j] == 8)//�˻�������Ŀ�ĵ��غ�
			{
				r = i;//�õ��˵��±�
				c = j;
				break;
			}
		}
		if (map[i][j] == 5 || map[i][j] == 8)
			break;
	}

	ch = getch();
	//getchar �����ַ� ��ʾ���� ���»س���ʱ�����
	//getch �����ַ� ����ʾ���� ֱ�ӽ���

	switch (ch)
	{
	case 'W'://�� �� ��һ������ 
	case 'w'://���ߵĻ�����  ������ɶҲ����
	case 72:// ��ֵ    ��

		if (map[r][c - 1] == 0 || map[r][c - 1] == 3)//�򻯺�Ĵ���   0-->5 3-->8   
		{
			map[r][c - 1] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)//�˵�ǰ��������  ��һ�� ���ӵ�ǰ����ʲô
		{
			if (map[r][c - 2] == 0 || map[r - 2][c] == 3)//�ж����ӵ�ǰ����ʲô
			{
				map[r][c - 2] += 4;
				map[r][c - 1] += 1;
				map[r][c] -= 5;
			}
		}

		break;
	case 'S':
	case 's':
	case 80:// ��

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
	case 75://��

		//�˵�ǰ���ǿյػ�����Ŀ�ĵ�
		if (map[r - 1][c] == 0 || map[r - 1][c] == 3)//�򻯺�Ĵ���   0-->5 3-->8   
		{
			map[r - 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//�˵�ǰ��������  ��һ�� ���ӵ�ǰ����ʲô
		{
			if (map[r - 2][c] == 0 || map[r - 2][c] == 3)//�ж����ӵ�ǰ����ʲô
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
	case 77://��

		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)//�򻯺�Ĵ���   0-->5 3-->8   
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





