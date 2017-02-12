/* 
 *      Gebze Techincal University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 5
 */
/* 
 * File:   CPUProgram.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 13 Kasım 2016 Pazar, 19:41
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

//INCLUDES
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class CPUProgram {
public:
    //Constructor

    CPUProgram() : CPUProgram(0) {
        /* left blank intentionally*/
    }
    CPUProgram(int option);
    //Naming constant
    const static int INVALID = -1;

    string operator[](int index);
    CPUProgram operator+=(string line);
    CPUProgram operator+(string line);
    const CPUProgram operator+(const CPUProgram& other);
    bool operator==(const CPUProgram& other) const;
    bool operator!=(const CPUProgram& other) const;
    bool operator<(const CPUProgram& other) const;
    bool operator>(const CPUProgram& other) const;
    bool operator>=(const CPUProgram& other) const;
    bool operator<=(const CPUProgram& other) const;
    friend ostream& operator<< (ostream& outputFile, const CPUProgram& other);
    CPUProgram operator--();
    CPUProgram operator--(int);
    CPUProgram operator()(int first, int last);
    
    
    //!!ACCORDING TO PDF OF HOMEWORK , FIRST LETTER OF 
    // READFILE FUNCTION MUST BE UPPERCASE !!!!!!!!!!!!!!!!!!!!!
    bool ReadFile(string fileName);
    string getLine(int lineNumber);
    int size() const;


private:
    int opt;
    vector<string> fileStr;
    //Helper Fuctions for readFile(...)
    string ignoreComment(string line);
    string upCaseStr(string line);
};

#endif /* CPUPROGRAM_H */

