/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 4
 */

/* 
 * File:   Memory.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 06 Kasım 2016 Pazar, 00:50
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
using namespace std;

class Memory {
public:
    //Constructor
    Memory();
    Memory(int option);
    //Naming Constants
    const static int MAX_MEM = 50;
    const static int DECIMAL = 10;
    //getter Function
    unsigned int getMem(int address) const;
    unsigned int* getMemArr();
    //setter Function
    void setMem(int address, unsigned int value);

    void printAll();
private:
    int opt; //option
    //Memory Array
    unsigned int memArr[MAX_MEM];
};

#endif /* MEMORY_H */

