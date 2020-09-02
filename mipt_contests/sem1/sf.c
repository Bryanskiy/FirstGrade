#include <stdio.h>

#define MAX_FIB_NUM 45 //максимальное число фиб., которое влезает в int

unsigned long long fib(unsigned n)
{
    unsigned long long first = 0, second = 1;
    unsigned idx;
    if (n == 0)
        return 0;
    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = (second + first);
        first = tmp;
    }
    return second;
}

int search(int x, int* fibs)
{
    int i = 0;
    while(fibs[i] <= x)
    {
        ++i;
    }

    if(i == 0)
        return 0;

    return i - 1;
}

int main()
{
    int x;
    int fibs[MAX_FIB_NUM] = { 0 };
    int ans[MAX_FIB_NUM] = { 0 };
    int print = MAX_FIB_NUM - 1;
    scanf("%d", &x);

    for(int i = 0; i < MAX_FIB_NUM; ++i)
        fibs[i] = fib(i+2);
    
    while(x != 0)
    {
        int count;
        count = search(x, fibs);
        ans[count] = 1;

        if(x == fibs[count])
        {
            break;
        }
        x = x - fibs[count];
    }

    while(ans[print] != 1)
    {
        --print;
    }

    for(int i = print; i >= 0; --i)
    {
        printf("%d", ans[i]);
    }
}
