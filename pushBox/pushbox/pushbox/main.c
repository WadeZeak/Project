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


void DrawMap()//��ͼ
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
			case 1://ǽ
				printf("��");
				break;
			case  3://Ŀ��
				printf("��");
				break;
			case 4://����
				printf("��");
				break;
			case 5://��
				printf("��");
				break;
			case 8://��+Ŀ�ĵ��غ�
				printf("��");
				break;
			case 7://����+Ŀ�ĵ��غ�
				printf("��");
				break;
			}
			
		}
		printf("\n");
	}

}


//����Ϸ
void PlayGame()
{

	char ch;
	int r,c;//�˵��к���
	int i, j;
	//ʱ�̵ĵõ��˵��±�
	for ( i = 0; i < 7; i++)
	{
		for ( j = 0; j < 10; j++)
		{
			if (map[i][j]==5||map[i][j]==8)//�˻�������Ŀ�ĵ��غ�
			{
				r = i;//�õ��˵��±�
				c = j;
				break;
			}
		}
		if (map[i][j] == 5||map[i][j] == 8)
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

		//�˵�ǰ���ǿյػ�����Ŀ�ĵ�
		if (map[r-1][c]==0||map[r-1][c]==3)//�򻯺�Ĵ���   0-->5 3-->8   
		{
			map[r - 1][c] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)//�˵�ǰ��������  ��һ�� ���ӵ�ǰ����ʲô
		{
			if (map[r - 2][c] == 0 || map[r - 2][c]==3)//�ж����ӵ�ǰ����ʲô
			{
				map[r - 2][c] += 4;
		
				map[r - 1][c] += 1;
				//-4+5

				map[r][c] -= 3;
			}
		}

		//�˵�ǰ���ǿյ�
		//if (map[r-1][c]==0)//�˵�ǰ���ǿյ�
		//{
		//	map[r - 1][c] = 5;//����ǰ�� ǰ���Ԫ�ر����5

		//	//if (map[r][c]==8)//��ԭ����λ����Ŀ�ĵ�
		//	//	map[r][c] = 3;//����֮����Ŀ�ĵ�
		//	//else
		//	//	map[r][c] = 0;//����֮����ԭ����λ�ñ�ɿյ�

		//	map[r][c] -= 5;
		//}
		//else if (map[r-1][c]==3)//�˵�ǰ����Ŀ�ĵ�
		//{
		//	map[i - 1][r] = 8;
		//	map[r][c] -=5;
		//}

		break;




	case 'S':
	case 's':
	case 80:// ��

		if (map[r + 1][c] == 0 || map[r + 1][c] == 3)//�򻯺�Ĵ���   0-->5 3-->8   
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
	case 75://��
		if (map[r ][c-1] == 0 || map[r][c-1] == 3)//�򻯺�Ĵ���   0-->5 3-->8   
		{
			map[r][c-1] += 5; //5-->0  8-->3
			map[r][c] -= 5;
		}
		else if (map[r ][c-1] == 4 || map[r][c-1] == 7)//�˵�ǰ��������  ��һ�� ���ӵ�ǰ����ʲô
		{
			if (map[r][c-2] == 0 || map[r - 2][c] == 3)//�ж����ӵ�ǰ����ʲô
			{
				map[r][c-2] += 4;
				map[r][c-1] += 1;
				map[r][c] -= 3;
			}
		}


		break;
	case 'D':
	case 'd':
	case 77://��
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




