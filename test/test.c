ll minimax(struct LISTNODE *old_list_head, struct TNODE *tree_head, int depth, int alpha, int beta, int round, int player_turn)
{
    static int count = 0;
    ll max_eval;                // 最大值
    ll min_eval;                // 最小值
    ll eval;                    // 打分值
    int row;                    // 当前落子的行
    int col;                    // 当前落子的列
    struct LISTNODE *list_head; // 新建的链表头
    struct TNODE *child_node;   // 用于遍历子节点的一个结构体指针
    ll score;                   // 最后返回的分数
    int judge = 0;              // 判断第一步下去后是不是应该剪枝

    row = tree_head->row; // 赋值: 当前落子的行
    col = tree_head->col; // 赋值: 当前落子的列
    place_stone_on_copy(row, col, player_turn);

    if (depth == TREE_DEPTH)
    {
        list_head = create_first_floor(root, player_turn, round, depth); // 建立初层
        player_turn = BLACK + WHITE - player_turn;
    }
    else
        list_head = create_new_floor(old_list_head, tree_head, row, col, BLACK + WHITE - player_turn, round + 1, depth - 1);

    // 如果没有子节点, 那就返回本身的分数值
    if (tree_head->child == NULL)
    {
        list_free(list_head);
        place_stone_on_copy(row, col, SPARE);
        return tree_head->point;
    }

    // 如果现在正在处于最大层, 需要进行递归

    if (player_turn == WHITE) // 最大层. 本层落白子, 下一层该下黑子, 黑方会选分数最高的一个, 因此最高分就是白子的分
    {
        max_eval = -INFINITY;          // 最大值
        child_node = tree_head->child; // 把新层中head的子节点记录, 开始依次搜索
        while (child_node != NULL)     // 如果子节点非空
        {
            eval = minimax(list_head, child_node, depth - 1, alpha, beta, round + 1, BLACK); // 递归, 得到eval值

            max_eval = max(max_eval, eval);   // 找到eval与maxeval中的较大值
            alpha = max(alpha, eval);         // 找到eval与alpha  中的较大值
            if (beta <= alpha)                // alpha大于等于beta!
                break;                        // 子节点的兄弟可以无需考虑了
            child_node = child_node->sibling; // 重复一遍上面的过程
        }
        tree_head->point = max_eval;
        list_free(list_head);
        place_stone_on_copy(row, col, SPARE);
        return max_eval;
    }

    // 如果现在正在处于最小层, 需要进行递归

    else // 最小层. 本层落黑子, 下一层该下白子, 白方会选分数最低的一个, 因此最低分就是黑子的分
    {
        min_eval = INFINITY;
        child_node = tree_head->child;
        while (child_node != NULL)
        {
            eval = minimax(list_head, child_node, depth - 1, alpha, beta, round + 1, WHITE);

            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha)
                break;
            child_node = child_node->sibling;
        }
        tree_head->point = min_eval;
        list_free(list_head);
        place_stone_on_copy(row, col, SPARE);
        return min_eval;
    }
}