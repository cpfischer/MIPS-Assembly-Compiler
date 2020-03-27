#include <iostream>
#include <string>
#include <vector>
#include "compiler.h"
#include "mystring.h"
#include "regFile.h"
#include "dataLabel.h"

class CommandError
{};

void initOp(std::map < unsigned int, std::string > & op)
{
    op[0] = "add";
    op[1] = "addu";
    op[2] = "addi";
    op[3] = "addiu";
    op[4] = "sub";
    op[5] = "subu";
    op[6] = "subi";
    op[7] = "subiu";
    op[8] = "mul";
    op[9] = "mult";
    op[10] = "multu";
    op[11] = "div";
    op[12] = "divu";
    op[13] = "mfhi";
    op[14] = "mflo";
    op[15] = "move";
    op[16] = "beq";
    op[17] = "bne";
    op[18] = "bgt";
    op[19] = "bge";
    op[20] = "blt";
    op[21] = "ble";
    op[22] = "seq";
    op[23] = "sne";
    op[24] = "sgt";
    op[25] = "sge";
    op[26] = "slt";
    op[27] = "sle";
    op[28] = "abs"; //slti definied twice, replaced
    op[29] = "seqi";
    op[30] = "snei";
    op[31] = "sgti";
    op[32] = "sgei";
    op[33] = "slti";
    op[34] = "slei";
    op[35] = "lw";
    op[36] = "sw";
    op[37] = "la";
    op[38] = "li";
    op[39] = "j";
    op[40] = "jr";
    op[41] = "jal";
    op[42] = "syscall";
}


//total ops is the total num of operations in initialization
int getOpNumber(std::string & x,
                std::map < unsigned int, std::string > op)
{
    int totalOp = 43;
    if (!x.empty())
    {
        for (int i = 0; i < totalOp; ++i)
        {
            if (x.compare(op[i]) == 0) return i;
        }
    }
    return -1;
}

//extracts and executes correct operation
//x is token of input, and r is array of registers
int operation(std::string & input, std::vector<Reg> & r,
              Reg & HI, Reg & LO, std::map < unsigned int, std::string > & op,
              const std::vector<Reg> & labels, unsigned int & labelCount,
              unsigned int & pc, unsigned int & dc,
              std::map < unsigned int, DataObj > & data,
              std::map < unsigned int, int > & stack,
              bool & endLoop)
{
    //add map of strings for operators and loop compare through it
    std::string x;
    str_lstrip(input);
    int opNumber = -1;
 
    //x = first cut, input = rest
    //std::cout << "input: " << input << '\n';
    str_tok(x, input);
    //std::cout << " x: " << x <<'\n';
    
    opNumber = getOpNumber(x, op);
    //std::cout << "opNumber: " << std::dec << 32 << ' ' << opNumber << '\n';
//if operation is incorrect, throw error
    //if (opNumber == -1) throw CommandError;
    switch (opNumber)
    {
        //0, li; 1, add; 2, sub;
        case 0:
            add(x, input, r);
            break;
        case 1:
            addu(x, input, r);
            break;
        case 2:
            addi(x, input, r);
            break;
        case 3:
            addiu(x, input, r);
            break;
        case 4:
            sub(x, input, r);
            break;
        case 5:
            subu(x, input, r);
            break;
        case 6:
            subi(x, input, r);
            break;
        case 7:
            subiu(x, input, r);
            break;
        case 8:
            mul(x, input, r);
            break;
        case 9:
            mult(x, input, r, HI, LO);
            break;
        case 10:
            multu(x, input, r, HI, LO);
            break;
        case 11:
            div(x, input, r, HI, LO);
            break;
        case 12:
            divu(x, input, r, HI, LO);
            break;
        case 13:
            mfhi(x, input, r, HI);
            break;
        case 14:
            mflo(x, input, r, LO);
            break;
        case 15:
            move(x, input, r);
            break;
        case 16:
            beq(x, input, r, labels, labelCount, pc);
            break;
        case 17:
            bne(x, input, r, labels, labelCount, pc);
            break;
        case 18:
            bgt(x, input, r, labels, labelCount, pc);
            break;
        case 19:
            bge(x, input, r, labels, labelCount, pc);
            break;
        case 20:
            blt(x, input, r, labels, labelCount, pc);
            break;
        case 21:
            ble(x, input, r, labels, labelCount, pc);
            break;
        case 22:
            seq(x, input, r);
            break;
        case 23:
            sne(x, input, r);
            break;
        case 24:
            sgt(x, input, r);
            break;
        case 25:
            sge(x, input, r);
            break;
        case 26:
            slt(x, input, r);
            break;
        case 27:
            sle(x, input, r);
            break;
        case 28:
            abs(x, input, r);
            break;
        case 29:
            seqi(x, input, r, 0);
            break;
        case 30:
            snei(x, input, r, 0);
            break;
        case 31:
            sgti(x, input, r, 0);
            break;
        case 32:
            sgei(x, input, r, 0);
            break;
        case 33:
            slti(x, input, r, 0);
            break;
        case 34:
            slei(x, input, r, 0);
            break;
        case 35:
            lw(x, input, r, data, stack, labels, labelCount);
            break;
        case 36:
            sw(x, input, r, dc, data, stack, labels, labelCount);
            break;
        case 37:
            la(x, input, r, labels, labelCount, 0);
            break;
        case 38:
            li(x, input, r);
            break;
        case 39:
            j(x, input, r, labels, labelCount, pc);
            break;
        case 40:
            jr(x, input, r, labels, labelCount, pc);
            break;
        case 41:
            jal(x, input, r, labels, labelCount, pc);
            break;
        case 42:
            syscall(x, input, r, dc, data, stack, endLoop);
            break;
    }
    return 0;
}


