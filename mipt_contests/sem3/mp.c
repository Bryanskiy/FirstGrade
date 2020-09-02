#include <stdio.h>
#include <stdlib.h>

struct poly_t
{
    unsigned n;
    unsigned *p;
};

//инициализация идет от младших -> К СТАРШИМ
void init(struct poly_t* A, struct poly_t* B)
{
    int A_len, B_len;
    scanf("%u%u", &A_len, &B_len);

    A->n = A_len;
    B->n = B_len;

    A->p = (unsigned*)calloc(A_len, sizeof(unsigned));
    B->p = (unsigned*)calloc(B_len, sizeof(unsigned));

    for(int i = 0; i < A_len; ++i)
        scanf("%u", &(A->p[i]));

    for(int i = 0; i < B_len; ++i)
        scanf("%u", &(B->p[i]));
}

void print_poly(struct poly_t* X)
{
    int j = X->n - 1;
    while(X->p[j] == 0)
        --j;

    for(int i = 0; i <= j; ++i)
        printf("%u ", X->p[i]);
}

void mult(struct poly_t* A, struct poly_t* B, struct poly_t* C)
{
    for(int i = 0; i < A->n; ++i)
    {
        for(int k = 0; k < B->n ; ++k)
        {
            C->p[i + k] += A->p[i] * B->p[k];
        }
    }
}

int main()
{
    struct poly_t A = {0, NULL};
    struct poly_t B = {0, NULL};
    struct poly_t C = {0, NULL};
    
    init(&A, &B);

    C.n = A.n + B.n - 1;
    C.p = (unsigned*)calloc(C.n, sizeof(unsigned));

    mult(&A, &B, &C);

    print_poly(&C);
}
