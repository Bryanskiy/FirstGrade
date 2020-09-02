#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct tree_t
{
    struct tree_t* left;
    struct tree_t* right;
    int data;
};

int find(int const * const arr, int len, int key);

struct tree_t* create_node(int data)
{
    struct tree_t* ret;

    ret = (struct tree_t*)calloc(1, sizeof(struct tree_t));
    assert(NULL != ret);

    ret->data = data;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

int* read_arr(FILE* f, int len)
{
    int* arr = (int*)calloc(len, sizeof(int));
    assert(NULL != arr);

    for(int i = 0; i < len; ++i)
    {
        int res = fscanf(f, "%d", arr + i);
        assert(1 == res);
    }

    return arr;
}

//функция возвращает указатель на вершину дерева
struct tree_t* recover(int const * const preorder, int const * const inorder, int len)
{
    static int preorder_idx = 0;
    struct tree_t* top;
    int top_idx;
    
    if(len == 0)
        return NULL;

    top = create_node(preorder[preorder_idx++]);

    if(len == 1)
        return top;

    top_idx = find(inorder, len, top->data);

    top->left = recover(preorder, inorder, top_idx);
    top->right = recover(preorder, inorder + top_idx + 1, len - top_idx - 1);

    return top;
}

int find(int const * const arr, int len, int key)
{
    int ret = -1;
    for(int i = 0; i < len; ++i)
    {
        if(arr[i] == key)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

/*
void indr(struct tree_t const * const top)
{
    if(NULL == top)
        return;

    indr(top->left);
    printf("%d ", top->data);
    indr(top->right);
}

void prdr(struct tree_t const * const top)
{
    if(NULL == top)
        return;

    printf("%d ", top->data);
    prdr(top->left);
    prdr(top->right);
}

void psdr(struct tree_t* top)
{
    if(NULL == top)
        return;

    psdr(top->left);
    psdr(top->right);

    printf("%d ", top->data);
}
*/

void delete(struct tree_t* top)
{
    if(NULL == top)
        return;

    delete(top->left);
    delete(top->right);
    
    free(top);
}

void out(struct tree_t* top)
{
    if(top == NULL)
        return;
    
    if((top->left != NULL) || (top->right != NULL))
    {
        printf("%d ", top->data);

        if(top->left != NULL)
            printf("%d ", top->left->data);
        else
            printf("-1 ");

        if(top->right != NULL)
            printf("%d ", top->right->data);
        else
            printf("-1 ");

        printf("\n");
    }

    out(top->left);
    out(top->right);

}

int main()
{
    int node_count;
    int* preorder;
    int* inorder;
    struct tree_t* top;

    fscanf(stdin, "%d", &node_count);
    preorder = read_arr(stdin, node_count);
    inorder = read_arr(stdin, node_count);

    top = recover(preorder, inorder, node_count);

    printf("%d\n", node_count);
    out(top);

    delete(top);
    free(preorder);
    free(inorder);
}
