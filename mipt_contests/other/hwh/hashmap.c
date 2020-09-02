#include "hashmap.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct node_t;
void delete_list(struct node_t* head);

struct hashmap_t
{
    int cap;
    struct node_t** data;
};

struct node_t
{
    struct node_t* next;
    char* key;
    unsigned value;
};

int hash(char const * key, int key_len, int hm_cap)
{
    int hash = 0;
    
    for(int i = 0; i < key_len; ++i)
        hash += key[i] * (key_len - i);

    hash = hash % hm_cap;

    return hash;
}

struct node_t* create_node(char const * key, int key_len)
{
    struct node_t* ret = (struct node_t*)calloc(1, sizeof(struct node_t));
    assert(NULL != ret);

    ret->next = NULL;
    ret->value = 0;

    ret->key = (char*)calloc(key_len + 1, sizeof(char));
    assert(NULL != ret->key);
    memcpy(ret->key, key, key_len);
    ret->key[key_len] = '\0';

    return ret;
}

struct hashmap_t* hashmap_create(unsigned size)
{
    struct hashmap_t* ret = (struct hashmap_t*)calloc(1, sizeof(struct hashmap_t));
    assert(NULL != ret);

    ret->data = (struct node_t**)calloc(size, sizeof(struct node_t*));
    assert(NULL != ret->data);

    ret->cap = size;

    return ret; 
}

unsigned hashmap_get_size(struct hashmap_t* hm)
{
    assert(NULL != hm);

    return hm->cap;
}

void hashmap_add(struct hashmap_t* hm, char const * key)
{
    int len = strlen(key);

    struct node_t* node = create_node(key, len);
    
    int str_hash = hash(key, len, hm->cap);

    if(hm->data[str_hash] == NULL)
    {
        hm->data[str_hash] = node;
        hm->data[str_hash]->value = 1;
    }
    else
    {
        struct node_t* current = hm->data[str_hash];
        while(current->next != NULL)
        {
            if(strcmp(current->key, key))
            {
                current->value += 1;
                free(node);
                return;
            } 
            current = current->next;
        }

        if(strcmp(current->key, key) == 0)
        {
            current->value += 1;
            free(node);
            return;
        }

        current->next = node;
    }
}

unsigned hashmap_find(struct hashmap_t* hm, char const * key)
{
    int len = strlen(key);

    int str_hash = hash(key, len, hm->cap);

    struct node_t* current = hm->data[str_hash];
    if(current == NULL)
        return 0;

    while(strcmp(current->key, key) != 0)
    {
        current = current->next;
        if(current == NULL)
            return 0;
    }

    return current->value;
}

void hashmap_destroy(struct hashmap_t* hm)
{
    for(int i = 0; i < hm->cap; ++i)
    {
        if(hm->data[i] == NULL)
            continue;

        delete_list(hm->data[i]);
    }
}

void delete_list(struct node_t* head)
{
    struct node_t* tmp;
    while(head != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

