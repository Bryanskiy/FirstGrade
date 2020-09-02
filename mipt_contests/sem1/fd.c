#include <stdio.h>

unsigned long long fib(unsigned n);
main()
{
    unsigned n;
    scanf("%u", &n);
    printf("%llu", fib(n));
}
unsigned long long fib(unsigned n)
{
    unsigned long long first = 0ull, second = 1ull;
    int idx;
    if (n == 0) return 0ll;
    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = (second + first) % 10;
        first = tmp;
    }
    return second;
}
