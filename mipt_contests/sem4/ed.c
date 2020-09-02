#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c)
{
    int min = a;
    if(b <= min)
        min = b;
    if(c <= min)
        min = c;

    return min;
}

void solver(int add_cost, int del_cost, int change_cost, int first_len, char* first, int second_len, char* second, int** table)
{
    int koef = 0;
    // start init
    for(int i = 0; i < second_len + 1; ++i)
        table[0][i] = i;

    for(int i = 0; i < first_len + 1; ++i)
        table[i][0] = i;

    for(int i = 1; i < first_len + 1; ++i)
    {
        for(int k = 1; k < second_len + 1; ++k)
        {
            if(first[i-1] == second[k-1])
            {
                koef = 0;
            }
            else
            {
               koef = change_cost;
            }

            table[i][k] = min(table[i-1][k] + del_cost, table[i][k-1] + add_cost, table[i-1][k-1] + koef);
        }
    }
}

int main()
{
    int add_cost, del_cost, change_cost;
    int first_len, second_len;
    char* first;
    char* second;
    int** table;

    scanf("%d %d %d", &add_cost, &del_cost, &change_cost);
    
    // init spoon str
    scanf("%d", &first_len);
    getchar();
    first = (char*) calloc(first_len, sizeof(char));
    for(int i = 0; i < first_len; ++i)
        scanf("%c", &first[i]);

    // init sponge str
    scanf("%d", &second_len);
    getchar();
    second = (char*) calloc(second_len, sizeof(char));
    for(int i = 0; i < second_len; ++i)
        scanf("%c", &second[i]);

    // create table
    table = (int**)calloc(first_len + 1, sizeof(int*));
    for(int i = 0; i < first_len + 1; ++i)
        table[i] = (int*)calloc(second_len + 1, sizeof(int));

    solver(add_cost, del_cost, change_cost, first_len, first, second_len, second, table);
    printf("%d", table[first_len][second_len]);
}
