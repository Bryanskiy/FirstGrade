int loop_len(struct node_t *top)
{                                         
    struct node_t* turt;
    struct node_t* hare;
    int len = 0;
    int flag = 0;

    if(top == NULL)
        return 0;

    hare = top->next;
    if(hare == NULL)
        return 0;

    turt = hare->next;
    while(turt != NULL)
    {
        if(turt == hare)
        {
            flag = 1;
            break;
        }
        turt = turt->next;
        if(turt == NULL)
            return 0;
        turt = turt->next;
        hare = hare->next;
    }

    if(flag == 1)
    {
        len = 1;
        hare = hare->next;
        while(hare != turt)
        {
            hare = hare->next;
            ++len;
        }

        return len;
    }

    return 0;
} 
