char *strcat_r(char *dest, const char *src, int *bufsz)
{
    int dest_len, src_len;
    dest_len = strlen(dest);
    src_len = strlen(src);

    if(*bufsz <= dest_len + src_len)
    {
        dest = (char*)realloc(dest, (dest_len + src_len + 1) * sizeof(char));
        strcat(dest, src);
        return dest;
    }
    else
    {
        strcat(dest, src);
        return dest;
    }

    return NULL;
}
