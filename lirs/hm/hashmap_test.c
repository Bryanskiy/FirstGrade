#include "hashmap.h"
#include "hashmap_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void hashmap_test_1()
{
    int cap = 11;
    struct hashmap_t* hm = hashmap_create(cap);
    hashmap_add(hm, 13, 4);             //hash = 0; value = 4;
    hashmap_add(hm, 4, 7);              //hash = 3; value = 7;
    hashmap_add(hm, 22, 12);            //hash = 8; value = 12;
    hashmap_add(hm, 17, 86);            //hash = 6; value = 86;
    hashmap_add(hm, 75, 61);            //hash = 5; value = 61;
    hashmap_add(hm, 9, 33);             //hash = 5; value = 33;
    assert(hashmap_find(hm, 9) == 33);
    hashmap_add(hm, 60, 47);            //hash = 10; value = 7;
    hashmap_add(hm, 48, 19);            //hash = 3; value = 19;
    assert(hashmap_find(hm, 17) == 86);
    assert(hashmap_get_size(hm) == 11);
    hashmap_add(hm, 9, 4);              //hash = 5; value = 4;
    hashmap_add(hm, 57, 82);            //hash = 0; value = 82;
    assert(hashmap_find(hm, 9) == 4);
    assert(hashmap_find(hm, 48) == 19);
    assert(hashmap_find(hm, 4) == 7);
    hashmap_destroy(hm);
}

void hashmap_test_2()
{
    int cap = 3;
    struct hashmap_t* hm = hashmap_create(cap);
    hashmap_add(hm, 35, 92);                //hash = 0; value = 92;
    hashmap_add(hm, 20, 64);                //hash = 0; value = 64;
    hashmap_add(hm, 19 ,81);                //hash = 2; value = 81;
    hashmap_add(hm, 93, 4);                 //hash = 1; value = 4;
    hashmap_add(hm, 18, 2);                 //hash = 1; value = 2;
    assert(hashmap_find(hm, 20) == 64);
    assert(hashmap_find(hm, 19) == 81);
    hashmap_add(hm, 20, 99);                //hash = 0; value = 99;
    hashmap_add(hm, 47, 1);                 //hash = 0; value = 1;
    assert(hashmap_find(hm, 20) == 99);
    hashmap_add(hm, 63, 4);                 //hash = 1; value = 4;
    hashmap_add(hm, 88, 56);                //hash = 2; value = 56;
    assert(hashmap_find(hm, 63) == 4);
    assert(hashmap_find(hm, 35) == 92);
    assert(hashmap_find(hm, 88) == 56);
    hashmap_add(hm, 88, 9);                 //hash = 2; value = 9;
    assert(hashmap_find(hm, 88) == 9);
    hashmap_destroy(hm);
}

void hashmap_test_3()
{
    int cap = 20;
    struct hashmap_t* hm = hashmap_create(cap);
    hashmap_add(hm, 1, 1);//hash = 6; value = 1;
    hashmap_add(hm, 2, 2);//hash = 13; value = 2;
    hashmap_add(hm, 4, 4);//hash = 7; value = 4;
    hashmap_add(hm, 6, 6);//hash = 1; value = 6;
    assert(hashmap_find(hm, 4) == 4);
    hashmap_add(hm, 7, 7);//hash = 8; value = 7;
    hashmap_add(hm, 9, 9);//hash = 2; value = 9;
    hashmap_add(hm, 19, 19);//hash = 12; value = 19
    hashmap_add(hm, 1, 99);//hash = 6; value = 99;
    hashmap_add(hm, 20, 20);//hash = 19; value = 20
    assert(hashmap_find(hm, 1) == 99);
    hashmap_add(hm, 11, 11);//hash = 16; value = 11;
    hashmap_add(hm, 14, 14);//hash = 17; value = 14;
    assert(hashmap_find(hm, 9) == 9);
    hashmap_add(hm, 17, 17);//hash = 18; value = 17;
    hashmap_add(hm, 3, 3);//hash = 0; value = 3;
    hashmap_add(hm, 19, 34);//hash = 12; value = 34;
    hashmap_add(hm, 4, 61);//hash = 7; value = 61;
    assert(hashmap_find(hm, 19) == 34);
    assert(hashmap_get_size(hm) == 20);
    hashmap_add(hm, 8, 8);//hash = 15; value = 8;
    assert(hashmap_find(hm, 4) == 61);
    hashmap_destroy(hm);
}

void hashmap_test()
{
    hashmap_test_1();
    hashmap_test_2();
    hashmap_test_3();
    printf("Hashmap tests passed\n");
}    

void hashmap_print(struct hashmap_t* hm)
{
    printf("\n");
    for(int i = 0; i < hm->cap; ++i)
    {
        struct hm_node_t* tmp = hm->data[i];
        if(tmp != NULL)
        {
            printf("%2d %2d   ", tmp->key, tmp->value);
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
                printf("%2d %2d   ", tmp->key, tmp->value);
            }
        }
        printf("\n");
    }
    printf("\n");
}
