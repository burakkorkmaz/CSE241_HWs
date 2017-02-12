/* 
 *      Gebze Techincal University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 5
 */
/* 
 * File:   CPUProgram.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 13 Kasım 2016 Pazar, 19:41
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram(int option) : opt(option) {
    /* left blank intentionally*/
}


//OPERATOR OVERLOADINGS

string CPUProgram::operator[](int index) {

    if(index < 0){
        cerr << "ERROR! Index is negative.\n";
        string temp;
        return temp;
    }
    else if(index > size() -1){
        cerr << "ERROR! Index is bigger than size.\n";
        string temp;
        return temp;
    }
    return getLine(index);
}

 CPUProgram CPUProgram::operator+(string line) {

      if( line == "" || line == " " || line == "\t"){
        cerr << "WARNING! Empty string !.\n";
        CPUProgram empty;
        return empty;
    }    
    CPUProgram newProg = *this;
    newProg.fileStr.push_back(line);
    return newProg;
}

 const CPUProgram CPUProgram::operator+(const CPUProgram& other) {

    CPUProgram newProg = *this;
    
    if(other.size() == 0){
        cerr << "WARNING! Empty string !.\n";
        CPUProgram empty;
        return empty;
    }
    
    for (int i = 0; i < other.size(); ++i)
        newProg.fileStr.push_back(other.fileStr[i]);

    return newProg;

}

CPUProgram CPUProgram::operator+=(string line) {

    if( line == "" || line == " " || line == "\t"){
        cerr << "WARNING! Empty string !.\n";
        CPUProgram empty;
        return empty;
    }
    
    this->fileStr.push_back(line);

    return *this;

}

    bool CPUProgram::operator==(const CPUProgram& other) const{
        
        return (this->size() == other.size());
    }

    bool CPUProgram::operator!=(const CPUProgram& other) const{
        
        return (this->size() != other.size());
    }
    
    bool CPUProgram::operator<(const CPUProgram& other) const{
        
        return (this->size() < other.size());
    }
    
    bool CPUProgram::operator>(const CPUProgram& other) const{
        
        return (this->size() > other.size());
    }
    
    bool CPUProgram::operator>=(const CPUProgram& other) const{
        
        return (this->size() >= other.size());
    }
    
    bool CPUProgram::operator<=(const CPUProgram& other) const{
        
        return (this->size() <= other.size());
    }

    ostream& operator<< (ostream& outputFile, const CPUProgram& other){
        
        for(int i = 0; i < other.size() ; ++i)
            outputFile << other.fileStr[i] << endl;
        
        return outputFile;
    }
    
    CPUProgram CPUProgram::operator--(){
        
        this->fileStr.erase(this->fileStr.begin() + size() - 1);
        return *this;
    }
    
    CPUProgram CPUProgram::operator--(int){
        
        this->fileStr.erase(this->fileStr.begin() + size() - 1);
        return *this;
    }
    
    CPUProgram CPUProgram::operator()(int first, int last){
        
        CPUProgram stuff;
        if(first < 0 || last < 0){
            cerr << "WARNING! Indexes can NOT be negative.\n";
            return stuff;
        }
        else if(first > size() || last > size()){
            cerr << "WARNING! Indexes can NOT be bigger than the size.\n";
            return stuff;            
        }
        else if(first > last){
            cerr << "WARNING! Indexes can NOT be bigger than the size.\n";
            return stuff; 
        }
        else{
            stuff.opt = this->opt;
            
            for(int i = first; i <= last; ++i)
            stuff.fileStr.push_back(this->fileStr[i]);
            
        return stuff;
        }
    }
    
//!!ACCORDING TO HOMEWORK PDF, FIRST LETTER OF FUNC. NAME MUST BE UPPERCASE

bool CPUProgram::ReadFile(string fileName) {

    fstream inputFile;
    inputFile.open(fileName);
    if (inputFile.fail()) {

        cerr << "File NOT found" << endl;
        return false;
    }

    string temp;
    while (getline(inputFile, temp)) {
        fileStr.push_back(upCaseStr(ignoreComment(temp)));
    }
    return true;
}

string CPUProgram::getLine(int lineNumber) {

    return fileStr[lineNumber];

}

int CPUProgram::size() const {

    return fileStr.size();
}

string CPUProgram::ignoreComment(string line) {

    int i = line.find_first_of(';');
    if (i != -1)
        line.erase(i);
    return line;
}

string CPUProgram::upCaseStr(string line) {

    for (int i = 0; i < line.size(); ++i)
        if (line[i] >= 'a' && line[i] <= 'z')
            line[i] -= ('a' - 'A');
    return line;

}

//void CPUProgram::appendLines(const CPUProgram& other) {
//
//
//
//}