bool isReg(std::string & x, std::vector<Reg> & r)
{
    //NO TOKENIZATION
    for (int i = 0; i < 32; ++i)
    {
        if (x.compare(r[i].name()) == 0) return 1;
    }
    //return invalid register error
    return 0;
}


int getReg(std::string & x, std::string & input, std::vector<Reg> & r)
{
    str_tok(x, input);
    //std::cout << "xGetReg: " << x << '\n';
    for (int i = 0; i < 32; ++i)
    {
        //std::cout << "i: " << i << std::endl;
        if (x.compare(r[i].name()) == 0) return i;
    }
    //return invalid register error
    return -1;
}


bool isLabel(std::string & x, const std::vector<Reg> & labels,
            const unsigned int & labelCount)
{
    for (int i = 0; i < labelCount; ++i)
    {                                                                                                 
        if (x.compare(labels[i].name()) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int getLabel(std::string & x, std::string & input,
             const std::vector<Reg> & labels,
             const unsigned int & labelCount)
{
    str_tok(x, input);
    for (int i = 0; i < labelCount; ++i)
    {                                                                                                 
        if (x.compare(labels[i].name()) == 0)
        {
            return i;
        }
    }
    return -1;
}


void bitConv(int x, int b[])
{
    for (int i = 0; i < 32; ++i)
    {
        b[i] = x % 2;
        x >>= 1;
    }
}


bool checkOverflow(int x, int y, int z)
{
    int b0[32] = {0};
    int b1[32] = {0};
    int b2[32] = {0};
    bitConv(x, b0);
    bitConv(y, b1);
    bitConv(z, b2);

    return (b0[32] | b1[32] == b2[32]);
}


//opNum 0
void add(std::string & x, std::string & input, std::vector<Reg> & r)
{
    //add sign bit.  if answ 32 bit != sign bit 1 + sign bit 2, error
    //bitwise |
    // if 0110 = 1001 & 1001   -8 + 1 1 | 0 = 1  so if answer != num | num, error
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);

    r[reg0].val() = r[reg1].val() + r[reg2].val();
    if (checkOverflow(r[reg1].val(), r[reg2].val(), r[reg0].val()))
    {
        //ERROR
    }
}


//opNum 1
void addu(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);

    r[reg0].val() = r[reg1].val() + r[reg2].val();
}


//opNum 2
void addi(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);

    r[reg0].val() = r[reg1].val() + i;
    if (checkOverflow(r[reg1].val(), i, r[reg0].val()))
    {
        //ERROR
    }
}

