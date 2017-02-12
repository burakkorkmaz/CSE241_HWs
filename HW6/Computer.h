/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   Computer.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 13:02
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "requiredIncs.h"
using namespace CPUPDynamical;

class Computer {
  
public:
    //Contructor
    Computer();
    Computer(int option);
    Computer(CPU myCpu, CPUProgramDyn myCpuProg, Memory myMem, int option);
    //Getter Functions
    CPU& getCPU();
    CPUProgramDyn& getCPUProgram();
    Memory& getMemory();
    //setter Funtions
    void setCPU(CPU& otherCPU);
    void setCPUProgram(CPUProgramDyn& other);
    void setMemory(Memory& otherMem);

    void execute();
private:
    CPU myCPU;
    CPUProgramDyn myCPUProg;
    Memory myMemory;
    int opt;
};


#endif /* COMPUTER_H */

