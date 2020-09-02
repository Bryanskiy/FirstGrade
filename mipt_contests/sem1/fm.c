#include <stdio.h>

unsigned long long fib(unsigned n, int m);
main()
{
    unsigned n;
    int m;
    scanf("%u", &n);
    scanf("%d", &m);
    printf("%llu", fib(n,m));
}
unsigned long long fib(unsigned n, int m)
{
    unsigned long long first = 0ull, second = 1ull;
    int idx;
    if (n == 0) return 0ll;
    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = (second + first) % m;
        first = tmp;
    }
    return second;
}
