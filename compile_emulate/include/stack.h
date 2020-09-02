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

template <typename T>
void Stack<T>::init()
{
    logfile << "Trying to init stack..\n";

    m_cap  = start_cap;
    m_data = new char[sizeof(T) * m_cap + sizeof(kanary_t) * 2];
    m_size = 0;
    m_kan1 = kan;                                                                   
    m_kan2 = kan;                                                                   
         
    *(kanary_t*)m_data = kan;                                                       
    *(kanary_t*)(m_data + sizeof(kanary_t) + sizeof(T) * m_cap) = kan; 

    m_hash = hash();    

    m_stat = STACK_OK;
    
    logfile  << "OK, I'm ready to work!!\n";    
}

template <typename T>
void Stack<T>::destroy()
{
    logfile << "Trying to destroy stack...\n"; 

    *(kanary_t*)m_data = 0;
    *(kanary_t*)(m_data + sizeof(kanary_t) + sizeof(T) * (m_cap)) = 0;

    for (int i = 0; i < m_cap; ++i)
        ((T*)(m_data + sizeof(kanary_t)))[i] = 0;

    m_size = 0;
    m_kan1 = 0;
    m_kan2 = 0;
    m_cap  = 0;
    m_hash = 0;
    m_stat = STACK_DESTROYED;

    delete[] m_data;

    logfile  << "Stack destroyed.\n";
}

template <typename T>
int Stack<T>::OK()
{
    if(m_hash != hash())
    {
        m_stat = STACK_HASH_ERROR;
        return STACK_HASH_ERROR;
    }

    if((m_kan1 != kan) || (m_kan2 != kan))
    {
        m_stat = STACK_CLASS_KAN_ERROR;
    return STACK_CLASS_KAN_ERROR;
    }

    if((*(kanary_t*)m_data != kan) || (*(kanary_t*)(m_data + sizeof(kanary_t) + sizeof(T) * m_cap) != kan))
    {
        m_stat = STACK_DATA_KAN_ERROR;
        return STACK_DATA_KAN_ERROR;
    }

    if((m_size < 0) || (m_size > m_cap))
    {
        m_stat = STACK_SIG_FOULT;
    return STACK_SIG_FOULT;
    }

    return STACK_OK;
}

template <typename T>
int Stack<T>::push(T value)
{
    int err = OK();
    if(err != STACK_OK)
    {
        logfile << "Something goes wrong when you push, " << value << "Error code: " << err << std::endl;
        return err;
    }

    if(m_size == m_cap)
    {
        err = expand();
    if(err == STACK_EXPAND_ERROR)
    {
            m_stat = STACK_EXPAND_ERROR;
        return STACK_EXPAND_ERROR;
    }
     }

    ((T*)(m_data + sizeof(kanary_t)))[m_size] = value;
    m_size += 1;

    m_hash = hash();

    logfile << "Pushing " << value << ", " <<"new size: " << m_size << std::endl;

    return STACK_OK;
}

template <typename T>
int Stack<T>::expand()
{
    logfile << "Trying realloc stack...\n";
    int new_cap = m_cap * realloc_number;
    char* tmp = new char[sizeof(T) * new_cap + sizeof(kanary_t) * 2];
    if(tmp == nullptr)
    {
    logfile << "realloc was failed, your capaciry = " << m_cap << std::endl;
        return STACK_EXPAND_ERROR;
    }

    std::memcpy(tmp, m_data, m_cap * sizeof(T) + sizeof(kanary_t));

    for (int i = 0; i < m_cap; ++i)
        ((T*)(m_data + sizeof(kanary_t)))[i] = 0;
    delete[] m_data;

    m_data = tmp;
    m_cap = new_cap;
    tmp = nullptr;

    *(kanary_t*)(m_data + sizeof(kanary_t) + m_cap * sizeof(T)) = kan;

    m_hash = hash();

    logfile << "Realloced to " << m_cap << std::endl;
    return STACK_OK;
}

template <typename T>
T Stack<T>::pop()
{   
    int err = OK();
    if(err != STACK_OK)
    {   
        logfile << "Something goes wrong when you pop, " << "Error code: " << err << std::endl;
        return err;
    }

    --m_size;
    if(m_size < 0)
    {
        logfile <<"Poping whith negative size " << std::endl;
        m_stat = STACK_SIG_FOULT;
    return STACK_SIG_FOULT;
    }

    T ret = ((T*)(m_data + sizeof(kanary_t)))[m_size];

    ((T*)(m_data + sizeof(kanary_t)))[m_size] = 0;

    m_hash = hash();

    logfile << "Popping " << ret << ", " << "new size: " << m_size << std::endl;

    return ret;
}

template <typename T>
void Stack<T>::tell_stat()
{
    switch(m_stat)
    {
    case STACK_OK:
        std::cout << "Stack is OK" << std::endl;
        break;
    
    case STACK_DESTROYED:
        std::cout << "Stack destroyed" << std::endl;
        break;
        
    case STACK_EXPAND_ERROR:
        std::cout << "ERROR: stack expand failed" << std::endl;
        break;

    case STACK_HASH_ERROR:
        std::cout << "ERROR: stack hash is dead" << std::endl;
        break;

    case STACK_SIG_FOULT:
        std::cout << "ERROR: sigmintation foult" << std::endl;
        break;

    case STACK_DATA_KAN_ERROR:
        std::cout << "ERROR: data kanary dead" << std::endl;
        break;

    case STACK_CLASS_KAN_ERROR:
        std::cout << "ERROR: class kanary dead" << std::endl;
        break;

    }    
}

template <typename T>
void Stack<T>::dump_file()
{
    using std::endl;
    std::ofstream stack_out ("stack.txt");

    stack_out << "STATUS CODE:             " << m_stat                                                      << endl;
    stack_out << "data pointer:            " << (size_t)m_data                                              << endl;
    stack_out << "capacity:                " << m_cap                                                       << endl;
    stack_out << "size:                    " << m_size                                                      << endl;
    stack_out << "class hash:              " << m_hash                                                      << endl;
    stack_out << "compute hash:            " << hash()                                                      << endl;
    stack_out << "first kanary in class:   " << m_kan1                                                      << endl;
    stack_out << "second kanary in class:  " << m_kan2                                                      << endl;
    stack_out << "first kanary in data:    " << *(kanary_t*)m_data                                          << endl;
    stack_out << "second kanary in data:   " << *(kanary_t*)(m_data + sizeof(kanary_t) + sizeof(T) * m_cap) << endl;
 
    for(int i = 0; i < m_cap; ++i)
    {
        if(i < m_size)  stack_out << " ";
    else            stack_out << "*";

    stack_out << "[" << i << "/" << m_cap - 1 << "] = " << ((T*)(m_data + sizeof(kanary_t)))[i] << endl;
    }

    stack_out.close();
}

template <typename T>
unsigned long long Stack<T>::hash()
{
    unsigned long long hash = 0;
    unsigned int num_data_bites = sizeof(T) * m_cap + sizeof(kanary_t) * 2;

    for(unsigned int i = 0; i < num_data_bites; ++i)
        m_hash = m_hash * 7 + m_data[i] + 53;

    hash += m_cap * 31 - m_size * 12;
    hash += m_kan1 * 23 - m_kan2 * 11;
    
    return hash;
}

