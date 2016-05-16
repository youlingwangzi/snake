/*
 *�������ƣ�̰����v2.1
 *����������һ�����׵�̰����С��Ϸ
 *�汾��Ϣ��v2.1
 *v1.1�汾���£�1������˵�ѡ����
 *v1.2�汾���£�1���޸��˵�ѡ��bug
 *v1.3�౾���£�1�������Ѷ�ѡ����
 *             2:���Ӽ��̲ɼ�Ƶ�ʣ�������Ӳ���������
 *             3:�Ż���Ļˢ��Ƶ�ʣ�ƽ����۵����
 *v2.0�汾���£�1:ʹ���µ����ݴ洢�ṹ
 *             2:ʹ��ȫ�µ��ߵ���״����������
 *             3:�����1.X�汾��ͼ�����Ⱦ������
 *v2.1�汾���£�1:�޸����н������п����л�������������bug
 *             2:��Ļˢ�¸�Ϊ��ÿǰ��һ��ˢ��һ�Σ����������
 *             3:�����˳���汾��Ϣ�����
 */

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<conio.h>

#define N 25
#define M 22

//�ṹ�����ĺ궨��
#define STRU_B struct board
//�ṹ��Ԫ��part��ֵ����
#define bBORDER "��"
#define sHEAD "��"
#define sBODY "��"
#define sTAIL "��"
#define bNONE "  "
#define bFOOD "��"
//�ṹ��Ԫ��drection��ֵ����
#define UP 24
#define DOWN 25
#define RIGHT 26
#define LEFT 27

struct board{
	char drection;
	char part[4];
};

void print_first(void);
int degree_difficulty(void);
void start(int diff);
void initialise_board(STRU_B(*p)[N]);
void creat_sanke(STRU_B(*p)[N]);
void show_board(STRU_B(*p)[N]);
int move_snake(STRU_B(*p)[N], char drection);
void delete_tail(STRU_B(*p)[N]);
void lose(STRU_B(*p)[N]);
void add_food(STRU_B(*p)[N]);
void print_last();

int main(void)
{
	print_first();
	int ch;
	do
	{
		start(degree_difficulty());
		printf("1������һ��\n2���˳�\n��ѡ��");
		fflush(stdin);
		scanf("%d", &ch);
	} while (ch == 1);
	print_last();
	return 0;
}

void print_first(void)
{
	printf("*************��ӭ����̰����*************\n\n");
	printf("ʹ�ü����ϡ��¡����Ҽ����Ʒ���\n\n\n");
}

int degree_difficulty(void)
{
	int diff;
	do
	{
		printf("\n��ѡ���Ѷȣ���1����3����");
		scanf("%d", &diff);
		switch (diff)
		{
		case 1:diff = 10; break;
		case 2:diff = 6; break;
		case 3:diff = 2; break;
		default:
			break;
		}
		if (2 <= diff && diff <= 10)
			return diff;
		printf("\n��������ȷ�ı��ѡ���Ѷȣ���1����3����");
	} while (1);
}

void start(int diff)
{
	STRU_B board[M][N];
	char drection = RIGHT;
	int isn_lose = 1, i, dc;

	initialise_board(board);
	creat_sanke(board);

	while (isn_lose)
	{
		dc = 0;
		system("CLS");
		show_board(board);
		for (i = 0; i < diff; i++)
		{
			if (GetKeyState(VK_UP) < 0 && drection != DOWN && dc == 0) drection = UP, dc++;
			if (GetKeyState(VK_DOWN) < 0 && drection != UP && dc == 0) drection = DOWN, dc++;
			if (GetKeyState(VK_LEFT) < 0 && drection != RIGHT && dc == 0) drection = LEFT, dc++;
			if (GetKeyState(VK_RIGHT) < 0 && drection != LEFT && dc == 0) drection = RIGHT, dc++;
			Sleep(10);
		}
		isn_lose = move_snake(board, drection);
	}
	system("CLS");
	show_board(board);
}

void initialise_board(STRU_B(*p)[N])
{
	int i, j;
	for (j = 0; j < N; j++)
		strcpy(p[0][j].part , bBORDER);
	for (i = 1; i < M - 1; i++)
		for (j = 0; j < N; j++)
			if (j == 0 || j == (N - 1))
				strcpy(p[i][j].part , bBORDER);
			else
				strcpy(p[i][j].part , bNONE);
	for (j = 0; j < N; j++)
		strcpy(p[M - 1][j].part , bBORDER);
}

