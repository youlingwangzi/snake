/*
 *程序名称：贪吃蛇v2.1
 *程序描述：一个简易的贪吃蛇小游戏
 *版本信息：v2.1
 *v1.1版本更新：1：加入菜单选择项
 *v1.2版本更新：1：修复菜单选择bug
 *v1.3班本更新：1：加入难度选择项
 *             2:增加键盘采集频率，大大增加操作灵敏度
 *             3:优化屏幕刷新频率，平衡刺眼的情况
 *v2.0版本更新：1:使用新的数据存储结构
 *             2:使用全新的蛇的形状，更加美观
 *             3:解决了1.X版本地图长宽不等距的问题
 *v2.1版本更新：1:修复蛇行进过程中快速切换方向至死亡的bug
 *             2:屏幕刷新改为蛇每前进一次刷新一次，闪屏更柔和
 *             3:更新退出后版本信息的输出
 */

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<conio.h>

#define N 25
#define M 22

//结构体名的宏定义
#define STRU_B struct board
//结构体元素part的值定义
#define bBORDER "◆"
#define sHEAD "■"
#define sBODY "◆"
#define sTAIL "◇"
#define bNONE "  "
#define bFOOD "☆"
//结构体元素drection的值定义
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
		printf("1：再来一局\n2：退出\n请选择：");
		fflush(stdin);
		scanf("%d", &ch);
	} while (ch == 1);
	print_last();
	return 0;
}

void print_first(void)
{
	printf("*************欢迎来到贪吃蛇*************\n\n");
	printf("使用键盘上、下、左、右键控制方向\n\n\n");
}

int degree_difficulty(void)
{
	int diff;
	do
	{
		printf("\n请选择难度：（1——3）：");
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
		printf("\n请输入正确的编号选择难度：（1——3）：");
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
	printf("*                      贪吃蛇v2.1                      *\n");
	printf("*                                                      *\n");
	printf("********************************************************\n");
	Sleep(1000);
}