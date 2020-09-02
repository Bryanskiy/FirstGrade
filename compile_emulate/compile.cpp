#include "include/compile.h"

int compile(char const asm_file_name[], char const elf_file_name[])
{     
    char* buffer = NULL;
    char** words = NULL;
    lexem_t* lexems = NULL;
    instruction_t* instr = NULL;
    std::ifstream asm_file(asm_file_name);
    std::ofstream elf_file(elf_file_name);
    if(asm_file.is_open() == 0)
    {
        errs::describe_general_mistake(errs::CANT_OPEN_ASM_FILE);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    }
    
    if(elf_file.is_open() == 0)
    {
        errs::describe_general_mistake(errs::CANT_OPEN_ELF_FILE);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    }

    int buffer_size = read(&asm_file, &buffer);

    if(buffer_size <= 0)
    {
	    errs::describe_general_mistake(errs::EMPTY_ASM_FILE);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    }

    if(buffer == NULL)
    {
        errs::describe_general_mistake(errs::CANT_CREATE_BUFFER);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    }
    
    int words_count = processing_buffer(&words, buffer, buffer_size);
    if(words_count <= 0)
    {
	    errs::describe_general_mistake(errs::EMPTY_ASM_FILE);
	    mfree(&buffer, &words, &lexems, &instr);
        return -1;
    }

    if(words == NULL)
    {
        errs::describe_general_mistake(errs::CANT_CREATE_WORDS);
	    mfree(&buffer, &words, &lexems, &instr);
        return -1;
    }
    
    int cmd_count = syntax_analize(&lexems, words_count, words);
    if(cmd_count <= 0)
    {
        errs::describe_general_mistake(errs::EMPTY_ASM_FILE);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    } 

    if(lexems == NULL)
    {
        errs::describe_general_mistake(errs::CANT_CREATE_LEXEMS);
	    mfree(&buffer, &words, &lexems, &instr);
	    return -1;
    }
    
    symantic_analize(&instr, lexems, words_count, cmd_count);
    for(int i = 0; i < cmd_count; ++i)
        printf("%d %d %d %ld\n", instr[i].CMD_flag, instr[i].CMD_code, instr[i].arg_flag, instr[i].arg);
  
    
    elf_file.write((char*)&cmd_count, sizeof(int));
    for(int i = 0; i < cmd_count; ++i)
        elf_file.write((char*)(instr + i), sizeof(instruction_t));
        
    asm_file.close();
    elf_file.close();
    free(buffer);
    free(words);
    free(lexems);
    free(instr);
}

int read(std::ifstream* asm_file, char** buffer)
{
    int buffer_size = size_file(asm_file);
    if(buffer_size <= 0)
        return buffer_size;

    *buffer = (char*)calloc(buffer_size + 1, sizeof(char));
    asm_file->getline(*buffer, buffer_size, '\0');

    (*buffer)[buffer_size] = '\0';

    return buffer_size;
}

int size_file(std::ifstream* file)
{
    if(file->is_open() == 0)
        return -1;

    file->seekg(0, std::ios::end);
    int file_len = file->tellg();
    file->seekg(0, std::ios::beg);

    return file_len;
}

int processing_buffer(char*** words, char* buffer, int buffer_size)
{
    int words_count = 0;
    int max_count = buffer_size / 3;
    *words = (char**)calloc(max_count, sizeof(char*));
    if(*words == NULL)
        return -1;

    char* word = strtok(buffer, " \n\t");
    if(word == NULL)
        return -1;

    (*words)[0] = word;
    words_count += 1;

    while((word = strtok(NULL, " \n\t")) != NULL)
    {
        if(words_count == max_count)
        {
            max_count += 10;
	        *words = (char**)realloc(*words, max_count * sizeof(char*));
	        if(*words == NULL)
                return -1;
	    }
	(*words)[words_count] = word;
	++words_count;
    }

    *words = (char**)realloc(*words, words_count * sizeof(char*));
    if(*words == NULL)
        return -1;

    return words_count;
}

int syntax_analize(lexem_t** lexems, int lexems_count, char** words)
{
    int cmd_count = 0;
    *lexems = (lexem_t*)calloc(lexems_count, sizeof(lexem_t));
    if(*lexems == NULL)
        return -1;
    
    std::map <std::string, int> labels;
    // 1 проход
    for(int i = 0; i < lexems_count; ++i)
    {
        auto word = tables::CMD.find(words[i]);
	    if(word != tables::CMD.end())
        {
            (*lexems)[i] = { tables::_CMD_, word->second };
	        ++cmd_count;
 
	        continue;
        }

	word = tables::REG.find(words[i]);
	if(word != tables::REG.end())
	{
	    (*lexems)[i] = { tables::_REG_, word->second };
	    continue;
	}
	    
        char* unidentified = strstr(words[i], ":");
        if(unidentified != NULL)
        {
            if((unidentified == words[i]) && (i == 0))
	         errs::describe_syntax_mistake(errs::UNDEFINED_REF, words[i]);

            if(unidentified == words[i])
                (*lexems)[i] = { tables::_Label_arg_, 0};

            if(*(unidentified + 1) == '\0')
            {
                *(unidentified) = '\0';
		        if(labels.find(words[i]) == labels.end())
                    labels.emplace(words[i], cmd_count);

		        else
                    errs::describe_syntax_mistake(errs::LABEL_EXIST, words[i]);

		        (*lexems)[i] = { tables::_Label_create_, cmd_count };
	        }
        
        }

	if(unidentified == NULL)
	{
        int num = 0;
	    for(int k = 0; words[i][k] != '\0'; ++k)
	    {
		    if(isdigit(words[i][k]))
		        num = num * 10 + words[i][k] - '0';

		else
		    errs::describe_syntax_mistake(errs::UNDEFINED_REF, words[i]);

		(*lexems)[i] = { tables::_NUM_, num };
	    }
	}
    }

    // 2 проход
    for(int i = 0; i < lexems_count; ++i)
    {
        if((*lexems)[i].flag == tables::_Label_arg_)
	    {
	        auto label = labels.find(words[i] + 1);
	        if(label != labels.end())
	            (*lexems)[i] = {tables::_Label_resolv_, label -> second};

            else
	            errs::describe_syntax_mistake(errs::LABEL_NOT_FOUND, words[i]);
	    }
    }

    return cmd_count;
}

