#include <stdio.h>
#include <stdlib.h>

int solver(int sum, int number, int* arr, int* table)
{
    int start = arr[0];
    table[start] = 1;
    for(int i = start + 1; i < sum + 1; ++i)
    {
        int min = sum;
        int current = 0;
        for(int k = 0; (k < number) && (i >= arr[k]); ++k)
        {
            if(i == arr[k])
            {
                table[i] = 1;
                continue;
            }

            if(table[i - arr[k]] == 0)
            {
                continue;
            }

            current = table[i - arr[k]] + 1;

            if(current < min)
            {
                table[i] = min = current;
            }
        }
    }

    return 0;
}

int compare(const void* first, const void* second)
{
    int f = *(int*)first;
    int s = *(int*)second;

    return f - s;
}


int main()
{
    int sum = 0;
    int number = 0;
    int* arr = NULL;
    int* table = NULL;

    scanf("%d %d", &sum, &number);
    arr = (int*)calloc(number, sizeof(int));
    table = (int*)calloc(sum + 1, sizeof(int));
    for(int i = 0; i < number; ++i)
        scanf("%d", &arr[i]);

    qsort(arr, number, sizeof(int), compare);

    solver(sum, number, arr, table);
    printf("%d ", table[sum]);
}

