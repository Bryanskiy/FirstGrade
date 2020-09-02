int is_prime(int n);
void fill_sieve(struct sieve_t *sv)
{
    assert(sv != NULL);
    for(int i = 2; i*i  < (sv -> n); ++i)
    {
        if(is_prime(i))
        {
            for(int j = i * i; j < (sv -> n) + 1; j += i)
                (sv -> s[j]) = 1;
        }
    }
}

int is_prime(int n)
{
    if ((n == 2) || (n == 3))
        return 1;
    if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0))
        return 0;
    for (int j = 5; j * j < n; j += 6)
        if (((n % j) == 0) || ((n % (j + 2)) == 0))
            return 0;
    return 1;
}

int nth_prime(struct sieve_t *sv, int N)
{
    int k = 0;
    int i = 2;
    int p = 0;
    while(k < N)
    {
        if((sv->s[i]) == 0)
            ++k;
        p = i;
        ++i;
    }
    return p;
}
