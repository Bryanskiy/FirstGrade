#pragma once

#include <cstdint>
#include <cstring>
#include <fstream>
#include <cassert>
#include <map>
#include "tables.h"
#include "errors.h"

struct lexem_t
{
    uint16_t flag;
    int64_t arg;
};

#ifndef INSTR_T
#define INSTR_T

struct instruction_t
{
    int64_t arg;
    uint16_t CMD_flag;
    uint16_t CMD_code;
    uint16_t arg_flag;
};

#endif

int compile(char const asm_file_name[], char const elf_file_name[]);
int read(std::ifstream* asm_file, char** buffer);
int size_file(std::ifstream* file);
int processing_buffer(char*** words, char* buffer, int buffer_size);
int syntax_analize(lexem_t** lexems, int lexems_count, char** words);
int analize_cmd_code(uint16_t code, uint16_t const arr[], uint16_t arr_size);
int symantic_analize(instruction_t** instr, lexem_t* lexems, int lexems_count, int cmd_count);
void mfree(char** buffer, char*** words, lexem_t** lexems, instruction_t** instr);