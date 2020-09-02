#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int NUMLIM = 30;

unsigned long long prod_mod (unsigned long long n, unsigned long long k, unsigned long long m)
{
    unsigned long long add, sum;
    assert (m > 1);
    if (k == 0)
        return 1;
    add = n % m;
    sum = 0;
    while (k > 0)
    {
        if ((k % 2) == 1)
        {
            sum = (sum + add) % m;
            k = k - 1;
        }
        else
        {
            add = (add + add) % m;
            k = k / 2;
        }
    }
    return sum;
}

unsigned long long smart_prod_mod (unsigned long long n, unsigned long long k, unsigned long long m)
{
    unsigned long long ullmax = -0ull;
    if((ullmax - k) > n)
        return prod_mod(n, k, m);
    else
        return n * k;
}
unsigned pow_mod (unsigned long long n, unsigned long long k, unsigned long long m)
{
    unsigned long long mult, prod;
    assert (m > 1);
    if (k == 0)
        return 1;
    mult = n % m;
    prod = 1;
    while (k > 0)
    {
        if ((k % 2) == 1)
        {
            prod = smart_prod_mod (prod, mult, m);
            k = k - 1;
        }
        else
        {
            mult = smart_prod_mod (mult, mult, m);
            k = k / 2;
        }
    }
    return prod;
}

unsigned long long gcd(unsigned long long a, unsigned long long p)
{
    return p ? gcd(p, a % p) : a;
}

int main ()
{
    int res;
    unsigned long long p, a;
    res = scanf("%llu", &p);
    assert(res == 1);
    srand(time(NULL));
    for(int i = 0; i < NUMLIM; ++i)
    {
        a = (unsigned long long) rand() << 32;
        a |= rand();
        if(gcd(a, p) != 1)
            continue;
        if(pow_mod(a, p - 1, p) != 1)
        {
            printf("0");
            return 0;
        }
    }
    printf("1");
    return 0;
}
