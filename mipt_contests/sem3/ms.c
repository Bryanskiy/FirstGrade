void merge(int *arr, int l, int m, int r)
{
    int len = r - l + 1;
    int i = l, j = m + 1;
    int* tmp = (int*)malloc(len * sizeof(int));
    for(int k = 0; k < len; ++k)
    {
        if(((arr[i] < arr[j]) && (i <= m)) || j > r)
        {
            tmp[k] = arr[i];
            ++i;
        }
        else
        {
            tmp[k] = arr[j];
            ++j;
        }
    }

    for(int k = 0; k < len; ++k)
        arr[l + k] = tmp[k];

    free(tmp);
}
