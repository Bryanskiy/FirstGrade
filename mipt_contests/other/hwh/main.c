#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hashmap.h"

char* read()
{
    int cap = 10;
    int size = 0;
    int const step = 10;
    char symbol;

    char* buffer = (char*)calloc(cap, sizeof(char));
    assert(NULL != buffer);

    while(1 == scanf("%c", &symbol))
    {
         if(size == cap)
         {
             cap += step;
             buffer = (char*)realloc(buffer, cap * sizeof(char));
             assert(NULL != buffer);
         }

         buffer[size] = symbol;
         ++size;
    }

    if(0 == size)
    {
        free(buffer);
        return NULL;
    }

    cap = size + 1;
    buffer = (char*)realloc(buffer, cap * sizeof(char));
    assert(NULL != buffer);
    buffer[size] = '\0';

    return buffer;
}

char** processing(char * const buffer)
{
    int cap = 10;
    int size = 0;
    int const step = 10;

    char* word = strtok(buffer, " \n\t");
    if(NULL == word)
        return NULL;

    char** ret = (char**)calloc(cap, sizeof(char*));
    assert(NULL != ret);
    ret[size] = word;
    
    ++size;

    while(NULL != (word = strtok(NULL, " \n\t")))
    {
        if(size == cap)
         {
             cap += step;
             ret = (char**)realloc(ret, cap * sizeof(char*));
             assert(NULL != ret);
         }

        ret[size] = word;
        ++size;
    }

    cap = size + 1;
    ret = (char**)realloc(ret, cap * sizeof(char*));
    assert(NULL != ret);
    ret[size] = NULL;

    return ret;
}

int get_size_file(FILE* file)
{
    if(NULL == file)
        return -1;

    fseek(file, 0, SEEK_END);
    int file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    return file_len;
}

void fill(struct hashmap_t* hm, FILE* text)
{
   int cap = 10;
   int step = 10;
   int size = 0;

   char* tmp = (char*)calloc(cap, sizeof(char));
   assert(tmp != NULL);

   while(1 == fscanf(text, "%c", tmp + size))
   {
       if(isspace(tmp[size]))
       {
           tmp[size] = '\0';
           hashmap_add(hm, tmp);
           size = 0;
           continue;
       }

       if(size == cap - 1)
       {
           cap += step;
           tmp = (char*)realloc(tmp, cap * sizeof(char));
           assert(NULL != tmp);
       }

       ++size;
   }

   free(tmp);
}

int main()
{
    char* input_buffer = read();
    if(NULL == input_buffer)
    {
        printf("empty input");
        return -1;
    }

    char** input_words = processing(input_buffer);
    assert(NULL != input_words);

    char* file_name = input_words[0];
    FILE* text = fopen(file_name, "r");
    if(NULL == text)
    {
        printf("can't open file");
        return -1;
    }
     
    int file_size = get_size_file(text);
    assert(file_size > 0);
    
    unsigned map_size = file_size / 3 + 1;
    struct hashmap_t* hm = hashmap_create(map_size);

    fill(hm, text);

    for(int i = 1; input_words[i] != NULL; ++i)
        printf("%u ", hashmap_find(hm, input_words[i]));

    hashmap_destroy(hm);
    free(input_buffer);
    free(input_words);
    fclose(text);
}
