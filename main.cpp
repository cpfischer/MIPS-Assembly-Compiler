//Author: Caleb Fischer
//File: a03q06.cpp
#include <iostream>
#include <limits>
#include <cmath>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "mystring.h"
#include "regFile.h"
#include "compiler.h"
#include "dataLabel.h"

bool pRegisters = 1;
bool pText = 1;
bool pData = 1;
bool pLabels = 1;


void initRegs(std::vector<Reg> & r)
{
    for (int i = 0; i < 32; ++i)
    {
        Reg x;
        r.push_back(x);
    }
    r.shrink_to_fit();
    
    r[0].name() = "$zero";
    r[1].name() = "$at";
    r[2].name() = "$v0";
    r[3].name() = "$v1";
    r[4].name() = "$a0";
    r[5].name() = "$a1";
    r[6].name() = "$a2";
    r[7].name() = "$a3";
    r[8].name() = "$t0";
    r[9].name() = "$t1";
    r[10].name() = "$t2";
    r[11].name() = "$t3";
    r[12].name() = "$t4";
    r[13].name() = "$t5";
    r[14].name() = "$t6";
    r[15].name() = "$t7";
    r[16].name() = "$s0";
    r[17].name() = "$s1";
    r[18].name() = "$s2";
    r[19].name() = "$s3";
    r[20].name() = "$s4";
    r[21].name() = "$s5";
    r[22].name() = "$s6";
    r[23].name() = "$s7";
    r[24].name() = "$t8";
    r[25].name() = "$t9";
    r[26].name() = "$k0";
    r[27].name() = "$k1";
    r[28].name() = "$gp";
    r[29].name() = "$sp";
    r[30].name() = "$s8";
    r[31].name() = "$ra";
    
    r[0].val() = 0;
    r[29].val() = 0x7FFFFFFF;
}


void saveFile(unsigned int pc, std::map < unsigned int, std::string > text)
{
    std::string fileName;
    std::cout << "\t" << "INPUT FILENAME: ";
    std::cin >> fileName;
    
    std::ofstream f(fileName, std::ios::out);
    for (unsigned int i = 0x004000000; i <= pc; i += 0x4)
    {
        f << text[i] << '\n';
    }
}


std::string loadFile(bool & readFile, std::string & fileName)
{
    std::cout << "\n\t" << "INPUT FILENAME: ";
    std::cin >> fileName;
    readFile = 1;
    return fileName;
}


bool labelCheck(std::string & input,
                std::vector<Reg> & labels, unsigned int & labelCount,
                const unsigned int pc)
{
    std::string x;
    std::string inputClone = input;
    str_tok(x, inputClone);
    
    if (x[x.length() - 1] == ':')
    {
        //cut and store label from input
        str_tok(x, input);
        Reg label;
        x.erase(x.begin() + x.length() - 1);
        label.name() = x;
        label.val() = pc;
        labels.push_back(label);
        ++labelCount;
        
        return 1;
    }
    return 0;
}


//0 = help, 1 = saveFile, 2 = loadFile, 3 = write in text, 4 = write in data
void execCommand(const int i, unsigned int & pc,
                 const std::map < unsigned int, std::string > text,
                 bool & writeText, bool & writeData, bool & readFile,
                 std::string & fileName, bool & endLoop)
{
    switch(i)
    {
        case 0:
            std::cout << "commands: \ntype save to save your file" << std::endl;
            std::cout << "load to load a file" << "then type thefile name" << std::endl;
            std::cout << ".text to edit the text segment" << std::endl;
            std::cout << ".data to edit the data segment"
                      << "\npregisters to print registers" << std::endl;
            std::cout << "t\nptext to print" << std::endl;
            std::cout << "text seg\npdata for data seg\nplabels to";
            std::cout << "print labels and addresses\ntype run to run your program"
                      << "(not loaded files)" << "\nexit to exit program" << std::endl;  
            break;
        case 1:
            saveFile(pc, text);
            break;
        case 2:
            loadFile(readFile, fileName);
            break;
        case 3:
            writeText = 1;
            writeData = 0;
            break;
        case 4:
            writeText = 0;
            writeData = 1;
            break;
        case 5:
            pRegisters = !pRegisters;
            break;
        case 6:
            pText = !pText;
            break;
        case 7:
            pData = !pData;
            break;
        case 8:
            pLabels = !pLabels;
            break;
        case 9:
            pc = 0x004000000;
            break;
        case 10:
            endLoop = 1;
            break;
    }
}



