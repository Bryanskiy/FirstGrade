void change_one(struct sieve_t *sv, unsigned long long bit);
int is_prime_n(unsigned long long n);
void fill_sieve(struct sieve_t* sv);
int is_prime(struct sieve_t *sv, unsigned n);

void fill_sieve(struct sieve_t* sv)
{
    assert(sv != NULL);

    change_one(sv, 0u);
    change_one(sv, 1u);

    for(unsigned long long i = 2; i * i < ((sv -> n) * 8); ++i)
    {
        if(is_prime_n(i))
        {
            for(unsigned long long j = i * i; j < ((sv -> n) * 8) + 1; j += i)
                change_one(sv, j);
        }
    }

}

void change_one(struct sieve_t *sv, unsigned long long bit)
{
    unsigned long long byte = bit / 8u;
    unsigned long long bit_in = bit % 8u;

    (sv -> s[byte]) = ((sv -> s[byte]) | (1u << bit_in));
}

int is_prime_n(unsigned long long n)
{
    if ((n == 2) || (n == 3))
        return 1;
    if ((n < 2) || ((n % 2) == 0) || ((n % 3) == 0))
        return 0;
    for (unsigned long long j = 5; j * j < n; j += 6)
        if (((n % j) == 0) || ((n % (j + 2)) == 0))
            return 0;
    return 1;
}



int is_prime(struct sieve_t *sv, unsigned n)
{
    unsigned long long byte = n / 8u;
    unsigned long long bit = n % 8u;

    unsigned val = ((sv -> s[byte]) >> bit) & 1u;

    if(val == 1u)
        return 0;
    return 1;
}
