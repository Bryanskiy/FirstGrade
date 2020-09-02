#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "../queue/queue.h"
#include "../lirs/lirs.h"
#include "../hm/hashmap.h"

void lirs_test_1()
{
  int cash_size = 4;
  int request_count = 10;
  struct lirs_t* lirs = lirs_create(cash_size);
  lirs_get(lirs, 1);                                  //s:1
  lirs_get(lirs, 2);
  assert(hashmap_find(lirs->hm, 1) == LIR);
  assert(hashmap_find(lirs->hm, 2) == LIR);
  lirs_get(lirs, 3);
  lirs_get(lirs, 4);                                 //s:[1 2 3] (4)  q:4
  assert(lirs->s->tail->data == 4);
  assert(hashmap_find(lirs->hm, 1) == LIR);
  assert(hashmap_find(lirs->hm, 4) == RES_HIR);
  lirs_get(lirs, 5);                                 //s:[1 2 3] 4 (5) q: 5
  assert(lirs->q->head->data == 5);
  lirs_get(lirs, 4);                                 //s:[2 3] 5 [4] q: 1
  assert((lirs->s->head->data == 2)&&(lirs->q->head->data == 1));
  lirs_get(lirs, 2);
  lirs_get(lirs, 3);
  assert(hashmap_find(lirs->hm, 1) == NONRS_HIR);
  lirs_get(lirs, 4);                                  //s:[2 3 4] q: 1
  assert(hashmap_find(lirs->hm, 5) == NONR_HIR);
  assert(lirs->q->head->data == 1);
  lirs_get(lirs, 1);
  lirs_destroy(lirs);
}

void lirs_test_2()
{
  int cash_size = 3;
  int request_count = 10; 
  struct lirs_t* lirs = lirs_create(cash_size);
  lirs_get(lirs, 5);
  lirs_get(lirs, 2);
  lirs_get(lirs, 7);                              //s:[2 5] (7) q:7
  assert(hashmap_find(lirs->hm, 7) == RES_HIR);
  lirs_get(lirs, 8);                              //s:[2 5] 7 (8) q:8
  assert(lirs->q->head->data == 8);
  assert(hashmap_find(lirs->hm, 7) == NONRQ_HIR);
  assert(hashmap_find(lirs->hm, 8) == RES_HIR);
  assert(lirs->s->tail->data == 8);
  lirs_get(lirs, 61);                             //s:[2 5] 7 8 (61) q:61
  assert(lirs->q->head->data == 61);
  assert(hashmap_find(lirs->hm, 5) == LIR);
  assert(lirs->s->tail->data == 61);
  lirs_get(lirs, 2);                              //s:[5] 7 8 (61) [2] q:61
  assert(lirs->s->tail->data == 2);
  lirs_get(lirs, 8);                              //s:[2][8] q:5
  assert(hashmap_find(lirs->hm, 8) == LIR);
  assert(lirs->q->head->data == 5);
  assert(lirs->s->tail->data == 8);
  lirs_get(lirs, 35);                             //s:[2 8] (35) q:35
  assert(lirs->q->tail->data == 35);
  lirs_get(lirs, 7);                              //s:[2 8] 35 (7) q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 35) == NONRQ_HIR);
  lirs_get(lirs, 2);                              //s:[8] 35 (7) [2] q:7
  assert(lirs->s->tail->data == 2);
  assert(lirs->s->head->data == 8);
  lirs_destroy(lirs);
}
 
void lirs_test_3()
{
  int cash_size = 3;
  int request_count = 10; 
  struct lirs_t* lirs = lirs_create(cash_size);
  lirs_get(lirs, 3);
  lirs_get(lirs, 5);
  lirs_get(lirs, 7);                //s:[3 5](7) q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 3) == LIR);
  assert(lirs->s->tail->data == 7);
  lirs_get(lirs, 3);
  lirs_get(lirs, 5);                //s:[3 5]  q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 7) == NONRS_HIR);
  assert(lirs->s->tail->data == 5);
  lirs_get(lirs, 7);                //s:[3 5](7) q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 7) == RES_HIR);
  assert(lirs->s->tail->data == 7);
  lirs_get(lirs, 9);                //s:[3 5] 7 (9) q:9
  assert(lirs->q->head->data == 9);
  assert(hashmap_find(lirs->hm, 9) == RES_HIR);
  assert(hashmap_find(lirs->hm, 7) == NONRQ_HIR);
  assert(lirs->s->tail->data == 9);
  lirs_get(lirs, 9);                //s:[5] 7 [9] q:3
  assert(lirs->q->head->data == 3); 
  assert(lirs->s->tail->data == 9);
  lirs_get(lirs, 7);                //s:[9 7] q:5
  assert(lirs->q->head->data == 5);
  assert(hashmap_find(lirs->hm, 5) == NONRS_HIR);
  assert(lirs->s->tail->data == 7);
  assert(lirs->s->head->data == 9);
  lirs_get(lirs, 5);                //s:[9 7] (5) q:5
  assert(lirs->q->head->data == 5);
  assert(hashmap_find(lirs->hm, 9) == LIR);
  assert(lirs->s->tail->data == 5);
  lirs_destroy(lirs);
}

