#ifndef REGFILE_H
#define REGFILE_H
#include <iostream>
#include <map>
#include <string>


class Reg
{
public:
    Reg()
        :regValue(0), regName("ERROR"), isLabelAddr(0)
    {}

    int val() const
    {
        return regValue;
    }

    int &val()
    {
        return regValue;
    }

    std::string &name()
    {
        return this->regName;
    }

    std::string name() const
    {
        return this->regName;
    }
    
private:
    std::string regName;
    int regValue;
    bool isLabelAddr;
};
   
#endif
