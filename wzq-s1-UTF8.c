#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15
#define CHARSIZE 3
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);

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

// 此数组用于记录当前的棋盘的格局
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()
{

    initRecordBorard(); // 初始化一个空棋盘
    innerLayoutToDisplayArray();
    displayBoard();
    getchar();
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
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayForDisplayBoard[i][j * CHARSIZE] = arrayForEmptyBoard[i][j * CHARSIZE];
        }
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            switch (arrayForInnerBoardLayout[i][j])
            {
            case 0:;
            case 1:
                arrayForDisplayBoard[i][j] = *play1Pic;
            case 2:
                arrayForDisplayBoard[i][j] = *play2Pic;
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
        for (int j = 0; j < 15; j++)
        {
            // printf("1");
            printf("%c", arrayForEmptyBoard[i][j * CHARSIZE]);
        }
        printf("\n");
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