struct node_t* reverse(struct node_t* top)
{
    struct node_t* last;
    struct node_t* current;
    struct node_t* next;

    if(top == NULL)
        return NULL;
    if(top->next == NULL)
        return top;

    last = top;
    current = last->next;
    next = current->next;
    last->next = NULL;
    while(next != NULL)
    {
        current->next = last;
        last = current;
        current = next;
        next = next->next;
    }

    current->next = last;

    return current;
}
