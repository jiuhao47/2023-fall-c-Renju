#include "head.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Treenode *scoreRoot[SIZE][SIZE];
struct Treenode *root = NULL;
int arrayForInnerBoardForScore[SIZE][SIZE];
int evolveLayers = 0;

// copy inner board to score board
void updateInnerBoardForScore(void) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      arrayForInnerBoardForScore[i][j] = arrayForInnerBoardLayout[i][j];
    }
  }
}
// scoreRoot initialize
void init_scoreRoot(struct Treenode **scoreRoot) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      scoreRoot[i * SIZE + j] = NULL;
    }
  }
}

// generate evaluation of chessshape
void evolve(int depth) {
  long long score = 0;
  long long score_mine = 0;
  long long score_oppo = 0;
  int attack;
  int defence;
  if (evolveLayers == 0) {
    updateInnerBoardForScore();
  }
  if (!(gamestates.playerstate == BLACK)) {
    attack = 7;
    defence = 3;
  } else {
    attack = 3;
    defence = 7;
  }
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (arrayForInnerBoardForScore[i][j] == EMPTY) {
        // check EMPTY
        arrayForInnerBoardForScore[i][j] =
            (!(gamestates.playerstate == BLACK)) ? BLACKCHESS : WHITECHESS;

        score_mine = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);
        if (score_mine > P_DIRECTFOUR) {
          attack = 7;
          defence = 3;
          // attack mode
        }
        arrayForInnerBoardForScore[i][j] = EMPTY;
        // self score evaluation
        gamestates.playerstate = !gamestates.playerstate;
        arrayForInnerBoardForScore[i][j] =
            (!(gamestates.playerstate == BLACK)) ? BLACKCHESS : WHITECHESS;
        score_oppo = judge_score(SIZE - i, j, arrayForInnerBoardForScore[0]);
        if (score_oppo > P_DIRECTFOUR) {
          attack = 3;
          defence = 7;
          // defence mode
        }
        gamestates.playerstate = !gamestates.playerstate;
        // opponent score evaluation
        score = score_mine * attack + score_oppo * defence;
        scoreRoot[i][j] = addSon(score, i, j, scoreRoot[i][j]);
        // sum and and build the tree
        if ((depth < MAXEVOLVELAYERS) && ((score > mypow(600, depth + 1)))) {
          gamestates.playerstate = !gamestates.playerstate;
          evolve(depth + 1);
          gamestates.playerstate = !gamestates.playerstate;
          // single chessshape evolve
          // with enter limitation
        }
        arrayForInnerBoardForScore[i][j] = EMPTY;
      } else {
        score = FORBIDDEN;
        scoreRoot[i][j] = addSon(score, i, j, scoreRoot[i][j]);
      }
    }
  }
}

struct Treenode *collect(struct Treenode *root, struct Treenode **scoreRoot) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      /* skip empty entries */
      if (scoreRoot[i * SIZE + j] == NULL)
        continue;
      getbrotherScore(scoreRoot[i * SIZE + j]);
      /* collect every "brother tree"'s score and add initial weight */
      scoreRoot[i * SIZE + j]->score =
          scoreRoot[i * SIZE + j]->score + weight(i, j);
      /* sort and get the maximum point */
      root = treeBrotherSort(root, scoreRoot[i * SIZE + j]);
    }
  }
  return root;
}

// tree-add-brother-node
void addBrother(long long score, int x, int y, struct Treenode *root) {
  struct Treenode *new;
  new = talloc();
  new->brother = new->son = NULL;
  new->depth = root->depth;
  new->x = x;
  new->y = y;
  new->score = score;
  treeBrotherSort(root, new);
}
// sort and get the maxmium point according to the score
struct Treenode *treeBrotherSort(struct Treenode *root, struct Treenode *new) {
  if (new == NULL)
    return root;
  new->brother = NULL;
  if (root == NULL) {
    return new;
  }
  /* insert at head if new has greater or equal score */
  if (new->score >= root->score) {
    new->brother = root;
    return new;
  }
  /* find insertion point */
  struct Treenode *cur = root;
  while (cur->brother != NULL && cur->brother->score > new->score) {
    cur = cur->brother;
  }
  new->brother = cur->brother;
  cur->brother = new;
  return root;
}
// tree-add-son-node
struct Treenode *addSon(long long score, int x, int y, struct Treenode *root) {
  if (root == NULL) {
    root = talloc();
    root->depth = 0;
    root->x = x;
    root->y = y;
    root->score = score;
    root->son = root->brother = NULL;
  } else {
    struct Treenode *temp = root;
    while (temp->son != NULL) {
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

// free a tree
struct Treenode *freeTree(struct Treenode *root) {
  if (root == NULL) {
    return root;
  }
  freeTree(root->brother);
  freeTree(root->son);
  free(root);
  return NULL;
}

// update a tree(abandon)
struct Treenode *treeupdate(struct Treenode *root) {
  if (root != NULL) {
    struct Treenode *temp = root;
    free(root);
    depthupdate(temp->son);
    freeTree(temp->brother);
    return temp->son;
  } else {
    return NULL;
  }
}
// update a tree's depth(abandon)
void depthupdate(struct Treenode *root) {

  if (root != NULL) {
    root->depth = root->depth - 1;
    depthupdate(root->brother);
    depthupdate(root->son);
  } else {
    return;
  }
}
// collect every "brother tree"'s score
void getbrotherScore(struct Treenode *root) {
  root->score = root->score + sontreeScoreSum(root->son);
}
// collect every "brother tree"'s score (form its son tree)
long long sontreeScoreSum(struct Treenode *son) {
  long long temp = 0;
  if (son != NULL) {
    if (son->score != OCCUPIED) {
      long long childsum =
          sontreeScoreSum(son->son) + sontreeScoreSum(son->brother);
      long long decay = 1LL << (son->depth + 5);
      temp = son->score + (childsum / decay);
    }
  }
  return temp;
}
// alloc memory from heap
struct Treenode *talloc(void) {
  return (struct Treenode *)malloc(sizeof(struct Treenode));
}

// main function of ai
int ai_tree(void) {
  gamestates.playerstate = !gamestates.playerstate;
  init_scoreRoot(scoreRoot[0]);
  evolve(0);
  root = collect(root, scoreRoot[0]);
  pos.x = SIZE - root->x;
  pos.y = root->y;
  // for (int i = 0; i < SIZE; i++) {
  //   for (int j = 0; j < SIZE; j++) {
  //     log(DEBUG, "%5d ", scoreRoot[i][j]->score);
  //   }
  //   log(DEBUG, "\n");
  // }
  freeTree(root);
  /* avoid reusing freed global root pointer in subsequent calls */
  root = NULL;
  ai_input(SIZE - pos.x, pos.y);
  return 0;
}

// random placing(abandon)
int ai_random(void) {
  pos.x = rand() % SIZE + 1;
  pos.y = rand() % SIZE;
  ai_input(pos.x, pos.y);
  return 0;
}

// ai-input
void ai_input(int x, int y) {
  arrayForInnerBoardLayout[x][y] = (!(gamestates.playerstate == BLACK))
                                       ? BLACKCHESSCURRENT
                                       : WHITECHESSCURRENT;
}
// ai-input
void ai_input_clear(int x, int y) { arrayForInnerBoardLayout[x][y] = EMPTY; }