void initCommands(std::string command[])
{
    command[0] = "?";
    command[1] = "save";
    command[2] = "load";
    command[3] = ".text";
    command[4] = ".data";
    command[5] = "pregisters";
    command[6] = "ptext";
    command[7] = "pdata";
    command[8] = "plabels";
    command[9] = "run";
    command[10] = "exit";
}



bool commandCheck(std::string & input, const std::string command[],
                  unsigned int pc, std::map < unsigned int, std::string > text,
                  bool & writeText, bool & writeData, bool & readFile,
                  std::string & readName, bool & endLoop)
{
    std::string x;
    std::string inputClone = input;
    str_tok(x, inputClone);

    int commandCount = 11;
    for (int i = 0; i < commandCount; ++i)
    {
        if (x.compare(command[i]) == 0)
        {
            //ERROR make it to where command must be typed first
            execCommand(i, pc, text, writeText, writeData, readFile, readName,
                        endLoop);
            return 1;
        }
    }
    return 0;
}


//Prints the registers and all current commands in the text segment
void printRegisters(const unsigned int pc,
                    const std::vector<Reg> & r, const Reg & HI, const Reg & LO)
{
    std::cout << "\n==========================================================================="
              << "===============================\n"
              << "REGISTERS\n"
              << "==========================================================================="
              << "===============================" << std::endl;
              
    std::cout << "$PC: " << std::hex << pc << '\t'
              << HI.name() << ": " << HI.val() << '\t'
              << LO.name() << ": " << LO.val() << '\t' << std::endl;

    //print registers
    for (int i = 0; i < 8; ++i)
    {
        //cout value to 8 digits max
        std::cout << "R" << i << " (" << r[i].name() << "): " << std::dec << r[i].val() % 10000000 << "\t\t"
                  << "R" << i << " (" << r[i + 8].name() << "): " << std::dec << r[i + 8].val() % 10000000 << "\t\t"
                  << "R" << i << " (" << r[i + 16].name() << "): " << std::dec << r[i + 16].val() % 10000000 << "\t\t"
                  << "R" << i << " (" << r[i + 24].name() << "): " << std::dec << r[i + 24].val() % 10000000 << "\t\t"
                  << std::endl;                                                     
    }
    std::cout << "==========================================================================="
              << "===============================" << std::endl;
}
    
    
void printText(const unsigned int pc,
               std::map < unsigned int, std::string > text)
{
    std::cout << "\n==========================================================================="
              << "===============================\n"
              << "TEXT SEGMENT\n"
              << "==========================================================================="
              << "===============================" << std::endl;
    for (int i = 0x004000000; i <= pc; i += 0x4)
    {
        std::cout << '[' << std::hex << i << "]\t" << text[i] << std::endl;
    }
    std::cout << "==========================================================================="
              << "===============================" << std::endl;
}


void printData(const unsigned int dc,
               std::map < unsigned int, DataObj > & data)
{
    std::cout << "\n==========================================================================="
              << "===============================\n"
              << "DATA SEGMENT\n"
              << "==========================================================================="
              << "===============================" << std::endl;
    for (int i = 0x10000000; i <= dc; i += 0x4)
    {
        std::cout << '[' << std::hex << i << "]\t";
        if (data[i].isInt() || data[i].isLA())
        {
            std::cout << data[i].intVal();
        }
        else if (data[i].isStr())
        {
            std::cout << data[i].strVal();
        }
        else if (data[i].isEmp())
        {
            std::cout << "00000000";
        }
        std::cout << std::endl;
    }
    std::cout << "==========================================================================="
        << "===============================" << std::endl;
}


