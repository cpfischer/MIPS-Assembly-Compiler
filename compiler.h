#ifndef COMPILER_H
#define COMPILER_H
#include <iostream>
#include <vector>
#include <string>
#include "regFile.h"
#include "dataLabel.h"

void initOp(std::map < unsigned int, std::string > & op);

int getOpNumber(std::string & x,
                std::map < unsigned int, std::string > op);

int operation(std::string & input, std::vector<Reg> & r,
              Reg & HI, Reg & LO, std::map < unsigned int, std::string > & op,
              const std::vector<Reg> & labels, unsigned int & labelCount,
              unsigned int & pc, unsigned int & dc,
              std::map < unsigned int, DataObj > & data,
              std::map < unsigned int, int > & stack, bool & endLoop);

bool isReg(std::string & x, std::vector<Reg> & r);

int getReg(std::string & x, std::string & input, std::vector<Reg> & r);

bool isLabel(std::string & x, const std::vector<Reg> & labels,
             const unsigned int & labelCount);

int getLabel(std::string & x, std::string & input,
             const std::vector<Reg> & labels,
             const unsigned int & labelCount);

void add(std::string & x, std::string & input, std::vector<Reg> & r);

void addu(std::string & x, std::string & input, std::vector<Reg> & r);

void addi(std::string & x, std::string & input, std::vector<Reg> & r);

void addiu(std::string & x, std::string & input, std::vector<Reg> & r);

void sub(std::string & x, std::string & input, std::vector<Reg> & r);

void subu(std::string & x, std::string & input, std::vector<Reg> & r);

void subi(std::string & x, std::string & input, std::vector<Reg> & r);

void subiu(std::string & x, std::string & input, std::vector<Reg> & r);

void mul(std::string & x, std::string & input, std::vector<Reg> & r);

void mult(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO);

void multu(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO);

void div(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO);

void divu(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI, Reg & LO);

void mfhi(std::string & x, std::string & input, std::vector<Reg> & r, Reg & HI);

void mflo(std::string & x, std::string & input, std::vector<Reg> & r, Reg & LO);

void move(std::string & x, std::string & input, std::vector<Reg> & r);

void beq(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void bne(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void bgt(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void bge(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void blt(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void ble(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

void seq(std::string & x, std::string & input, std::vector<Reg> & r);

void sne(std::string & x, std::string & input, std::vector<Reg> & r);

void sgt(std::string & x, std::string & input, std::vector<Reg> & r);

void sge(std::string & x, std::string & input, std::vector<Reg> & r);

void slt(std::string & x, std::string & input, std::vector<Reg> & r);

void sle(std::string & x, std::string & input, std::vector<Reg> & r);

void abs(std::string & x, std::string & input, std::vector<Reg> & r);

void seqi(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void snei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void sgti(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void sgei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void slti(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void slei(std::string & x, std::string & input, std::vector<Reg> & r,
          bool isPass);

void lw(std::string & x, std::string & input, std::vector<Reg> & r,
        std::map < unsigned int, DataObj > & data,
        std::map < unsigned int, int > & stack,
        const std::vector<Reg> & labels, const unsigned int & labelCount);

void sw(std::string & x, std::string & input, std::vector<Reg> & r,
        unsigned int & dc,
        std::map < unsigned int, DataObj > & data,
        std::map < unsigned int, int > & stack,
        const std::vector<Reg> & labels, const unsigned int & labelCount);

void la(std::string & x, std::string & input, std::vector<Reg> & r,
        const std::vector<Reg> & labels, const unsigned int & labelCount,
        bool isPass);

void li(std::string & x, std::string & input, std::vector<Reg> & r);

void j(std::string & x, std::string & input, std::vector<Reg> & r,
       const std::vector<Reg> & labels, const unsigned int & labelCount,
       unsigned int & pc);

void jr(std::string & x, std::string & input, std::vector<Reg> & r,
        const std::vector<Reg> & labels, unsigned int & labelCount,
        unsigned int & pc);

void jal(std::string & x, std::string & input, std::vector<Reg> & r,
         const std::vector<Reg> & labels, unsigned int & labelCount,
         unsigned int & pc);

bool syscall(std::string & x, std::string & input, std::vector<Reg> & r,
             unsigned int & dc,
             std::map < unsigned int, DataObj > & data,
             std::map < unsigned int, int > & stack, bool & endLoop);

#endif
