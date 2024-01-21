#include "head.h"
// Empty ChessBoard
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
    {
        "©³©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©·",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©»©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©¿"};
// ChessBoard_display

char play1Pic[] = "¡ñ"; // Black chess;
char play1CurrentPic[] = "¡ø";
char play2Pic[] = "¡ò"; // White chess;
char play2CurrentPic[] = "¡÷";
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];

// Current ChessBoard
int arrayForInnerBoardLayout[SIZE][SIZE];

// ChessBoard_inner_initialize
void initRecordBoard(void)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            arrayForInnerBoardLayout[i][j] = EMPTY;
        }
    }
}

// Copy ChessBoard_inner to ChessBoard_display
void innerLayoutToDisplayArray(void)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE * CHARSIZE + 1; j++)
        {
            arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if ((arrayForInnerBoardLayout[i][j] == BLACKCHESS) || (arrayForInnerBoardLayout[i][j] == BLACKCHESSCURRENT))
            {
                arrayForDisplayBoard[i][j * CHARSIZE] = play1Pic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1Pic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1Pic[2];
                }
                arrayForInnerBoardLayout[i][j] = BLACKCHESS;
            }

            if ((arrayForInnerBoardLayout[i][j] == WHITECHESS) || (arrayForInnerBoardLayout[i][j] == WHITECHESSCURRENT))
            {
                arrayForDisplayBoard[i][j * CHARSIZE] = play2Pic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2Pic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2Pic[2];
                }
                arrayForInnerBoardLayout[i][j] = WHITECHESS;
            }
        }
    }
}

// Update chess that is put this turn
void updatechesscurrent(void)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardLayout[i][j] == BLACKCHESSCURRENT)
            {

                arrayForDisplayBoard[i][j * CHARSIZE] = play1CurrentPic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1CurrentPic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1CurrentPic[2];
                }
            }
            if (arrayForInnerBoardLayout[i][j] == WHITECHESSCURRENT)
            {
                arrayForDisplayBoard[i][j * CHARSIZE] = play2CurrentPic[0];
                arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2CurrentPic[1];
                if (CHARSIZE == 3)
                {
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2CurrentPic[2];
                }
            }
        }
    }
}

// Display ChessBoard
void displayBoard(void)
{
    int i;
    system("clear");
    printf(GAMEINFO);
    for (int i = 0; i < 15; i++)
    {
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }
    printf("    ");
    for (int i = 0; i < 15; i++)
    {
        printf("%2c", 'A' + i);
    }
    printf("\n");
}

// input state control
void update(void)
{
    innerLayoutToDisplayArray();
    if (gamestates.runningstate == -2)
    {
        gamestates.runningstate = 0;
        return;
    }
    else if (gamestates.runningstate == 1)
    {
        updateHumanInput();
    }
    else if (gamestates.runningstate == 2)
    {
        updateHumanInput();
        if (gamestates.runningstate)
            updateAiInput();
    }
    else if (gamestates.runningstate == 3)
    {
        updateAiInput();
        if (gamestates.runningstate)
            updateHumanInput();
    }
    else if (gamestates.runningstate == 4)
    {
        updateAiInput();
    }
    else if (gamestates.runningstate == 5)
    {
        input();
    }
}

// human input update
void updateHumanInput(void)
{
    innerLayoutToDisplayArray();
    input();
    updatechesscurrent();
    displayBoard();
    gamejudger();
}

// Ai input update
void updateAiInput(void)
{
    innerLayoutToDisplayArray();
    ai_tree();
    updatechesscurrent();
    displayBoard();
    gamejudger();
    printf(AIINFO, 'A' + pos.y, pos.x);
}