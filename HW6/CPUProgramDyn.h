/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   CPUProgramDyn.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 13:01
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H


//INCLUDES
#include <iostream>
#include <fstream>
#include <string>

#include "PFADyn.h"


using std::string;
using std::ostream;
using namespace PFAD_Korkmaz;


namespace CPUPDynamical
{
    
    class CPUProgramDyn
    {
    public:
        //Constructor

        CPUProgramDyn();
        CPUProgramDyn(int option);
        CPUProgramDyn(const CPUProgramDyn& orig);
        virtual ~CPUProgramDyn();

        string operator [](int index) const;
        CPUProgramDyn operator +=(string line);
        CPUProgramDyn operator +(string line);
        const CPUProgramDyn operator +(const CPUProgramDyn& other);
        bool operator ==(const CPUProgramDyn& other) const;
        bool operator !=(const CPUProgramDyn& other) const;
        bool operator <(const CPUProgramDyn& other) const;
        bool operator >(const CPUProgramDyn& other) const;
        bool operator >=(const CPUProgramDyn& other) const;
        bool operator <=(const CPUProgramDyn& other) const;
        friend ostream& operator <<(ostream& outputFile, 
                const CPUProgramDyn& other);
        CPUProgramDyn operator --();
        CPUProgramDyn operator --(int);
        CPUProgramDyn operator ()(int first, int last);
        //!!ACCORDING TO PDF OF HOMEWORK , FIRST LETTER OF 
        // READFILE FUNCTION MUST BE UPPERCASE !!!!!!!!!!!!!!!!!!!!!
        bool ReadFile(string fileName);
        string getLine(int lineNumber) const;
        int size() const;
        int getOption() const {return opt;}
        void setOption(int optValue){opt=optValue;}
    private:
        int opt; //option
        PFADyn arr;
    };

}
#endif /* CPUPROGRAMDYN_H */