void printLabels(std::vector<Reg> & labels, unsigned int & labelCount)
{
    std::cout << "\n==========================================================================="
              << "===============================\n"
              << "LABELS\n"
              << "==========================================================================="
              << "===============================" << std::endl;
    for (int i = 0; i < labelCount; ++i)
    {
        std::cout << labels[i].name() << ": " << std::hex <<
            labels[i].val() << std::endl;
    }
    std::cout << "==========================================================================="
        << "===============================" << std::endl;
}




bool writeTextSeg(std::string & input, std::string & copy,
                  bool & read, std::vector<Reg> & r,
                  Reg & HI, Reg & LO,
                  std::map < unsigned int, std::string > & text,
                  std::map < unsigned int, std::string > & op,
                  std::vector<Reg> & labels, unsigned int & labelCount,
                  unsigned int & pc,
                  unsigned int & dc,
                  std::map < unsigned int, DataObj > & data,
                  std::map < unsigned int, int > & stack,
                  bool & endLoop)
{
    //std::string x;
    //std::cout << "text: " << text[pc] << "\n length: " << text[pc].length() << '\n';
        
    //make sure input is good;
    if (text[pc].compare("EOF") == 0)
    {
        std::cout << "EOF Error. Must use syscall 10 to exit.";
        return endLoop = 1;
    }
            
    if (text[pc].length() > 0)
    {
        input = text[pc];
        read = 1;
    }
    else if (text[pc].length() <= 0)
    {
        //saves input into memory. If invalid, pc -= 0x4
        //text[pc] = copy;
        read = 0;
    }
    //std::cout << "pc: " << pc << " text: " << text[pc] << '\n';
    //std::cout << " input: " << input << '\n';
    
    str_lstrip(input);
    //check for labels
    labelCheck(input, labels, labelCount, pc);
    
    if (operation(input, r, HI, LO, op, labels, labelCount, pc,
                  dc, data, stack, endLoop) == -1)
    {}
    else
    {
        //ERROR
    }

    //printRegisters(pc, r, HI, LO);
     //printText(pc, text);
    // printData(dc, data);
    // printLabels(labels, labelCount);
    pc += 0x4;
    
}


void dataStoreWord(std::string & x, std::string & input,
                   unsigned int & dc,
                   std::map < unsigned int, DataObj > & data,
                   std::vector<Reg> & labels, unsigned int & labelCount)
{
    while (x.length() > 0)
    {
        bool isLabel = 0;
        for (int i = 0; i < labelCount; ++i)
        {
            if (x.compare(labels[i].name()) == 0)
            {
                isLabel = 1;
                break;
            }
        }

        if (isLabel)
        {
            while (x.length() > 0)
            {
                DataObj newObj;
                newObj.isLA() = 1;
                
                for (int i = 0; i < labelCount; ++i)
                {
                    if (x.compare(labels[i].name()) == 0)
                    {
                        newObj.intVal() = labels[i].val();
                    }
                    else
                    {
                        std::cout << "ERROR: Label undefined!\n";
                        //ERROR Label undefined
                    }
                }
                data[dc] = newObj;
                dc += 0x4;
                str_tok(x, input);
            }
        }
        else
        {
            while (x.length() > 0)
            {
                DataObj newObj;
                newObj.isInt() = 1;
            
                while (x.length() > 0)
                {
                    int i = getInt(x);
                    newObj.intVal() = i;
                    data[dc] = newObj;
                    dc += 0x4;
                    str_tok(x, input);
                }
            }
        }
    }
    
    //make sure bytes are properly allocated
    while (dc % 16 != 0)
    {
        DataObj newObj;
        newObj.isEmp() = 1;
        data[dc] = newObj;
        dc += 4;
    }
}


