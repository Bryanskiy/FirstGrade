#include <stdio.h>
#include <assert.h>

unsigned long long gcd(unsigned long long x, unsigned long long y);
int main()
{
    unsigned long long a = 2;
    unsigned long long i = 3;
    int n; scanf("%d", &n);

    for(i; i < n + 1; ++i)
    {
        unsigned long long b = i;
        a = a * b / gcd(a, b);
    }
    printf("%llu", a);
}


unsigned long long gcd(unsigned long long x, unsigned long long y)
{
  unsigned long long q;
  if (y > x)
    return gcd(y, x);
  assert (y > 0);
  q = x % y;
  if (q == 0)
    return y;
  return gcd(y, q);
}
