#include "lirs.h"
#include "../queue/queue.h"
#include "../hm/hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct lirs_t* lirs_create(int cash_size)
{
    assert(cash_size > 0);

    struct lirs_t* lirs = (struct lirs_t*)malloc(sizeof(struct lirs_t));
    assert(lirs != NULL);

    int hirsize = 0.01 * cash_size + 1;
    lirs->max_lirsize = cash_size - hirsize;
    int ssize = cash_size * 2;

    lirs->s = queue_create(ssize);
    lirs->q = queue_create(hirsize);
    lirs->lirsize = 0;
    lirs->hm = hashmap_create(cash_size); // ???????????????????

    return lirs;
}

void lirs_destroy(struct lirs_t* lirs)
{
    assert(lirs != NULL);

    queue_destroy(lirs->s);
    queue_destroy(lirs->q);
    hashmap_destroy(lirs->hm);
    free(lirs);
}

void lirs_puning(struct lirs_t* lirs)
{
    assert(lirs != NULL);

    if(lirs->s->size == 0)
        return;

    while(hashmap_find(lirs->hm, lirs->s->head->data) != LIR)
    {
        int tmp = queue_pop(lirs->s);
        if(hashmap_find(lirs->hm, tmp) == NONRQ_HIR)
            hashmap_delete_elem(lirs->hm, tmp);

        else
            hashmap_add(lirs->hm, tmp, NONRS_HIR);

        if(lirs->s->size == 0)
            return;
    }
}

int lirs_get(struct lirs_t* lirs, int data)
{
    assert(lirs != NULL);

    if (lirs->lirsize < lirs->max_lirsize)
    {
        if (hashmap_find(lirs->hm, data) != LIR)
        {
            queue_push(lirs->s, data);
            hashmap_add(lirs->hm, data, LIR);
            lirs->lirsize++;
            return 0;
        }
        else
        {
            queue_delete_dat(lirs->s, data);
            queue_push(lirs->s, data);
            return 1;
        }

    }

    if (hashmap_find(lirs->hm, data) == LIR)
    {
        if (lirs->s->head->data == data)
        {
            queue_pop(lirs->s);
            lirs_puning(lirs);
        } else
            queue_delete_dat(lirs->s, data);

        queue_push(lirs->s, data);

        return 1;
    }

    if (hashmap_find(lirs->hm, data) == RES_HIR)
    {
        queue_delete_dat(lirs->s, data);
        queue_push(lirs->s, data);
        hashmap_add(lirs->hm, data, LIR);

        queue_delete_dat(lirs->q, data);
        int tmp = queue_pop(lirs->s);
        queue_push(lirs->q, tmp);
        hashmap_add(lirs->hm, tmp, NONRS_HIR);

        lirs_puning(lirs);

        return 1;
    }

    if (hashmap_find(lirs->hm, data) == NONRS_HIR)
    {
        queue_push(lirs->s, data);

        queue_delete_dat(lirs->q, data);
        queue_push(lirs->q, data);

        hashmap_add(lirs->hm, data, RES_HIR);

        return 1;
    }

    int tmp = queue_pop(lirs->q);
    if (hashmap_find(lirs->hm, tmp) == RES_HIR)
        hashmap_add(lirs->hm, tmp, NONRQ_HIR);

    else
        hashmap_delete_elem(lirs->hm, tmp);


    if(hashmap_find(lirs->hm, data) == NONRQ_HIR)
    {
        queue_delete_dat(lirs->s, data);
        queue_push(lirs->s, data);
        hashmap_add(lirs->hm, data, LIR);

        int tmp1 = queue_pop(lirs->s);
        queue_push(lirs->q, tmp1);
        hashmap_add(lirs->hm, tmp1, NONRS_HIR);
        lirs_puning(lirs);

        return 0;
    }    

    if(hashmap_find(lirs->hm, data) == NONR_HIR)
    {
        queue_push(lirs->s, data);
        hashmap_add(lirs->hm, data, RES_HIR);
        queue_push(lirs->q, data);

        return 0;
    }
}
