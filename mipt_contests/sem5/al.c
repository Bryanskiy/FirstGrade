#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
struct node_t 
{
    struct node_t* next;
    int data;
};
*/
struct node_t* create_node(int value)
{
    struct node_t* ret;
    ret = (struct node_t*)calloc(1, sizeof(struct node_t));
    assert(ret != NULL);

    ret->data = value;
    
    return ret;
}

struct node_t* insert(struct node_t* parent, int value)
{
    struct node_t* ret;
    assert(parent != NULL);

    ret = create_node(value);
    ret->data = value;
    ret->next = parent->next;
    parent->next = ret;

    return ret;
}

void concatinate(struct node_t* tail, struct node_t* head)
{
    assert(tail != NULL);
    assert(head != NULL);
    tail->next = head->next;
}

struct node_t* read_list(FILE *inp)
{
    struct node_t* last_chet = NULL;
    struct node_t* last_nech = NULL;
    int data = 0;
    int flag_chet = 0, flag_nech = 0;
    struct node_t* top_chet = create_node(0);
    struct node_t* top_nech = create_node(0);

    top_chet->next = last_chet;
    top_nech->next = last_nech;
    while(fscanf(inp, "%d", &data) == 1)
    {
        if((data % 2) == 0)
        {
            if(flag_chet == 0)
            {
                last_chet = insert(top_chet, data);
                flag_chet = 1;
            }
            else
                last_chet = insert(last_chet, data);
        }
        else
        {
            if(flag_nech == 0)
            {
                last_nech = insert(top_nech, data);
                flag_nech = 1;
            }
            else
                last_nech = insert(last_nech, data);
        }
    }

    if(last_chet == NULL)
        return top_nech->next;
    
    concatinate(last_chet, top_nech);

    return top_chet->next;
}



void delete_list(struct node_t* top)
{
    struct node_t* next;

    while(next != NULL)
    {
        next = top->next;
        free(top);
        top = next;
    }
}

/*

void output_list(FILE* output, struct node_t* top)
{
    struct node_t* current = top->next;
    while(current != NULL)
    {
        fprintf(output, "%d ", current->data);
	current = current->next;
    }
}

int main()
{
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    struct node_t* top = read_list(input);
    output_list(output, top);
    //delete_list(top);

    fclose(input);
    fclose(output);
}

*/
