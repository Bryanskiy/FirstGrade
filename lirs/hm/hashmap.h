#pragma once

struct hm_node_t
{
    struct hm_node_t* next;
    int key;
    char value;
};

struct hashmap_t
{
    int cap;
    struct hm_node_t** data;
};

//This function creates a link on a new hashmap and allocate memory on it.
struct hashmap_t* hashmap_create(int size);

//This function returns maximum size of hashmap
unsigned hashmap_get_size(struct hashmap_t* hm);

//This function add data into the hashmap to the certain hash_node
void hashmap_add(struct hashmap_t* hm, int key, char status);

//This funtction find the data in the hashmap and returns its status
unsigned hashmap_find(struct hashmap_t* hm, int key);

//This function delete from hashmap element same as data 
void hashmap_delete_elem(struct hashmap_t* hm, int data);

//This function destroy the hashmap and free all allocated memory
void hashmap_destroy(struct hashmap_t* hm);


