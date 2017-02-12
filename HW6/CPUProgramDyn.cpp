/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   CPUProgramDyn.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 13:01
 */

#include "CPUProgramDyn.h"
#include <string>
#include "PFADyn.h"

using std::string;
using std::fstream;
using std::iostream;
using std::cout;
using std::cerr;
using std::endl;

namespace
{
    //Naming constant
    const int INVALID = -1;

    //Helper Fuctions for readFile(...)
    string ignoreComment(string line) {

        int i = line.find_first_of(';');
        if (i != INVALID)
            line.erase(i);
        return line;
    }
    string upCaseStr(string line) {

        for (int i = 0; i < line.size(); ++i)
            if (line[i] >= 'a' && line[i] <= 'z')
                line[i] -= ('a' - 'A');
        return line;

    }
}

namespace CPUPDynamical
{

    CPUProgramDyn::CPUProgramDyn() : CPUProgramDyn(0){ }

    CPUProgramDyn::CPUProgramDyn(int option) :arr(),opt(option)
    {  }

    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& orig): arr() {
        
        this->setOption(orig.getOption());
        
        int tempSize = orig.size();
        
        for(int i = 0 ; i < tempSize;++i)
            this->arr.addLine(orig[i]);
    }

    CPUProgramDyn::~CPUProgramDyn() {
        
        
        
        }


    //OPERATOR OVERLOADINGS

    string CPUProgramDyn::operator [](int index) const{

        return getLine(index);

    }

    CPUProgramDyn CPUProgramDyn::operator +(string line) {
        
        if (line == "" || line == " " || line == "\t") {
            cerr << "WARNING! Empty string !.\n";
            
            return CPUProgramDyn();
        }
        CPUProgramDyn newProg(*this);
        newProg+=line;
        
        return newProg;
    }

    const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& other) {

        CPUProgramDyn newProg(*this);

         if (other[0] == "" || other[0] == " " || other[0] == "\t") {
            cerr << "WARNING! Empty object !.\n";
            
            return CPUProgramDyn();
        }
        for (int i = 0; i < other.size(); ++i)
            newProg+=other[i];

        return newProg;

    }

    CPUProgramDyn CPUProgramDyn::operator +=(string line) {
        
        
        if (line == "" || line == " " || line == "\t") {
            cerr << "WARNING! Empty string !.\n";
            return CPUProgramDyn();
        }

        arr.addLine(line);
        return *this;
    }

    bool CPUProgramDyn::operator ==(const CPUProgramDyn& other) const {

        return (this->size() == other.size());
    }

    bool CPUProgramDyn::operator !=(const CPUProgramDyn& other) const {

        return (this->size() != other.size());
    }

    bool CPUProgramDyn::operator <(const CPUProgramDyn& other) const {

        return (this->size() < other.size());
    }

    bool CPUProgramDyn::operator >(const CPUProgramDyn& other) const {

        return (this->size() > other.size());
    }

    bool CPUProgramDyn::operator >=(const CPUProgramDyn& other) const {

        return (this->size() >= other.size());
    }

    bool CPUProgramDyn::operator <=(const CPUProgramDyn& other) const {

        return (this->size() <= other.size());
    }

    ostream& operator <<(ostream& outputFile, const CPUProgramDyn& other) {

        for (int i = 0; i < other.size(); ++i)
            outputFile << other[i] << endl;

        return outputFile;
    }

    CPUProgramDyn CPUProgramDyn::operator --() {
        arr.deleteLast();
        return *this;
    }

    CPUProgramDyn CPUProgramDyn::operator --(int index) {

        CPUProgramDyn backup(*this);
        arr.deleteLast();
        return backup;
    }

    CPUProgramDyn CPUProgramDyn::operator ()(int first, int last) {

        // pfarr icin () yaz
        // yeni obje yarat option ile
        // gelen elemanları tek tek oraya ekle
        CPUProgramDyn stuff(opt);
        PFADyn temp = arr(first, last);

            
        for (int i = 0; i <= temp.getUsed(); ++i)
                stuff += temp[i];
            return stuff;
        
    }

    //!!ACCORDING TO HOMEWORK PDF, FIRST LETTER OF FUNC. NAME MUST BE UPPERCASE
    bool CPUProgramDyn::ReadFile(string fileName) {

        fstream inputFile;
        
        inputFile.open(fileName);
        if (inputFile.fail()) {
            cerr << "File NOT found" << endl;
            return false;
        }
        
        string temp;
        while (getline(inputFile, temp)) {
            string updatedLine = upCaseStr(ignoreComment(temp));
            arr.addLine(updatedLine);
        }

        inputFile.close();
        return true;
    }

    string CPUProgramDyn::getLine(int lineNumber) const {
        return arr[lineNumber];

    }

    int CPUProgramDyn::size() const {
        return arr.getUsed();
    }
}