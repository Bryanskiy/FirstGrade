int selstep(void* parr, int eltsize, int numelts, int nsorted, cmp_t cmp);
void swap_char(char* v1, char* v2);
void swap(void* v1, void* v2, unsigned size);
int search_min(void* parr, int eltsize, int numelts, int nsorted, cmp_t cmp);
int cmp(void const* lhs, void const* rhs);

int selstep(void* parr, int eltsize, int numelts, int nsorted, cmp_t cmp)
{
    int min_number = search_min((char*)parr, eltsize, numelts, nsorted, cmp);

    swap((char*)parr + min_number * eltsize, (char*)parr + nsorted * eltsize, eltsize);

    return 0;
}

void swap_char(char* v1, char* v2)
{
    char tmp = *v1;
    *v1 = *v2;
    *v2 = tmp;
}

void swap(void* v1, void* v2, unsigned size)
{
    unsigned i;
    for(i = 0; i < size; ++i)
        swap_char((char*)v1 + i, (char*)v2 + i);
}

int search_min(void* parr,int eltsize, int numelts, int nsorted, cmp_t cmp)
{
    char* min = (char*)parr + nsorted * eltsize;

    int min_number = nsorted;

    for(int i = nsorted  + 1; i < numelts; ++i)
    {
        if(cmp((char*)parr + i * eltsize, min) > 0)
        {
            min = (char*)parr + i * eltsize;
            min_number = i;
        }
    }

    return min_number;
}
