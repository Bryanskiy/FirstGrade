#define START 100
#define STEP 100

unsigned gcd(unsigned first, unsigned second);

struct denom_array_t egyptian_fractions(unsigned num, unsigned den)
{
    struct denom_array_t ret = {NULL, 0};
    unsigned MAX_SIZE = START;
    ret.arr = (unsigned*)calloc(START, sizeof(unsigned));
    while(num != 1)
    {
        int term_den;
        int nod = 1;
        term_den = den / num + 1;
        nod = gcd(num * term_den - den, den * term_den);

        num = (num * term_den - den) / nod;
        den = (den * term_den) / nod;

        if(ret.sz >= MAX_SIZE)
        {
            MAX_SIZE += STEP;
            ret.arr = (unsigned*)realloc(ret.arr, MAX_SIZE);
        }
        ret.arr[ret.sz] = term_den;
        ++ret.sz;
    }

    ret.sz += 1;
    ret.arr = (unsigned*)realloc(ret.arr, ret.sz);
    ret.arr[ret.sz - 1] = den;

    return ret;
}

unsigned gcd(unsigned x, unsigned y)
{
    unsigned long long q;
    if (y > x)
        return gcd(y, x);
    q = x % y;
    if (q == 0)
        return y;

    return gcd(y, q);
}
