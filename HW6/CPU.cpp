/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 6
 */
/* 
 * File:   CPU.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * StudentID: 141044041
 * Created on 26 Kasım 2016 Cumartesi, 18:44
 */

#include "CPU.h"

//constructors

CPU::CPU() : warning(0), parseSize(0), status(0),
halt(0), error(false), lastExec(false) {
    for (int i = 0; i < MAX_TOKEN; ++i) {
        parseArr[i] = "";
    }

    regstr.resize(MAX_REG);
    for (int i = 1; i <= MAX_REG; ++i)
        setReg(i, 0);

    setPC(1);

    chooseOption(0);

}

CPU::CPU(int option) : warning(0), parseSize(0), status(0),
halt(0), error(false), lastExec(false) {
    for (int i = 0; i < MAX_TOKEN; ++i) {
        parseArr[i] = "";
    }

    regstr.resize(MAX_REG);
    for (int i = 1; i <= MAX_REG; ++i)
        setReg(i, 0);

    setPC(1);

    chooseOption(option);

}

//getter functions

int CPU::getReg(int regID)const {

    return regstr[regID - 1];
}

int CPU::getPC() const {

    return PC;
}

int CPU::getOption() const {

    return opt;
}

//setter functions

void CPU::setReg(int regID, int regValue) {

    regstr[regID - 1] = regValue;
    return;
}

void CPU::setPC(int lineNumber) {

    PC = lineNumber;
    return;
}

void CPU::setFSize(int size) {

    fSize = size;
}

void CPU::chooseOption(int argv) {

    opt = argv;
    return;
}

// print content of registers

void CPU::print() const {

    cout << "Last value of PC: " << PC << endl
            << "\nCONTENT OF REGISTERS" << endl;
    for (int i = 0; i < MAX_REG; ++i) {
        cout.width(3);
        cout << regstr[i] << " ";
    }
    cout << endl;

    return;
}

// function takes a string that contains an instruction line, 
// executes it and advances the PC accordingly.

void CPU::execute(string line, Memory& myMem) {

    int isOptionTwo = false;

    for (int i = 0; i < MAX_TOKEN; ++i) {
        parseArr[i] = "";
    }

    parseSize = parseStr(line); //tokenizes string
    if (parseSize != INVALID) {
        // {...option...}
        if (opt == 1)
            option();
        else if (opt == 2) {
            option();
            isOptionTwo = true;
        }
        else if (opt != 0 && !warning) {
            cerr << "WARNING! Option is not zero. It will be assumed zero!\n";
            warning = 1;
        }

        //halted control
        if (parseArr[0] == "HLT") {
            halt = 1;
            if (!lastExec)
                cerr << "WARNING! HLT is not Last Execution.\n";
        }
        else
            if (lastExec)
            cerr << "WARNING! The Last Execution is not HLT. "
                << "Program may get error!\n";

        //Processing Instruction
        status = process(myMem);
        if (status != INVALID) {

            if (status == 0) {
                setPC(getPC() + 1);
            }
            else if (status > fSize) {
                cerr << "Invalid Line Number\n";
                cerr << "ERROR LINE : " << PC << endl;
                error = true;
            }
            else if (status > 0)
                setPC(status);
        }
        else {
            cerr << "ERROR LINE : " << PC << endl;
            error = true;
        }

        if (isOptionTwo)
            myMem.printAll();


        return;
    }
    cerr << "Invalid Use Of Comma\n";
    cerr << "ERROR LINE : " << PC << endl;
    error = true;
    return;
}

/**
 * @brief halts the loop if instrc. is Hlt or Error occured
 * @return false if No HLT or NO Error, otherwise true.
 */
bool CPU::halted() {

    if (halt)
        return true;

    else if (error)
        return true;
    else {



        return false;
    }
}

/**
 * @brief Helper function for halted(). It checks whether pragram counter 
 * is at last line
 */
void CPU::isLastExec(int fileSize) {
    if (fileSize == PC)
        lastExec = true;
    else
        lastExec = false;
}

/**
 * @brief Process instruction like MOV, ADD by calling them.
 * @return 0 or line number(JMP) if valid. -1 if not valid.
 */
