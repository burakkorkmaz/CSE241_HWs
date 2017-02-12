/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   _mainTester.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 26 Kasım 2016 Cumartesi, 18:42
 */

#include "requiredIncs.h"

void testFunc(CPUProgramDyn myCPUProgram, const char* filename, int option)
{
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram[0] << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    //op +
    cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size()]) << endl;
    //op +=
    myCPUProgram += "MOV R2, #50";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    //op + <<
    CPUProgramDyn myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    cout << (myCPUProgram + myOtherCPUProgram) << endl;
    //op COMP --
    cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    --myOtherCPUProgram;
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    //op ()
    cout << myCPUProgram(5, 10) << endl;
    //error check
    cout << myCPUProgram[myCPUProgram.size()] << endl;
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    //////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv){
    //////////////////////////////////////////////////////////////////////////
    //command line parameters
    const char* filename = argv[1];
    int option = atoi(argv[2]);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    //Testing class CPUProgramDyn
    CPUProgramDyn myProg(option);
    testFunc(myProg, filename, option);
    // Test again	
    testFunc(myProg, filename, option);
    // Test with a copy
    CPUProgramDyn myProgCopy(myProg);	
    testFunc(myProgCopy, filename, option);
    //////////////////////////////////////////////////////////////////////////

    return 0;
}