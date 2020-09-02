#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max(int first, int second)
{
    if(first >= second)
        return first;
    else
        return second;
}

void solver(int num_elements, int** table, int* weights, int max_weight)
{
    for(int i = 1; i < num_elements + 1; ++i)
    {
        for(int k = 1; k < max_weight + 1; ++k)
        {
            if(weights[i] <= k)
            {
                table[i][k] = max(table[i-1][k], table[i-1][k - weights[i]] + 1);
            }
            else
                table[i][k] = table[i-1][k];
        }
    }
}

int compare(const void* first, const void* second)
{
    int f = *(int*)first;
    int s = *(int*)second;

    return f - s;
}

int main()
{
    int num_elements; // число предметов
    int** table;      // таблица для заполнения
    int* weights;     // массив с массами
    int max_weight;   // максимальный вес юкзака

    // инициализаяция
    scanf("%d", &max_weight);
    scanf("%d", &num_elements);
    weights = (int*)calloc(num_elements + 1, sizeof(int));
    for(int i = 1; i < num_elements + 1; ++i)
        scanf("%d", &weights[i]);

    table = (int**)calloc(num_elements + 1, sizeof(int*));
    for(int i = 0; i < num_elements + 1; ++i)
    {
        table[i] = (int*)calloc(max_weight + 1, sizeof(int));
    }
    //----------------
    
    qsort(weights, num_elements, sizeof(int), compare); // sort weights

    solver(num_elements, table, weights, max_weight);

    printf("%d", table[num_elements][max_weight]);
}

