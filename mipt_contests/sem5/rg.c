/*

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int (*generator_t)(int);

*/

struct node_t
{
    struct node_t* next;
    int data;
};

struct node_t* create_elem(int value)
{
    struct node_t* ret;
    ret = (struct node_t*)calloc(1, sizeof(struct node_t));
    assert(ret != NULL);

    ret->data = value;
    
    return ret;
}

struct node_t* insert(struct node_t* prev, int value)
{
    struct node_t* ret;
    assert(prev != NULL);

    ret = create_elem(value);
    ret->data = value;
    ret->next = prev->next;
    prev->next = ret;

    return ret;
}

int loop_len(struct node_t *top)
{                                         
    struct node_t* turt;
    struct node_t* hare;
    int len = 0;
    int flag = 0;

    if(top == NULL)
        return 0;

    hare = top->next;
    if(hare == NULL)
        return 0;

    turt = hare->next;
    while(turt != NULL)
    {
        if(turt == hare)
        {
            flag = 1;
            break;
        }
        turt = turt->next;
        if(turt == NULL)
            return 0;
        turt = turt->next;
        hare = hare->next;
    }

    if(flag == 1)
    {
        len = 1;
        hare = hare->next;
        while(hare != turt)
        {
            hare = hare->next;
            ++len;
        }

        return len;
    }

    return 0;
} 

void delete_list(struct node_t* head, unsigned size)
{
    struct node_t* tmp;
    for(unsigned i = 0; i < size; ++i)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

struct node_t* search_circle(struct node_t* top, int key, int list_len)
{
    for(int i = 0; i < list_len; ++i)
    {
        if(top->data == key)
            return top;
        top = top->next;
    }

    return NULL;
}

unsigned cycle_len(generator_t gen)
{
    int prev = 0;
    int list_len = 1;
    int ans;
    struct node_t* top = create_elem(0);
    struct node_t* tmp = top;
    struct node_t* circle;

    while((circle = search_circle(top, gen(prev), list_len)) == NULL)
    {
        tmp = insert(tmp, gen(prev));
        prev = gen(prev);
        ++list_len;
    }

    tmp->next = circle;
    ans = loop_len(top);
    delete_list(top, list_len);

    return ans;
}
/*
int g(int x)
{
    return (3 * x + 2) % 5 + 4;
}

int main()
{
    printf("%d", cycle_len(g));
}
*/
