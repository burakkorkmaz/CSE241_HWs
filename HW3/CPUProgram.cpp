/* 
 * File:   CPUProgram.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Ekim 2016
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram() : index(0) {
    setFileSize(0);
}

void CPUProgram::setFileSize(int size) {

    fileSize = size;
    return;
}

bool CPUProgram::readLine(string fileName) {

    fstream inputFile;

    inputFile.open(fileName);
    if (!(inputFile.is_open())) {

        cerr << "File NOT found" << endl;
        return false;
    }

    while (getline(inputFile, fileStr[index])) {

        ignoreComment(fileStr[index]);
        upCaseStr(fileStr[index]);
        ++index;
    }

    setFileSize(index);

    return true;
}

string CPUProgram::getLine(int lineNumber) {

    return fileStr[lineNumber - 1];

}

int CPUProgram::size() const{

    return fileSize;
}

void CPUProgram::ignoreComment(string& line) {

    int i = line.find_first_of(';');
    if (i != -1)
        line.erase(i);
    return;
}

void CPUProgram::upCaseStr(string& line) {

    for (int i = 0; i < line.size(); ++i)
        if (line[i] >= 'a' && line[i] <= 'z')
            line[i] -= ('a' - 'A');
    return;

} 