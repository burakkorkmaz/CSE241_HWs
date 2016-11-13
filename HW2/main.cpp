/* 
 *      Gebze Techical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 2
 * 
 */

/* 
 * File:   main.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * Student_ID : 141044041
 * Created on 15 Ekim 2016
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>        //for pow function
#include <cstdint>    //for uint8_t type

using namespace std;

// NAMING CONSTANTS
const int MAX_LINE = 200; //Maximum number of lines reading from file
const int MAX_REG = 5; // Maximum Register in CPU
const int MAX_MEM = 50; // Maximum number of integers in memory
const int DECIMAL = 10;
const int INVALID = -1;

/*** FUNCTION PROTOTYPES ***/

/**
 * @brief Resets all elements of int array (initilize 0 all of them).
 * @param _arr[]_ source int array
 * @param _arrSize_ Size of array
 */
void resetArr(int arr[], int arrSize);

/**
 * @brief Resets all elements of unsigned int array (initilize 0 all of them).
 * @param _arr[]_ source unsigned int array
 * @param _arrSize_ Size of array
 */
void resetArr(uint8_t arr[], int arrSize);

/**
 * @brief Delete part after ";" in string 
 * @param _st_source string.
 * @return New string.
 */
string ignoreComment(string st);

/**
 * @brief Convert each character to UpperCase if it is lowercase letter.
 * @param _line_ a line as string from file.
 * @return new string full Uppercased.
 */
string upCaseStr(string line);

/**
 * @brief Split string to tokens from spaces and comma.
 * @param _line_ a line as string from file.
 * @param _parse[]_ string array that is tokenized.
 * @return Number of token
 */
int parseStr(string line, string parse[]);

/**
 * @brief Check validity of register name.
 * @param _reg_ source string
 * @return Register number if valid. -1 if not valid.
 */
int checkReg(string reg);

/**
 * @brief Check validity of address name.
 * @param _address_ source string
 * @return Addres number if valid. -1 if not valid.
 */
int checkAddr(string address);

/**
 * @brief Convert string to integer if all of them char digit .
 * @param _token_ source string
 * @return converted number if all number. -1 if not number.
 */
int strToInt(string token);

/**
 * @brief Process instruction like MOV, ADD by calling them.
 * @param _tokens[]_ string array includes tokens.
 * @param _rgArr_ Registers in CPU
 * @param _memArr_ unsigned Integer Values in memory.
 * @param _size_ Registers size
 * @return Register number if valid. -1 if not valid.
 */
int process(string tokens[], int rgArr[], uint8_t memArr[], int size);

/**
 * @brief MOVE instruction copies value of 1th reg to 2nd reg OR constant to r1
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool MOV(int rgArr[], string token[]);

/**
 * @brief Copies value of reg or const to adr and copies value in adr to reg.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _memArr_ unsigned integer array in memory includes addresses.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid
 */
bool MOV(int rgArr[], uint8_t memArr[], string token[]);

/**
 * @brief ADD instruction adds value of 1th reg to 2nd reg OR constant to r1.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool ADD(int rgArr[], string token[]);

/**
 * @brief Adds value of a memory location to register.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _memArr_ unsigned int array in memory includes addresses locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool ADD(int rgArr[], uint8_t memArr[], string token[]);
/**
 * @brief SUB instruc subtracts the value of reg2 from reg1 and puts into reg1.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool SUB(int rgArr[], string token[]);

/**
 * @brief Subtracts value of a memory location from register
 * @param _rgArr_ Register array in CPU includes reg locations
 * @param _memArr_ unsigned integer array in memory includes addresses loc.s
 * @param _token_ tokens string includes register name or constants
 * @return true if parameters valid. false if param invalid
 */
bool SUB(int rgArr[], uint8_t memArr[], string token[]);
/**
 * @brief PRN instruction print value of register/address or constant.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _memArr_ array in memory includes address locations.
 * @param _token_ tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool PRN(int rgArr[], uint8_t memArr[], string token[]);

/**
 * @brief JMP instruction if register equals zero, jump to line. else contniue.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return line number if parameters valid. false if param invalid.
 */
int JMP(int rgArr[], string token[]);

/**
 * @brief Overload of JMP jumps to given line
 * @param _token_ tokens string includes register name or constants.
 * @return line number if parameters valid. false if param invalid.
 */
int JMP(string token[]);

/**
 * @brief if register equals zero or smaller, jump to line. else contniue.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _token_ tokens string includes register name or constants.
 * @return line number if parameters valid. false if param invalid.
 */
