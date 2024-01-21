#include "head.h"
struct Treenode *scoreRoot[SIZE][SIZE];
struct Treenode *scoreRoot_oppo_temp[SIZE][SIZE];
struct Treenode *scoreRoot_depth_temp[SIZE][SIZE];
struct Treenode *root = NULL;
struct Treenode *root_temp = NULL;
int arrayForInnerBoardForScore[SIZE][SIZE];
int alloccount = 0;

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
            scoreRoot[i * SIZE + j] = NULL;
        }
    }
}
void evolve(struct Treenode **scoreRoot)
{
    int score = 0;
    int score_mine_1 = 0;
    int score_oppo = 0;
    updateInnerBoardForScore();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardForScore[i][j] == EMPTY)
            {
                arrayForInnerBoardForScore[i][j] = (!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS;
                score_mine_1 = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);
                arrayForInnerBoardForScore[i][j] = EMPTY;
                gamestates.playerstate = !gamestates.playerstate;
                arrayForInnerBoardForScore[i][j] = (!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS;
                score_oppo = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);
                gamestates.playerstate = !gamestates.playerstate;
                score = score_mine_1 * 1 + score_oppo * 1;
                scoreRoot[i * SIZE + j] = addSon(score, i, j, scoreRoot[i * SIZE + j]);
                arrayForInnerBoardForScore[i][j] = EMPTY;
            }
            else
            {
                score = OCCUPIED;

                // if (scoreRoot[i * SIZE + j] != NULL)
                // printf("(%c%d)ScoreBefore=%d\n", j + 'A', SIZE - i, scoreRoot[i * SIZE + j]->score);
                if ((scoreRoot[i * SIZE + j] == NULL) || (scoreRoot[i * SIZE + j]->score > 0))
                    scoreRoot[i * SIZE + j] = addSon(score, i, j, scoreRoot[i * SIZE + j]);
                /*
                if (scoreRoot[i * SIZE + j] != NULL)
                {
                    printf("1(%c%d)ScoreAfter=%d\n", j + 'A', SIZE - i, scoreRoot[i * SIZE + j]->score);
                    if (scoreRoot[i * SIZE + j]->son != NULL)
                    {
                        printf("2(%c%d)ScoreAfter=%d\n", j + 'A', SIZE - i, scoreRoot[i * SIZE + j]->son->score);
                        if ((scoreRoot[i * SIZE + j]->son)->son != NULL)
                        {
                            printf("3(%c%d)ScoreAfter=%d\n", j + 'A', SIZE - i, ((scoreRoot[i * SIZE + j]->son)->son)->score);
                        }
                        else
                            printf("None\n");
                    }
                }
                */
            }
        }
    }
}

/*
void evolve(int depth)
{
    int score = 0;
    int score_mine_1 = 0;
    int score_oppo = 0;
    if (evolveLayers == 0)
    {
        updateInnerBoardForScore();
    }

    int scoreBoard_test[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            scoreBoard_test[i][j] = 0;
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardForScore[i][j] == EMPTY)
            {
                arrayForInnerBoardForScore[i][j] = (!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS;

                score_mine_1 = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);

                arrayForInnerBoardForScore[i][j] = EMPTY;

                gamestates.playerstate = !gamestates.playerstate;
                arrayForInnerBoardForScore[i][j] = (!gamestates.playerstate == BLACK) ? BLACKCHESS : WHITECHESS;
                score_oppo = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);
                gamestates.playerstate = !gamestates.playerstate;
                score = score_mine_1 * 1 + score_oppo * 1;
                // scoreBoard_test[i][j] = score;
                scoreRoot[i][j] = addSon(score, i, j, scoreRoot[i][j]);

                if ((depth < MAXEVOLVELAYERS) && ((score > mypow(100, depth + 1))))
                {
                    printf("ScoreEnter:%d\n", score);
                    evolve(depth + 1);
                }
                arrayForInnerBoardForScore[i][j] = EMPTY;
            }
            else
            {
                score = FORBIDDEN;
                // scoreBoard_test[i][j] = score;
                scoreRoot[i][j] = addSon(score, i, j, scoreRoot[i][j]);
            }
        }
    }
}
*/

struct Treenode *collect(struct Treenode *root, struct Treenode **scoreRoot, int mode)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            getbrotherScore(scoreRoot[i * SIZE + j]);
            scoreRoot[i * SIZE + j]->score = scoreRoot[i * SIZE + j]->score + weight(i, j);
            // printf("(%c%drootscore:%d)\n", 'A' + scoreRoot[i][j]->y, SIZE - scoreRoot[i][j]->x, scoreRoot[i][j]->score);
            if (mode == 0)
            {
                root = treeBrotherSort(root, scoreRoot[i * SIZE + j]);
            }
        }
    }
    return root;
}

// 先生成0层兄弟下的二叉树，然后统计每棵树的权，然后按照权排序添加兄弟

