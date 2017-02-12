/* 
 *      Gebze Techincal University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 5
 */
/* 
 * File:   _mainTester.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 13 Kasım 2016 Pazar, 19:35
 */

#include "requiredIncs.h"

int main(int argc, char** argv){
//////////////////////////////////////////////////////////////////////////
//command line parameters
    
const char* filename = argv[1];
int option = atoi(argv[2]);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//Testing class CPUProgram
//op []
CPUProgram myCPUProgram(option);
myCPUProgram.ReadFile(filename);
cout << myCPUProgram[0] << endl;
cout << myCPUProgram[myCPUProgram.size() - 1] << endl;

//op +
cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() - 1]) << endl;
//
//op +=
myCPUProgram += "MOV R2, #50";
cout << myCPUProgram[myCPUProgram.size() - 1] << endl;

//op + <<
CPUProgram myOtherCPUProgram(option);
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
return 0;
}