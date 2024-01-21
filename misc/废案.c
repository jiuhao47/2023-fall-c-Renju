#include "head.h"
struct Treenode *root = NULL;
struct Treenode *scoreRoot[SIZE][SIZE];
int arrayForInnerBoardForScore[SIZE][SIZE];

void updateInnerBoardForScore(void)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            arrayForInnerBoardForScore[i][j] = arrayForInnerBoardLayout[i][j];
        }
    }
}
void init_scoreRoot(struct Treenode **scoreRoot)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            scoreRoot[i * SIZE + j] = talloc();
            scoreRoot[i * SIZE + j]->type = MAX;
            scoreRoot[i * SIZE + j]->alpha = INVINF;
            scoreRoot[i * SIZE + j]->beta = POSINF;
            scoreRoot[i * SIZE + j]->brother = scoreRoot[i * SIZE + j]->son = NULL;
            scoreRoot[i * SIZE + j]->pos.x = i;
            scoreRoot[i * SIZE + j]->pos.x = j;
        }
    }
}
struct Treenode *talloc(void)
{
    return (struct Treenode *)malloc(sizeof(struct Treenode));
}

struct Treenode *addBrother(struct Treenode *root, int x, int y, int type)
{
    struct Treenode *p;
    if (root == NULL)
    {
        p = talloc();
        p->alpha = INVINF;
        p->beta = POSINF;
        p->brother = p->son = NULL;
        p->pos.x = x;
        p->pos.y = y;
        p->type = type;
        return p;
    }
    p = talloc();
    p->alpha = INVINF;
    p->beta = POSINF;
    p->brother = root->brother;
    root->brother = p;
    p->son = NULL;
    p->pos.x = x;
    p->pos.y = y;
    p->type = type;
    return root;
}
/*
struct Treenode *addSon(struct Treenode *root, int x, int y, int type)
{
    struct Treenode *p;
    if (root == NULL)
    {
        p = talloc();
        p->alpha = INVINF;
        p->beta = POSINF;
        p->brother = p->son = NULL;
        p->pos.x = x;
        p->pos.y = y;
        p->type = type;
        return p;
    }
    p = talloc();
    p->alpha = INVINF;
    p->beta = POSINF;
    p->brother = root->brother;
    root->brother = p;
    p->son = NULL;
    p->pos.x = x;
    p->pos.y = y;
    p->type = type;
    return root;
}
*/
struct Treenode *freeTree(struct Treenode *root)
{
    if (root == NULL)
    {
        return root;
    }
    freeTree(root->brother);
    freeTree(root->son);
    free(root);
}
struct Treenode *search(int depth, struct Treenode *childroot)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardForScore[i][j] == EMPTY)
            {
                // arrayForInnerBoardForScore[i][j] = depth;
                printf("Enter\n");
                arrayForInnerBoardForScore[i][j] = (childroot->type == MAX) ? ((gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS) : ((!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS);
                printf("Exit\n");
                childroot->son = addBrother(childroot->son, i, j, !childroot->type);
                if (childroot->son->brother != NULL)
                {
                    if (childroot->type == MIN)
                    {
                        childroot->son->brother->beta = childroot->beta;
                    }
                    else
                    {
                        childroot->son->brother->alpha = childroot->alpha;
                    }
                }
                if (depth < DEPTH - 1)
                {
                    if (childroot->son->brother != NULL)
                    {
                        childroot->son->brother = search(depth + 1, childroot->son->brother);
                    }
                    else
                    {
                        childroot->son = search(depth + 1, childroot->son);
                    }
                }
                int score;
                if (childroot->type == MIN)
                {
                    gamestates.playerstate = !gamestates.playerstate;
                    score = judge_score(i, j, arrayForInnerBoardForScore[0]);
                    gamestates.playerstate = !gamestates.playerstate;
                    childroot->beta = (childroot->beta < score) ? childroot->beta : score;
                }
                else
                {
                    // gamestates.playerstate = !gamestates.playerstate;
                    score = judge_score(i, j, arrayForInnerBoardForScore[0]);
                    // gamestates.playerstate = !gamestates.playerstate;

                    childroot->alpha = (childroot->alpha > score) ? childroot->alpha : score;
                };
                for (int i = 0; i < SIZE; i++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        printf("%d ", arrayForInnerBoardForScore[i][j]);
                    }
                    printf("\n");
                }
                arrayForInnerBoardForScore[i][j] = EMPTY;
                if (childroot->beta <= childroot->alpha)
                {
                    childroot->son = freeTree(childroot->son);
                    return childroot;
                }
            }
            // printf("Depth:%d,finish:%d,%d,alpha:%d beta:%d\n", depth, i, j, childroot->alpha, childroot->beta);
        }
    }
    // printf("Finish\n");
    //  每次Finish代表了一次search的结束，进入到下一层
    return childroot;
}

int ai_tree(void)
{
    gamestates.playerstate = !gamestates.playerstate;
    printf("Playerstates=%d\n", gamestates.playerstate);
    int max = 0;
    struct point temppos;
    init_scoreRoot(scoreRoot[0]);
    updateInnerBoardForScore();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardForScore[i][j] == EMPTY)
            {
                arrayForInnerBoardForScore[i][j] = (!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS;
                scoreRoot[i][j] = search(0, scoreRoot[i][j]);
                printf("scoreRoot[i][j]->alpha=%d\n", scoreRoot[i][j]->alpha);
                if (max < scoreRoot[i][j]->alpha)
                {
                    max = scoreRoot[i][j]->alpha;
                    temppos.x = i;
                    temppos.y = j;
                }
                arrayForInnerBoardForScore[i][j] = EMPTY;
            }
        }
    }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%5d ", scoreRoot[i][j]->alpha);
        }
        printf("\n");
    }
    // SIZE-这里优化会出bug，回头修一下
    pos.x = SIZE - temppos.x;
    pos.y = temppos.y;
    ai_input(SIZE - pos.x, pos.y);
}

int ai_random(void)
{
    pos.x = rand() % SIZE + 1;
    pos.y = rand() % SIZE;
    ai_input(pos.x, pos.y);
    return 0;
}

void ai_input(int x, int y)
{
    arrayForInnerBoardLayout[x][y] = (!gamestates.playerstate == BLACK) ? BLACKCHESSCURRENT : WHITECHESSCURRENT;
}
void ai_input_clear(int x, int y)
{
    arrayForInnerBoardLayout[x][y] = EMPTY;
}