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

// ����ʹ�õ���UTF8���룬ÿһ�������ַ�ռ��3���ֽڡ�

// ������ģ��
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
    {
        "���өөөөөөөөөөөөө�",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "�ĩ��������������",
        "���۩۩۩۩۩۩۩۩۩۩۩۩۩�"};
// ������洢������ʾ������
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];

char play1Pic[] = "��"; // ������;
char play1CurrentPic[] = "��";

char play2Pic[] = "��"; // ������;
char play2CurrentPic[] = "��";
char line[6];

// ���������ڼ�¼��ǰ�����̵ĸ��
int arrayForInnerBoardLayout[SIZE][SIZE];

int main()
{
    int x, y;
    int i;
    arrayForInnerBoardLayout[5][5] = 0; // �����̵����Ͻ���һ����ɫ����
    innerLayoutToDisplayArray();        // �����е�����ת��������ʾ������
    displayBoard();                     // ��ʾ����
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

// ��ʼ��һ�������̸��
void initRecordBorard(void)
{
    // ͨ��˫��ѭ������arrayForInnerBoardLayout��0
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            arrayForInnerBoardLayout[i][j] = 0;
        }
    }
}

// ��arrayForInnerBoardLayout�м�¼������λ�ã�ת����arrayForDisplayBoard��
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

    // ��һ������arrayForEmptyBoard�м�¼�Ŀ����̣����Ƶ�arrayForDisplayBoard��

    // �ڶ�����ɨ��arrayForInnerBoardLayout����������0��Ԫ�أ�������ߡ��Ƶ�arrayForDisplayBoard����Ӧλ����
    // ע�⣺arrayForDisplayBoard����¼���ַ��������ַ���ÿ���ַ�ռ2���ֽڡ���͡�Ҳ�������ַ���ÿ��Ҳռ2���ֽڡ�
}

// ��ʾ���̸��
void displayBoard(void)
{
    int i;
    // ��һ��������
    system("clear"); // ����
    // �ڶ�������arrayForDisplayBoard�������Ļ��
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
    // ������������������һ����ĸA B ....
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
