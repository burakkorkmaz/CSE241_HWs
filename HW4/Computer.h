/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 4
 * 
 */

/* 
 * File:   Computer.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 06 Kasım 2016 Pazar, 00:51
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer {
public:
    //Contructor
    Computer();
    Computer(int option);
    Computer(CPU myCpu, CPUProgram myCpuProg, Memory myMem, int option);
    //Getter Functions
    CPU getCPU() const;
    CPUProgram getCPUProgram() const;
    Memory getMemory() const;
    //setter Funtions
    void setCPU(CPU otherCPU);
    void setCPUProgram(CPUProgram other);
    void setMemory(Memory otherMem);

    void execute();
private:
    CPU myCPU;
    CPUProgram myCPUProg;
    Memory myMemory;
    int opt;
};

#endif /* COMPUTER_H */

