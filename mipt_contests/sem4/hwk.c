void patpreproc(char const * needle, int * needle_lps)
{
    int n_len;
    n_len = strlen(needle);
    for(int i = 0; i < n_len; ++i)
    {
        int lps_value = 0;
        for(int sp_len = 1; sp_len < i + 1; ++sp_len)
        {
            int flag = 1;
            for(int j = 0; j < sp_len; ++j)
            {
                if(needle[j] != needle[i - sp_len + 1 + j])
                {
                    flag = 0;
                    break;
                }
            }

            if(flag == 1)
            {
                lps_value = sp_len;
            }
        }

        needle_lps[i] = lps_value;
    }
}

char * strstrci(char const * needle, int const * needle_lps, char const * haystack)
{
    const char * found = NULL;
    int i = 0;
    int n_len = strlen(needle);
    while(*haystack != '\0')
    {
        while((needle[i] != '\0') && (toupper(needle[i]) == toupper(*haystack)) && (*haystack != '\0'))
        {
            ++i;
            ++haystack;
        }

        if(needle[i] == '\0')
        {
            found = haystack - n_len;
            break;
        }

        if(i != 0)
        {
            i = needle_lps[i-1];
        }
        else
        {
            ++haystack;
        }
    }

    return (char*)found;
}
