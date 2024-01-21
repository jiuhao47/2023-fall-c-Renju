#include <stdio.h>
#include <stdlib.h>
#define LEN 100
void left(int n, int k);
int main(int argc, char *argv[])
{
    int n, k, leftno;
    if (argc != 3 || (n = atoi(argv[1])) <= 0 || (k = atoi(argv[2])) <= 0)
    {
        printf("Usage: ./game n k \n");
        return 1;
    }
    if (n > LEN)
    {
        printf("n is too large, it should be less than%d\n", LEN);
        return 1;
    }
    left(n, k);
    return 0;
}

void left(int n, int k)
{
    struct player
    {
        int num;
        int status;
    } cycle[LEN];
    int i, count, remain;
    for (i = 0; i < n; i++)
    {
        cycle[i].num = i + 1;
        cycle[i].status = 1;
    }
    i = count = 0;
    remain = n;
    while (remain)
    {
        if (cycle[i].status == 1)
        {
            if (++count % k == 0)
            {
                printf("%3d", cycle[i].num);
                cycle[i].status = 0;
                remain--;
            }
        }
        i = (i + 1) % n;
    }
    printf("\n");
    return;
}