void dataStoreString(std::string & x, std::string & input,
                     unsigned int & dc,
                     std::map < unsigned int, DataObj > & data)
{
    while (input.length() > 0)
    {
        DataObj newObj;
        newObj.isStr() = 1;
        //tok with quotes
        str_lstrip(input);
        int start = -1;
        int end = -1;
        for (int i = 0; i < input.length(); ++i)
        {
            if (int(input[i]) == 34 && start == -1)
            {
                start = i;
            }
            else if (int(input[i]) == 34 && start != -1 && end == -1)
            {
                end = i;
            }
        }
            
        if (start == -1 || end == -1)
        {
            //std::cout << "ERROR: Need opening/close quotation marks\n";
            break;
        }

        for (int i = 1; i < end; ++i)
        {
            if (input[i] == 92)
            {
                if (input [i + 1] == 'n')
                {
                    newObj.strVal() = newObj.strVal() + '\n';
                    ++i;
                }
                else if (input [i + 1] == 't')
                {
                    newObj.strVal() = newObj.strVal() + '\t';
                    ++i;
                }
                else
                {
                    newObj.strVal() = newObj.strVal() + input[i];
                }
            }
            else
            {
                newObj.strVal() = newObj.strVal() + input[i];
            }
        }
        input.erase(start, end + 1);

        data[dc] = newObj;
        dc += 0x4;
    }

    //make sure bytes are properly allocated
    while (dc % 16 != 0)
    {
        DataObj newObj;
        newObj.isEmp() = 1;
        data[dc] = newObj;
        dc += 4;
    }
}


void storeVal(std::string & x, std::string & input,
              unsigned int & dc,
              std::map < unsigned int, DataObj > & data,      
              std::vector<Reg> & labels, unsigned int & labelCount)
{
    if (x.compare(".word") == 0)
    {
        str_tok(x, input);
        dataStoreWord(x, input, dc, data, labels, labelCount);
    }
    else if (x.compare(".asciiz") == 0)
    {
        dataStoreString(x, input, dc, data);
    }
    else
    {
        //ERROR
    }
}



bool dataLabelCheck(std::string & x, std::string & input,
                    unsigned int & dc,
                    std::map < unsigned int, DataObj > & data,
                    std::vector<Reg> & labels, unsigned int & labelCount)
{
    str_tok(x, input);
    
    if (x[x.length() - 1] == ':' && x[0] != '.')
    {
        //store into data segment
        //cut and store label from input
        Reg dlabel;
        //remove semicolon
        x.erase(x.begin() + x.length() - 1);
        dlabel.name() = x;
        dlabel.val() = dc;
        labels.push_back(dlabel);
        ++labelCount;

        str_tok(x, input);
        storeVal(x, input, dc, data, labels, labelCount);    
    }
    else if (x[0] == '.')
    {
        storeVal(x, input, dc, data, labels, labelCount);    
    }
    else
    {
        //ERROR
    }
    
    return 0;
}


void writeDataSeg(std::string & input, std::string & copy, bool & read,
                  unsigned int & dc,
                  std::map < unsigned int, DataObj > & data,
                  std::vector<Reg> & labels, unsigned int & labelCount)
{
    std::string x;

    dataLabelCheck(x, input, dc, data, labels, labelCount);
}


