#include "head.h"

// get an line of characters from the input
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
    return i;
}

// to judge whether the point is in the chessboard
int pointInBoard(int tempx, int tempy)
{
    int ret = 0;
    if ((tempx > 0) && (tempy >= 0) && (tempx <= SIZE) && (tempy < SIZE))
    {
        ret = 1;
    }
    return ret;
}

// transfer display board position to inner board position
int displayPosToInnerPos(int tempx, int tempy)
{
    return (SIZE - (tempx)) * SIZE + tempy;
}
int mypow(int x, int n)
{
    int temp = 1;
    for (int i = 0; i < n; i++)
    {
        temp = temp * x;
    }
    return temp;
}

// get weight of different places on the chessboard
// used for initial value of score board
int weight(int x, int y)
{
    return 7 - mymax(myabs(x - 7), myabs(y - 7));
}

// maximum
int mymax(int x, int y)
{
    return (x > y) ? x : y;
}

int myabs(int x)
{
    return (x >= 0) ? x : ((-1) * x);
}