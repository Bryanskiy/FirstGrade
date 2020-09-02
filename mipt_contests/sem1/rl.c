#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long long x = 0, y = 0, g;
    int res;

    res = scanf("%llu %llu", &x, &y);
    assert(res == 2);

    while(x != 0 && y != 0)
    {
        if (x > y)
            x = x % y;
        else
            y = y % x;
    }
    g = x + y;
    printf("%llu\n", g);
    return 0;
}
