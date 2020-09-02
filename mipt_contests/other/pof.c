unsigned pown(unsigned n, unsigned k)
{
    unsigned mult, prod;
    if (k == 0) 
        return 1;
    mult = n;
    prod = 1;
    while (k > 0)
    {
        if ((k % 2) == 1)
        {
            prod = prod * mult;
            k = k - 1;
        }
        else
        {
            mult = mult * mult;
            k = k / 2;
        }
    }
    return prod;
}

unsigned take_left(unsigned n, unsigned m)
{
    unsigned ret = 0;
    while((pown(4, ret) <= n) && (ret <= m))
        ++ret;

    return pown(4, ret - 1);
}

unsigned powers_of_four(unsigned n, unsigned m)
{
    int ret = 0;
    while(n > 0)
    {
        n = n - take_left(n , m);
        ret += 1;
    }

    return ret;
}