int symantic_analize(instruction_t** instr, lexem_t* lexems, int lexems_count, int cmd_count)
{
    *instr = (instruction_t*)calloc(cmd_count, sizeof(instruction_t));
    int current_cmd = 0;
    int code = 0;
    for(int i = 0; i < lexems_count; ++i)
    {
        if(lexems[i].flag == tables::_CMD_)
	    {
            (*instr)[current_cmd].CMD_flag = tables::_CMD_;
	        (*instr)[current_cmd].CMD_code = code = lexems[i].arg;
	        if(analize_cmd_code(code, tables::NULL_CMD, tables::_NULL_CMD_COUNT_) == 1)
            {
		       //if((i < lexems_count-1) && ((lexems[i+1].flag == _NUM_) || (lexems[i].flag == _REG_) || (lexems[i].flag == _Label_arg_)))
		       //{
		       //error
		       //}
		       //else
                    (*instr)[current_cmd].arg_flag = tables::_NULL_;

            }
            
            if(analize_cmd_code(code, tables::REG_CMD, tables::_REG_CMD_COUNT_) == 1)
            {
                (*instr)[current_cmd].arg_flag = tables::_REG_;
		        ++i;
		        if(i >= lexems_count)
		        {
		           errs::describe_symantic_mistake(errs::END_OF_CODE, (*instr)[current_cmd]);
		           return -1;
		        }

  
		        else if(lexems[i].flag == tables::_REG_)
                    (*instr)[current_cmd].arg = lexems[i].arg;

		        else
                    errs::describe_symantic_mistake(errs::EXPECTED_REG, (*instr)[current_cmd]);
            }

            if(analize_cmd_code(code, tables::NUM_AND_REG_CMD, tables::_NUM_AND_REG_CMD_COUNT_) == 1)
	        {
                ++i;
		        if(i >= lexems_count)
                {
		            errs::describe_symantic_mistake(errs::END_OF_CODE, (*instr)[current_cmd]);
                    return -1;
                }
		        else if(lexems[i].flag == tables::_NUM_)
                {
                    (*instr)[current_cmd].arg_flag = tables::_NUM_;
		            (*instr)[current_cmd].arg = lexems[i].arg;
                }
		        else if(lexems[i].flag == tables::_REG_)
	            {
                    (*instr)[current_cmd].arg_flag = tables::_REG_;
		            (*instr)[current_cmd].arg = lexems[i].arg;
		        }
		    else
		        errs::describe_symantic_mistake(errs::EXPECTED_NUM_OR_REG, (*instr)[current_cmd]);

	        }

	        if(analize_cmd_code(code, tables::LABEL_CMD, tables::_LABEL_CMD_COUNT_ ) == 1)
            {
                ++i;
		        if(i >= lexems_count)
		        {
		            errs::describe_symantic_mistake(errs::END_OF_CODE, (*instr)[current_cmd]);
                    return -1;
		        }

		    else if(lexems[i].flag == tables::_Label_resolv_)
            {
                (*instr)[current_cmd].arg_flag = tables::_Label_resolv_;
		        (*instr)[current_cmd].arg = lexems[i].arg;
            }
		    else
		        errs::describe_symantic_mistake(errs::EXPECTED_LABEL, (*instr)[current_cmd]);
            }    
	        ++current_cmd;   
	    }
    }
}

int analize_cmd_code(uint16_t code, uint16_t const arr[], uint16_t arr_size)
{
    for(int i = 0; i < arr_size; ++i)
    {
        if(arr[i] == code)
	    return 1;
    }

    return 0;
}

void mfree(char** buffer, char*** words, lexem_t** lexems, instruction_t** instr)
{
    if(*buffer != NULL)
    {
        free(*buffer);
	    *buffer = NULL;
    }

    if(*words != NULL)
    {
        free(*words);;
	    *words = NULL;
    }

    if(*lexems != NULL)
    {
	    free(*lexems);
	    *lexems = NULL;
    }

    if(*instr != NULL)
    {
        free(*lexems);
	    *lexems = NULL;
    }
}
