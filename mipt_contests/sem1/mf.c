#include <stdio.h>

void mul(int* matrix1, int* matrix2, int* res_matrix,  int m)
{
    res_matrix[0] = (matrix1[0]*matrix2[0] + matrix1[1]*matrix2[2]) % m;
    res_matrix[1] = (matrix1[0]*matrix2[1] + matrix1[1]*matrix2[3]) % m;
    res_matrix[2] = (matrix1[2]*matrix2[0] + matrix1[3]*matrix2[2]) % m;
    res_matrix[3] = (matrix1[2]*matrix2[1] + matrix1[3]*matrix2[3]) % m;
}

void pow_m(int* matrix, int* res, int n, int m)
{
    int tmp[4] = { 1, 0, 0 , 1 };
    for(int i = 0; i < n; ++i)
    {
        mul(matrix, tmp, res, m);
        tmp[0] = res[0];
        tmp[1] = res[1];
        tmp[2] = res[2];
        tmp[3] = res[3];
    }
    
}

int main()
{
    int n, m;
    int matrix[4] = { 0 };
    int res[4] = { 0 };
    for(int i = 0; i < 4; ++i)
        scanf("%d", &matrix[i]);

    scanf("%d%d", &n, &m);

    pow_m(matrix, res, n, m);
    for(int i = 0; i < 4; ++i)
        printf("%d ", res[i]);
}
