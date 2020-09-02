void *cbsearch(const void *key, const void *base, int num, int size, cmp_t cmp)
{
    char const * pivot;
    char const * bs = (char const *)base;
    int result;
    while (num > 0)
    {
        pivot = bs + (num / 2) * size;
        result = cmp(key, pivot);
        if (result == 0)
            return (void *)pivot;
        if(result < 0) // key < pivot
            num = num / 2;
        if(result > 0) // key > pivot
        {
            num = num / 2;
            bs = pivot + size;
        }
    }
    return NULL;
}