int JPN(int rgArr[], string token[]);

/**
 * @brief HLT instruc halts the program and prints the contents of all regs.
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _memArr_ array in memory includes address locations.
 */
void HLT(int rgArr[], uint8_t memArr[]);

/**
 * @brief Takes an argument as option show instructions and print reg contents
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _tokens[]_ string array includes tokens.
 * @param _tokenSize_ NUmber of tokens
 */
void option(int rgArr[], string tokens[], int tokenSize);

/**
 * @brief Takes argument as option show instructions and print reg and memory contents
 * @param _rgArr_ Register array in CPU includes reg locations.
 * @param _memArr_ array in memory includes memory locations.
 * @param _tokens[]_ string array includes tokens.
 * @param _tokenSize_ Number of tokens
 */
void option(int rgArr[], uint8_t memArr[], string tokens[], int tokenSize);


int main(int argc, char** argv) {

    int line = 0;
    int regArr[MAX_REG];
    uint8_t memory[MAX_MEM];
    resetArr(regArr, MAX_REG);
    resetArr(memory, MAX_MEM);

    string str[MAX_LINE];
    fstream inputFile;

    inputFile.open(argv[1]);
    if (!(inputFile.is_open())) {
        cerr << "File NOT found" << endl;
    }

    while (getline(inputFile, str[line])) { //find number of lines
        str[line] = ignoreComment(str[line]);
        str[line] = upCaseStr(str[line]);
        ++line;
    }

    inputFile.close();
    int opt = strToInt(argv[2]);//second argument will be option
    int warning = 0;    //option control
    int exit = 0;
    int i = 0;
    while (i < line && !exit) {
        string parses[MAX_LINE];
        int parseNum = parseStr(str[i], parses);
        //option choose
        if (parseNum != INVALID) {
            if (opt == 1)
                option(regArr, parses, parseNum);
            else if(opt == 2)
                option(regArr, parses, parseNum);//call option 1 in option 2
            else
                if(opt != 0 && !warning){
                cout << "WARNING! Option is not zero.\n";
                warning = 1;
                }
        }
            // process instruction     
        int status = process(parses, regArr, memory, parseNum);
        if (status == -1) {
            cerr << "main.cpp - ERROR LINE : " << i + 1 << endl;
            exit = 1;
        }
        else if (status != 0)
            if (status > line) {
                cerr << "Invalid Line Number\n"
                        << "main.cpp - ERROR LINE : " << i + 1 << endl;
                exit = 1;
            }
            else
                i = status - 1; // Line which JMP returns converts index 
        else ++i;
        //if option is 2, show memory
        if (opt == 2 && !exit )
                option(regArr, memory, parses, parseNum);
    }
    return 0;
}

void resetArr(int arr[], int arrSize) {
    for (int i = 0; i < arrSize; ++i)
        arr[i] = 0;
    return;
}

void resetArr(uint8_t arr[], int arrSize) {
    for (int i = 0; i < arrSize; ++i)
        arr[i] = 0;
    return;
}

string ignoreComment(string line) {
    int i = line.find_first_of(';');
    if (i != -1)
        line.erase(i);
    return line;
}

string upCaseStr(string line) {
    for (int i = 0; i < line.size(); ++i)
        if (line[i] >= 'a' && line[i] <= 'z')
            line[i] -= ('a' - 'A');
    return line;
}

int parseStr(string line, string parse[]) {
    int k = 0; //index of parse array
    int parseSize = 0; // Number of parses after tokenizing
    bool found = false;
    int firstComma = line.find_first_of(',');
    int lastComma = line.find_last_of(',');

    if (firstComma != lastComma) //control whether comma is not more than one
        return INVALID;

    for (int i = 0; i < line.size(); ++i) {
        
        if (line[i] != ' ' && line[i] != ',') {
            if (k == 2) { // if comma is in wrong place or not exist
            if (lastComma == INVALID || lastComma > i)
                return INVALID;
            }
            parse[k] += line[i];
            found = true;
            parseSize = k + 1;
        }
        else if ((line[i] == ' ' || line[i] == ',') && found == true) {
            ++k;
            found = false;
        }
        else if(line[i]== ','){
        	if(k < 2)
        		return INVALID;
        }        
    }
    return parseSize;
}

int checkReg(string reg) {
    int regID;
    if (reg[0] == 'R') {
        reg = reg.substr(1);
        regID = strToInt(reg);
        if (regID != INVALID && regID <= MAX_REG)
            return regID;
    }
    return INVALID;
}

