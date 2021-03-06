/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 4
 * 
 */

/* 
 * File:   Computer.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 06 Kasım 2016 Pazar, 00:51
 */

#include "Computer.h"

//CONSTRUCTORS

Computer::Computer() : opt(0) {
    setCPU(myCPU);
    myCPU.setPC(1);
    setCPUProgram(myCPUProg);
    setMemory(myMemory);
}

Computer::Computer(int option) : opt(option) {

    setCPU(myCPU);
    myCPU.setPC(1);
    setCPUProgram(myCPUProg);
    setMemory(myMemory);
}

Computer::Computer(CPU myCpu, CPUProgram myCpuProg, Memory myMem, int option) {

    setCPU(myCpu);
    myCPU.setPC(1);
    setCPUProgram(myCpuProg);
    setMemory(myMem);
    myCpu.chooseOption(option);
    opt = option;
}

//Getter Functions

CPU Computer::getCPU() const{

    return myCPU;
}

CPUProgram Computer::getCPUProgram() const{

    return myCPUProg;
}

Memory Computer::getMemory() const{

    return myMemory;
}

//setter Funtions

void Computer::setCPU(CPU otherCPU) {

    myCPU = otherCPU;
}

void Computer::setCPUProgram(CPUProgram other) {

    myCPUProg = other;

}

void Computer::setMemory(Memory otherMem) {

    myMemory = otherMem;
}

/**
 * Executes each line as using other class members
 */
void Computer::execute() {


    myCPU.chooseOption(opt);

    myCPU.setFSize(myCPUProg.size()); //sends value of file size to myCPU class


    while (!myCPU.halted()) {

        myCPU.isLastExec(myCPUProg.size());
        string instruction = myCPUProg.getLine(myCPU.getPC() - 1);
        myCPU.execute(instruction, myMemory);

    }


}


