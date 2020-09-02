#include <stdio.h>

unsigned long long fib_mod (unsigned long long n, unsigned long long m)
{
    unsigned long long first = 0, second = 1;
    unsigned idx;
    if (n == 0)
        return 0;
    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = (second + first) % m;
        first = tmp;
    }
    return second;
}

int piz_period (unsigned long long m)
{
    unsigned long long a = 1, b = 1, len = 1;
    while((a != 0) || (b != 1))
    {
        unsigned long long tmp = b;
        b = (b+a) % m;
        a = tmp;
        len += 1;
    }
    return len;
}

int main ()
{
    unsigned long long n, m;
    scanf("%lld%lld", &n, &m);
    printf("%lld\n%d\n", fib_mod(n % piz_period(m), m), piz_period(m));
}
