#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct buff_t
{
    int len;
    char* str;
};

const int FILE_NOT_FOUND = -1;
const int EMPTY_FILE = -2;
const int NO_MEMORY = -3;
const int READ_ERROR = -4;

int size_file_in_bites(FILE* file);

int open_file(const char file_name[], const char open_file_mode[], FILE** file);

int read_file(const char file_name[], FILE* file, struct buff_t* buffer);

int change_buffer(struct buff_t* buffer);

int processing_lines(struct buff_t* buffer, char** str_ptrs);

int compare(const void* stra, const void* strb);

int file_out(FILE* file, char** str_ptrs, int str_ptrs_len);

void sort(char** str_ptrs, int str_ptrs_len);

int compare_rifm(const void* s1, const void* s2);

