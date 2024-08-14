#include "head.h"

int main()
{
    init_state();
    input();
    update();
    while (gamestates.runningstate)
    {
        update();
    }
    return 0;
}