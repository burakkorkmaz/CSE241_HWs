/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   Memory.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 27 Kasım 2016 Pazar, 13:01
 */

#include "Memory.h"

//CONSTRUCTORS

Memory::Memory() {

    for (int i; i < MAX_MEM; ++i)
        setMem(i, 0);

}

Memory::Memory(int option) : opt(option) {

    for (int i; i < MAX_MEM; ++i)
        setMem(i, 0);

}

/**
 * @brief Gets value of memory at that address
 * @param address _ Index of MemArr
 * @return The value of Memory which is at address
 */
unsigned int Memory::getMem(int address) const {

    return memArr[address];
}

unsigned int* Memory::getMemArr() {

    return memArr;
}

/**
 * @brief Assign the value to content of the memory address
 * @param address Index of MemArr
 * @param value Unsigned int Value which will be assign to memory
 */
void Memory::setMem(int address, unsigned int value) {

    memArr[address] = value;
}

/**
 * Prints all contents of memory 
 */
void Memory::printAll() {

    cout << endl << "CONTENT OF MEMORY" << endl;
    cout << " ADR|#0s #1s #2s #3s #4s #5s #6s #7s #8s #9s|" << endl;

    for (int i = 0; i < MAX_MEM; ++i) {
        int value = memArr[i];
        if (i % DECIMAL == 0 && i != 0) // print 10 integer in a line
            cout << endl;
        if (i == 0 || 0 == i % 10) {
            if (i == 0) {
                cout << "[00s]";
            }
            else {
                cout << "[";
                cout.width(2);
                cout << i << "s]";
            }
        }
        cout.width(3);
        cout << value << " ";
    }
    cout << endl << endl;
}