/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 7
 */
/* 
 * File:   Bigram.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 *
 * Created on 18 Aralık 2016 Pazar, 21:48
 */

#ifndef BIGRAM_H
#define BIGRAM_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::pair;
using std::ostream;

template<class T>
class Bigram
{
public:
    
    virtual void readFile(string filename) = 0;
    virtual int numGrams() = 0;
    virtual int numOfGrams(T first, T second) = 0;
    friend ostream& operator <<(ostream& outputStream,const Bigram& other)
    { return other.printAll(outputStream); }
    virtual ostream& printAll(ostream& other) const = 0 ;
    virtual pair<T, T> maxGrams()  = 0;

    
};

#endif /* BIGRAM_H */

