#pragma once

struct queue_node_t
{
    int data;
    struct queue_node_t* next;
    struct queue_node_t* pre;
};

struct queue_t
{
    struct queue_node_t* head;
    struct queue_node_t* tail;
    int size;
    int cap;
};

//This function creates link on new queue and allocate memory on it.
struct queue_t* queue_create(int cap);

//This function pushes data in the tail.
int queue_push(struct queue_t* queue, int data);

//This funtion returnes data from tail and remooves it from queue.
int queue_pop(struct queue_t* queue);

//This function delete data from any position in queue.
int queue_delete_dat(struct queue_t* queue, int data);

//This function destroy queue and free all allocated memory.
void queue_destroy(struct queue_t* queue);