int CPU::process(Memory& mem) {

    int status = INVALID;
    int memExist = 0;

    if (checkAddr(parseArr[1]) != INVALID || checkAddr(parseArr[2]) != INVALID)
        memExist = 1;

    if (parseArr[0] == "MOV" && parseSize == 3) {

        if (memExist) {
            if (MOV(mem.getMemArr()))
                status = 0;
        }
        else {
            if (MOV())
                status = 0;
        }
    }
    else if (parseArr[0] == "ADD" && parseSize == 3) {

        if (memExist) {
            if (ADD(mem.getMemArr()))
                status = 0;
        }
        else {
            if (ADD())
                status = 0;
        }
    }
    else if (parseArr[0] == "SUB" && parseSize == 3) {
        if (memExist) {
            if (SUB(mem.getMemArr()))
                status = 0;
        }
        else {
            if (SUB())
                status = 0;
        }
    }
    else if (parseArr[0] == "PRN" && parseSize == 2) {

        if (PRN(mem.getMemArr())) status = 0;
    }
    else if (parseArr[0] == "JMP") {

        if (parseSize == 3)
            status = JMP(1);

        else if (parseSize == 2)
            status = JMP(0);

        else
            cerr << "JMP -> Invalid Use of Parameters \n";
    }
    else if (parseArr[0] == "JPN") {
        if (parseSize == 3)
            status = JPN();
    }
    else if (parseArr[0] == "HLT" && parseSize == 1) {
        status = 0;
        HLT(mem);
    }
    else {
        status = INVALID;
        cerr << "Undeclared Instruction or Error on Use of Parameter(s). \n";
    }
    return status;
}

/**
 * @brief Split string to tokens from spaces, tab and comma .
 * @param _line_ a line as string from file.
 * @return Number of token
 */
int CPU::parseStr(const string line) {

    int k = 0; //index of parse array
    int parseSize = 0; // Number of parses after tokenizing
    bool found = false;
    //comma control
    int firstComma = line.find_first_of(',');
    int lastComma = line.find_last_of(',');

    if (firstComma != lastComma) //control whether comma is not more than one
        return INVALID;

    for (int i = 0; i < line.size(); ++i) {

        if (line[i] != ' ' && line[i] != ',' && line[i] != '\t') {

            if (k == 2) { // if comma is in wrong place or not exist

                if (lastComma == INVALID || lastComma > i)
                    return INVALID;
            }

            parseArr[k] += line[i];
            found = true;
            parseSize = k + 1;

        }
        else if ((line[i] == ' ' || line[i] == ','
                || line[i] == '\t') && found == true) {
            ++k;
            found = false;
        }
        else if (line[i] == ',')
            if (k < 2)
                return INVALID;

    }
    return parseSize;
}

/**
 * @brief Check validity of register name.
 * @param _reg_ source string
 * @return Register number if valid. -1 if not valid.
 */
int CPU::checkReg(string reg) {

    int regID;

    if (reg[0] == 'R') {
        reg = reg.substr(1);
        regID = strToInt(reg);

        if (regID != INVALID && regID <= MAX_REG)
            return regID;
    }

    return INVALID;
}

/**
 * @brief Check validity of address name.
 * @param _address_ source string
 * @return Addres number if valid. -1 if not valid.
 */
int CPU::checkAddr(string address) {

    int adr;

    if (address[0] == '#') {
        address = address.substr(1);
        adr = strToInt(address);
        if (adr != INVALID && adr < MAX_MEM)
            return adr;
    }
    return INVALID;
}

/**
 * @brief Convert string to integer if all of them char digit .
 * @param _token_ source string
 * @return converted number if all number. -1 if not number.
 */
int CPU::strToInt(string token) {
    //converts only positive integers otherwise get error
    int number = 0;

    for (int i = 0; i < token.size(); ++i) {

        if (token[i] >= '0' && token[i] <= '9') {

            int basement = token.size() - i - 1;

            if (basement != 0)
                number += (token[i] - '0') * pow(DECIMAL, basement);

            else number += (token[i] - '0');
        }
        else
            return INVALID;
    }
    return number;
}

/**
 * @brief Takes an argument as option show instructions and print contents of
 * registers. Also it prints Program Counter(PC)
 */
