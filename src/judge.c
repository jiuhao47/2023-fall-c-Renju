#include "head.h"

// all judge
void gamejudger(void)
{
    int check;
    check = judge(pos.x, pos.y);
    winHandle(check);
    // winner info and state process
}

// rule judge
int judge(int x, int y)
{
    int chessshape[DIRECTION][9];
    chessShapeToken(x, y, arrayForInnerBoardLayout[0], chessshape[0]);
    int count = chainjudge(chessshape[0]);
    if (count == -1)
    {
        return 1;
        // five in row
    }
    else if (count == -2)
    {
        return 2;
        // long chain
    }
    else
    {
        if (doublefourjudge(x, y, chessshape[0]))
        {
            return 4;
            // double four
        }
        else
        {
            if (doublethreejudge(x, y, chessshape[0]))
            {
                return 3;
                // double three
            }
        }
    }
    return 0;
}

// to get how many chess in row in the chessshape
// four directions
int chainjudge(int *chessshape)
{
    int count = 0;
    int maxcount = 0;
    for (int mode = 0; mode < DIRECTION; mode++)
    {
        count = 0;
        for (int i = 0; i < 9; i++)
        {
            if ((chessshape[mode * 9 + i] == ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS)) || (chessshape[mode * 9 + i] == ((!gamestates.playerstate == BLACK) ? BLACKCHESSCURRENT : WHITECHESSCURRENT)))
            {
                count = count + 1;
                maxcount = (maxcount < count) ? count : maxcount;
            }
            else
            {
                count = 0;
            }
        }
        if (maxcount == 5)
        {
            return -1;
            // five in row
        }
        else if ((maxcount > 5))
        {
            return -2;
            // long chain
        }
    }
    return maxcount;
}

// to get how many chess in row in the chessshape in specific direction
int chainjudge_mode(int mode, int *chessshape)
{
    int count = 0;
    int maxcount = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS)) || (chessshape[mode * 9 + i] == ((!gamestates.playerstate == BLACK) ? BLACKCHESSCURRENT : WHITECHESSCURRENT)))
        {
            count = count + 1;
            maxcount = (maxcount < count) ? count : maxcount;
        }
        else
        {
            count = 0;
        }
    }
    if (maxcount == 5)
    {
        return -1;
        // five in row
    }
    else if ((maxcount > 5))
    {
        return -2;
        // long chain
    }

    return maxcount;
}

// double four fobbiden judge
// 1:yes
// 0:no
int doublefourjudge(int x, int y, int *chessshape)
{
    int count = 0;

    for (int mode = 0; mode < DIRECTION; mode++)
    {
        if ((chainjudge_mode(mode, chessshape) < 4) && (fourjudge(x, y, mode, chessshape) == 2))
        {
            return 1;
        }
        count = count + ((fourjudge(x, y, mode, chessshape) > 0) ? 1 : 0);
        if (count >= 2)
        {
            return 1;
        }
    }
    return 0;
}

// four situation judge
// place an chess and check if it could make five chess in row
// 2:flexfour
// 1:directfour
int fourjudge(int x, int y, int mode, int *chessshape)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == EMPTY))
        {
            chessshape[mode * 9 + i] = ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
            if (chainjudge(chessshape) == -1)
            {
                count = count + 1;
            }
            chessshape[mode * 9 + i] = EMPTY;
        }
    }
    return count;
}

// double three fobbiden judge
// 1:yes
// 0:no
int doublethreejudge(int x, int y, int *chessshape)
{
    int count = 0;
    for (int mode = 0; mode < DIRECTION; mode++)
    {
        count = count + ((threejudge(x, y, mode, chessshape) > 0) ? 1 : 0);
        if (count >= 2)
        {
            return 1;
        }
    }
    return 0;
}

// flexthree situation judge
// place an chess and check if it could make flexfour chessshape
// 1:yes
// 0:no
int threejudge(int x, int y, int mode, int *chessshape)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == EMPTY))
        {
            chessshape[mode * 9 + i] = ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
            if (chainjudge_mode(mode, chessshape) != -1)
            {
                if (fourjudge(x, y, mode, chessshape) == 2)
                {
                    count = count + 1;
                }
            }
            chessshape[mode * 9 + i] = EMPTY;
        }
    }
    return (count > 0) ? 1 : 0;
}

// mode 1,2,3,4
// 1:x
// 2:y
// 3:x-y
// 4:y-x
// get chessshape in different directions
// 4*9
void chessShapeToken(int x, int y, int *Board, int *chessshape)
{
    for (int mode = 0; mode < DIRECTION; mode++)
    {
        int dx = 0;
        int dy = 0;
        switch (mode)
        {
        case 0:
            dx = 1, dy = 0; // 竖直
            break;
        case 1:
            dx = 0, dy = 1; // 水平
            break;
        case 2:
            dx = 1, dy = 1; // 正斜
            break;
        case 3:
            dx = 1, dy = -1; // 反斜
            break;
        default:;
        }
        for (int i = -4; i <= 4; i++)
        {
            struct point temppoint;
            temppoint.x = x + i * dx;
            temppoint.y = y + i * dy;
            if (pointInBoard(temppoint.x, temppoint.y))
            {
                chessshape[mode * 9 + i + 4] = Board[displayPosToInnerPos(temppoint.x, temppoint.y)];
            }
            else
            {
                chessshape[mode * 9 + i + 4] = 5;
            }
        }
    }
}