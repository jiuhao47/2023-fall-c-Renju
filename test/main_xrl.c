#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 15
#define BLACKtem 10
#define WHITEtem 11
#define BLACK 20
#define WHITE 21
#define CHENG_5_STRING "11111"
#define HUO_4_STRING "011110"
#define CHONG_4_STRING_1_1 "011112"
#define CHONG_4_STRING_1_2 "211110"
#define CHONG_4_STRING_2_1 "10111"
#define CHONG_4_STRING_2_2 "11101"
#define CHONG_4_STRING_3 "11011"
#define DAN_HUO_3_STRING "01110"
#define TIAO_HUO_3_STRING_1_1 "010110"
#define TIAO_HUO_3_STRING_1_2 "011010"
#define MIAN_3_1_1 "001112"
#define MIAN_3_1_2 "211100"
#define MIAN_3_2_1 "010112"
#define MIAN_3_2_2 "211010"
#define MIAN_3_3_1 "011012"
#define MIAN_3_3_2 "210110"
#define MIAN_3_4_1 "10011"
#define MIAN_3_4_2 "11001"
#define MIAN_3_5 "10101"
#define MIAN_3_6 "2011102"
#define HUO_2_STRING_1 "001100"
#define HUO_2_STRING_2 "01010"
#define HUO_2_STRING_3 "1001"
#define MIAN_2_1_1 "000112"
#define MIAN_2_1_2 "211000"
#define MIAN_2_2_1 "001012"
#define MIAN_2_2_2 "210100"
#define MIAN_2_3_1 "010012"
#define MIAN_2_3_2 "210010"
#define MIAN_2_4 "10001"
int Board[SIZE][SIZE];
int AI;
int x, y;
char strxb[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char stryb[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char strxyb[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char stryxb[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char strxw[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char stryw[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char strxyw[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
char stryxw[10] = {'2', '2', '2', '2', '2', '2', '2', '2', '2', '\0'};
void Mode();
void InitBoardArray(); // 初始化空棋盘
void DisplayBoard();   // 显示棋盘
void WHITEAI();
// void BLACKAI();
int scoreWhite(int, int);
int scoredirections(char *);
int banthree(char *);
int banfour(char *);
int bansix(char *);
int ban(int, int);
int scoreBlack_notban(int, int);
int scoreBlack(int, int);
int scoreAI(int, int, int);

int main()
{
	int turn = 1;
	int xb;
	char yb;
	char str[10];
	InitBoardArray();
	DisplayBoard();
	printf("玩家执白请按1，玩家执黑请按2\n");
	scanf("%d", &AI);
	getchar();
	printf("%d-\n", AI);
	printf("输入规范A1\n");

	while (AI == 1)
	{
		if (turn % 2 == 1)
		{
			WHITEAI();
			Board[x][y] = BLACKtem;
			DisplayBoard();
			Board[x][y] = BLACK;
		}
		else if (turn % 2 == 0)
		{
			scanf("%c%d", &yb, &xb);
			getchar();

			//			scanf("%s",&str);
			y = yb - 'A';
			x = 15 - xb;
			Board[x][y] = WHITEtem;
			DisplayBoard();
			Board[x][y] = WHITE;
		}
		if (scoreWhite(x, y) >= 5000000)
		{
			printf("一方获胜\n");
			system("pause");
			break;
		}
		else
		{
			++turn;
		}
	}
	while (AI == 2)
	{
		if (turn % 2 == 0)
		{
			WHITEAI();
			Board[x][y] = WHITEtem;
			DisplayBoard();
			Board[x][y] = WHITE;
		}
		else if (turn % 2 == 1)
		{
			scanf("%c%d", &yb, &xb);
			getchar();

			y = yb - 'A';
			x = 15 - xb;
			if (ban(x, y) == 0)
			{
				Board[x][y] = BLACKtem;
				DisplayBoard();
				Board[x][y] = BLACK;
			}
			else if (ban(x, y) == 1)
			{
				printf("禁手位置");
				system("pause");
				break;
			}
		}
		if (scoreBlack(x, y) >= 5000000)
		{
			printf("一方获胜\n");
			system("pause");
			break;
		}
		else
		{
			++turn;
		}
	}
}

void WHITEAI()
{
	int sBoard[15][15] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
		{0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0},
		{0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0},
		{0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0},
		{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
	int i = 0;
	int j = 0;
	int max_value = sBoard[0][0]; // 假设第一个元素是最大值
	int max_row = 0;			  // 最大值所在的行
	int max_col = 0;			  // 最大值所在的列
	int x5;
	int y5;

	for (x5 = 0; x5 < 15; ++x5)
	{
		for (y5 = 0; y5 < 15; ++y5)
		{
			sBoard[x5][y5] += scoreAI(x5, y5, AI);
		}
	}
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if ((sBoard[i][j] > max_value) && (Board[i][j] >= 1) && (Board[i][j] < 10))
			{
				max_value = sBoard[i][j];
				max_row = i;
				max_col = j;
			}
		}
	}
	x = max_row;
	y = max_col;
}
/*void BLACKAI(){
	int sBoard[15][15];
	int i=0;
	int j=0;

	int max_value = sBoard[0][0];  // 假设第一个元素是最大值
	int max_row = 0;  // 最大值所在的行
	int max_col = 0;  // 最大值所在的列
	Allscore();
	for (i = 0; i < 15; i++) {
		for (j = 0; j < 15; j++) {
			if (sBoard[i][j] > max_value) {
				max_value = sBoard[i][j];
				max_row = i;
				max_col = j;
			}
		}
	}
	x=max_row;
	y=max_col;
}
*/
void InitBoardArray()
{
	int j, i;

	Board[0][0] = 1;
	Board[0][SIZE - 1] = 2;
	Board[SIZE - 1][SIZE - 1] = 3;
	Board[SIZE - 1][0] = 4;

	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][0] = 5;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[0][i] = 6;
	}

	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][SIZE - 1] = 7;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[SIZE - 1][i] = 8;
	}

	for (j = 1; j <= SIZE - 2; j++)
	{
		for (i = 1; i <= SIZE - 2; i++)
		{
			Board[j][i] = 9;
		}
	}
}

void DisplayBoard()
{
	int i, j;
	char line;
	char ary;

	system("cls"); // 清屏

	for (j = 0, line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d", line);
		line -= 1;
		for (i = 0; i <= SIZE - 1; i++)
		{
			switch (Board[j][i])
			{
			case 1:
				printf("┏");
				break;

			case 2:
				printf("┓");
				break;

			case 3:
				printf("┛");
				break;

			case 4:
				printf("┗");
				break;

			case 5:
				printf("┠");
				break;

			case 6:
				printf("┯");
				break;

			case 7:
				printf("┨");
				break;

			case 8:
				printf("┷");
				break;

			case 9:
				printf("┼");
				break;

			case BLACKtem: // 黑子上一步
				printf("▲");
				break;

			case WHITEtem: // 白子上一步
				printf("△");
				break;

			case BLACK: // 黑子通常
				printf("●");
				break;

			case WHITE:
				printf("○"); // 白子通常
				break;
			}
			if (i == SIZE - 1)
			{
				printf("\n");
			}
		}
	}

	printf("   ");
	for (ary = 'A'; ary < 'A' + SIZE; ary++)
		printf("%c ", ary);

	printf("\n");
	printf("最后一步落子%c%d\n", y + 'A', 15 - x);
}

// 搜索字符串，把四个方向的字符串收集起来，打分完毕
int scoreWhite(int x0, int y0)
{
	int i;
	int score_x = 0;
	int score_y = 0;
	int score_xy = 0;
	int score_yx = 0;
	for (i = -4; i <= 4; i++)
	{
		if ((x0 + i >= 0) && (y0 >= 0) && (x0 + i < 15) && (y0 <= 15))
		{
			if ((Board[x0 + i][y0] == BLACK) || (Board[x0 + i][y0] == BLACKtem))
			{
				strxw[i + 4] = '2';
			}
			else if ((Board[x0 + i][y0] == WHITE) || (Board[x0 + i][y0] == WHITEtem))
			{
				strxw[i + 4] = '1';
			}
			else if (((Board[x0 + i][y0]) >= 1) && ((Board[x0 + i][y0]) <= 9))
			{
				strxw[i + 4] = '0';
			}
			strxw[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((y0 + i >= 0) && (x0 >= 0) && (y0 + i < 15) && (x0 <= 15))
		{
			if ((Board[x0][y0 + i] == BLACK) || (Board[x0][y0 + i] == BLACKtem))
			{
				stryw[i + 4] = '2';
			}
			else if ((Board[x0][y0 + i] == WHITE) || (Board[x0][y0 + i] == WHITEtem))
			{
				stryw[i + 4] = '1';
			}
			else if (((Board[x0][y0 + i]) >= 1) && ((Board[x0][y0 + i]) <= 9))
			{
				stryw[i + 4] = '0';
			}
			stryw[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((x0 + i >= 0) && (y0 + i >= 0) && (x0 + i < 15) && (y0 + i <= 15))
		{
			if ((Board[x0 + i][y0 + i] == BLACK) || (Board[x0 + i][y0 + i] == BLACKtem))
			{
				strxyw[i + 4] = '2';
			}
			else if ((Board[x0 + i][y0 + i] == WHITE) || (Board[x0 + i][y0 + i] == WHITEtem))
			{
				strxyw[i + 4] = '1';
			}
			else if (((Board[x0 + i][y0 + i]) >= 1) && ((Board[x0 + i][y0 + i]) <= 9))
			{
				strxyw[i + 4] = '0';
			}
			strxyw[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((x0 + i >= 0) && (y0 - i >= 0) && (x0 + i < 15) && (y0 - i <= 15))
		{
			if ((Board[x0 + i][y0 - i] == BLACK) || (Board[x0 + i][y0 - i] == BLACKtem))
			{
				stryxw[i + 4] = '2';
			}
			else if ((Board[x0 + i][y0 - i] == WHITE) || (Board[x0 + i][y0 - i] == WHITEtem))
			{
				stryxw[i + 4] = '1';
			}
			else if (((Board[x0 + i][y0 - i]) >= 1) && ((Board[x0 + i][y0 - i]) <= 9))
			{
				stryxw[i + 4] = '0';
			}
			stryxw[4] = '1';
		}
	}

	score_x = scoredirections(strxw);
	score_y = scoredirections(stryw);
	score_xy = scoredirections(strxyw);
	score_yx = scoredirections(stryxw);
	// 算分
	return score_x + score_y + score_xy + score_yx;
}

int scoredirections(char *str)
{
	int scoredirect = 0;
	if (strstr(str, CHENG_5_STRING) != NULL)
	{
		scoredirect += 5000000;
	}
	if (strstr(str, HUO_4_STRING) != NULL)
	{
		scoredirect += 100000;
	}
	if (strstr(str, CHONG_4_STRING_1_1) != NULL)
	{
		scoredirect += 10000;
	}
	if (strstr(str, CHONG_4_STRING_1_2) != NULL)
	{
		scoredirect += 10000;
	}
	if (strstr(str, CHONG_4_STRING_2_1) != NULL)
	{
		scoredirect += 10000;
	}
	if (strstr(str, CHONG_4_STRING_2_2) != NULL)
	{
		scoredirect += 10000;
	}
	if (strstr(str, CHONG_4_STRING_3) != NULL)
	{
		scoredirect += 10000;
	}
	if (strstr(str, DAN_HUO_3_STRING) != NULL)
	{
		scoredirect += 8000;
	}
	if (strstr(str, TIAO_HUO_3_STRING_1_1) != NULL)
	{
		scoredirect += 7000;
	}
	if (strstr(str, TIAO_HUO_3_STRING_1_2) != NULL)
	{
		scoredirect += 7000;
	}
	if (strstr(str, MIAN_3_1_1) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_1_2) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_2_1) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_2_2) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_3_1) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_3_2) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_4_1) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_4_2) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_5) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, MIAN_3_6) != NULL)
	{
		scoredirect += 500;
	}
	if (strstr(str, HUO_2_STRING_1) != NULL)
	{
		scoredirect += 50;
	}
	if (strstr(str, HUO_2_STRING_2) != NULL)
	{
		scoredirect += 50;
	}
	if (strstr(str, HUO_2_STRING_3) != NULL)
	{
		scoredirect += 50;
	}
	if (strstr(str, MIAN_2_1_1) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_1_2) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_2_1) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_2_2) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_3_1) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_3_2) != NULL)
	{
		scoredirect += 10;
	}
	if (strstr(str, MIAN_2_4) != NULL)
	{
		scoredirect += 10;
	}
	return scoredirect;
}
int banthree(char *strban)
{
	int ban_three = 0;
	if (strstr(strban, DAN_HUO_3_STRING) != NULL)
	{
		ban_three += 1;
	}
	if (strstr(strban, TIAO_HUO_3_STRING_1_1) != NULL)
	{
		ban_three += 1;
	}
	if (strstr(strban, TIAO_HUO_3_STRING_1_2) != NULL)
	{
		ban_three += 1;
	}
	return ban_three;
}
int banfour(char *strban)
{
	int ban_4 = 0;
	if (strstr(strban, HUO_4_STRING) != NULL)
	{
		ban_4 += 1;
	}
	if (strstr(strban, CHONG_4_STRING_1_1) != NULL)
	{
		ban_4 += 1;
	}
	if (strstr(strban, CHONG_4_STRING_1_2) != NULL)
	{
		ban_4 += 1;
	}
	if (strstr(strban, CHONG_4_STRING_2_1) != NULL)
	{
		ban_4 += 1;
	}
	if (strstr(strban, CHONG_4_STRING_2_2) != NULL)
	{
		ban_4 += 1;
	}
	if (strstr(strban, CHONG_4_STRING_3) != NULL)
	{
		ban_4 += 1;
	}
	return ban_4;
}
int bansix(char *strban)
{
	int ban_6 = 0;
	if (strstr(strban, "111111") != NULL)
	{
		ban_6 += 1;
	}
	return ban_6;
}
int ban(int x4, int y4)
{
	int ban3_x = 0;
	int ban3_y = 0;
	int ban3_xy = 0;
	int ban3_yx = 0;
	int ban4_x = 0;
	int ban4_y = 0;
	int ban4_xy = 0;
	int ban4_yx = 0;
	int ban6_x = 0;
	int ban6_y = 0;
	int ban6_xy = 0;
	int ban6_yx = 0;
	int ban3 = 0;
	int ban4 = 0;
	int ban6 = 0;
	ban3_x = banthree(strxb);
	ban3_y = banthree(stryb);
	ban3_xy = banthree(strxyb);
	ban3_yx = banthree(stryxb);
	ban3 = ban3_x + ban3_y + ban3_yx + ban3_yx;
	if (ban3 >= 2)
	{
		printf("33禁手");
		return 1;
	}
	ban4_x = banfour(strxb);
	ban4_y = banfour(stryb);
	ban4_xy = banfour(strxyb);
	ban4_yx = banfour(stryxb);
	ban4 = ban4_x + ban4_y + ban4_yx + ban4_yx;
	if (ban4 >= 2)
	{
		printf("44禁手");
		return 1;
	}
	ban6_x = banfour(strxb);
	ban6_y = banfour(stryb);
	ban6_xy = banfour(strxyb);
	ban6_yx = banfour(stryxb);
	ban6 = ban6_x + ban6_y + ban6_yx + ban6_yx;
	if (ban6 >= 2)
	{
		printf("长连禁手");
		return 1;
	}
	else
	{
		return 0;
	}
}

