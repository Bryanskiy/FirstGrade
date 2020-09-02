int modul(int a)
{
    if(a >= 0)
        return a;
    else
        return -a;
}

char *replace(char *str, char const *from, char const *to)
{
    char* buffer;
    int current_buffer_len;
    int to_len, from_len;
    from_len = strlen(from);
    to_len = strlen(to);
    current_buffer_len = strlen(str);

    buffer = (char*)calloc(current_buffer_len, sizeof(char));

    for(int i = 0; ; )
    {
        int last;
        const char* tmp = strstr(str, from);
        if(tmp == NULL)
        {
            last = strlen(str);
            if(last > current_buffer_len - i)
            {
                buffer = (char*)realloc(buffer, i + last);
                current_buffer_len = i + last;
            }
            while(*str != '\0')
            {
                buffer[i] = *str;
                str += 1;
                ++i;
            }

            break;
        }
	
        last = modul((char*)tmp - (char*)str);
        if(last > current_buffer_len - i)
        {
            buffer = (char*)realloc(buffer, i + last);
            current_buffer_len = i + last;
        }

        for(int k = 0; k < last; ++k)
        {
            buffer[i] = *str;
            str += 1;
            ++i;
        }

        if(to_len > current_buffer_len - i)
        {
            buffer = (char*)realloc(buffer, i + to_len);
            current_buffer_len = i + to_len;
        }

        for(int j = 0; j < to_len; ++j)
        {
            buffer[i] = to[j];
            ++i;
        }

        str += from_len;
    }

    buffer = (char*)realloc(buffer, current_buffer_len + 1);
    buffer[current_buffer_len] = '\0';

    return buffer;

}