void creat_sanke(STRU_B(*p)[N])
{
	p[M / 2][N / 2].drection = RIGHT;
	strcpy(p[M / 2][N / 2].part , sHEAD);
	p[M / 2][N / 2 - 1].drection = RIGHT;
	strcpy(p[M / 2][N / 2 - 1].part , sBODY);
	p[M / 2][N / 2 - 2].drection = RIGHT;
	strcpy(p[M / 2][N / 2 - 2].part , sTAIL);
	add_food(p);
}

void show_board(STRU_B(*p)[N])
{
	int i, j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
			printf("%s", p[i][j].part);
		printf("\n");
	}
}

int move_snake(STRU_B(*p)[N], char drection)
{
	int i, j, NH = 0;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
		if (strcmp(p[i][j].part, bNONE) == 0 || strcmp(p[i][j].part, sBODY) == 0);

		else if (strcmp(p[i][j].part , sHEAD) == 0 && NH == 0)
		{
			p[i][j].drection = drection;
			switch (drection)
			{
			case UP:if (strcmp(p[i - 1][j].part , bBORDER) == 0) { lose(p); return 0; }
					if (strcmp(p[i - 1][j].part , bFOOD) == 0) add_food(p);
					else delete_tail(p);
					p[i - 1][j] = p[i][j];
					break;
			case DOWN:if (strcmp(p[i + 1][j].part, bBORDER) == 0) { lose(p); return 0; }
					  if (strcmp(p[i + 1][j].part, bFOOD) == 0) add_food(p);
					  else delete_tail(p);
					  p[i + 1][j] = p[i][j];
					  break;
			case LEFT:if (strcmp(p[i][j - 1].part, bBORDER) == 0) { lose(p); return 0; }
					  if (strcmp(p[i][j - 1].part, bFOOD) == 0) add_food(p);
					  else delete_tail(p);
					  p[i][j - 1] = p[i][j];
					  break;
			case RIGHT:if (strcmp(p[i][j + 1].part, bBORDER) == 0) { lose(p); return 0; }
					   if (strcmp(p[i][j + 1].part, bFOOD) == 0) add_food(p);
					   else delete_tail(p);
					   p[i][j + 1] = p[i][j];
					   break;
			}
			strcpy(p[i][j].part, sBODY);
			NH++;
		}
		}
	return 1;
}

void delete_tail(STRU_B(*p)[N])
{
	int i, j, NT = 0;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			if (strcmp(p[i][j].part, sTAIL) == 0 && NT == 0)
			{
				switch (p[i][j].drection)
				{
				case UP:strcpy(p[i - 1][j].part, p[i][j].part), strcpy(p[i][j].part, bNONE);
					break;
				case DOWN:strcpy(p[i + 1][j].part, p[i][j].part), strcpy(p[i][j].part, bNONE);
					break;
				case LEFT:strcpy(p[i][j - 1].part, p[i][j].part), strcpy(p[i][j].part, bNONE);
					break;
				case RIGHT:strcpy(p[i][j + 1].part, p[i][j].part), strcpy(p[i][j].part, bNONE);
					break;
				}
				NT++;
			}
}

void lose(STRU_B(*p)[N])
{
	strcpy(p[M / 2][N / 3].part, "Yo");
	strcpy(p[M / 2][N / 3 + 1].part, "u ");
	strcpy(p[M / 2][N / 3 + 2].part, "lo");
	strcpy(p[M / 2][N / 3 + 3].part, "se");
	strcpy(p[M / 2][N / 3 + 4].part, "! ");
}

void add_food(STRU_B(*p)[N])
{
	int x, y;
	srand(time(0));
	x = (rand() % N - 2) + 1;
	y = (rand() % M - 2) + 1;
	while (strcmp(p[y][x].part, bNONE) != 0)
	{
		x = (rand() % N - 2) + 1;
		y = (rand() % M - 2) + 1;
	}
	strcpy(p[y][x].part, bFOOD);
}

void print_last()
{
	system("CLS");
	printf("\n\n\n********************************************************\n");
	printf("*                                                      *\n");
	printf("*                      ̰����v2.1                      *\n");
	printf("*                                                      *\n");
	printf("********************************************************\n");
	Sleep(1000);
}