int scoreBlack(int x1, int y1)
{
	if (ban(x1, y1) == 1)
	{
		return 0;
	}
	if (ban(x1, y1) == 0)
	{
		return scoreBlack_notban(x1, y1);
	}
}

int scoreBlack_notban(int x2, int y2)
{
	int i;
	int score_x = 0;
	int score_y = 0;
	int score_xy = 0;
	int score_yx = 0;
	for (i = -4; i <= 4; i++)
	{
		if ((x2 + i >= 0) && (y2 >= 0) && (x2 + i < 15) && (y2 <= 15))
		{
			if ((Board[x2 + i][y2] == BLACK) || (Board[x2 + i][y2] == BLACKtem))
			{
				strxb[i + 4] = '1';
			}
			else if ((Board[x2 + i][y2] == WHITE) || (Board[x2 + i][y2] == WHITEtem))
			{
				strxb[i + 4] = '2';
			}
			else if (((Board[x2 + i][y2]) >= 1) && ((Board[x2 + i][y2]) <= 9))
			{
				strxb[i + 4] = '0';
			}
			strxb[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((y2 + i >= 0) && (x2 >= 0) && (y2 + i < 15) && (x2 <= 15))
		{
			if ((Board[x2][y2 + i] == BLACK) || (Board[x2][y2 + i] == BLACKtem))
			{
				stryb[i + 4] = '2';
			}
			else if ((Board[x2][y2 + i] == WHITE) || (Board[x2][y2 + i] == WHITEtem))
			{
				stryb[i + 4] = '1';
			}
			else if (((Board[x2][y2 + i]) >= 1) && ((Board[x2][y2 + i]) <= 9))
			{
				stryb[i + 4] = '0';
			}
			stryb[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((x2 + i >= 0) && (y2 + i >= 0) && (x2 + i < 15) && (y2 + i <= 15))
		{
			if ((Board[x2 + i][y2 + i] == BLACK) || (Board[x2 + i][y2 + i] == BLACKtem))
			{
				strxyb[i + 4] = '2';
			}
			else if ((Board[x2 + i][y2 + i] == WHITE) || (Board[x2 + i][y2 + i] == WHITEtem))
			{
				strxyb[i + 4] = '1';
			}
			else if (((Board[x2 + i][y2 + i]) >= 1) && ((Board[x2 + i][y2 + i]) <= 9))
			{
				strxyb[i + 4] = '0';
			}
			strxyb[4] = '1';
		}
	}
	for (i = -4; i <= 4; i++)
	{
		if ((x2 + i >= 0) && (y2 - i >= 0) && (x2 + i < 15) && (y2 - i <= 15))
		{
			if ((Board[x2 + i][y2 - i] == BLACK) || (Board[x2 + i][y2 - i] == BLACKtem))
			{
				stryxb[i + 4] = '2';
			}
			else if ((Board[x2 + i][y2 - i] == WHITE) || (Board[x2 + i][y2 - i] == WHITEtem))
			{
				stryxb[i + 4] = '1';
			}
			else if (((Board[x2 + i][y2 - i]) >= 1) && ((Board[x2 + i][y2 - i]) <= 9))
			{
				stryxb[i + 4] = '0';
			}
			stryxb[4] = '1';
		}
	}

	score_x = scoredirections(strxb);
	score_y = scoredirections(stryb);
	score_xy = scoredirections(strxyb);
	score_yx = scoredirections(stryxb);

	return score_x + score_y + score_xy + score_yx;
}
int scoreAI(int x3, int y3, int AI3)
{
	if (AI == 1)
	{
		return scoreBlack(x3, y3) + scoreWhite(x3, y3);
	}
	else if (AI == 2)
	{
		if (ban(x3, y3) == 0)
		{
			return scoreBlack(x3, y3) + scoreWhite(x3, y3);
		}
		else if (ban(x3, y3) == 1)
		{
			return -100;
		}
	}
}
