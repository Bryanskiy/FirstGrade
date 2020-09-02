char * strstrci(char const * needle, char const * haystack)
{
    char const * found = NULL;
    while(*haystack != '\0')
    {
        char const * s = needle;
        int i = 0;
        while((*s != '\0') && (toupper(*s) == toupper(*(haystack + i))))
        {
            ++i;
            ++s;
        }

        if(*s == '\0')
        {
            found = haystack;
            break;
        }

        haystack += 1;
    }

    return (char *) found;
}
