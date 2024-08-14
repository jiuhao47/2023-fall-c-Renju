#include "head.h"
int chessshape_score[DIRECTION][9];

// evaluate score at x,y in Board
int judge_score(int x, int y, int *Board)
{
    int count;

    chessShapeToken(x, y, Board, chessshape_score[0]);
    if (!gamestates.playerstate == BLACK)
    {
        count = chainjudge(chessshape_score[0]);
        if (count == -1)
        {
            return P_FIVEINROW;
            // five in row
        }
        else if (count == -2)
        {
            return FORBIDDEN;
            // long chain fobbiden
        }
        else
        {
            if (doublefourjudge(x, y, chessshape_score[0]))
            {
                return FORBIDDEN;
                // double four fobbiden
            }
            else
            {
                if (doublethreejudge(x, y, chessshape_score[0]))
                {
                    return FORBIDDEN;
                    // double three fobbiden
                }
            }
        }
    }
    int fourshape;
    int threeshape;
    int twoshape;
    int pointTotal = 0;
    for (int mode = 0; mode < DIRECTION; mode++)
    {
        if (chainjudge_mode(mode, chessshape_score[0]) < 0)
        {

            pointTotal = pointTotal + P_FIVEINROW;
            // five in row
            continue;
        }
        else
        {

            fourshape = fourjudge_score(x, y, mode, chessshape_score[0]);
            if (fourshape == 2)
            {
                pointTotal = pointTotal + P_FLEXFOUR;
                // flex four
                continue;
            }
            else if (fourshape == 1)
            {
                pointTotal = pointTotal + P_DIRECTFOUR;
                // direct four
                continue;
            }
            else
            {
                threeshape = threejudge_score(x, y, mode, chessshape_score[0]);
                if (threeshape == 2)
                {
                    pointTotal = pointTotal + P_FLEXTHREE;
                    // flex three
                    continue;
                }
                else if (threeshape == 1)
                {
                    pointTotal = pointTotal + P_DIRECTTHREE;
                    // direct three
                    continue;
                }
                else
                {
                    twoshape = twojudge_score(x, y, mode, chessshape_score[0]);
                    if (twoshape == 2)
                    {
                        pointTotal = pointTotal + P_FLEXTWO;
                        // flex two
                        continue;
                    }
                    else if (twoshape == 1)
                    {
                        pointTotal = pointTotal + P_DIRECTTWO;
                        // direct two
                        continue;
                    }
                    else
                    {
                        pointTotal = pointTotal + P_ONE;
                        // single point
                        continue;
                    }
                }
            }
        }
    }
    return pointTotal;
}

// four shape evaluate
// 2:flex four
// 1:direct four
int fourjudge_score(int x, int y, int mode, int *chessshape)
{
    int count = 0;
    int fiveshape = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == EMPTY))
        {
            chessshape[mode * 9 + i] = ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
            if (chainjudge_mode(mode, chessshape) == -1)
            {
                count = count + 1;
            }
            chessshape[mode * 9 + i] = EMPTY;
        }
    }
    return count;
}
// three shape evaluate
// 2:flex three
// 1:direct three
int threejudge_score(int x, int y, int mode, int *chessshape)
{
    int count = 0;
    int fourshape = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == EMPTY))
        {
            chessshape[mode * 9 + i] = ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
            fourshape = fourjudge_score(x, y, mode, chessshape);
            if (fourshape == 2)
            {
                count = count | 0b10;
            }
            else if (fourshape == 1)
            {
                count = count | 0b01;
            }
            chessshape[mode * 9 + i] = EMPTY;
        }
    }
    if (count & 0b10)
    {
        count = 2;
    }
    else if (count & 0b1)
    {
        count = 1;
    }
    else
    {
        count = 0;
    }
    return count;
}
// two shape evaluate
// 2:flex two
// 1:direct two
int twojudge_score(int x, int y, int mode, int *chessshape)
{
    int count = 0;
    int threeshape = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((chessshape[mode * 9 + i] == EMPTY))
        {
            chessshape[mode * 9 + i] = ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
            threeshape = threejudge_score(x, y, mode, chessshape);
            if (threeshape == 2)
            {
                count = count | 0b10;
            }
            else if (threeshape == 1)
            {
                count = count | 0b01;
            }
            chessshape[mode * 9 + i] = EMPTY;
        }
    }
    if (count & 0b10)
    {
        count = 2;
    }
    else if (count & 0b1)
    {
        count = 1;
    }
    else
    {
        count = 0;
    }
    return count;
}