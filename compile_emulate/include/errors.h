#pragma once

#include <cstdint>
#include "tables.h"

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

namespace errs
{
	uint16_t const CANT_OPEN_ASM_FILE = 1;
    uint16_t const CANT_OPEN_ELF_FILE = 2;
    uint16_t const FEW_ARG_IN_MAIN    = 3;
    uint16_t const CANT_CREATE_BUFFER = 4;
    uint16_t const EMPTY_ASM_FILE     = 5;
    uint16_t const CANT_CREATE_WORDS  = 7;
    uint16_t const CANT_CREATE_LEXEMS = 8;

    uint16_t const UNDEFINED_REF   = 9;
    uint16_t const LABEL_EXIST      = 10;
    uint16_t const LABEL_NOT_FOUND  = 11;

    uint16_t const END_OF_CODE         = 12;
    uint16_t const EXPECTED_REG        = 13;
    uint16_t const EXPECTED_NUM_OR_REG = 14;
    uint16_t const EXPECTED_LABEL      = 15;
}	