#include "sort_text.h"

int main()
{
    char status = 0;

    FILE* text = NULL;
    status = open_file("text", "r", &text);
    if(status != 0)
    {
        printf("file not found");
        return FILE_NOT_FOUND;
    }

    struct buff_t buffer = {0, NULL};
    status = read_file("text", text, &buffer);
    if(status == EMPTY_FILE)
    {
        printf("file is empty");
        return EMPTY_FILE;
    }
    else if(status == NO_MEMORY)
    {
        printf("no memory to create a buffer");
        return NO_MEMORY;
    }
    else if(status == READ_ERROR)
    {
        printf("error which reading file)");
        return READ_ERROR;
    }


    fclose(text);

    char** str_ptrs = NULL;
    int str_ptrs_len = change_buffer(&buffer);

    str_ptrs = (char**)calloc(str_ptrs_len, sizeof(char*));
    if(str_ptrs == NULL)
    {
        printf("no memory to create str_ptrs");
        return NO_MEMORY;
    }

    int new_str_ptrs_len = processing_lines(&buffer, str_ptrs);
    if(new_str_ptrs_len <= 0)
    {
        printf("file <file> is empty");
        return EMPTY_FILE;
    }

    FILE* out = NULL;
    open_file("out", "w", &out);

    fprintf(out, "\n----------------------------direct compare-------------------------------------------\n");
    qsort(str_ptrs, new_str_ptrs_len, sizeof(char*), compare);
    status =  file_out(out, str_ptrs, new_str_ptrs_len);
    if(status == READ_ERROR)
    {
        printf("error whith reading file <out>");
        return READ_ERROR;
    }

    fprintf(out, "\n----------------------------reverse compare-------------------------------------------\n");
    qsort(str_ptrs, new_str_ptrs_len, sizeof(char*), compare_rifm);
    status =  file_out(out, str_ptrs, new_str_ptrs_len);
    if(status == READ_ERROR)
    {
        printf("error whith reading file <out>");
        return READ_ERROR;
    }

    fprintf(out, "\n--------------------------------original----------------------------------------------\n");
    for (int i = 0; i < buffer.len; ++i)
    {
        if(buffer.str[i] == '\0')
            fprintf(out,"\n");
        else
            fprintf(out, "%c", buffer.str[i]);
    }

    fclose(out);
    free(str_ptrs);
    free(buffer.str);

}
