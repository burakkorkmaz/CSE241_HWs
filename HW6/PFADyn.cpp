/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   PFADyn.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 21:29
 */

#include "PFADyn.h"



namespace PFAD_Korkmaz
{
    //temporary string for return empty string &
    string temp;
    
    PFADyn::PFADyn() : capacity(10), used(0){
        file = new string[capacity] ;
    }

    PFADyn::PFADyn(int size) : capacity(size), used(0){
        file = new string[capacity] ;

    }
    // copy constructor
    PFADyn::PFADyn(const PFADyn& orig) : capacity(orig.getCapacity()), 
                    used(orig.getUsed()){
        file = new string[capacity];
        for(int i = 0; i < used; ++i)
            file[i] = orig.file[i];
    }

    PFADyn::~PFADyn() {
        delete [] file;
    }
    
    void PFADyn::addLine(string line){
        
        if(!isFull()){
            
            file[used] = line;
            ++used;
        }
        else{
            
            resizeString();
            addLine(line);
        }
    }

  
    
    void PFADyn::resizeString(int amount){

        capacity = (capacity*amount) + 1;

        string * newString = new string[capacity];

        for(int i = 0; i < used; ++i){
            newString[i] = file[i];
        }
        delete [] file;
        file = newString; 

    }
    
    string& PFADyn::operator [](int index) const {
        
        
        if (index < 0) {
            std::cerr << "ERROR! Index is negative.\n";
            return temp; //temporay string declared in namespace.
        }
        else if (index > getUsed() - 1) {
            std::cerr << "ERROR! Index is bigger than size.\n";
            return temp; //temporay string declared in namespace.
        }
        return file[index];
    }
    
    PFADyn PFADyn::operator ()(int first, int last){
        
        PFADyn newString;
        
        if (first < 0 || last < 0) {
            std::cerr << "WARNING! Indexes can NOT be negative.\n";
        }
        else if (first > getUsed() || last > getUsed()) {
            std::cerr << "WARNING! Indexes can NOT be bigger than the size.\n";
        }
        else if (first > last) {
            std::cerr << "WARNING! Indexes can NOT be bigger than the size.\n";
        }
        else {
            
            for(int i = first; i < last ; ++i)
                newString.addLine(file[i]);
        }
        return newString;
    }
         
    PFADyn& PFADyn::operator =(const PFADyn& other){
       
        if(other.getCapacity() != capacity){
            delete [] file;
            file = new string[other.getCapacity()];
        }
        
        capacity = other.getCapacity();
        used = other.getUsed();
        
        for(int i = 0; i < used; ++i)
            file[i] = other[i];
        
        return *this;
    }


}