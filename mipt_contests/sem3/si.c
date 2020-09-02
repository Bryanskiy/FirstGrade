int moveright(int *arr, int key, int last)
{
    int i = last;
    while(key < arr[i-1])
    {
        if(i == 1)
        {
            return 0;
        }

        arr[i] = arr[i-1];
        --i;
    }
    return i;
}