//opNum3
void addiu(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);    

    r[reg0].val() = r[reg1].val() + i;
}


//opNum 4
void sub(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    int reg2Copy = r[reg2].val() * -1;
        
    r[reg0].val() = r[reg1].val() - r[reg2].val();
    if (checkOverflow(r[reg1].val(), reg2Copy, r[reg0].val()))
    {
        //ERROR
    }
}


//opNum 5
void subu(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);

    r[reg0].val() = r[reg1].val() - r[reg2].val();
}


//opNum 6
void subi(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    i *= -1;
    
    r[reg0].val() = r[reg1].val() + i;
    if (checkOverflow(r[reg1].val(), i, r[reg0].val()))
    {
        //ERROR
    }
}


//opNum7
void subiu(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() - i;
}


//opNum8
void mul(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);

    r[reg0].val() = r[reg1].val() * r[reg2].val();
}

//FIX WITH HI
//opNum9
void mult(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    
    LO.val() = r[reg0].val() * r[reg1].val();
}


//opNum10
void multu(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    
    LO.val() = r[reg0].val() * r[reg1].val();
}


//opNum11
void div(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);

    HI.val() = r[reg0].val() % r[reg1].val();
    LO.val() = r[reg0].val() / r[reg1].val();
}


//opNum12
void divu(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    
    HI.val() = r[reg0].val() % r[reg1].val();
    LO.val() = r[reg0].val() / r[reg1].val();

}


//opNum13
void mfhi(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI)
{
    int reg0 = getReg(x, input, r);
    
    r[reg0].val() = HI.val();
}


//opNum14
void mflo(std::string & x, std::string & input, std::vector<Reg> & r, Reg & LO)
{
    int reg0 = getReg(x, input, r);
    
    r[reg0].val() = LO.val();
}


//opNum15
void move(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val();
}


