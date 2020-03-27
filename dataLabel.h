#ifndef DATALABEL_H
#define DATALABEL_H
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "regFile.h"

class DataObj
{
    public:
    DataObj()
        : isInteger(0), isString(0), isLabelAddress(0), isEmpty(0), intValue(0),
        strValue("")
    {}
    
    int intVal() const
    {
        return intValue;
    }

    int &intVal()
    {
        return intValue;
    }

    std::string strVal() const
    {
        return strValue;
    }

    std::string &strVal()
    {
        return strValue;
    }
    
    bool isStr() const
    {
        return isString;
    }

    bool & isStr()
    {
        return isString;
    }

    bool isEmp() const
    {
        return isEmpty;
    }

    bool & isEmp()
    {
        return isEmpty;
    }


    bool isInt() const
    {
        return isInteger;
    }

    bool & isInt()
    {
        return isInteger;
    }

    bool isLA() const
    {
        return isLabelAddress;
    }

    bool & isLA()
    {
        return isLabelAddress;
    }

    void printVal() const
    {
        if (isString)
        {
            for (int i = 0; i < this->strValue.size(); ++i)
            {
                std::cout << this->strValue;
            }
        }
        else if (isInteger || isLabelAddress)
        {
            std::cout << this->intValue;
        }
        std::cout << std::endl;
    }


    
        
    
private:
    bool isInteger;
    bool isString;
    bool isLabelAddress;
    bool isEmpty;
    
    int intValue;
    std::string strValue;
};

#endif
