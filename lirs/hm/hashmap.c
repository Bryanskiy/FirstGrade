#include "hashmap.h"
#include "../lirs/lirs.h"
#include <stdlib.h>
#include <assert.h>

void delete_list(struct hm_node_t* head);

int hash(int key, int hm_cap)
{
    assert(hm_cap > 0);

    int hash = 0;
    
    for(int i = 0; i < hm_cap; ++i)
        hash += key * 7 + 19;

    hash = hash % hm_cap;

    return hash;
}

struct hm_node_t* create_hmnode(int key, char status)
{
    struct hm_node_t* ret = (struct hm_node_t*)calloc(1, sizeof(struct hm_node_t));
    assert(NULL != ret);

    ret->next = NULL;
    ret->value = status;
    ret->key = key;

    return ret;
}

struct hashmap_t* hashmap_create(int size)
{
    assert(size > 0);

    struct hashmap_t* ret = (struct hashmap_t*)calloc(1, sizeof(struct hashmap_t));
    assert(NULL != ret);

    ret->data = (struct hm_node_t**)calloc(size, sizeof(struct hm_node_t*));
    assert(NULL != ret->data);

    ret->cap = size;

    return ret; 
}

unsigned hashmap_get_size(struct hashmap_t* hm)
{
    assert(NULL != hm);

    return hm->cap;
}

void hashmap_add(struct hashmap_t* hm, int key, char status)
{
    assert(hm != NULL);

    struct hm_node_t* hmnode = create_hmnode(key, status);
    
    int k_hash = hash(key, hm->cap);

    if(hm->data[k_hash] == NULL)
        hm->data[k_hash] = hmnode;

    else
    {
        struct hm_node_t* current = hm->data[k_hash];
        while(current->next != NULL)
        {
            if(current->key == key)
            {
                current->value = status;
                free(hmnode);
                return;
            } 
            current = current->next;
        }

        if(current->key == key)
        {
            current->value = status;
            free(hmnode);
            return;
        }

        current->next = hmnode;
    }
}

unsigned hashmap_find(struct hashmap_t* hm, int key)
{
    assert(hm != NULL);

    int k_hash = hash(key, hm->cap);

    struct hm_node_t* current = hm->data[k_hash];
    if(current == NULL)
        return NONR_HIR;

    while(current->key != key)
    {
        current = current->next;
        if(current == NULL)
            return NONR_HIR;
    }

    return current->value;
}

void hashmap_delete_elem(struct hashmap_t* hm, int data)
{
    assert(hm != NULL);

    int k_hash = hash(data, hm->cap);

    struct hm_node_t* current = hm->data[k_hash];
    if(current == NULL)
        return;

    if(current->key == data)
    {
        hm->data[k_hash] = current->next;
        free(current);
        return;
    }

    if(current->next == NULL)
        return;

    while(current->next->key != data)
    {
        current = current->next;
        if(current->next == NULL)
            return;
    }

    struct hm_node_t* tmp = current->next;
    current->next = current->next->next;
    free(tmp);
}

void hashmap_destroy(struct hashmap_t* hm)
{
    assert(hm != NULL);

    for(int i = 0; i < hm->cap; ++i)
    {
        if(hm->data[i] == NULL)
            continue;

        delete_list(hm->data[i]);
    }

    free(hm->data);
    free(hm);
}

void delete_list(struct hm_node_t* head)
{
    assert(head != NULL);

    struct hm_node_t* tmp;
    while(head != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }

}
