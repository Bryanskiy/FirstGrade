#pragma once

#include <map>
#include <cstdint>

namespace tables
{
    std::map <std::string, uint16_t> CMD = { {"push"  , 10},
                                             {"pop"   , 11},
                                             {"add"   , 12}, 
                                             {"sub"   , 13}, 
                                             {"mul"   , 14}, 
                                             {"div"   , 15}, 
                                             {"in"    , 16}, 
                                             {"out"   , 17}, 
                                             {"jmp"   , 18}, //прыжок
                                             {"jaz"   , 19}, //прыжок, если последний эллемент > 0
                                             {"jlz"   , 20}, //прыжок, если последний эллемент < 0
                                             {"jz"    , 21}, //прыжок, если последний эллемент = 0
					     {"end"   , 22},
    };

    std::map <std::string, uint16_t> REG = { {"ax", 1},
                                             {"bx", 2},
                                             {"cx", 3},
                                             {"dx", 4}
    };

    uint16_t const _NULL_CMD_COUNT_  = 5;
    uint16_t const NULL_CMD[_NULL_CMD_COUNT_] = { 12, 13, 14, 15, 22};

    uint16_t const _REG_CMD_COUNT_ = 2;
    uint16_t const REG_CMD[_REG_CMD_COUNT_] = { 11, 16 };

    uint16_t const _NUM_AND_REG_CMD_COUNT_ = 2;
    uint16_t const NUM_AND_REG_CMD[_NUM_AND_REG_CMD_COUNT_] = { 10, 17 };

    uint16_t const _LABEL_CMD_COUNT_ = 4;
    uint16_t const LABEL_CMD[_LABEL_CMD_COUNT_] = { 18, 19, 20, 21 };


    uint16_t const _CMD_           =   50;
    uint16_t const _NUM_           =   51;
    uint16_t const _REG_           =   52;
    uint16_t const _NULL_          =   53;
    uint16_t const _Label_create_  =   54;
    uint16_t const  _Label_arg_    =   55;
    uint16_t const  _Label_resolv_ =   56;


    uint16_t const CMD_push        =   10;
    uint16_t const CMD_pop         =   11;
    uint16_t const CMD_sub         =   12;
    uint16_t const CMD_add         =   13;
    uint16_t const CMD_mul         =   14;
    uint16_t const CMD_div         =   15;
    uint16_t const CMD_in          =   16;
    uint16_t const CMD_out         =   17;
    uint16_t const CMD_jmp         =   18;
    uint16_t const CMD_jaz         =   19;
    uint16_t const CMD_jlz         =   20;
    uint16_t const CMD_jz          =   21;
    uint16_t const CMD_end         =   22;
}
