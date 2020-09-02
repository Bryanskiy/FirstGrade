#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

enum masks_t
{
    MOVMASK = (1 << 7),
    INOUTMASK = (1 << 6),
    REGMASK = 0x3,
};


enum reg_t
{
    A = 0, B = 1, C = 2, D = 3, RLAST = 4
};

enum opcode_t
{
    MOVI = 0x0, ADD = 0x8, SUB = 0x9, MUL = 0xA, DIV = 0xB, IN = 0x30, OUT = 0x31
};

union operand_t
{
    struct 
    { 
        int rd, rs; 
    } ops;
    int rop;
    int imm;
};

struct instr_t
{
    enum opcode_t opcode;
    union operand_t opnd;
};

struct reg_state_t
{
    unsigned char data;
    unsigned char init;
};

unsigned char exec_binop(enum opcode_t opcode, unsigned char rd, unsigned char rs)
{
    switch(opcode)
    {
        case ADD:
            return rd + rs;
        case SUB:
            return rd - rs;
        case MUL:
            return rd * rs;
        case DIV:
            if(rs == 0)
            {
                fprintf(stderr, "divide on zero");
                abort();
            }

            return rd / rs;
    }

    return 0;
}

void execute_instr(struct reg_state_t *st, struct instr_t instr)
{
    int d, res;
    int rd = instr.opnd.ops.rd;
    int rs = instr.opnd.ops.rs;
    switch(instr.opcode)
    {
        case MOVI:
            st[D].data = instr.opnd.imm;
            st[D].init = 1;
            break;

        case IN:
            res = scanf("%d", &d);
            assert(res == 1);
            st[instr.opnd.rop].data = d & 0xFF;
            st[instr.opnd.rop].init = 1;
            break;

        case OUT:
            d = st[instr.opnd.rop].data;
            printf("%d\n", d);
            break;

        case ADD:
        case SUB:
        case MUL:
        case DIV:
            if((st[rd].init == 0) || (st[rd].init == 0))
            {
                fprintf(stderr, "Using uninitialize regs: %d %d", rd, rs);
                abort();
            }

            st[rd].data = exec_binop(instr.opcode, st[rd].data, st[rs].data);
    }
}

struct instr_t decode_instr(unsigned char cmd)
{
    struct instr_t instr;

    if((cmd & MOVMASK) == 0)
    {
        instr.opcode = MOVI;
        instr.opnd.imm = cmd;
    }
    else if((cmd & INOUTMASK) != 0)
    {
        if((cmd >> 2) == IN)
            instr.opcode = IN;

        else if((cmd >> 2) == OUT)
            instr.opcode = OUT;

        else
        {
            fprintf(stderr, "Undefined command: %x", cmd);
            abort();
        }

        instr.opnd.rop = (cmd & REGMASK);
    }
    else
    {
        instr.opcode = (cmd >> 4);
        instr.opnd.ops.rd = (cmd >> 2) & REGMASK;
        instr.opnd.ops.rs = cmd & REGMASK;
    }

    return instr;
}

void execute_program(FILE *prog)
{
    unsigned command;
    struct reg_state_t regs[RLAST];
    for(int i = 0; i < RLAST; ++i)
        regs[i].init = 0;

    while (fscanf(prog, "%x", &command) == 1)
    {
        struct instr_t instr;
        unsigned char cmd = command & 0xff;
        assert(cmd == command);
        instr = decode_instr(cmd);
        execute_instr(regs, instr);
    }
}

int main(int argc, char **argv)
{
    FILE *prog;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <programm>\n", argv[0]);
        abort();
    }

    prog = fopen(argv[1], "r");
    if (NULL == prog)
    {
        fprintf(stderr, "Usage: %s <programm>\n", argv[0]);
        fprintf(stderr, "Where file with programm shall exist\n");
        abort();
    }

    execute_program(prog);

    fclose(prog);
}
