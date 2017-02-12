/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 7
 */
/* 
 * File:   BigramDyn.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 *
 * Created on 18 Aralık 2016 Pazar, 21:48
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <iostream>
#include <fstream>
#include <string>
#include <utility> //for pair
#include <exception> //exception of runtime_error
#include "Bigram.h"
using namespace std;

template<class T>
class BigramDyn : public Bigram<T>
{
public:
    BigramDyn();
    BigramDyn(int datatype);
    BigramDyn(const BigramDyn& orig);
    virtual ~BigramDyn();
    virtual void readFile(string filename) throw (exception) override;
    virtual int numGrams() override;
    virtual int numOfGrams(T first, T second) override;
    virtual ostream& printAll(ostream& other) const override;
    pair<T, T> maxGrams() override;  
    //setter and getter functions
    int getSize() const { return size; }
    void setSize(int value) { size = value;}
    
private:
    // Pair Array, which includes bigrams and Number of bigrams
    pair<pair<T,T>,int> *pairArr;   
    pair<T,T> p;
    
    T first;
    T second;
    int dataType;
    int size;   // size of pair array
    int sameBigrams; // number of same valued bigrams
    //helper functions
    
    // Finds index of pair in pairArr
    int findPair(T first, T second);
    void swapPair(int index1, int index2);
    void sortPairArr(pair<pair<T,T>,int> *p);
};

#endif /* BIGRAMDYN_H */

