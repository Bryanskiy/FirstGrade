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

int main()
{
    int a = 0, b = 0;
    int ans = 0;
    int current = 0;
    int n; scanf("%d", &n);

    for(int i = -n + 1; i < n; ++i)
    {
        for(int j = -n + 1; j < n; ++j)
        {
            for(int N = 0; ; ++N)
            {
                if(is_prime(N * N + i * N + j))
                {
                    current += 1;
                    if(current > ans)
                    {
                        a = i;
                        b = j;
                        ans = current;
                    }
                }
                else
                {
                    current = 0;
                    break;
                }
            }
        }
    }

    printf("%d %d %d", a, b, ans);
}

