/*
struct chessshape linejudge(int x, int y, int player, int *Board)
{
    struct chessshape chessshape;
    struct point tempbegin;
    struct point tempend;
    for (int i = 0; i < DIRECTION; i++)
    {
        chessshape.numcount[i] = 0;
    }
    // int tempBoard[SIZE][SIZE] = arrayForInnerBoardLayout;
    int count = 0;
    int maxcount = 0;
    int dx, dy;
    int tempx, tempy;
    // int tempxbegin, tempybegin;
    // int tempxend, tempyend;
    for (int mode = 0; mode < 4; mode++)
    {
        tempbegin.x = -1;
        tempbegin.y = -1;
        tempend.x = -1;
        tempend.y = -1;
        switch (mode)
        {
        case 0:
            dx = 1, dy = 0; // 竖直
            break;
        case 1:
            dx = 0, dy = 1; // 水平
            break;
        case 2:
            dx = 1, dy = 1; //
            break;
        case 3:
            dx = 1, dy = -1;
            break;
        default:;
        }
        for (int i = -4; i <= 4; i++)
        {
            tempx = pos.x + i * dx;
            tempy = pos.y + i * dy;
            if (pointInBoard(tempx, tempy))
            {
                if ((Board[displayPosToInnerPos(tempx, tempy)] == ((player == BLACK) ? BLACKCHESS : WHITECHESS)) || (Board[displayPosToInnerPos(tempx, tempy)] == ((player == BLACK) ? BLACKCHESSCURRENT : WHITECHESSCURRENT)))
                {
                    count = count + 1;
                }
                else
                {
                    if (count >= chessshape.numcount[mode])
                    {
                        tempbegin.x = tempx - (count + 1) * dx;
                        tempbegin.y = tempy - (count + 1) * dy;
                        tempend.x = tempx;
                        tempend.y = tempy;
                    }
                    count = 0;
                }
            }
            chessshape.numcount[mode] = (chessshape.numcount[mode] >= count) ? chessshape.numcount[mode] : count;
            chessshape.pointarray[mode * 2] = tempbegin;
            chessshape.pointarray[mode * 2 + 1] = tempend;
        }
        printf("(%d,%c) %d:Count=%d\n", pos.x, pos.y + 'A', mode, chessshape.numcount[mode]);
    }
    return chessshape;
}
*/
/*
void winjudge(void)
{
    int win = 0;
    struct chessshape chessshape_judge;
    chessshape_judge = linejudge(pos.x, pos.y, gamestates.playerstate, arrayForInnerBoardLayout[0]);
    for (int mode = 0; mode < 4; mode++)
    {
        win = win + (chessshape_judge.numcount[mode] == 5) ? 1 : 0;
    }
    if (win > 0)
    {
        gamestates.runningstate = -2;
    }
}
*/
/*
void forbiddenjudge(int x, int y, struct chessshape *chessshape, int *Board)
{
}

// 长连禁手
int longlinejudge(int x, int y, struct chessshape *chessshape)
{
    int judge = 0;
    for (int mode = 0; mode < 4; mode++)
    {
        judge = judge + (chessshape->numcount[mode] > 5) ? 1 : 0;
    }
    return (judge > 0) ? 1 : 0;
}

int doublethreejudge(int x, int y, struct chessshape *chessshape, int *Board)
{
    int judge = 0;
    for (int mode = 0; mode < 4; mode++)
    {
        if (chessshape->numcount[mode] == 3)
        {
        }
    }
}

// 四四禁手
// Board：目标棋盘
// chessshape: 当前棋形
int doublefourjudge(struct chessshape *chessshape, int *Board)
{
    int judge = 0;
    int temp = 0;
    for (int mode = 0; mode < 4; mode++)
    {
        if (chessshape->numcount[mode] == 4)
        {
            temp = fourjudge(mode, chessshape, Board);
            if ((temp == 2) || (temp == 1))
            {
                judge = judge + 1;
            }
            if (judge >= 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int flexthreejudge(int x, int y, struct chessshape chessshape, int *Board)
{
}

// 四连判断
// ret:
// 2:flex
// 1:narrow
// 0:dead
int fourjudge(int mode, struct chessshape *chessshape, int *Board)
{
    struct point tempbegin, tempend;
    tempbegin = chessshape->pointarray[mode * 2];
    tempend = chessshape->pointarray[mode * 2 + 1];
    int empty = 0;
    int ret = 0;
    if (pointInBoard(tempbegin.x, tempbegin.y) && (Board[displayPosToInnerPos(tempbegin.x, tempbegin.y)] == 0))
    {
        empty = empty + 1;
    }
    if (pointInBoard(tempend.x, tempend.y) && (Board[displayPosToInnerPos(tempend.x, tempend.y)] == 0))
    {
        empty = empty + 1;
    }
    if (empty == 2)
    {
        ret = 2;
    }
    else if (empty == 1)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
*/