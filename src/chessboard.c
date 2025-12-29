#include "head.h"
#include <stdio.h>

// ANSI color codes for board and pieces
#define COL_RESET "\x1b[0m"
#define COL_BOARD "\x1b[90m"           // gray for board
#define COL_BLACK "\x1b[30m"           // black piece
#define COL_WHITE "\x1b[97m"           // white piece (bright white)
#define COL_BLACK_CURRENT "\x1b[1;30m" // bold black for current
#define COL_WHITE_CURRENT "\x1b[1;97m" // bold white for current

// Empty ChessBoard template (initialized at runtime to avoid encoding issues)
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1];
// ChessBoard_display

char play1Pic[4]; // Black chess (bytes per cell = CHARSIZE)
char play1CurrentPic[4];
char play2Pic[4]; // White chess
char play2CurrentPic[4];
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];

// Initialize ASCII templates and piece bytes according to CHARSIZE
void initEmptyBoardTemplate(void) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int base = j * CHARSIZE;
      if (CHARSIZE >= 1)
        arrayForEmptyBoard[i][base] = ' ';
      if (CHARSIZE >= 2)
        arrayForEmptyBoard[i][base + 1] = '+';
      if (CHARSIZE >= 3)
        arrayForEmptyBoard[i][base + 2] = ' ';
      for (int k = 3; k < CHARSIZE; k++)
        arrayForEmptyBoard[i][base + k] = ' ';
    }
    arrayForEmptyBoard[i][SIZE * CHARSIZE] = '\0';
  }
}

void initPieceDisplayChars(void) {
  // Default: use ASCII characters and pad with spaces to fill CHARSIZE bytes
  for (int k = 0; k < 4; k++) {
    play1Pic[k] = '\0';
    play1CurrentPic[k] = '\0';
    play2Pic[k] = '\0';
    play2CurrentPic[k] = '\0';
  }
  if (CHARSIZE >= 1) {
    play1Pic[0] = 'X';
    play1CurrentPic[0] = 'x';
    play2Pic[0] = 'O';
    play2CurrentPic[0] = 'o';
  }
  if (CHARSIZE >= 2) {
    play1Pic[1] = ' ';
    play1CurrentPic[1] = ' ';
    play2Pic[1] = ' ';
    play2CurrentPic[1] = ' ';
  }
  if (CHARSIZE >= 3) {
    play1Pic[2] = ' ';
    play1CurrentPic[2] = ' ';
    play2Pic[2] = ' ';
    play2CurrentPic[2] = ' ';
  }
}

// Current ChessBoard
int arrayForInnerBoardLayout[SIZE][SIZE];

// ChessBoard_inner_initialize
void initRecordBoard(void) {
  static int initialized = 0;
  if (!initialized) {
    initEmptyBoardTemplate();
    initPieceDisplayChars();
    initialized = 1;
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      arrayForInnerBoardLayout[i][j] = EMPTY;
    }
  }
}

// Copy ChessBoard_inner to ChessBoard_display
void innerLayoutToDisplayArray(void) {
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE * CHARSIZE + 1; j++) {
      arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
    }
  }
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if ((arrayForInnerBoardLayout[i][j] == BLACKCHESS) ||
          (arrayForInnerBoardLayout[i][j] == BLACKCHESSCURRENT)) {
        arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1Pic[0];
        arrayForDisplayBoard[i][j * CHARSIZE] = play1Pic[1];
        if (CHARSIZE == 3) {
          arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1Pic[2];
        }
        arrayForInnerBoardLayout[i][j] = BLACKCHESS;
      }

      if ((arrayForInnerBoardLayout[i][j] == WHITECHESS) ||
          (arrayForInnerBoardLayout[i][j] == WHITECHESSCURRENT)) {
        arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2Pic[0];
        arrayForDisplayBoard[i][j * CHARSIZE] = play2Pic[1];
        if (CHARSIZE == 3) {
          arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2Pic[2];
        }
        arrayForInnerBoardLayout[i][j] = WHITECHESS;
      }
    }
  }
}

// Update chess that is put this turn
void updatechesscurrent(void) {
  int i, j;
  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if (arrayForInnerBoardLayout[i][j] == BLACKCHESSCURRENT) {

        arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1CurrentPic[0];
        arrayForDisplayBoard[i][j * CHARSIZE] = play1CurrentPic[1];
        if (CHARSIZE == 3) {
          arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1CurrentPic[2];
        }
      }
      if (arrayForInnerBoardLayout[i][j] == WHITECHESSCURRENT) {
        arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2CurrentPic[0];
        arrayForDisplayBoard[i][j * CHARSIZE] = play2CurrentPic[1];
        if (CHARSIZE == 3) {
          arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2CurrentPic[2];
        }
      }
    }
  }
}

// Display ChessBoard (with colors)
void displayBoard(void) {
  // system("clear");
  printf(GAMEINFO);
  for (int i = 0; i < SIZE; i++) {
    printf("%3d ", SIZE - i);
    for (int j = 0; j < SIZE; j++) {
      int base = j * CHARSIZE;
      int cell = arrayForInnerBoardLayout[i][j];
      const char *color = COL_BOARD;
      if (cell == BLACKCHESS || cell == BLACKCHESSCURRENT) {
        color = (cell == BLACKCHESSCURRENT) ? COL_BLACK_CURRENT : COL_BLACK;
      } else if (cell == WHITECHESS || cell == WHITECHESSCURRENT) {
        color = (cell == WHITECHESSCURRENT) ? COL_WHITE_CURRENT : COL_WHITE;
      }
      fputs(color, stdout);
      fwrite(&arrayForDisplayBoard[i][base], 1, CHARSIZE, stdout);
      fputs(COL_RESET, stdout);
    }
    fputc('\n', stdout);
  }
  printf("    ");
  for (int i = 0; i < SIZE; i++) {
    printf("%2c", 'A' + i);
  }
  printf("\n");
}

// input state control
void update(void) {
  innerLayoutToDisplayArray();
  if (gamestates.runningstate == -2) {
    gamestates.runningstate = 0;
    return;
  } else if (gamestates.runningstate == 1) {
    updateHumanInput();
  } else if (gamestates.runningstate == 2) {
    updateHumanInput();
    if (gamestates.runningstate)
      updateAiInput();
  } else if (gamestates.runningstate == 3) {
    updateAiInput();
    if (gamestates.runningstate)
      updateHumanInput();
  } else if (gamestates.runningstate == 4) {
    updateAiInput();
  } else if (gamestates.runningstate == 5) {
    input();
  }
}

// human input update
void updateHumanInput(void) {
  innerLayoutToDisplayArray();
  input();
  updatechesscurrent();
  displayBoard();
  gamejudger();
}

// Ai input update
void updateAiInput(void) {
  innerLayoutToDisplayArray();
  ai_tree();
  updatechesscurrent();
  displayBoard();
  gamejudger();
  printf(AIINFO, 'A' + pos.y, pos.x);
}