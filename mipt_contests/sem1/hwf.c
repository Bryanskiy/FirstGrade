unsigned long long fib(unsigned n)
{
    unsigned long long first = 0, second = 1;
    unsigned idx;
    if (n == 0)
        return 0;
    for (idx = 2; idx <= n; ++idx)
    {
        unsigned long long tmp = second;
        second = (second + first);
        first = tmp;
    }
    return second;
}

unsigned long long search_left_fib(int x, unsigned long long* fibs, int fibs_len)
{
    int i = 1;
    while((fibs[i] <= x) && (i < fibs_len))
        ++i;

    return fibs[i-1];
}

unsigned long long search_min_zfib(int x)
{
    unsigned long long ret = x;
    int fibs_len = 50;
    int i = 1;

    unsigned long long* fibs = (unsigned long long*)calloc(fibs_len, sizeof(unsigned long long));

    while(fibs[i-1] <= x)
    {
        if(i > fibs_len)
        {
            fibs_len += 10;
            fibs = (unsigned long long*)realloc(fibs, fibs_len);
        }

        fibs[i] = fib(i);

        ++i;
    }

    while(x > 0)
    {
        ret = search_left_fib(x, fibs, fibs_len);

        if(x == ret)
            break;

        x = x - ret;
    }

    return ret;
}

int next_turn(int total, int possible) 
{
    int min_zfib = total;

    if(possible >= total)
        return total;

    min_zfib = search_min_zfib(total);     

    if(min_zfib > possible)
        return 1;

    return min_zfib;   
}