void lirs_test_4()
{ 
  int cash_size = 3;
  int request_count = 8; 
  struct lirs_t* lirs = lirs_create(cash_size);
  lirs_get(lirs, 1);
  lirs_get(lirs, 2);
  lirs_get(lirs, 3);                      //s:[1 2] (3) q:3
  assert(lirs->q->head->data == 3);
  assert(hashmap_find(lirs->hm, 2) == LIR);
  assert(hashmap_find(lirs->hm, 1) == LIR);
  assert(lirs->s->tail->data == 3);
  lirs_get(lirs, 2);                      //s:[1] (3) [2] q:3
  assert(lirs->q->head->data == 3);
  assert(hashmap_find(lirs->hm, 2) == LIR);
  assert(lirs->s->tail->data == 2);
  lirs_get(lirs, 4);                      //s:[1] 3 [2] (4) q:4
  assert(lirs->q->head->data == 4);
  assert(hashmap_find(lirs->hm, 3) == NONRQ_HIR);
  assert(hashmap_find(lirs->hm, 10) == NONR_HIR);
  assert(lirs->s->tail->data == 4);
  lirs_get(lirs, 3);                      //s:[2] 4 [3] q:1
  assert(lirs->q->head->data == 1);
  assert(hashmap_find(lirs->hm, 1) == NONRS_HIR);
  assert(lirs->s->tail->data == 3);
  lirs_get(lirs, 1);                      //s:[2] 4 [3] (1) q:1
  assert(lirs->q->head->data == 1);
  assert(hashmap_find(lirs->hm, 4) == NONRQ_HIR);
  assert(lirs->s->tail->data == 1);
  lirs_get(lirs, 4);                      //s:[3] 1 [4] q:2
  assert(lirs->q->head->data == 2); 
  assert(lirs->s->tail->data == 4);
  assert(hashmap_find(lirs->hm, 2) == NONRS_HIR);
  assert(lirs->s->head->data == 3);
  lirs_destroy(lirs);
}

void lirs_test_5()
{ 
  int cash_size = 3;
  int request_count = 8; 
  struct lirs_t* lirs = lirs_create(cash_size);
  lirs_get(lirs, 1);
  lirs_get(lirs, 2);
  lirs_get(lirs, 3);               //s:[1 2] (3) q:3
  assert(lirs->q->head->data == 3);
  assert(hashmap_find(lirs->hm, 5) == NONR_HIR);
  assert(lirs->s->tail->data == 3);
  lirs_get(lirs, 5);               //s:[1 2] 3 (5) q:5
  assert(lirs->q->head->data == 5);
  assert(hashmap_find(lirs->hm, 5) == RES_HIR);
  assert(lirs->s->tail->data == 5);
  lirs_get(lirs, 7);               //s:[1 2] 3 5 (7) q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 5) == NONRQ_HIR);
  assert(lirs->s->tail->data == 7);
  lirs_get(lirs, 2);               //s:[1] 3 5 (7) [2] q:7
  assert(lirs->q->head->data == 7);
  assert(hashmap_find(lirs->hm, 5) == NONRQ_HIR);
  assert(lirs->s->tail->data == 2);
  lirs_get(lirs, 5);               //s:[2 5] q:1
  assert(lirs->q->head->data == 1);
  assert(hashmap_find(lirs->hm, 5) == LIR);
  assert(lirs->s->tail->data == 5);
  assert(lirs->s->head->data == 2);
  lirs_get(lirs, 1);               //s:[2 5] (1) q:1
  assert(lirs->q->head->data == 1); 
  assert(lirs->s->tail->data == 1);
  lirs_destroy(lirs);
}


int lirs_hit_test(int cash_size, int request_count, int max_data)
{
    srand(time(NULL));
    int ans = 0;
    struct lirs_t* lirs = lirs_create(cash_size);
    for(int i = 0; i < request_count; ++i)
    {
        int data = rand() % max_data;
        ans += lirs_get(lirs, data);
    }

    lirs_destroy(lirs);

    return ans;
}

void lirs_test()
{
    lirs_test_1();
    lirs_test_2();
    lirs_test_3();
    lirs_test_4();
    lirs_test_5();

    printf("Lirs tests passed\n");

}
