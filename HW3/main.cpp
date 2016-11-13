/* 
 * File:   main.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 26 Ekim 2016
 */

#include <iostream>

#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

/*
 * MAIN FUNCTION
 */
int main(int argc, char** argv) {
    //CLASS DECLARATINS
    CPU myCPU;
    CPUProgram myCPUProg;
    
    cout << "*********************************************\n"
            << "   main.ccp\n   Resource File Name: " << argv[1] << endl
            << "   Execution Method: " << argv[2] << endl
            << "*********************************************\n";
    
    if(!myCPUProg.readLine(argv[1]))
        return myCPUProg.INVALID;
    myCPU.chooseOption(argv[2]);

    myCPU.setFSize(myCPUProg.size());//sends value of file size to myCPU class


    while (!myCPU.halted()) {

        myCPU.isLastExec(myCPUProg.size());
        string instruction = myCPUProg.getLine(myCPU.getPC());
        myCPU.execute(instruction);

    }

    return 0;
}
/*
 * END OF MAIN FUNCTION
 */