// 必须有一个节点后才能添加兄弟
void addBrother(int score, int x, int y, struct Treenode *root)
{
    struct Treenode *new;
    new = talloc();
    new->brother = new->son = NULL;
    new->depth = root->depth;
    new->x = x;
    new->y = y;
    new->score = score;
    treeBrotherSort(root, new);
}
/*
struct Treenode *treeBrotherSort(struct Treenode *root, struct Treenode *new)
{
    if (root == NULL)
    {
        root = new;
        root->brother = NULL;
        printf("Link NULL root to new\n");
        return root;
    }
    else if (root->score <= new->score)
    {
        printf("Put large root to head:(%c%drootscore:%d)(%c%dnewscore:%d)\n", 'A' + root->y, SIZE - root->x, root->score, 'A' + new->y, SIZE - new->x, new->score);
        new->brother = root;
        return new;
    }
    else if (root->score > new->score)
    {
        printf("Put small root to next:(%c%drootscore:%d)(%c%dnewscore:%d)\n", 'A' + root->y, SIZE - root->x, root->score, 'A' + new->y, SIZE - new->x, new->score);
    }
}
*/
/*
struct Treenode *treeBrotherSort(struct Treenode *root, struct Treenode *new)
{
    struct Treenode *temp = root;
    struct Treenode *pre = NULL;
    while (1)
    {
        if (root == NULL)
        {
            root = new;
            break;
        }
        // root为空
        if (temp != NULL)
        { // root is not NULL
            if (temp->score <= new->score)
            { // new larger than root
                if (pre == NULL)
                {
                    // new->brother = root;
                    root = new;
                    break;
                }
                // instantly larger
                else
                {
                    new->brother = temp;
                    pre->brother = new;
                    break;
                }
                //
            }
            else
            {
                pre = temp;
                temp = temp->brother;
                printf("Enter\n");
            }
        }
        else
        {
            temp = new;
            break;
        }
    }
    return root;
}
*/

struct Treenode *treeBrotherSort(struct Treenode *root, struct Treenode *new)
{
    struct Treenode *temp_pre;
    struct Treenode *temp_root;
    temp_root = root;
    if (root == NULL)
    {
        root = new;
        new->brother = NULL;
        return root;
    }
    while ((new->score <= temp_root->score) && (temp_root->brother != NULL))
    {
        temp_pre = temp_root;
        temp_root = temp_pre->brother;
    }

    if (new->score > temp_root->score)
    {
        if (temp_root == root)
        {
            root = new;
            new->brother = temp_root;
        }
        else
        {
            temp_pre->brother = new;
            new->brother = temp_root;
        }
    }
    else
    {
        temp_root->brother = new;
        new->brother = NULL;
    }
    return root;
}

struct Treenode *addSon(int score, int x, int y, struct Treenode *root)
{
    if (root == NULL)
    {
        root = talloc();
        root->depth = 0;
        root->x = x;
        root->y = y;
        root->score = score;
        root->son = root->brother = NULL;
    }
    else
    {
        struct Treenode *temp = root;
        while (temp->son != NULL)
        {
            temp = temp->son;
        }
        struct Treenode *new;
        new = talloc();
        new->brother = new->son = NULL;
        new->score = score;
        new->depth = temp->depth + 1;
        new->x = x;
        new->y = y;
        temp->son = new;
    }
    return root;
}
struct Treenode *freeTree_a(struct Treenode *root)
{
    if (root == NULL)
    {
        return root;
    }
    freeTree_a(root->brother);
    freeTree_a(root->son);
    free(root);
}
struct Treenode *treeupdate(struct Treenode *root)
{

    if (root != NULL)
    {
        struct Treenode *temp = root;
        free(root);
        depthupdate(temp->son);
        freeTree(temp->brother);
        return temp->son;
    }
    else
    {
        return NULL;
    }
}
void depthupdate(struct Treenode *root)
{

    if (root != NULL)
    {
        root->depth = root->depth - 1;
        depthupdate(root->brother);
        depthupdate(root->son);
    }
    else
    {
        return;
    }
}
void freeTree(struct Treenode *brother)

{
    if (brother != NULL)
    {
        freeTree(brother->son);
        freeTree(brother->brother);
        free(brother);
    }
    else
    {
        return;
    }
}
void getbrotherScore(struct Treenode *root)
{
    // if (root != NULL)
    //  判断条件为避免空指针调用临时添加，可以删除寻找原因
    root->score = root->score + sontreeScoreSum(root->son);
}
int sontreeScoreSum(struct Treenode *son)
{
    int temp = 0;
    if (son != NULL)
    {
        if (son->score != OCCUPIED)
            temp = son->score + ((sontreeScoreSum(son->son) + sontreeScoreSum(son->brother)) / mypow(2, son->depth));
    }
    return temp;
}
struct Treenode *talloc(void)
{
    // alloccount = alloccount + 1;
    return (struct Treenode *)malloc(sizeof(struct Treenode));
}