int checkAddr(string address) {
    int adr;
    if (address[0] == '#') {
        address = address.substr(1);
        adr = strToInt(address);
        if (adr != INVALID && adr < MAX_MEM)
            return adr;
    }
    return INVALID;
}
//convert only positive integers otherwise get error
int strToInt(string token) {
    int number = 0;
    for (int i = 0; i < token.size(); ++i) {
        if (token[i] >= '0' && token[i] <= '9') {
            int basement = token.size() - i - 1;
            if (basement != 0)
                number += (token[i] - '0') * pow(10, basement);
            else number += (token[i] - '0');
        }
        else
            return INVALID;
    }
    return number;
}

int process(string tokens[], int rgArr[], uint8_t memArr[], int tokenSize) {
    int status = INVALID;
    int memExist = 0;

    if (checkAddr(tokens[1]) != INVALID || checkAddr(tokens[2]) != INVALID)
        memExist = 1;
    if (tokens[0] == "MOV" && tokenSize == 3) {
        if (memExist) {
            if (MOV(rgArr, memArr, tokens)) status = 0;
        }
        else {
            if (MOV(rgArr, tokens)) status = 0;
        }
    }
    else if (tokens[0] == "ADD" && tokenSize == 3) {
        if (memExist) {
            if (ADD(rgArr, memArr, tokens)) status = 0;
        }
        else {
            if (ADD(rgArr, tokens)) status = 0;
        }
    }
    else if (tokens[0] == "SUB" && tokenSize == 3) {
        if (memExist) {
            if (SUB(rgArr, memArr, tokens)) status = 0;
        }
        else {
            if (SUB(rgArr, tokens)) status = 0;
        }
    }
    else if (tokens[0] == "PRN" && tokenSize == 2) {
        if (PRN(rgArr, memArr, tokens)) status = 0;
    }
    else if (tokens[0] == "JMP") {
        if (tokenSize == 3)
            status = JMP(rgArr, tokens);
        else if (tokenSize == 2)
            status = JMP(tokens);
    }
    else if (tokens[0] == "JPN") {
        if (tokenSize == 3)
            status = JPN(rgArr, tokens);
    }
    else if (tokens[0] == "HLT" && tokenSize == 1) {
        status = 0;
        HLT(rgArr, memArr);
    }
    else {
        status = INVALID;
        cerr << "\nUndeclared Instruction or Error in Using parameter. ";
    }
    return status;
}

