/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   CPU.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 26 Kasım 2016 Cumartesi, 18:44
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include <cmath>        //for pow function 
#include <vector>
#include "Memory.h"

using namespace std;

class CPU {
public:
    //constructors
    CPU();
    CPU(int option);
    //Naming constants
    const static int MAX_REG = 5;
    const static int MAX_LINE = 200;
    const static int MAX_TOKEN = 10;
    const static int DECIMAL = 10;
    const static int INVALID = -1;
    const static int MAX_MEM = 50;


    //Getter Functions
    int getReg(int regID) const;
    int getPC() const;
    int getOption() const;
    //Setter Functions
    void setReg(int regID, int regValue);
    void setPC(int lineNumber);
    void setFSize(int size);
    void chooseOption(int argv);

    void print() const;
    void execute(string line, Memory& myMem);
    bool halted();
    void isLastExec(int fileSize);
private:
    int PC; //Program Counter
    int opt; //execution method as 0 or 1
    int warning; // warns if option is not 0 or 1
    int parseSize; //number of tokens in parseArr
    int fSize; // total file lines
    int status; //return value of process(...) -> 0 or line numbr if valid
    //used for halted()
    int halt;
    bool error;
    bool lastExec;

    vector<int> regstr; //registers as vector
    string parseArr[MAX_TOKEN];

    //functions will be used by execute(...) function
    int process(Memory& mem);
    int strToInt(string token);
    int checkReg(string reg);
    int checkAddr(string Address);
    int parseStr(const string line);
    void option();

    //instructions
    bool MOV();
    bool MOV(unsigned int memAr[]);
    bool ADD();
    bool ADD(unsigned int memAr[]);
    bool SUB();
    bool SUB(unsigned int memAr[]);
    bool PRN(unsigned int memAr[]);
    int JMP(int method = 0);
    int JPN();
    void HLT(Memory& memory);
};
#endif /* CPU_H */