void CPU::option() {
    cout << "PC:" << getPC() << endl;
    cout << parseArr[0];
    if (parseSize >= 2)
        cout << " ";
    cout.width(2);
    cout << parseArr[1];
    if (parseSize >= 3)
        cout << ", ";
    cout.width(2);
    cout << parseArr[2];
    cout << " – ";
    for (int j = 1; j <= MAX_REG; ++j) {
        cout << "R" << j << "=" << getReg(j);
        if (j != MAX_REG)
            cout << ", ";
    }
    cout << endl;
    return;
}

/**
 * @brief Copies value of 1th reg to 2nd reg OR constant value to first reg
 * @return true if parameters valid. false if param invalid.
 */
bool CPU::MOV() {
    int r2ID;
    int r1ID = checkReg(parseArr[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(parseArr[2]); // second param num check
        if (rVal != INVALID) { // if second is num
            setReg(r1ID, rVal);
        }
        else if ((r2ID = checkReg(parseArr[2])) != INVALID) {//if second is reg
            setReg(r2ID, getReg(r1ID));
        }
        else { // second param invalid
            cerr << "MOV -> second parameter is invalid. " << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "MOV -> first register is invalid." << endl;
        return false;
    }
}

bool CPU::MOV(unsigned int memAr[]) {
    int p2ID;
    int p1ID = checkAddr(parseArr[1]);
    //MOV #X, const or MOV #X, RX control
    if (p1ID != INVALID) { // first param check
        int pVal = strToInt(parseArr[2]); // second param num check
        if (pVal != INVALID) { // if second is num
            if (pVal < 0 || pVal > 255) { //unsigned int must be between 0 and 256
                cerr << "MOV -> Value of 2nd parameter "
                        << "exceeds limit in memory(unsigned) " << endl;
                return false;
            }
            memAr[p1ID] = pVal;
        }//******return true;
        else if ((p2ID = checkReg(parseArr[2])) != INVALID) { // if second is reg
            //regstr[p2ID - 1] = memAr[p1ID];
            setReg(p2ID, memAr[p1ID]);
        }
        else { // second param invalid
            cerr << "MOV -> second parameter is invalid. " << endl;
            return false;
        }
    }
    else if ((p1ID = checkReg(parseArr[1])) != INVALID) {
        if ((p2ID = checkAddr(parseArr[2])) != INVALID)
            memAr[p2ID] = getReg(p1ID);
        else {
            cerr << "MOV -> second parameter(address) is invalid. ";
            return false;
        }
    }
    else {
        cerr << "MOV -> first register is invalid." << endl;
        return false;
    }
    return true;
}

/**
 * @brief PRN instruction prints value of register or constant.
 * @return true if parameters valid. false if parameters invalid.
 */
bool CPU::PRN(unsigned int memAr[]) {
    int p1ID;
    int pVal = strToInt(parseArr[1]); // param num check

    if (pVal != INVALID) // if param not num
        cout << pVal << endl;
    else if ((p1ID = checkReg(parseArr[1])) != INVALID) // if param is reg
        cout << regstr[p1ID - 1] << endl;
    else if ((p1ID = checkAddr(parseArr[1])) != INVALID)// if param is address
        cout << memAr[p1ID] << endl;
    else { // param invalid
        cerr << "PRN -> the parameter is invalid. " << endl;
        return false;
    }
    return true;
}

/**
 * @brief ADD instruction adds value of 1th reg to 2nd reg OR constant to r1.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool CPU::ADD() {
    int r2ID;
    int r1ID = checkReg(parseArr[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(parseArr[2]); // second param num check
        if (rVal != INVALID) { // if second is num
            setReg(r1ID, rVal + getReg(r1ID));
        }
        else if ((r2ID = checkReg(parseArr[2])) != INVALID) {//if second is reg
            setReg(r1ID, getReg(r1ID) + getReg(r2ID));
        }
        else { // second param invalid
            cerr << "ADD -> second parameter is invalid. " << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "ADD -> first register is invalid. " << endl;
        return false;
    }

}

/**
 * Adds value of a memory location to register.
 * @param memAr[]
 * @return false if invalid. true if valid.
 */
bool CPU::ADD(unsigned int memAr[]) {
    int p2ID;
    int p1ID = checkReg(parseArr[1]);
    //ADD RX, #X  --> <This ADD instruction has only one format.> 
    if (p1ID != INVALID) {
        if ((p2ID = checkAddr(parseArr[2])) != INVALID)
            //regstr[p1ID - 1] += memAr[p2ID];
            setReg(p1ID, getReg(p1ID) + memAr[p2ID]);
        else {
            cerr << "ADD -> second parameter(address) is invalid. ";
            return false;
        }
    }
    else {
        cerr << "ADD -> first register is invalid." << endl;
        return false;
    }
    return true;
}

/**
 * @brief SUB instruction subtracts the value of second reg. from first reg. 
 * and puts into reg1. Also if 2th param is constant, subtracts it from reg.
 * @return true if parameters valid. false if param invalid.
 */
bool CPU::SUB() {
    int r2ID;
    int r1ID = checkReg(parseArr[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(parseArr[2]); // second param num check
        if (rVal != -1) { // if second is num
            setReg(r1ID, getReg(r1ID) - rVal);
        }
        else if ((r2ID = checkReg(parseArr[2])) != INVALID) {//if second is reg
            setReg(r1ID, getReg(r1ID) - getReg(r2ID));
        }
        else { // second param invalid
            cerr << "SUB -> second parameter is invalid. " << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "SUB -> first register is invalid. " << endl;
        return false;
    }
}

/**
 * @brief Subtracts value of a memory location from register
 * @param memAr - unsigned int array in Memory class
 * @return true if parameters valid. false if param invalid.
 */
bool CPU::SUB(unsigned int memAr[]) {
    int p2ID;
    int p1ID = checkReg(parseArr[1]);
    //ADD RX, #X  --> <This ADD instruction has only one format.> 
    if (p1ID != INVALID) {
        if ((p2ID = checkAddr(parseArr[2])) != INVALID)
            //rgArr[p1ID - 1] -= memArr[p2ID];
            setReg(p1ID, getReg(p1ID) - memAr[p2ID]);
        else {
            cerr << "ADD -> second parameter(address) is invalid. ";
            return false;
        }
    }
    else {
        cerr << "ADD -> first register is invalid." << endl;
        return false;
    }
    return true;
}

/** 
 * @brief JMP has two method. First gets one param and jumps that line. 
 * Second method gets two param. and 1st param reg. if equals 0, it jumps
 * @param _method_ specifies running method of JMP
 * @return line number if valid. false reg. is zero. -1 if not valid
 */
int CPU::JMP(int method) {

    if (0 == method) {
        int line = strToInt(parseArr[1]);
        if (line != INVALID && line != 0)
            return line;
        else {
            cerr << "JMP ->  The parameter is invalid. ";
            return INVALID;
        }
    }
    else {
        int regID = checkReg(parseArr[1]);
        if (regID != INVALID) { // first param check
            int line = strToInt(parseArr[2]); // second param num check
            if (line != INVALID && regID != 0) { // if second is num
                if (line == 0) {
                    cerr << "JMP -> Invalid line number(ZERO). ";
                    return INVALID;
                }
                if (getReg(regID) == 0)
                    return line;
                else
                    return false; // if register is not zero, continue
            }

            else { // second param invalid
                cerr << "JMP -> second parameter is invalid. " << endl;
                return INVALID;
            }
        }
        cerr << "JMP -> first parameter is invalid. " << endl;
        return INVALID;
    }
}

int CPU::JPN() {
    int regID = checkReg(parseArr[1]);
    if (regID != INVALID) { // first param check
        int line = strToInt(parseArr[2]); // second param num check
        if (line != INVALID) { // if second is num
            if (line == 0) {
                cerr << "JPN -> Invalid line number(ZERO). ";
                return INVALID;
            }
            if (regstr[regID - 1] <= 0)
                return line;
            else
                return false; // if reg value is bigger than zero, continue
        }
        else { // second param invalid
            cerr << "JPN -> second parameter is invalid. " << endl;
            return INVALID;
        }
    }
    cerr << "JPN -> first parameter is invalid. " << endl;
    return INVALID;
}

/**
 * @brief provides halting the program and prints the contents of all regs.
 * and last Program counter
 */
void CPU::HLT(Memory& memory) {
    cout << "---------------------------------------\n";
    print();
    memory.printAll();
    cout << "---------------------------------------\n" << endl;
    return;
}