#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include "stack/stack.h"
#include "tables.h"

struct instruction_t
{
    int64_t arg;
    uint16_t CMD_flag;
    uint16_t CMD_code;
    uint16_t arg_flag;
};

class CPU_t
{
    private:  int            m_cmd_count;
              instruction_t* m_instr;
              int            m_reg[4];

    public:   int            read(const char* elf_file_name);
	          int            calculate();
                            
	      CPU_t()
	      {
	          m_cmd_count = 0;
              m_instr = NULL;
		        for(int i = 0; i < 4; ++i)
              m_reg[i] = 0;
	      }	      

	      ~CPU_t()
          {
		      if(m_instr != NULL)
	          delete[] m_instr;
	      }
};