//opNum16
void beq(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount, 
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to seqi for bool
        r[1].val() = 0;
        seqi(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() == r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum17
void bne(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to snei for bool
        r[1].val() = 0;
        snei(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() != r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum18
void bgt(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to seqi for bool
        r[1].val() = 0;
        sgti(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
    
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() > r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum19
void bge(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to sgei for bool
        r[1].val() = 0;
        sgei(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() >= r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum20
void blt(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to slti for bool
        r[1].val() = 0;
        slti(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() < r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum21
void ble(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    std::string inputCopy = input;
    str_tok(x, inputCopy); //snips first token
    str_tok(x, inputCopy); //gets second token
    if (isInt(x))
    {
        //if the second input is an int and not a reg, pass to slei for bool
        r[1].val() = 0;
        slei(x, input, r, 1);
        if (r[1].val() == 1)
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
    else
    {
        int reg0 = getReg(x, input, r);
        int reg1 = getReg(x, input, r);
        
        if (r[reg0].val() <= r[reg1].val())
        {
            j(x, input, r, labels, labelCount, pc);
        }
    }
}


//opNum22
void seq(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() == r[reg2].val();
}


//opNum23
void sne(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() != r[reg2].val();
}


//opNum24
void sgt(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() > r[reg2].val();
}


//opNum25
void sge(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() >= r[reg2].val();
}


//opNum26
void slt(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() < r[reg2].val();
}


//opNum27
void sle(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);
    int reg2 = getReg(x, input, r);
    
    r[reg0].val() = r[reg1].val() <= r[reg2].val();
}


//opNum28
void abs(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    int reg1 = getReg(x, input, r);

    if (r[reg1].val() < 0)
    {
        r[reg0].val() = r[reg1].val() * -1;
    }
    else
    {
        r[reg0].val() = r[reg1].val() * -1;
    }
}


//opNum29
void seqi(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    //reg = reg == int
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() == i;
}


//opNum30
void snei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);

    r[reg0].val() = r[reg1].val() != i;
}


//opNum31
void sgti(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() > i;
}


//opNum32
void sgei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() >= i;
}


//opNum33
void slti(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() < i;
}


//opNum34
void slei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass)
{
    int reg0;
    if (isPass)
    {
        reg0 = 1;
    }
    else
    {
        reg0 = getReg(x, input, r);
    }
    
    int reg1 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    
    r[reg0].val() = r[reg1].val() <= i;
}


//opNum34
void lw(std::string & x, std::string & input, std::vector<Reg> & r,
        std::map < unsigned int, DataObj > & data,
        std::map < unsigned int, int > & stack,
        const std::vector<Reg> & labels, const unsigned int & labelCount)
{
    //std::cout << "lw!\n";
    //lw $s0, offset($sp) --inside has address
    int reg0 = getReg(x, input, r);

    int reg1 = 1;
    std::string inputCopy = input;
    int offset = 0;
    str_tok(x, inputCopy);

    //std::cout << "x: " << x << std::endl;
    if (isInt(x))
    {
        //std::cout << "has an offset lw\n";
        offset = getInt(x);
        //std::cout << "offset: " << offset << '\n';
        str_tok(x, inputCopy);
    }
    
    if (isReg(x, r))
    {
        str_tok(x, input);
        //std::cout << "is a reg lw " << x << '\n';

        reg1 = getReg(x, input, r);
    }
    else if (isLabel(x, labels, labelCount))
    {
        //std::cout << "is a label lw \n";
        //loads label address into reg
        la(x, input, r, labels, labelCount, 1);
    }
    
    if (offset % 4 != 0)
    {
        //ERROR
        std::cout << "Offset must be divisible by 4!";
    }
    else
    {
        //ERROR Do i need this?
        //std::cout << "offset: " << offset << std::endl;
        //offset /= 4;
    }

    //sp check
    if (reg1 == 29 && r[29].val() + offset > 0x7FFFFFFF)
    {
        //ERROR
    }
    
    if ((r[reg1].val() + offset) % 4 == 0)
    {
        int oReg = r[reg1].val() + offset;
        if (oReg >= 0x10000000 && oReg < 0x10040000)
        {
            if (data[oReg].isInt())
            { 
                //std::cout << "dataLoaded: " << data[oReg].intVal()
                //          << std::endl;
                r[reg0].val() = data[oReg].intVal();
            }
            else
            {
                //ERROR
            }
        }
        else if (oReg <= 0x7FFFFFFF && oReg >= 0x7FFFF000)
        {
            r[reg0].val() = stack[oReg];
        }
        else
        {
            //ERROR
        }
    }
    else
    {
        //ERROR
    }
    // int i = getInt(x, input);
    
    // r[reg0].val() = oReg <= i;
}


//opNum36 FIX
void sw(std::string & x, std::string & input, std::vector<Reg> & r,
        unsigned int & dc,
        std::map < unsigned int, DataObj > & data,
        std::map < unsigned int, int > & stack,
        const std::vector<Reg> & labels, const unsigned int & labelCount)
{
    //printLabelsDebug(labels, labelCount);
    //std::cout << "sw!\n";    
    int reg0 = getReg(x, input, r);

    int reg1 = 1;
    std::string inputCopy = input;
    int offset = 0;
    str_tok(x, inputCopy);

    if (isInt(x))
    {
        offset = getInt(x);
        //twice to get past parenthesis
        str_tok(x, inputCopy);
    }
    
    if (isReg(x, r))
    {
        //std::cout << "is a reg sw \n";
        str_tok(x, input);
        reg1 = getReg(x, input, r);
        //std::cout << "reg: sw " << reg1 << '\n'; 
    }
    else if (isLabel(x, labels, labelCount))
    {
        //loads label address into reg
        la(x, input, r, labels, labelCount, 1);
    }
    
    if (offset % 4 != 0)
    {
        //ERROR
        std::cout << "Offset must be divisible by 4!";
    }
    else
    {
        //ERROR Do i need this?
        //std::cout << "offset: " << offset << std::endl;
        //offset /= 4;
        //CANT DO THIS
        //oReg += offset;
        //std::cout << "regVal: " << std::hex << oReg << std::endl;
    }

    //check if sp is out of bounds
    if (reg1 == 29 && r[29].val() + offset > 0x7FFFFFFF)
    {
        //ERROR
    }
    
    if ((r[reg1].val() + offset) % 4 == 0)
    {
        int oReg = r[reg1].val() + offset;
        //data seg
        if (oReg >= 0x10000000
            && oReg < 0x10040000)
        {
            if (oReg > dc) dc = oReg;
            DataObj newObj;
            newObj.intVal() = r[reg0].val();
            newObj.isInt() = 1;
            data[oReg] = newObj;
        }
        else if (oReg <= 0x7FFFFFFF && oReg >= 0x7FFFF000)
        {
            stack[oReg] = r[reg0].val();
        }
        else
        {
            //ERROR
        }
    }
    else
    {
        //ERROR
    }
}


//opNum37
void la(std::string & x, std::string & input, std::vector<Reg> & r,
        const std::vector<Reg> & labels, const unsigned int & labelCount,
        bool isPass)
{
    int reg0 = 1;
    if (!isPass)
    {
        reg0 = getReg(x, input, r);
    }

    int i = getLabel(x, input, labels, labelCount);

    if (i != -1)
    {
        r[reg0].val() = labels[i].val();
    }
//ERROR label not found
}



//opNum38
void li(std::string & x, std::string & input, std::vector<Reg> & r)
{
    int reg0 = getReg(x, input, r);
    str_tok(x, input);
    int i = getInt(x);
    r[reg0].val() = i;
}


//opNum39
void j(std::string & x, std::string & input, std::vector<Reg> & r,
       const std::vector<Reg> & labels, const unsigned int & labelCount,
       unsigned int & pc)
{
    int i = getLabel(x, input, labels, labelCount);
    pc = labels[i].val();
    pc -= 0x4;
//set $pc to label address
}


//opNum40 
void jr(std::string & x, std::string & input, std::vector<Reg> & r,
        const std::vector<Reg> & labels, unsigned int & labelCount,
        unsigned int & pc)
{
    bool isValid = 0;
    int reg0 = getReg(x, input, r);
    for (int i = 0; i < labelCount; ++i)
    {
        if (r[reg0].val() == labels[i].val())
        {
            isValid = 1;
        }
    }
    if (isValid)
    {
        pc = r[reg0].val();
        pc -= 0x4;
        //std::cout << "jumping to: " << std::hex << pc << std::endl;
    }
    else
    {
        //ERROR
    }
}


//opNum41
void jal(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc)
{
    //jal LABEL
    int i = getLabel(x, input, labels, labelCount);

    pc += 0x4;
    r[31].val() = pc;
    j(x, input, r, labels, labelCount, pc);
}


//opNum42 
bool syscall(std::string & x, std::string & input, std::vector<Reg> & r,
             unsigned int & dc,
             std::map < unsigned int, DataObj > & data,
             std::map < unsigned int, int > & stack,
             bool & endLoop)
{
    //CASE 9 == sbrk, memory allocation?
    if (r[2].val() == 1 || r[2].val() == 4 || r[2].val() == 5 || r[2].val() == 8
        || r[2].val() == 10 || r[2].val() == 9)
    {
        switch(r[2].val())
        {
            case 1:
                //print int
                std::cout << std::dec << r[4].val() << std::flush;
                break;
            case 4:
                //print string
                 if (r[4].val() >= 0x10000000 && r[4].val() < 0x10040000)
                 {
                     std::cout << data[r[4].val()].strVal() << std::flush;
                 }
                 else
                 {
                     //ERROR check if valid?
                 }
                //print string  CHECK IF IT IS A DATALABEL
                break;
            case 5:
                //read int
                std::cout << "Input integer: " << std::flush;
                std::cin >> r[2].val(); 
                break;
            case 8:
                //ERROR  dataStoreString
                //read string, store into a0???
                break;
            case 9:
                std::cout << "syscall 9 (sbrk) currently not implemented"
                          << std::endl;
                break;
            case 10:
                std::cout << "\nEND" << std::endl;
                endLoop = 1;
                return endLoop;
                break;
        }
    }
    else
    {
        //return ERROR
    }
    //set $pc to reg address
    //set ra to pc
}
