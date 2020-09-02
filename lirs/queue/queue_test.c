#include "queue.h"
#include "queue_test.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

void queue_test_1()
{
    struct queue_t* s;
    s = queue_create(10);
    queue_push(s, 13);              //13
    queue_push(s, 3);               //3 13
    queue_push(s, 4);               //4 3 13
    assert(queue_pop(s) == 13);     //4 3
    queue_push(s, 17);              //17 4 3
    queue_push(s, 28949);           //28949 17 4 3
    queue_delete_dat(s, 4);         //28949 17 3
    assert(queue_pop(s) == 3);      //28949 17
    assert(queue_pop(s) == 17);     //28949
    queue_push(s, 4438);            //4438 28949
    queue_push(s, 271);             //271 4438 28949
    queue_delete_dat(s, 28949);     //271 4438
    assert(queue_pop(s) == 4438);   //271
    assert(queue_pop(s) == 271);    //-
    assert(queue_pop(s) == -1);     //s is empty
    queue_destroy(s);
}


void queue_test_2()
{
    struct queue_t* s = queue_create(10);
    for(int i = 0; i < 10; ++i)                 //10 9 8 7 6 5 4 3 2 1
        queue_push(s, 1 + i);
    assert(queue_push(s, 11) == -1);            //10 9 8 7 6 5 4 3 2 1
    assert(queue_pop(s) == 1);                  //10 9 8 7 6 5 4 3 2
    assert(queue_push(s, 38) == 0);             //38 10 9 8 7 6 5 4 3 2
    assert(queue_delete_dat(s, 3) == 0);        //38 10 9 8 7 6 5 4 2
    assert(queue_delete_dat(s, 4) == 0);        //38 10 9 8 7 6 5 2
    assert(queue_delete_dat(s, 5) == 0);        //38 10 9 8 7 6 2
    assert(queue_pop(s) == 2);                  //38 10 9 8 7 6
    assert(queue_pop(s) == 6);                  //38 10 9 8 7
    assert(queue_delete_dat(s, 38) == 0);       //10 9 8 7
    assert(queue_delete_dat(s, 10) == 0);       //9 8 7
    assert(queue_push(s, 29) == 0);             //29 9 8 7
    assert(queue_pop(s) == 7);                  //29 9 8
    assert(queue_pop(s) == 8);                  //29 9
    assert(queue_pop(s) == 9);                  //29
    assert(queue_pop(s) == 29);                 //-
    assert(queue_pop(s) == -1);                 //s is empty
    assert(queue_push(s, 73) == 0);             //73
    assert(queue_pop(s) == 73);                 //-
    queue_destroy(s);
}

void queue_test_3()
{
    struct queue_t* s = queue_create(50);
    int arr[50];
    srand(time(NULL));
    for(int i = 0; i < 50; ++i)
    {
        arr[i] = rand();
        assert(queue_push(s, arr[i]) == 0);
    }
    queue_delete_dat(s, arr[4]);
    queue_delete_dat(s, arr[5]);
    queue_delete_dat(s, arr[17]);
    queue_delete_dat(s, arr[19]);
    queue_delete_dat(s, arr[30]);
    queue_delete_dat(s, arr[48]);
    queue_delete_dat(s, arr[25]);
    queue_delete_dat(s, arr[39]);

    assert(queue_pop(s) == arr[0]);
    assert(queue_pop(s) == arr[1]);
    assert(queue_pop(s) == arr[2]);
    assert(queue_pop(s) == arr[3]);
    for(int i = 6; i < 17; ++i)
    {
        assert(queue_pop(s) == arr[i]);
    }
    assert(queue_pop(s) == arr[18]);
    for(int i = 20; i < 25; ++i)
    {
        assert(queue_pop(s) == arr[i]);
    }
    for(int i = 26; i < 30; ++i)
    {
        assert(queue_pop(s) == arr[i]);
    }
    for(int i = 31; i < 39; ++i)
    {
        assert(queue_pop(s) == arr[i]);
    }
    for(int i = 40; i < 48; ++i)
    {
        assert(queue_pop(s) == arr[i]);
    }
    assert(queue_pop(s) == arr[49]);
    queue_destroy(s);
}

void queue_test()
{
    queue_test_1();
    queue_test_2();
    queue_test_3();
    printf("queue tests passed\n");
}

void queue_print_straight(struct queue_t* queue)
{
    struct queue_node_t* tmp = queue->tail;
    while(tmp != NULL)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}    

void queue_print_reverse(struct queue_t* queue)
{
    struct queue_node_t* tmp = queue->head;
    while(tmp != NULL)
    {
        printf("%d ", tmp->data);
        tmp = tmp->pre;
    }    
}
