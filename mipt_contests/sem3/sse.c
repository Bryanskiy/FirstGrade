#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int search_min(int *arr, int len, int last)
{
    int min = arr[last];
    int n_min = last;

    assert(len != last);

    for(int i = last + 1; i < len; ++i)
    {
        if(arr[i] < min)
        {
            min = arr[i];
            n_min = i;
        }
    }

    return n_min;
}

int main()
{
    int len, last;
    int* arr;

    scanf("%d", &len);
    arr = (int*)calloc(len, sizeof(int));

    for(int i = 0; i < len; ++i)
    {
        scanf("%d", &arr[i]);
    }

    scanf("%d", &last);

    if(last == len)
    {
        for(int i = 0; i < len; ++i)
        {
            printf("%d ", arr[i]);
        }
    }
    else
    {
        int n_min = search_min(arr, len, last);
        int tmp = arr[last];
        arr[last] = arr[n_min];
        arr[n_min] = tmp;
        for(int i = 0; i < len; ++i)
        {
            printf("%d ", arr[i]);
        }
   }

}
