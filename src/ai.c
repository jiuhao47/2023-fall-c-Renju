#include "head.h"
#include "log.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
  long long score;
  int i;
  int j;
} Item;

static int item_cmp(const void *a, const void *b) {
  const Item *A = a;
  const Item *B = b;
  if (A->score < B->score)
    return 1;
  if (A->score > B->score)
    return -1;
  return 0;
}

static int ll_cmp_desc(const void *a, const void *b) {
  const long long A = *(const long long *)a;
  const long long B = *(const long long *)b;
  if (A < B)
    return 1;
  if (A > B)
    return -1;
  return 0;
}

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
        // if score_mine or score_oppo > P_FLEXFOUR, do not need to evolve
        // deeper
        if (score_mine >= P_FLEXFOUR || score_oppo >= P_FLEXFOUR) {
          // printf("EvolveLayer[%d] Skip evolve at (%d,%d) with
          // score_mine=%lld, "
          //        "score_oppo=%lld\n",
          //        depth, i, j, score_mine, score_oppo);
          // if (depth == 0) {
          //   printf(
          //       "EvolveLayer[%d] Skip evolve at (%d,%d) with score_mine=%lld,
          //       " "score_oppo=%lld\n", depth, i, j, score_mine, score_oppo);
          //   break;
          // }
          // arrayForInnerBoardLayout[i][j] = EMPTY;
          // continue;
        }

        if ((depth < MAXEVOLVELAYERS) && ((score > mypow(300, depth + 1)))) {
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
      long long decay = 1LL << (son->depth + 3);
      temp = son->score + (childsum / decay);
    }
  }
  return temp;
}
// alloc memory from heap
struct Treenode *talloc(void) {
  return (struct Treenode *)malloc(sizeof(struct Treenode));
}

void display_score() {

  // system("clear");
  /* Render score board as levels 0-9 based on ranking (highest -> 9) */
  Item items[SIZE * SIZE];
  int n = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (scoreRoot[i][j] != NULL) {
        items[n].score = scoreRoot[i][j]->score;
        items[n].i = i;
        items[n].j = j;
        n++;
      }
    }
  }
  if (n > 1) {
    qsort(items, n, sizeof(items[0]), item_cmp);
  }

  /* build level map
   * - negative scores -> level 0
   * - non-negative scores -> levels 1..9 by rank (highest -> 9)
   */
  int levelmap[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      levelmap[i][j] = -1;

  /* first assign negatives to 0 and collect non-negative items */
  Item pos_items[SIZE * SIZE];
  int m = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (scoreRoot[i][j] != NULL) {
        long long s = scoreRoot[i][j]->score;
        if (s < 0) {
          levelmap[i][j] = 0;
        } else {
          pos_items[m].score = s;
          pos_items[m].i = i;
          pos_items[m].j = j;
          m++;
        }
      }
    }
  }

  /* sort non-negative scores by descending score */
  if (m > 1) {
    qsort(pos_items, m, sizeof(pos_items[0]), item_cmp);
  }

  /* map unique scores to levels 9..1 so identical scores get identical level */
  if (m > 0) {
    long long uniq[SIZE * SIZE];
    for (int i = 0; i < m; i++)
      uniq[i] = pos_items[i].score;
    qsort(uniq, m, sizeof(uniq[0]), ll_cmp_desc);
    /* uniq now sorted descending but may have duplicates */
    long long uniq2[SIZE * SIZE];
    int uk = 0;
    for (int i = 0; i < m; i++) {
      if (i == 0 || uniq[i] != uniq[i - 1]) {
        uniq2[uk++] = uniq[i];
      }
    }

    for (int k = 0; k < m; k++) {
      long long s = pos_items[k].score;
      int idx = 0;
      for (int u = 0; u < uk; u++) {
        if (uniq2[u] == s) {
          idx = u;
          break;
        }
      }
      int level;
      if (uk == 1) {
        level = 9;
      } else {
        /* idx 0 = highest -> 9; idx uk-1 -> 1 */
        level = 9 - (int)((idx * 8) / (uk - 1));
      }
      if (level < 1)
        level = 1;
      if (level > 9)
        level = 9;
      levelmap[pos_items[k].i][pos_items[k].j] = level;
    }
  }

  /* compute a fractional digit (0..9) for finer display within same level
   * subdigit is used only for display; color remains based on integer level
   */
  int subdigit[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      subdigit[i][j] = 0;

  for (int lv = 1; lv <= 9; lv++) {
    /* collect all positions with this level */
    int idxs_i[SIZE * SIZE];
    int idxs_j[SIZE * SIZE];
    int cnt = 0;
    for (int k = 0; k < m; k++) {
      int ii = pos_items[k].i;
      int jj = pos_items[k].j;
      if (levelmap[ii][jj] == lv) {
        idxs_i[cnt] = ii;
        idxs_j[cnt] = jj;
        cnt++;
      }
    }
    if (cnt <= 1) {
      /* keep subdigit 0 */
      continue;
    }
    /* sort these positions by actual score descending to give subrank */
    for (int a = 0; a < cnt; a++) {
      for (int b = a + 1; b < cnt; b++) {
        long long sa = scoreRoot[idxs_i[a]][idxs_j[a]]->score;
        long long sb = scoreRoot[idxs_i[b]][idxs_j[b]]->score;
        if (sa < sb) {
          int ti = idxs_i[a];
          int tj = idxs_j[a];
          idxs_i[a] = idxs_i[b];
          idxs_j[a] = idxs_j[b];
          idxs_i[b] = ti;
          idxs_j[b] = tj;
        }
      }
    }
    for (int p = 0; p < cnt; p++) {
      /* map p=0..cnt-1 so higher raw score -> larger digit (9..0)
       * we invert the mapping so p=0 (highest score) -> 9,
       * and p=cnt-1 (lowest in this level) -> 0.
       */
      int d = 0;
      if (cnt > 1)
        d = ((cnt - 1 - p) * 9) / (cnt - 1);
      subdigit[idxs_i[p]][idxs_j[p]] = d;
    }
  }

  printf("%s", GAMEINFO);
  for (int i = 0; i < SIZE; i++) {
    printf("%3d ", SIZE - i);
    for (int j = 0; j < SIZE; j++) {
      if (levelmap[i][j] >= 0) {
        int lv = levelmap[i][j];
        int d = subdigit[i][j];
        /* ANSI 256-color ramp for levels 0..9 */
        int colors[10] = {21, 27, 33, 39, 45, 51, 82, 118, 226, 196};
        int col = colors[lv];
        /* print colored value with one decimal, keep color by integer level */
        printf(" \x1b[38;5;%dm%d.%d\x1b[0m", col, lv, d);
      } else {
        /* empty cell printed as 3-char token with surrounding space to align */
        printf("  + ");
      }
    }
    printf("\n");
  }
  /* print column labels A..O */
  /* adjust column labels to match new cell width (4 chars per cell incl.
   * leading space) */
  printf("    ");
  for (int j = 0; j < SIZE; j++)
    printf("  %c ", 'A' + j);
  printf("\n\n");
}

// main function of ai
int ai_tree(void) {
  gamestates.playerstate = !gamestates.playerstate;
  init_scoreRoot(scoreRoot[0]);
  evolve(0);
  root = collect(root, scoreRoot[0]);
  pos.x = SIZE - root->x;
  pos.y = root->y;
  display_score();
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