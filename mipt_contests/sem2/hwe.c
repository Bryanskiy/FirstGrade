#define BITS_IN_BYTE 8

int get_bit(unsigned char *data, unsigned long long n);
void change_one(unsigned char *data, unsigned long long bit);

int is_prime(struct sieve_t *sv, unsigned n)
{
    unsigned bit = 0;
    if((n == 2) || (n == 3))
        return 1;
    if((n % 2 == 0) || (n % 3 == 0))
        return 0;

    bit = n / 6;
    if(n % 6 == 1)
        return 1 - get_bit(sv->mod1, bit);
    else
        return 1 - get_bit(sv->mod5, bit);
}

void fill_sieve(struct sieve_t *sv)
{
    unsigned long long current_index = 0;
    change_one(sv->mod1, 0);

    for(current_index; current_index * current_index < sv->n * BITS_IN_BYTE; ++current_index)
    {
        unsigned long long first = 6 * current_index + 1;
        unsigned long long second = 6 * current_index + 5;

        if(get_bit(sv->mod1, current_index) == 0)
        {
            unsigned long long run_index = ((6 * current_index + 1) * (6 * current_index + 1)) / 6;
            unsigned long long mod5_index_difference = 0;
            while((6 *(run_index + mod5_index_difference) + 5) % first != 0)
                ++mod5_index_difference;

            for(run_index; run_index < sv->n * BITS_IN_BYTE; run_index += first)
            {
                change_one(sv->mod1, run_index);
                if(run_index + mod5_index_difference < sv->n * BITS_IN_BYTE)
                    change_one(sv->mod5, run_index + mod5_index_difference);
            }
        }

        if(get_bit(sv->mod5, current_index) == 0)
        {
            unsigned long long run_index = ((6 * current_index + 5) * (6 * current_index + 5)) / 6;
            unsigned long long  mod5_index_difference = 0;
            while((6 * (run_index + mod5_index_difference) + 5) % second != 0)
                ++mod5_index_difference;

            for(run_index; run_index < sv->n * BITS_IN_BYTE; run_index += second)
            {
                change_one(sv->mod1, run_index);
                if(run_index + mod5_index_difference < sv->n * BITS_IN_BYTE)
                    change_one(sv->mod5, run_index + mod5_index_difference);
            }
        }
    }
}

void change_one(unsigned char *data, unsigned long long bit)
{
    unsigned long long byte = bit / 8u;
    unsigned long long bit_in = bit % 8u;

    data[byte] = ((data[byte]) | (1u << bit_in));
}

int get_bit(unsigned char *data, unsigned long long n)
{
    unsigned long long byte = n / 8u;
    unsigned long long bit = n % 8u;

    int val = (data[byte] >> bit) & 1u;

    return val;
}
