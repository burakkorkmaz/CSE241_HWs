/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 7
 */
/* 
 * File:   BigramMap.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 *
 * Created on 18 Aralık 2016 Pazar, 21:48
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include <iostream>

#include <fstream>
#include <string>
#include <map>
#include <cctype>   // for isdigit,isalpha functions
#include <exception> //exception of runtime_error
#include "Bigram.h"

using namespace std;

template <class T>
class BigramMap:public Bigram<T>
{
public:
    BigramMap();
    BigramMap(int datatype) ;
    virtual void readFile(string filename) throw (exception) override;
    virtual int numGrams() override;
    virtual int numOfGrams(T first, T second) override;
    virtual ostream& printAll(ostream& other) const override;
    virtual pair<T, T> maxGrams() override;

private:
    map<pair<T,T>, int> myMap;
    T first;
    T second;
    int dataType;
    //helper function
     
};



#endif /* BIGRAMMAP_H */

