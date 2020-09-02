#include <stdio.h>
#include <math.h>
int is_prime(unsigned n);
int main()
{
    int i = 2;
    int number = 0;
    int n;

    scanf("%d", &n);
    while(number < n)
    {
        if(is_prime(i) == 1)
            number = number +1;
        ++i;
    }
    printf("%d", i - 1);
}

int is_prime(unsigned n)
{
    unsigned last;
    if ((n == 2) || (n == 3))
        return 1;
    if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0))
        return 0;
    last = (unsigned) sqrt(n) + 1;
    for (int j = 5; j < last; j += 6)
        if (((n % j) == 0) || ((n % (j + 2)) == 0))
            return 0;
    return 1;
}
