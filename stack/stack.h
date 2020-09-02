#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

std::ofstream logfile ("log.txt");

typedef unsigned long long kanary_t;
enum STACK_stat
{
    STACK_OK              = 0,
    STACK_DESTROYED       = 3,
    STACK_EXPAND_ERROR    = 4,
    STACK_HASH_ERROR      = 5,
    STACK_CLASS_KAN_ERROR = 6,
    STACK_DATA_KAN_ERROR  = 7,
    STACK_SIG_FOULT       = 8,
};

const int        realloc_number   =   2;
const kanary_t   kan              =   0xEFA4BEDA;
const int        start_cap        =   10;

template <typename T>
class Stack
{
    private:
                kanary_t              m_kan1;
                char*                 m_data;
                int                   m_stat;
                int                   m_cap;
                int                   m_size;
		unsigned long long    m_hash;
                kanary_t              m_kan2;

		int                   expand();
                int                   OK();
		unsigned long long    hash();


   public:
                void                  init();
                void                  destroy();
                int                   push(T value);
                T                     pop();
                void                  tell_stat();
                void                  dump_file();
};

#include "stack.cpp"
