/* 
 * File:   CPUProgram.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Ekim 2016
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
    //Naming constants
    const static int MAX_LINE = 200;
    const static int INVALID = -1;
    
    void setFileSize(int size); //setter func.
    
    bool readLine(string fileName);
    string getLine(int lineNumber);
    int size() const;

private:
    int index;  // for fileStr
    int fileSize;
    string fileStr[MAX_LINE];
    
    //Helper Fuctions for readline(...)
    void ignoreComment(string& line);
    void upCaseStr(string& line);
};

#endif /* CPUPROGRAM_H */

