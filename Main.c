#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 15
#define CHARSIZE 2
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
int mygetline(char s[], int lim);

// 棋盘使用的是UTF8编码，每一个中文字符占用3个字节。

// 空棋盘模板
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
    {
        "┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
        "┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"};
// 此数组存储用于显示的棋盘
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];

char play1Pic[] = "●"; // 黑棋子;
char play1CurrentPic[] = "▲";

char play2Pic[] = "◎"; // 白棋子;
char play2CurrentPic[] = "△";
char line[6];

// 此数组用于记录当前的棋盘的格局
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()
{
    int x, y;
    int i;
    arrayForInnerBoardLayout[5][5] = 0; // 在棋盘的左上角落一个黑色棋子
    innerLayoutToDisplayArray();        // 将心中的棋盘转成用于显示的棋盘
    displayBoard();                     // 显示棋盘
    printf("\n");
    mygetline(line, 6);
    printf("%s\n", line);
    i = 0;
    x = y = 0;
    while (line[i] != '\0')
    {
        if (isalpha(line[i]))
        {
            y = line[i] - 'a';
        }
        else if (isdigit(line[i]))
        {
            ;
        }
        ++i;
    }
    arrayForInnerBoardLayout[SIZE - x - 1][y] = 1;
    innerLayoutToDisplayArray();
    displayBoard();
    return 0;
}

// 初始化一个空棋盘格局
void initRecordBorard(void)
{
    // 通过双重循环，将arrayForInnerBoardLayout清0
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

// 将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j <= SIZE * CHARSIZE + 1; j++)
        {
            arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE * CHARSIZE + 1; j++)
        {
            if (arrayForInnerBoardLayout[i][j] == 1)
            {
                arrayForDisplayBoard[i][j * CHARSIZE] = play1Pic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1Pic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][CHARSIZE * j + 2] = play1Pic[2];
                }
            }
            if (arrayForInnerBoardLayout[i][j] == 2)
            {
                arrayForDisplayBoard[i][j * CHARSIZE] = play2Pic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2Pic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][CHARSIZE * j + 2] = play2Pic[2];
                }
            }
        }
    }

    // 第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中

    // 第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
    // 注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
}

// 显示棋盘格局
void displayBoard(void)
{
    int i;
    // 第一步：清屏
    system("clear"); // 清屏
    // 第二步：将arrayForDisplayBoard输出到屏幕上
    for (int i = 0; i < 15; i++)
    {
        // printf("%s\n", arrayForEmptyBoard[i]);
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }
    printf("    ");
    for (int i = 0; i < 15; i++)
    {
        printf("%c", 'A' + i);
    }
    // 第三步：输出最下面的一行字母A B ....
}
// chcp 65001

int mygetline(char s[], int lim)
{
    int i, c;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = '\n';
    }
    s[i] = '\0';
    return i;
}
