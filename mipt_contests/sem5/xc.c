int ncollisions(char **strs, int n, get_hash_t f)
{
    int k = 0;
    int* arr = (int*)calloc(HASH_MAX, sizeof(int));
    for(int i = 0; i < n; ++i)
        arr[f(strs[i])]++;

    for(int i = 0; i < HASH_MAX; ++i)
    {
        if(arr[i] != 0)
            k += arr[i] - 1;
    }

    free(arr);

    return k;
} 
