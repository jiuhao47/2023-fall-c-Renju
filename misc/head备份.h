#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define DIRECTION 4         // Four directions
#define SIZE 15             // ChessBoardSize
#define CHARSIZE 2          // Single char size
#define LINEMAXLEN 7        // Input max length
#define EMPTY 0             // Empty place
#define BLACK 0             // Black player
#define WHITE 1             // White player
#define BLACKCHESS 1        // Black chess
#define WHITECHESS 2        // White chess
#define BLACKCHESSCURRENT 3 // Black chesscurrent
#define WHITECHESSCURRENT 4 // White chesscurrent
#define MAXEVOLVELAYERS 5   // Max evolve layers
#define P_FIVEINROW 100000
#define P_FLEXFOUR 90000
#define P_FLEXTHREE 10000
#define P_DIRECTFOUR 10000
#define P_FLEXTWO 100
#define P_DIRECTTHREE 100
#define P_DIRECTTWO 10
#define FORBIDDEN -30
#define OCCUPIED -20
#define P_ONE 1 // evaluation score
#define BLACKNAME "Black"
#define WHITENAME "White"
#define WININFO "%s Win!\n"
#define AIINFO "    AI SET %c%d    "
#define PLAYERINFO "Player %s's Turn\n"
#define GAMEINFO "    -----------Gomoku-----------\n    ----Work of Junyan Jiang----\n"
#define LONGCHAIN "Long Chain Detected!\n"
#define DOUBLETHREE "Double Three Detected!\n"
#define DOUBLEFOUR "Double Four Detected!\n"
#define INPUTCHESS_S "\nInput Chess Point:"
#define INPUTMODE_S "\n(1)Human Vs Human\n(2)Human(Black) Vs AI(White)\n(3)Human(White) Vs AI(BLACK)\n(4)AI Vs AI\n(5)AUTO CHECK\n\nInput Game Mode:"
#define ERROR_OUT_OF_RANGE "Input out of range, Please enter again!\n"
#define ERROR_ALREDY_HAVE "This place already has chess, Please enter again!\n" // Infomation for display
#define INPUT_EXAMPLE " MOVE(%d,%d)"                                            // Input example(abandon)
#define MANUAL "1\n"
#define HUMANVSAI "2\n"
#define AIVSHUMAN "3\n"
#define AIVSAI "4\n"
#define AUTO "READY\n"
#define EXIT "quit\n" // State string

void input(void);
void initRecordBoard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
void updatechesscurrent(void);
extern int arrayForInnerBoardLayout[SIZE][SIZE];
// chessboard.c

int displayPosToInnerPos(int tempx, int tempy);
int mygetline(char s[], int lim);
int pointInBoard(int tempx, int tempy);
int mypow(int x, int n);
int weight(int x, int y);
int mymax(int x, int y);
int myabs(int x);
// functions.c

int stateprocess(char line[]);
void inputprocess_manual(void);
void inputprocess_auto(void);
struct point
{
    int x;
    int y;
};
extern struct point pos;
// inputprocess.c

void init_state(void);
void update(void);
void updateHumanInput(void);
void updateAiInput(void);
void input(void);
// main.c

void ErrorHandle(void);
void winHandle(int check);
void InfoDisplay(void);
struct gamestate
{
    int runningstate;
    int playerstate;
};
extern struct gamestate gamestates;

// state.c
void chessShapeToken(int x, int y, int *Board, int *chessshape);
int chainjudge(int *chessshape);
int chainjudge_mode(int mode, int *chessshape);
int doublefourjudge(int x, int y, int *chessshape);
int fourjudge(int x, int y, int mode, int *chessshape);
int doublethreejudge(int x, int y, int *chessshape);
int threejudge(int x, int y, int mode, int *chessshape);
int judge(int x, int y);
void gamejudger(void);

// judge.c
int ai_random(void);
int ai_tree(void);
void ai_input(int x, int y);
void ai_input_clear(int x, int y);

struct Treenode
{
    int score;
    int x;
    int y;
    int depth;
    struct Treenode *son;
    struct Treenode *brother;
};

void evolve(int depth);
struct Treenode *collect(struct Treenode *root, struct Treenode **scoreRoot);
void init_scoreRoot(struct Treenode **scoreRoot);
void updateInnerBoardForScore(void);

struct Treenode *talloc(void);
void depthupdate(struct Treenode *root);
struct Treenode *addSon(int score, int x, int y, struct Treenode *root);
void addBrother(int score, int x, int y, struct Treenode *root);
void getbrotherScore(struct Treenode *root);
struct Treenode *treeBrotherSort(struct Treenode *root, struct Treenode *new);
int sontreeScoreSum(struct Treenode *son);
struct Treenode *treeupdate(struct Treenode *root);
struct Treenode *freeTree(struct Treenode *root);
// ai.c

int fourjudge_score(int x, int y, int mode, int *chessshape);
int judge_score(int x, int y, int *Board);
int threejudge_score(int x, int y, int mode, int *chessshape);
int twojudge_score(int x, int y, int mode, int *chessshape);

// judge_score.c
#endif