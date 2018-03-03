#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>//ͼ��



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
		//	���е�0�ƶ�������
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


		
		//����ͬ�����ֽ������
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
	switch (getch())//��ȡ�û�����
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




void draw(IMAGE *img)//���ƽ���
{
	//ÿ�ζ���Ҫ������ͼ
	putimage(0, 0, img);//��ͼ
	setlinecolor(WHITE);//������ɫ
	for (int i = 0; i < 4; i++)
	{
		line(160 * i, 0, 160 * i, 640);//����
		line(0, 160 * i, 640, 160 * i);//����
	}
	char arr[10];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			//ͼ�οⲻ��ֱ��ʹ�� printf outtextxy
			//�Ȱ�����ת�����ַ��� sprintf
			sprintf(arr, "%d", map[i][j]);
			outtextxy(160 * i + 50, 160 * j + 50, arr);//��ָ��λ������ַ���
		}
	}
}

int gameover()
{

	//Ӯ

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] >= 2048)
			{
				MessageBox(0, "Win", "��ϲ", MB_OK);
							return  1;
			}
			
		}
	}


	//��������ȵ����־Ϳ��Լ�����Ϸ
	for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						//�ж���Χ�Ƿ����ظ�����
						if ((i + 1 < 4 && map[i][j] == map[i + 1][j]) || (j + 1 < 4 && map[i][j] == map[i][j + 1]))
						{
							//�����Ϸ�����Լ���
							//�������
							return -1;
						}
					}
				}

	for (int i = 0; i < 3; i++)
	{
		if (map[i][3]==map[i+1][3]||map[3][i]==map[3][i+1])//���ұ�  ������
		{
			return -1;
		}
	}

	//�Ƿ�����
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


	return 0;//��Ϸ����

}

int main()
{
	
	initgraph(640, 640);//���ڴ�С
	IMAGE img;

	//������ɫ
	settextcolor(WHITE);//
	settextstyle(30, 0, "����");//�����ʽ
	setbkcolor(TRANSPARENT);//ȥ�����ֺڱ�
	loadimage(&img, "����.jpg", 640, 640);//�����ز�


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = 0;
		}
	}
	


	srand((unsigned)time(NULL));
	
	int i, j;
	int flag;//�ж���Ӯ


	while (1)
	{
		do
		{
			i = rand() % 4;//��
			j = rand() % 4;//��		
		} while (map[i][j] != 0);

		map[i][j] = rand() % 2 * 2 + 2;//2��4

		draw(&img);
		playgame();

		flag = gameover();
		if (flag==1)
		{
			MessageBox(0, "Win", "��ϲ", MB_OK);
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