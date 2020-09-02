#include <stdio.h>

#define MAX 100

int main()
{
    int arr[MAX] = { 0 };
    unsigned long long  x;
    int y;
    int count = 0;
    scanf("%llu%d", &x, &y);

    while(x != 0)
    {
        arr[count] = x % y;
        x = x / y;
        count += 1;
    }

    for(int i = count - 1; i >= 0; --i)
        printf("%d", arr[i]);
}
