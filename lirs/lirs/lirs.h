#pragma once

struct lirs_t
{
    struct queue_t* s;
    struct queue_t* q;

    struct hashmap_t* hm;

    int max_lirsize;
    int lirsize;
};

//This function creates stacks q and s, and hashmap and set their sizes.
struct lirs_t* lirs_create(int cash_size);

//This function prunes stack s bottom untile there is a LIR data.
void lirs_puning(struct lirs_t* lirs);

//This function get data in lirs algorithm.
int lirs_get(struct lirs_t* lirs, int data);

//This function destroys all lirs stacks and hashmap and free all allocated memory.
void lirs_destroy(struct lirs_t* lirs);

enum stats
{
    LIR = 1,
    RES_HIR = 2,
    NONRS_HIR = 3,
    NONRQ_HIR = 4,
    NONR_HIR = 0,
};

