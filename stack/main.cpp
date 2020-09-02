#include <iostream>
#include <fstream>
#include <cstring>
#include "stack.h"

int main()
{
    Stack <int> stack_int;
    stack_int.init();
    stack_int.push(2);
    for(int i = 0; i < 100; ++i)
        stack_int.push(i);

    stack_int.dump_file();

    stack_int.destroy();
}

