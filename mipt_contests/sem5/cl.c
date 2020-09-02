#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_INT 2147483647

struct list_t
{
    struct list_t* next;
    int data;
};

void init_ptrs(struct list_t* top, struct list_t** ptrs, int* coins, int arrs_len);

struct list_t* create_elem(int value)
{
    struct list_t* ret;
    ret = (struct list_t*)calloc(1, sizeof(struct list_t));
    assert(ret != NULL);

    ret->data = value;
    
    return ret;
}

struct list_t* insert(struct list_t* prev, int value)
{
    struct list_t* ret;
    assert(prev != NULL);

    ret = create_elem(value);
    ret->data = value;
    ret->next = prev->next;
    prev->next = ret;

    return ret;
}


struct list_t* create(int size)
{
    struct list_t* head;
    struct list_t* tmp;

    if(size == 0)
        return NULL;

    head = create_elem(0);
    head->next = head;
    tmp = head;

    for(int i = 0; i < size - 1; ++i)
        tmp = insert(tmp, 0);

    tmp->next = head;

    return head;
}

void output_list(FILE* output, struct list_t* head, int size)
{
    for(int i = 0; i < size; ++i)
    {
        fprintf(output, "%d ", head->data);
        head = head->next;
    }
}

int mcmp(const void* fst, const void* scd)
{
    int fsti, scdi;

    assert(fst != NULL);
    assert(scd != NULL);

    fsti = *(int*)fst;
    scdi = *(int*)scd;

    return fsti - scdi;
}

void delete_list(struct list_t* head, int size)
{
    struct list_t* tmp;
    for(int i = 0; i < size; ++i)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}



int search_min(struct list_t** ptrs, int mptrs_idx, int key)
{
    int min = MAX_INT;
    int flag = 0;
    for(int i = 0; i <= mptrs_idx; ++i)
    {
        if((ptrs[i]->data <= min) && (ptrs[i]->data != key))
        {
            min = ptrs[i]->data;
            flag = 1;
        }
    }

    if (flag == 1)
        return min;

    else
        return -1;
}

void init_ptrs(struct list_t* top, struct list_t** ptrs, int* coins, int arrs_len)
{
    int max_coin = coins[arrs_len - 1];
    int coins_idx = arrs_len - 1;
    int ptrs_idx = 0;

    for(int i = 0; i < max_coin; ++i)
    {
        if(coins_idx >= 0)
        {
            if(i == max_coin - coins[coins_idx])
            {
                ptrs[ptrs_idx] = top;
                --coins_idx;
                ++ptrs_idx;
            }
        }

        top = top->next;
    }

}

void dance(struct list_t** ptrs, int ptrs_len)
{
    for(int i = 0; i <  ptrs_len; ++i)
        ptrs[i] = ptrs[i]->next;
}

int bin_search(int* data, int data_len, int key)
{
    int l = 0;
    int r = data_len - 1;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        if(data[mid] == key)
            return 1;
        if(data[mid] < key)
            l = mid + 1;
        if(data[mid] > key)
            r = mid - 1;
    }

    return 0;
}

int execute(int* coins, int max_coin, int sum, struct list_t** ptrs, int ptrs_len)
{
    int min;
    for(int i = 1; i <= sum; ++i)
    {
        if(i <= max_coin)
        {
            if(bin_search(coins, ptrs_len, i))
            {
                ptrs[0]->data = 1;
                dance(ptrs, ptrs_len);
                continue;
            }
        }

        min = search_min(ptrs, ptrs_len - 1, 0);

        if(min == -1)
        {
            dance(ptrs, ptrs_len);
            continue;
        }

        ptrs[0]->data = min + 1;
        dance(ptrs, ptrs_len);

    }

    return ptrs[ptrs_len - 1]->data;
}

int main()
{
    int sum;
    int coins_count;
    int* coins;
    int max_coin;
    struct list_t** ptrs;
    int ret = 0;
    int ans = 0;
    struct list_t* top;

    ret = scanf("%d", &sum);
    assert(ret == 1);

    ret = scanf("%d", &coins_count);
    assert(ret == 1);
    if(coins_count == 0)
    {
        printf("%d", 0);
        return 0;
    }

    coins = (int*)calloc(coins_count, sizeof(int));
    assert(coins != NULL);

    ptrs = (struct list_t**)calloc(coins_count, sizeof(struct list_t*));
    assert(ptrs != NULL);

    for(int i = 0; i < coins_count; ++i)
        scanf("%d", &(coins[i]));

    qsort(coins, coins_count, sizeof(int), mcmp);
    max_coin = coins[coins_count - 1];

    top = create(max_coin);

    init_ptrs(top, ptrs, coins, coins_count);

    ans = execute(coins, max_coin, sum, ptrs, coins_count);

    printf("%d", ans);

    free(coins);
    free(ptrs);
}

