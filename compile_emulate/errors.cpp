#include "include/errors.h"

namespace errs
{
    void describe_general_mistake(uint16_t code)
    {
        if(code == CANT_OPEN_ASM_FILE)
	    {
            std::cout << "ERROR: cant open file with your assembler code" << std::endl;
	        return;
	    }

	    if(code == CANT_OPEN_ELF_FILE)
        {
	        std::cout << "ERROR: cant open binary file" << std::endl;
	        return;
	    }

	    if(code == FEW_ARG_IN_MAIN)
        {
            std::cout << "ERROR: expected more arguments when you start the programm" << std::endl;
	        return;
	    }

	    if(code == CANT_CREATE_BUFFER)
	    {
            std::cout << "ERROR: cant read assembler file in buffer" << std::endl;
	        return;
	    }

	    if(code == EMPTY_ASM_FILE)
	    {
            std::cout << "ERROR: assemler file is empty or something goes wrong" << std::endl;
	        return;
	    }
 
        if(code == CANT_CREATE_WORDS)
	    {
            std::cout << "ERROR: cant devide your code on words" << std::endl;
	        return;
        }

	    if(code == CANT_CREATE_LEXEMS)
	    {
            std::cout << "ERROR: cant devide your code on lexems" << std::endl;
	        return;
	    }
    }

    void describe_syntax_mistake(uint16_t code, char* word)
    {
        if(code == UNDEFINED_REF)
	    {
            std::cout << "ERROR: undefined reference [" << word << "]" << std::endl;
	        return;
	    }

	   if(code == LABEL_EXIST)
	   {
            std::cout << "ERROR: label " << word << " already exist" << std::endl;
            return;
	   }

        if(code == LABEL_NOT_FOUND)
	    {
            std::cout << "ERROR: label " << word << " not found" << std::endl;
	        return;
	    }
    }

    void describe_symantic_mistake(uint16_t code, instruction_t instr)
    {
        if(code == END_OF_CODE)
        {
            std::cout << "ERROR: unexpected end of code" << std::endl;
	        std::cout << "       CMD_flag: " << instr.CMD_flag << std::endl;
	        std::cout << "       CMD_code: " << instr.CMD_code << std::endl;
	        std::cout << "       arg_flag: " << instr.arg_flag << std::endl;
	        std::cout << "       arg     : " << instr.arg << std::endl;
	        return;
        }

	   if(code == EXPECTED_REG)
	   {
	        std::cout << "ERROR: command expected REG arg" << std::endl;
            std::cout << "       CMD_flag: " << instr.CMD_flag << std::endl;
            std::cout << "       CMD_code: " << instr.CMD_code << std::endl;
            std::cout << "       arg_flag: " << instr.arg_flag << std::endl;
            std::cout << "       arg     : " << instr.arg << std::endl;
            return;
	   }

	   if(code == EXPECTED_NUM_OR_REG)
       {
            std::cout << "ERROR: command expected REG or number arg" << std::endl;
            std::cout << "       CMD_flag: " << instr.CMD_flag << std::endl;
            std::cout << "       CMD_code: " << instr.CMD_code << std::endl;
            std::cout << "       arg_flag: " << instr.arg_flag << std::endl;
            std::cout << "       arg     : " << instr.arg << std::endl;
            return;
       }
	
	   if(code == EXPECTED_LABEL)
       {
            std::cout << "ERROR: command expected label arg" << std::endl;
            std::cout << "       CMD_flag: " << instr.CMD_flag << std::endl;
            std::cout << "       CMD_code: " << instr.CMD_code << std::endl;
            std::cout << "       arg_flag: " << instr.arg_flag << std::endl;
            std::cout << "       arg     : " << instr.arg << std::endl;
            return;
       }

    }
}
