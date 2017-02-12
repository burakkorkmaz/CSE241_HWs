/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PFADyn.h
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 21:29
 */

#ifndef PFADYN_H
#define PFADYN_H

#include <iostream>

using std::string;

namespace PFAD_Korkmaz
{

    class PFADyn
    {
    public:
        //Initilizes with a capacity of 10
        PFADyn();
        
        //explicit prevents creating object with this constructor
        explicit PFADyn(int size);
        
        PFADyn(const PFADyn& orig);

        void addLine(string line);

        void deleteLast() { --used;}
        
        bool isFull() const { return used == capacity; }

        bool isEmpty()const { return used == 0 ? true : false;}
        
        void resizeString(int amount = 2);
        
        int getUsed() const { return used; }

        int getCapacity() const { return capacity; }
        
        void emptyString() { used = 0; }

        string& operator[](int index) const;
        
        PFADyn operator ()(int first, int last);
        
        PFADyn& operator =(const PFADyn& other);
        
        ~PFADyn();
    private:
        string *file;
        int used;
        int capacity;
    };
}
#endif /* PFADYN_H */

