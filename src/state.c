#include "head.h"

// runningstate -2 -1 0 1 2 3 4 5
// -2:win
// -1:error
// 0:off
// 1-5:different mode
struct gamestate gamestates;

// state initialize
void init_state(void)
{
    gamestates.runningstate = 0;
    gamestates.playerstate = 0; //
    initRecordBoard();
}
// state input process
// 1:pvp
// 2:pve
// 3:evp
// 4:eve
// READY:auto check (abandoned)
// quit:exit
//
int stateprocess(char line[])
{
    int vaild = 0;
    if ((!gamestates.runningstate) && (!strcmp(line, MANUAL)))
    {
        gamestates.runningstate = 1;
        vaild = 1;
    }
    else if ((!gamestates.runningstate) && (!strcmp(line, HUMANVSAI)))
    {
        gamestates.runningstate = 2;
        vaild = 1;
    }
    else if ((!gamestates.runningstate) && (!strcmp(line, AIVSHUMAN)))
    {
        gamestates.runningstate = 3;
        vaild = 1;
    }
    else if ((!gamestates.runningstate) && (!strcmp(line, AIVSAI)))
    {
        gamestates.runningstate = 4;
        vaild = 1;
    }
    else if ((!gamestates.runningstate) && (!strcmp(line, AUTO)))
    {
        gamestates.runningstate = 5;
        vaild = 1;
    }
    else if (!strcmp(line, EXIT))
    {
        gamestates.runningstate = 0;
        vaild = 1;
    }
    else
    {
        if (gamestates.runningstate != -1)
        {
            gamestates.playerstate = !gamestates.playerstate;
        }
        vaild = 0;
        // invalid input process
    }
    return vaild;
}

// Display essential infomation
void InfoDisplay(void)
{
    if (gamestates.runningstate)
    {
        printf(PLAYERINFO, (gamestates.playerstate == BLACK) ? BLACKNAME : WHITENAME);
        // player info
        printf(INPUTCHESS_S);
        // input chess tip
    }
    else
    {
        printf(INPUTMODE_S);
        // input mode tip
    }
}

// invalid input handling
void ErrorHandle(void)
{
    int preState;
    if ((pos.x < 1) || (pos.x > SIZE) || (pos.y < 0) || (pos.y > SIZE - 1))
    {
        printf(ERROR_OUT_OF_RANGE);
        // Out of range infomation display
        preState = gamestates.runningstate;
        gamestates.runningstate = -1;
        inputprocess_manual();
        gamestates.runningstate = preState;
    }
    if (arrayForInnerBoardLayout[SIZE - pos.x][pos.y] != 0)
    {
        printf(ERROR_ALREDY_HAVE);
        // Place an chess on other chess infomation display
        preState = gamestates.runningstate;
        gamestates.runningstate = -1;
        inputprocess_manual();
        gamestates.runningstate = preState;
    }
}

// winning state handling
void winHandle(int check)
{
    if ((check == 1) || ((check == 2) && (!gamestates.playerstate == WHITE)))
    {
        printf(WININFO, (!gamestates.playerstate == BLACK) ? BLACKNAME : WHITENAME);
        gamestates.runningstate = 0;
        // winner infomation and shutdown the game
    }
    else if ((check >= 2) && (!gamestates.playerstate == BLACK))
    {
        switch (check)
        {
        case 2:
            printf(LONGCHAIN);
            break;
        case 3:
            printf(DOUBLETHREE);
            break;
        case 4:
            printf(DOUBLEFOUR);
            break;
        default:
            break;
        }
        gamestates.playerstate = !gamestates.playerstate;
        printf(WININFO, (!gamestates.playerstate == BLACK) ? BLACKNAME : WHITENAME);
        gamestates.runningstate = 0;
    }
    else
    {
        ; // Do nothing
    }
}
