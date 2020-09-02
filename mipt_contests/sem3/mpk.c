#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define KARATSUBA_MIN 8

typedef struct
{
    unsigned n;
    int *p;
} poly_t;


//сумма полиномов равных длин
poly_t sum(poly_t X, poly_t Y)
{
    for(unsigned i = 0; i < X.n; ++i)
        X.p[i] = X.p[i] + Y.p[i];

    return X;
}

//вычисляет слагаемое при x ^ (n / 2)
poly_t middle(poly_t X, poly_t Y, poly_t Z)
{
    for(unsigned i = 0; i < X.n; ++i)
        X.p[i] = X.p[i] - Y.p[i] - Z.p[i];

    return X;
}

poly_t mult(poly_t A, poly_t B)
{
    poly_t A1, A0, B1, B0;
    poly_t SA, SB, mid;
    poly_t A1B1, A0B0, SASB;
    poly_t ret;

    unsigned n = A.n;
    ret.n = 2 * n - 1;
    ret.p = (int*)malloc(ret.n * sizeof(int));
    
    if(n <= KARATSUBA_MIN)
    {
        memset(ret.p, 0, sizeof(int) * ret.n);
        for(unsigned i = 0; i < A.n; ++i)
        {
            for(unsigned k = 0; k < B.n ; ++k)
                ret.p[i + k] += A.p[i] * B.p[k];
        }
        return ret;
    }

    A1.n = n/2, A1.p = A.p + n/2;
    A0.n = n/2, A0.p = A.p;
    B1.n = n/2, B1.p = B.p + n/2;
    B0.n = n/2, B0.p = B.p;

    SA = sum(A1, A0);
    SB = sum(B1, B0);

    A1B1 = mult(A1, B1);
    A0B0 = mult(A0, B0);
    SASB = mult(SA, SB);

    mid = middle(SASB, A1B1, A0B0);

    memcpy(ret.p, A0B0.p, n * sizeof(int));
    memcpy(ret.p + n, A1B1.p, n * sizeof(int));
    for(unsigned i = 0; i < n; ++i)
        ret.p[i + n/2] += mid.p[i];

    free(A1B1.p), free(A0B0.p), free(SASB.p);

    return ret;
}

int main()
{
    unsigned j = 0;
    poly_t A = {0, NULL};
    poly_t B = {0, NULL};
    poly_t C = {0, NULL};

    
    int res = scanf("%u%u", &(A.n), &(B.n));
    assert(res == 2);
    A.p = (int*)malloc(A.n * sizeof(int));
    assert(A.p != NULL);
    B.p = (int*)malloc(B.n * sizeof(int));
    assert(B.p != NULL);

    for(unsigned i = 0; i < A.n; ++i)
    {
        res = scanf("%d", &(A.p[i]));
        assert(res == 1);
    }

    for(unsigned i = 0; i < B.n; ++i)
    {
        res = scanf("%d", &(B.p[i]));
        assert(res == 1);
    }

    C = mult(A, B);

    // распечатка
    j = C.n - 1;
    while(C.p[j] == 0)
        --j;
    for(unsigned i = 0; i <= j; ++i)
        printf("%d ", C.p[i]);
}
