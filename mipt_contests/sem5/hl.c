int list_is_a_loop(struct node_t *top)
{       
    struct node_t* turt;
    struct node_t* hare;

    if(top == NULL)
        return 0;

    hare = top->next;
    if(hare == NULL)
        return 0;

    turt = hare->next;
    while(turt != NULL)
    {
        if(turt == hare)
            return 1;

        turt = turt->next;
        if(turt == NULL)
            return 0;
        turt = turt->next;
        hare = hare->next;
    }       
    
    return 0;
} 
