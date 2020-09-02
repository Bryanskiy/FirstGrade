#include <stdio.h>

void gcd(unsigned long long a, unsigned long long b, unsigned long long *d, unsigned long long *x, unsigned long long *y)
{
    unsigned long long s;
    if (b == 0)
    {
        *d = a;
        *x = 1;
        *y = 0;
        return;
    }
    gcd(b, a % b, d, x, y);
    s = *y;
    *y = *x - (a / b) * (*y);
    *x = s;
}

int main()
{
    unsigned long long a, b, x = 0, y = 0, d;

    scanf("%lld%lld", &a, &b);

    gcd(a, b, &d, &x, &y);

    printf("%lld %lld %lld", x, y, d);
}