int main()
{
    //PROGRAM COUNTER
    unsigned int pc = 0x004000000;
    unsigned int pcMax = pc;
    std::map < unsigned int, std::string > text;
    std::map < unsigned int, std::string > printableText;
    
    //stack stores integers
    std::map < unsigned int, int > stack;
    
    //Data Counter for data seg
    unsigned int dc = 0x10000000;
    std::map < unsigned int, DataObj > data;
    std::map < unsigned int, DataObj > printableData;

    unsigned int count = 0;
    
    std::vector<Reg> labels;
    unsigned int labelCount = 0;

    std::string command[11];
    initCommands(command);
// for (unsigned int i = 0x00400000; i < 0x10000000; ++i)
    // {
    //     std::cout << "i: " << std::hex << i << '\n';
    //     text[count] = i;
    //     ++count;
    // }

    //INITIALIZE REGISTERS
    //Make register array
    std::vector<Reg> r;
    initRegs(r);

    //special registers HI and LO
    Reg HI;
    HI.name() = "$HI";
        
    Reg LO;
    LO.name() = "$LO";
        
    //operations and opCodes
    std::map < unsigned int, std::string > op;
    initOp(op);

    //check if writing in text seg or data seg
    bool writeText = 1;
    bool writeData = 0;
    bool endLoop = 0;
    bool readFile = 0;
    bool loadData = 0;
    bool loadText = 1;
            
    //for loading files
    std::string fileName;
    while (!endLoop)
    {
        //check if pc, dc, or sp are out of bounds
        if (pc >= 0x10000000) {}//throw error
        
        //printRegisters(pc, r, HI, LO);
        //printText(pc, text);
        //printData(dc, data);
        //printLabels(labels, labelCount);
        std::string input;
        std::string copy;
        bool read = 0;
 
        if (readFile)
        {
            //first load labels and data segment
            std::ifstream f(fileName, std::ios::in);
            while (std::getline(f, input))
            {
                        
                std::string x;
                // if (f.eof()) break;
                // f >> input;
                
                str_lstrip(input);
                
                if(inputLineCheck(input, copy, read))
                {                    
                    str_tok(x, copy);
                    if (x.compare(".data") == 0)
                    {
                        //std::cout << "I AM AT DATA SEGMENT";
                        loadText = 0;
                        loadData = 1;
                    }
                    
                    if (loadText)
                    {
                        printableText[pc] = input;
                        labelCheck(input, labels, labelCount, pc);
                        text[pc] = input;
// std::cout << "text: " << std::hex << pc << "   " << text[pc]
                        //           << std::endl;
                        pc += 0x4;
                        if (pc > pcMax)
                        {
                            pcMax = pc;
                        }
                    }
                    else if (loadData)
                    {
                        //std::cout << "HERE";
                        writeDataSeg(input, copy, read, dc, data, labels,
                                     labelCount);
                    }
                }
                //next, execute text seg
            }
            text[pc] = "EOF";
            //printRegisters(pc, r, HI, LO);
            //printText(pc, text);
            //printData(dc, data);
            //printLabels(labels, labelCount);
        
            pc = 0x004000000;
            while(!endLoop)
            {
                writeTextSeg(input, copy, read, r, HI, LO,
                             text, op, labels, labelCount, pc,
                             dc, data, stack, endLoop);
            }
            endLoop = 1;
        }
        
        
        if (pRegisters) { printRegisters(pc, r, HI, LO); }
        if (pLabels) { printLabels(labels, labelCount); }
        if (pText) { printText(pcMax, printableText); }
        if (pData) { printData(dc, data); }
            
        
        if (writeText && !readFile)
        {
            if (pc > pcMax)
            {
                pcMax = pc;
            }

            std::cout << "TEXT: " << std::hex << pc <<  ">>> ";
            if(inputString(input, copy, read))
            {
                
                if(!commandCheck(input, command, pc, text, writeText,
                                 writeData, readFile, fileName, endLoop))
                {
                    printableText[pc] = input;
                    writeTextSeg(input, copy, read, r, HI, LO,
                                 text, op, labels, labelCount, pc,
                                 dc, data, stack, endLoop);
                }
                   
            }
        }
        else if (writeData && !readFile)
        {
            if (pc > pcMax)
            {
                pcMax = pc;
            }
            
            // if (pRegisters) printRegisters(pc, r, HI, LO);
            // if (pLabels) printLabels(labels, labelCount);
            // if (pText) printText(pcMax, printableText);
            // if (pData) printData(dc, data);
            
            std::cout << "DATA: " << std::hex << dc <<  ">>> ";
            if(inputString(input, copy, read))
            {
                
                if(!commandCheck(input, command, pc, text, writeText,
                                 writeData, readFile, fileName, endLoop))
                {
                    writeDataSeg(input, copy, read, dc, data, labels,
                                 labelCount);
                }
            }
        }
    }
    if (pRegisters) printRegisters(pc, r, HI, LO);
    if (pLabels) printLabels(labels, labelCount);
    if (pText) printText(pcMax, printableText);
    if (pData) printData(dc, data);
    
    if (!readFile)
    {
        std::cout << "Save File? (y / n)";
        char c;
        std::cin >> c;
        if (c == 'y') saveFile(pcMax, printableText);
    }
    return 0;
}
