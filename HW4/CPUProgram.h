/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 4
 * 
 */

/* 
 * File:   CPUProg.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 06 Kasım 2016 Pazar, 00:46
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

//INCLUDES
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class CPUProgram {
public:
    //Constructor
    CPUProgram();
    CPUProgram(int option);
    //Naming constants
    const static int MAX_LINE = 200;
    const static int INVALID = -1;

    void setFileSize(int size); //setter func.
    //!!ACCORDING TO PDF OF HOMEWORK , FIRST LETTER OF 
    // READFILE FUNCTION MUST BE UPPERCASE !!!!!!!!!!!!!!!!!!!!!
    bool ReadFile(string fileName);
    string getLine(int lineNumber);
    int size() const;

private:
    int index; // for fileStr
    int opt;
    int fileSize;
    string fileStr[MAX_LINE];

    //Helper Fuctions for readline(...)
    void ignoreComment(string& line);
    void upCaseStr(string& line);
};

#endif /* CPUPROGRAM_H */


