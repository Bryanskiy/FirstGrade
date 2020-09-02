# include "include/processor.h"

//проверки
int CPU_t::read(const char* elf_file_name)
{
    std::ifstream elf_file(elf_file_name);
    elf_file.read((char*)&m_cmd_count, sizeof(int));
    
    m_instr = new instruction_t[m_cmd_count]();
    for(int i = 0; i < m_cmd_count; ++i)
        elf_file.read((char*)m_instr, sizeof(instruction_t) * m_cmd_count);

    for(int i = 0; i < m_cmd_count; ++i)
        printf("%d %d %d %ld\n", m_instr[i].CMD_flag, m_instr[i].CMD_code, m_instr[i].arg_flag, m_instr[i].arg);

    return 0;
}

int CPU_t::calculate()
{
    Stack <int64_t> stack;
    stack.init();
    for(int current_cmd = 0; current_cmd < m_cmd_count; ++current_cmd)
    {
        switch(m_instr[current_cmd].CMD_code)
		{
            case CMD_push:
	        
	        	if(m_instr[current_cmd].arg_flag == _REG_)
		    		stack.push(m_reg[m_instr[current_cmd].arg - 1]); 
				else
		    		stack.push(m_instr[current_cmd].arg);		
	        	break;

	    	case CMD_pop:
            	m_reg[m_instr[current_cmd].arg - 1] = stack.pop();
				break;

            	case CMD_add:

				stack.push(stack.pop() + stack.pop());
				break;

	    	case CMD_mul:

				stack.push(stack.pop() * stack.pop());
				break;
	   
	    	case CMD_out:

				if(m_instr[current_cmd].arg_flag == _REG_)
	            	std::cout << m_reg[m_instr[current_cmd].arg - 1] << std::endl;
				else
		    		std::cout << m_instr[current_cmd].arg << std::endl;;
				break;

	    	case CMD_in:

				std::cin >> m_reg[m_instr[current_cmd].arg - 1];
				break;

	    	case CMD_jmp:

				current_cmd = m_instr[current_cmd].arg - 1;
				break;
        }


    }
}
