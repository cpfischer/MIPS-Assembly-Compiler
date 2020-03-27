// Author: Caleb Fischer
// File  : mystring.h
#ifndef MYSTRING_H
#define MYSTRING_H
#include <iostream>
#include <limits>
#include <cmath>
#include <vector>
#include <string>
#include "regFile.h"

const int MAX_BUF = 1024;

//inputs a string and checks if the string is good
//bool inputString(char input[], std::vector<char> & textSeg);
bool inputLineCheck(std::string & input, std::string & copy, bool read);

bool inputString(std::string & input, std::string & textSeg, bool read);

//counts the length of an array
int str_len(char []);

//combines two strings
void str_cat(char [], char []);

//compares two strings, x must be the smaller array
bool str_cmp(char x[], char check[]);

//Copies an array y to x
void str_cpy(char x[], char y[]);

//cuts up a string into two arrays based on delimiters (punctuation or spaces)
//array y is the old one with x being the new
bool str_tok(char x[], char y[]);
void str_tok(std::string & x, std::string & y);

//Removes punctuation
void remove_punct(char x[]);

//Removes left spaces
void str_lstrip(char x[]);

void str_lstrip(std::string & x);

//checks what command was entered and goes into the right switch case
int operation(std::string & x, std::string & input, Reg r[]);

//returns an int based on correct register
int getReg(std::string & x, std::string & input);

//loads an int into a register
void loadImmediate(std::string & x, std::string & input, Reg r[]);

//adds two registers and stores value in a third
void add(std::string & x, std::string & input, Reg r[]);

//subtracts two registers and stores value in a third
void sub(std::string & x, std::string & input, Reg r[]);

//multiplies two registers and stores LO value in third
void mul(std::string & x, std::string & input, Reg r[]);

void syscall(Reg r[]);

//checks if x is an integer
bool isInt(std::string & x);

//converts x into an int
int getInt(std::string & x);

//prints x
void print(char x[]);

#endif
