#include <stdio.h>

unsigned search_old(unsigned long long n)
{
    unsigned i = sizeof(unsigned long long) * 8 - 1;
    unsigned bit;
    for(i; ; --i)
    {
        bit = (n >> i) & 1u;
        if(bit == 1)
            return i;
        if(i == 0)
            break;
    }

    return 0;
}

int main()
{
    unsigned long long n;
    unsigned number;
    scanf("%llu", &n);

    if(n == 0)
    {
        printf("%d", -1);
        return 0;
    }
    else
    {
        number = search_old(n);
        printf("%u", number);
        return 0;
    }
}
