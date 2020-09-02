#include "sort_text.h"

int open_file(const char file_name[],const char open_file_mode[], FILE** file)
{
    assert(file != NULL);

    *file = fopen(file_name, open_file_mode);
    if(*file == NULL)
    {
        return FILE_NOT_FOUND;
    }
    return 0;
}

int size_file_in_bites(FILE* file)
{
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    int file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(file_len < 1)
    {
        return EMPTY_FILE;
    }

    return file_len;
}

int read_file(const char file_name[], FILE* file, struct buff_t* buffer)
{
    assert(file != NULL);
    assert(buffer != NULL);

    buffer -> len = size_file_in_bites(file);
    if ((buffer -> len) < 1)
    {
        return EMPTY_FILE;
    }

    buffer -> str = (char*)calloc(buffer -> len, sizeof(char));
    if (buffer == NULL)
    {
        return NO_MEMORY;
    }
    size_t read = fread(buffer -> str, sizeof(char), buffer -> len, file);
    if(read != buffer -> len)
    {
        return READ_ERROR;
    }

    return 0;
}

int change_buffer(struct buff_t* buffer)
{
    assert(buffer != NULL);

    int n_lines_in_buffer = 0;
    for(int i = 0; i < buffer -> len; ++i)
    {
        if(buffer -> str[i] == '\n')
        {
            n_lines_in_buffer += 1;
            buffer -> str[i] = '\0';
        }
    }

    return n_lines_in_buffer;
}

int is_symbol_useless(char symbol)
{

    if (symbol == ' ' || symbol == '\0' || symbol == '\t')
        return 1;
    return 0;

}

int processing_lines(struct buff_t* buffer, char** str_ptrs)
{
    assert(buffer != NULL);
    assert(str_ptrs != NULL);

    int buffer_start = 0;
    while(is_symbol_useless(buffer -> str[buffer_start]) && buffer_start < buffer -> len)
        ++buffer_start;
    if (buffer_start == buffer -> len)
    {
        return EMPTY_FILE;
    }

    str_ptrs[0] = &(buffer -> str[buffer_start]);

    int end_point = 0;
    int n_lines = 0;
    for(int i = buffer_start; i < (buffer -> len); ++i)
    {
        if(end_point == 1)
        {

            if(is_symbol_useless(buffer -> str[i]))
                continue;

            else
            {
                ++n_lines;
                str_ptrs[n_lines] = &(buffer -> str[i]);
                end_point = 0;
            }
        }

        else
        {
            if(buffer -> str[i] == '\0')
                end_point = 1;
        }

    }
    ++n_lines;

    return n_lines;
}

int compare(const void * s1, const void * s2)
{
    int i = 0, j = 0;
    char** p1 = (char**)s1;
    char** p2 = (char**)s2;
    int i_len = strlen(*p1);
    int j_len = strlen(*p2);

    while (((*p1)[i] != '\0') && ((*p2)[j] != '\0'))
    {
        while(isalpha((*p1)[i]) == 0)
        {
            i++;
            if (i >= i_len)
                break;
        }
        while(isalpha((*p2)[j]) == 0)
        {
            j++;
            if (j >= j_len)
                break;
        }
        if ((*p1)[i] > (*p2)[j])
            return 1;

        if ((*p1)[i] < (*p2)[j])
            return -1;
        i++;
        j++;
    }

    if(((*p1)[i] == '\0') && ((*p2)[j] != '\0'))
        return -1;
    if(((*p1)[i] != '\0') && ((*p2)[j] == '\0'))
        return 1;

    return 0;
}

int file_out(FILE* file, char** str_ptrs, int str_ptrs_len)
{
    assert(file != NULL);
    assert(str_ptrs != NULL);

    for(int i = 0; i < str_ptrs_len; i++)
    {
        if(fprintf(file, "%s\n", str_ptrs[i]) < 0)
        {
            return READ_ERROR;
        }
    }
    fprintf(file, "\n");
}

int compare_rifm(const void* s1, const void* s2)
{
    char** p1 = (char**)s1;
    char** p2 = (char**)s2;

    int p1_len = strlen(*p1);
    int p2_len = strlen(*p2);

    while((p1_len >= 0) && (p2_len >= 0))
    {
        while(isalpha((*p1)[p1_len]) == 0)
        {
            p1_len--;
            if (p1_len < 0)
                break;
        }

        while(isalpha((*p2)[p2_len]) == 0)
        {
            p2_len--;
            if (p2_len < 0)
                break;
        }

        if ((*p1)[p1_len] > (*p2)[p2_len])
            return 1;

        if ((*p1)[p1_len] < (*p2)[p2_len])
            return -1;
        p1_len--;
        p2_len--;

    }

    if((p1_len == 0) && (p2_len != 0))
        return -1;

    if((p1_len != 0) && (p2_len == 0))
        return 1;

    return 0;
}

