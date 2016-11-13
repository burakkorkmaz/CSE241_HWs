/* 
 * File:   CPU.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 26 Ekim 2016 
 */

#ifndef CPU_H
#define CPU_H


#include <iostream>
#include <string>
#include <cmath>        //for pow function 
#include <vector>

using namespace std;

class CPU {
public:
    //constructors
    CPU();
    //Naming constants
    const static int MAX_REG = 5;
    const static int MAX_LINE = 200;
    const static int MAX_TOKEN = 10;
    const static int DECIMAL = 10;
    const static int INVALID = -1;

    //Getter Functions
    int getReg(int regID) const;
    int getPC() const;
    int getOption() const;
    //Setter Functions
    void setReg(int regID, int regValue);
    void setPC(int lineNumber);
    void setFSize(int size);
    void chooseOption(string argv);

    void print() const;
    void execute(string line);
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
    int process();
    int strToInt(string token);
    int checkReg(string reg);
    int parseStr(const string line);
    void option();

    //instructions
    bool MOV();
    bool ADD();
    bool SUB();
    bool PRN();
    int JMP(int method = 0);
    void HLT();
};

#endif /* CPU_H */

