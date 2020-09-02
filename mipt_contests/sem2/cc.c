#include <stdio.h>

int is_prime(int n)
{
    if((n == 2) || (n == 3))
        return 1;
    if((n < 2) || (n % 2 == 0) || (n % 3 == 0))
        return 0;

    for(int j = 5; j * j <= n; j += 6)
        if (((n % j) == 0) || ((n % (j + 2)) == 0))
            return 0;
    return 1;
}

int pown(int value, int n)
{
    int ans = value;
    int mult = value;
    while(n > 1)
    {
        ans = ans * mult;
        --n;
    }

    return ans;
}

int is_cprime(int n)
{
    int circule = n;
    int power = 0;
    while(n > 0)
    {
        n = n / 10;
        ++power;
    }

    for(int i = 0; i < power; ++i)
    {
        int last;
        if(is_prime(circule) == 0)
            return 0;

        last = circule % 10;
        circule = circule / 10 + last * pown(10, power - 1);
    }

    return 1;
}

int main()
{
    int n;
    int toleft = 0, toright = 0;
    int ans;
    scanf("%d", &n);

    while((is_cprime(n + toright) == 0) && (is_cprime(n - toleft) == 0))
    {
        ++toright;
	++toleft;
    }

    if(is_cprime(n + toright) == 1)
        printf("%d", n + toright);
    else
        printf("%d", n - toleft);
}
