int arrpopcount(const unsigned char *parr, int len);
int bits_in_char(char x);

int arrpopcount(const unsigned char *parr, int len)
{
    int sum = 0;
    for(int i = 0; i < len; ++i)
    {
        sum += bits_in_char(parr[i]);
    }

    return sum;
}

int bits_in_char(char x)
{
    int max = sizeof(char) * 8;
    char bit;
    int sum = 0;
    for(int i = 0; i < max; ++i)
    {
        bit = (x >> i) & 1u;
        if(bit == 1)
            sum += 1;
    }

    return sum;
}