bool MOV(int rgArr[], string token[]) {
    int r2ID;
    int r1ID = checkReg(token[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(token[2]); // second param num check
        if (rVal != INVALID) { // if second is num
            rgArr[r1ID - 1 ] = rVal;
        }
        else if ((r2ID = checkReg(token[2])) != INVALID) { // if second is reg
            rgArr[r2ID - 1] = rgArr[r1ID - 1];
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

bool MOV(int rgArr[], uint8_t memArr[], string token[]) {
    int p2ID;
    int p1ID = checkAddr(token[1]);
    //MOV #X, const or MOV #X, RX control
    if (p1ID != INVALID) { // first param check
        int pVal = strToInt(token[2]); // second param num check
        if (pVal != INVALID) { // if second is num
            if (pVal < 0 || pVal > 255) { //unsigned int must be between 0 and 256
                cerr << "MOV -> Value of 2nd parameter "
                        << "exceeds limit in memory(unsigned) " << endl;
                return false;
            }
            memArr[p1ID] = pVal;
        }//******return true;
        else if ((p2ID = checkReg(token[2])) != INVALID) { // if second is reg
            rgArr[p2ID - 1] = memArr[p1ID];
        }
        else { // second param invalid
            cerr << "MOV -> second parameter is invalid. " << endl;
            return false;
        }
    }
    else if ((p1ID = checkReg(token[1])) != INVALID) {
        if ((p2ID = checkAddr(token[2])) != INVALID)
             memArr[p2ID] = rgArr[p1ID - 1];
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

bool PRN(int rgArr[], uint8_t memArr[], string token[]) {
    int p1ID;
    int pVal = strToInt(token[1]); // param num check

    if (pVal != INVALID) // if param not num
        cout << pVal << endl;
    else if ((p1ID = checkReg(token[1])) != INVALID) // if param is reg
        cout << rgArr[p1ID - 1] << endl;
    else if ((p1ID = checkAddr(token[1])) != INVALID)// if param is address
        cout << static_cast<unsigned>(memArr[p1ID]) << endl;
    else { // param invalid
        cerr << "PRN -> the parameter is invalid. " << endl;
        return false;
    }
    return true;
}

bool ADD(int rgArr[], string token[]) {
    int r2ID;
    int r1ID = checkReg(token[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(token[2]); // second param num check
        if (rVal != INVALID) { // if second is num
            rgArr[r1ID - 1] += rVal;
        }
        else if ((r2ID = checkReg(token[2])) != INVALID) { // if second is reg
            rgArr[r1ID - 1] = rgArr[r1ID - 1] + rgArr[r2ID - 1];
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

bool ADD(int rgArr[], uint8_t memArr[], string token[]) {
    int p2ID;
    int p1ID = checkReg(token[1]);
    //ADD RX, #X  --> <This ADD instruction has only one format.> 
    if (p1ID != INVALID) {
        if ((p2ID = checkAddr(token[2])) != INVALID)
            rgArr[p1ID - 1] += memArr[p2ID];
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

bool SUB(int rgArr[], string token[]) {
    int r2ID;
    int r1ID = checkReg(token[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(token[2]); // second param num check
        if (rVal != -1) { // if second is num
            rgArr[r1ID - 1] -= rVal;
        }
        else if ((r2ID = checkReg(token[2])) != INVALID) { // if second is reg
            rgArr[r1ID - 1] = rgArr[r1ID - 1] - rgArr[r2ID - 1];
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

bool SUB(int rgArr[], uint8_t memArr[], string token[]) {
    int p2ID;
    int p1ID = checkReg(token[1]);
    //ADD RX, #X  --> <This ADD instruction has only one format.> 
    if (p1ID != INVALID) {
        if ((p2ID = checkAddr(token[2])) != INVALID)
            rgArr[p1ID - 1] -= memArr[p2ID];
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

int JMP(int rgArr[], string token[]) {
    int line;
    int regID = checkReg(token[1]);
    if (regID != INVALID) { // first param check
        int line = strToInt(token[2]); // second param num check
        if (line != INVALID && regID != 0) { // if second is num
            if (line == 0) {
                cerr << "JMP -> Invalid line number(ZERO). ";
                return INVALID;
            }
            if (rgArr[regID - 1] == 0)
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

int JMP(string token[]) {
    int line = strToInt(token[1]);
    if (line != INVALID && line != 0)
        return line;
    else {
        cerr << "JMP ->  The parameter is invalid. ";
        return INVALID;
    }

}

int JPN(int rgArr[], string token[]) {
    int line = 0;
    int regID = checkReg(token[1]);
    if (regID != INVALID) { // first param check
        int line = strToInt(token[2]); // second param num check
        if (line != INVALID) { // if second is num
            if (line == 0) {
                cerr << "JPN -> Invalid line number(ZERO). ";
                return INVALID;
            }
            if (rgArr[regID] <= 0)
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

void HLT(int rgArr[], uint8_t memArr[]) {
    cout << "---------------------------------------\n";
    cout << "CONTENT OF REGISTERS" << endl;
    for (int i = 0; i < MAX_REG; ++i) {
        cout.width(3);
        cout << rgArr[i] << " ";
    }
    cout << endl << endl << "CONTENT OF MEMORY" << endl;
    cout << "#0s #1s #2s #3s #4s #5s #6s #7s #8s #9s" << endl;
    for (int i = 0; i < MAX_MEM; ++i) {
        int value = static_cast<unsigned> (memArr[i]);
        if (i % DECIMAL == 0 && i != 0) // print 10 integer in a line
            cout << endl;
        cout.width(3);
        cout << value << " ";
    }
    cout << endl;
    cout << "---------------------------------------\n" << endl ;
    return;
}

void option(int rgArr[], string tokens[], int tokenSize) {
    cout << tokens[0];
    if (tokenSize >= 2)
        cout << " ";
    cout.width(2);
    cout << tokens[1];
    if (tokenSize >= 3)
        cout << ", ";
    cout.width(2);
    cout << tokens[2];
    cout << " – ";
    for (int j = 0; j < MAX_REG; ++j) {
        cout << "R" << j + 1 << "=" << rgArr[j];
        if (j != MAX_REG - 1)
            cout << ", ";
    }
    cout << endl;
    return;
}
//Option 2

void option(int rgArr[], uint8_t memArr[], string tokens[], int tokenSize) {
    
    cout << "MEMORY\n";
    for (int i = 0; i < MAX_MEM; ++i) {
        int value = static_cast<unsigned> (memArr[i]);
        if (i % DECIMAL == 0 && i != 0) // print 10 integer in a line
            cout << endl;
        cout.width(3);
        cout << value << " ";
    }
    cout << endl << endl;
    return;
}