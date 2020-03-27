// Author: Caleb Fischer
// File  : mystring.cpp
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <string>
#include "mystring.h"
#include "regFile.h"

bool inputString(std::string & input, std::string & copy, bool read)
{
    if (read) return 1;
    
    copy.clear();
    std::getline(std::cin, input);
    if (std::cin.eof()) return 0;
    if (std::cin.fail() || std::cin.bad())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    str_lstrip(input);
    if (input.length() > 0)
    {
        copy = input;
        return 1;
    }
    else
    {
        return 0;
    }
}


bool inputLineCheck(std::string & input, std::string & copy, bool read)
{
    if (read) return 1;
    
    copy.clear();
    if (std::cin.eof()) return 0;
    if (std::cin.fail() || std::cin.bad())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    str_lstrip(input);
    if (input.length() > 0 && input[0] != '#')
    {
        copy = input;
        return 1;
    }
    else
    {
        return 0;
    }
}


void str_tok(std::string & x, std::string & input)
{
    x.clear();

    //strips left spaces of y
    str_lstrip(input);
    
    //copies y until a delimiter is found
    for (int i = 0; i <= input.length(); ++i)
    {
        if (input[i] == ' ' || input[i] == ','
            || input[i] == '\0' || input[i] == '\t' || int(input[i]) <= 32
            || i == input.length() || input[i] == '(' || input[i] == ')')
        {
            //std::cout << "i: " << i << '\n';
            x = input.substr(0, i);
            //std::cout << "x: " << x << std::endl;
            input.erase(0, i + 1);
            str_lstrip(input);
            //std::cout << " input: " << input << '\n';
            break;
        }
    }
}



void str_lstrip(std::string & x)
{
    int startInt;

    //if x[i]  == ' ', then i gets moved up
    for (int i = 0; i < x.length(); ++i)
    {
        if (!(x[i] == ' ') && !(x[i] == '\t') && !(int(x[i]) == 9)
            && !(int(x[i]) <= 32))
        {
            if (i > 0) x.erase(0, i);
            break;
        }
    }
}


bool isInt(std::string & x)
{
    //57 -> 48
    if (x[0] == 45)
    {
        if (x[1] <= 57 && x[1] >= 48) return 1;
    }
    else if (x[0] <= 57 && x[0] >= 48) return 1;
}

int getInt(std::string & x)
{
    //45 is minus;
    int returnInt = 0;
    bool isNeg = 0;

    int place = x.length();
    --place;
    
    if (x[0] == 45)
    {
        isNeg = 1;
    }

    //if isNeg = 1, minus is not counted
    for (int i = place; i >= isNeg; --i)
    {
        returnInt += (x[i] - 48) * pow(10, (place - i));
    }

    if (isNeg) returnInt *= -1;

    return returnInt;
}