struct Treenode *evolve_tree(struct Treenode **scoreRoot, struct Treenode **scoreRoot_oppo_temp, struct Treenode *root, struct Treenode *root_temp, int depth)
{
    // 得先有广度！
    struct point pos_origin, pos_root, pos_root_temp;
    init_scoreRoot(scoreRoot);
    evolve(scoreRoot);
    root = collect(root, scoreRoot, depth);
    ai_input(root->x, root->y);

    gamestates.playerstate = !gamestates.playerstate;
    init_scoreRoot(scoreRoot_oppo_temp);
    evolve(scoreRoot_oppo_temp);
    root_temp = collect(root_temp, scoreRoot_oppo_temp, 0);
    ai_input(root_temp->x, root_temp->y);
    pos_root.x = root->x;
    pos_root.y = root->y;
    pos_root_temp.x = root_temp->x;
    pos_root_temp.y = root_temp->y;
    // freeTree_a(root_temp);????这样反而能跑了?
    gamestates.playerstate = !gamestates.playerstate;
    if (depth < MAXDEPTH)
    {
        root = evolve_tree(scoreRoot, scoreRoot_oppo_temp, root, root_temp, depth + 1);
    }
    root->score = root->score + (maxscore(scoreRoot) / (mypow(2, depth)));
    // root->score = root->score + (maxscore(scoreRoot));
    printf("root->score=%d\n", root->score);
    printf("DepthReturn:%d\n", depth);
    ai_input_clear(pos_root.x, pos_root.y);
    ai_input_clear(pos_root_temp.x, pos_root_temp.y);
    return root;
}
// 目前是判定有问题

int ai_tree(void)
{
    struct point temppoint, temppoint_max;
    struct Treenode *temp;
    int max = 0;
    int width = 0;
    int evolvedepth = 0;
    int evolvewidth = 0;
    gamestates.playerstate = !gamestates.playerstate;
    printf("Playerstates=%d\n", gamestates.playerstate);
    init_scoreRoot(scoreRoot[0]);
    evolve(scoreRoot[0]);
    root = collect(root, scoreRoot[0], 0);
    // breakpoint();
    temp = root;
    while (width < MAXWIDTH)
    {
        temppoint.x = temp->x;
        temppoint.y = temp->y;
        ai_input(temppoint.x, temppoint.y);
        root->score = 0;
        temp->score = evolve_tree(scoreRoot_depth_temp[0], scoreRoot_oppo_temp[0], root, root_temp, 1)->score;
        if (max < temp->score)
        {
            temppoint_max.x = temppoint.x;
            temppoint_max.y = temppoint.y;
        }
        printf("(%c%d):score=%d,depth=%d\n", 'A' + temp->y, SIZE - temp->x, temp->score, temp->depth);
        temp = temp->brother;
        width = width + 1;
        ai_input_clear(temppoint.x, temppoint.y);
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                scoreRoot[i][j]->son = freeTree_a(scoreRoot[i][j]->son);
            }
        }
    }

    // printf("alloccount=%d\n", alloccount);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf("%10d ", scoreRoot[i][j]->score);
        }
        printf("\n");
    }
    pos.x = SIZE - temppoint_max.x;
    // SIZE-这里优化会出bug，回头修一下
    pos.y = temppoint_max.y;
    //
    freeTree_a(root);
    ai_input(SIZE - pos.x, pos.y);
}
// 理一下思路应该是，我方评分选出最优，然后落子，然后在此基础上给黑方评分，落子，以此循环迭代层数，然后统计
// 这里有落子可能的选择，这里其实可以选择前几个（作为搜索广度），然后；去讨论这几个情况下对方落子（深度）后的情况！
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
void display_scoreBoard(struct Treenode *root)
{
    int scoreBoard[SIZE][SIZE];
    struct Treenode *temp;
    temp = root;
    while (temp != NULL)
    {
        printf("Enter\n");
        printf("(%c,%d):score:%d\n", 'A' + temp->y, SIZE - temp->x, temp->score);
        scoreBoard[temp->x][temp->y] = temp->score;
        temp = temp->brother;
    }

    displaychessshape(scoreBoard[0], SIZE, SIZE);
}

void display_treenode(struct Treenode *root)
{
    if (root != NULL)
    {
        printf("%c%d: ", 'A' + root->y, SIZE - root->x);
        printf("score=%d ", root->score);
        printf("depth=%d\n ", root->depth);
    }
}

void breakpoint(void)
{
    ;
}

int maxscore(struct Treenode **scoreRoot)
{
    int max = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            max = (max > scoreRoot[i * SIZE + j]->score) ? max : scoreRoot[i * SIZE + j]->score;
        }
    }
    return max;
}