#include <stdio.h>
#include <stdlib.h>
#include "queue/queue.h"
#include "lirs/lirs.h"
#include "queue/queue_test.h"
#include "hm/hashmap_test.h"
#include "lirs/lirs_tests.h"

int hits_count(int cash_size, int request_count)
{
    int ans = 0;
    struct lirs_t* lirs = lirs_create(cash_size);
    for(int i = 0; i < request_count; ++i)
    {
        int data;
        int tmp = fscanf(stdin, "%d", &data);
        if(tmp != 1)
            return -1;

        ans += lirs_get(lirs, data);
    }

    lirs_destroy(lirs);

    return ans;
}

int main(int argc, char* argv[])
{
    int cash_size;
    int request_count;
    int ans;
    
    queue_test();
    hashmap_test();
    lirs_test();

    int tmp = fscanf(stdin, "%d %d", &cash_size, &request_count);
    if(tmp != 2)
    {
        printf("incorrect input cash size or request count");
        return -1;
    }

    ans = hits_count(cash_size, request_count);    
    printf("hits count: %d\n", ans);

}
