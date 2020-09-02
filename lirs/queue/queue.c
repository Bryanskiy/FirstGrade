#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct queue_node_t* create_node(int data)
{
    struct queue_node_t* node = (struct queue_node_t*)malloc(sizeof(struct queue_node_t));
    assert(node != NULL);

    node->data = data;
    node->next = NULL;
    node->pre = NULL;

    return node;
}

struct queue_t* queue_create(int cap)
{
    struct queue_t* queue = (struct queue_t*)malloc(sizeof(struct queue_t));
    assert(queue != NULL);

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->cap = cap;

    return queue;
}

int queue_push(struct queue_t* queue, int data)
{
    assert(queue != NULL);

    if(queue->size >= queue->cap)
        return -1;

    struct queue_node_t* add = create_node(data);
    if(queue->size == 0)
    {
        queue->head = queue->tail = add;
        queue->size++;
        return 0;
    }

    add->next = queue->tail;
    queue->tail->pre = add;
    queue->tail = add;
    queue->size++;

    return 0;
}

int queue_pop(struct queue_t* queue)
{
    assert(queue != NULL);

    if(queue->size <= 0)
        return -1;

    int ret = queue->head->data;

    struct queue_node_t* tmp = queue->head;
    if(tmp->pre != NULL)
    {
        queue->head = tmp->pre;
        queue->head->next = NULL;
        queue->size--;
        free(tmp);
    }
    else
    {
        queue->head = NULL;
        queue->tail = NULL;
        queue->size--;
        free(tmp);
    }
    return ret;
}

int queue_delete_dat(struct queue_t* queue, int data)
{
    assert(queue != NULL);

    struct queue_node_t* tmp = queue->tail;
    while(tmp != NULL)
    {
        if(tmp->data == data)
            break;

        tmp = tmp->next;
    }

    if(tmp != NULL)
    {
        if((tmp->pre != NULL) && (tmp->next!= NULL))
        {
            tmp->pre->next = tmp->next;
            tmp->next->pre = tmp->pre;
            queue->size--;
            free(tmp);
        }

        else if(tmp->next == NULL)
            queue_pop(queue);


        else if(tmp->pre == NULL)
        {
            queue->tail = tmp->next;
            tmp->next->pre = NULL;
            queue->size--;
            free(tmp);
        }
    }
    return 0;
}

void queue_destroy(struct queue_t* queue)
{
    assert(queue != NULL);

    struct queue_node_t* tmp;
    struct queue_node_t* cure = queue->head;
    for(int i = 0; i < queue->size; ++i )
    {
        tmp = cure->pre;
        free(cure);
        cure = tmp;
    }
    free(queue);
}
