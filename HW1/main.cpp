/* 
 * File:   main.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * Student_ID : 141044041
 * Created on 07 Ekim 2016 Cuma
 */

// INCLUDES
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

// CONSTANT NUMBERS
const int MAX_LINE = 200; //Maximum number of lines reading from file
const int MAX_REG = 5; // Maximum Register in memory
const int DECIMAL = 10;
const int INVALID = -1;

/*** FUNCTION PROTOTYPES ***/

/**
 * @brief Delete part after ";" in string 
 * @param __st source string.
 * @return New string.
 */
string ignoreComment(string st);

/**
 * @brief Convert each character to UpperCase if it is lowercase letter.
 * @param __line a line as string from file.
 * @return new string full Uppercased.
 */
string upCaseStr(string line);

/**
 * @brief Split string to tokens from spaces and comma
 * @param __line a line as string from file.
 * @param __parse[] string array that is tokenized
 * @return Number of token
 */
int parseStr(string line, string parse[]);

/**
 * @brief Check validity of register name 
 * @param __reg source string
 * @return Register number if valid. -1 if not valid
 */
int checkReg(string reg);

/**
 * @brief Convert string to integer if all of them char digit 
 * @param __token source string
 * @return converted number if all number. -1 if not number
 */
int strToInt(string token);
/**
 * @brief Process instruction like MOV, ADD by calling them
 * @param __tokens[] string array includes tokens
 * @param __rgArr Registers in memory
 * @param __size Registers size
 * @return Register number if valid. -1 if not valid
 */
int process(string tokens[], int rgArr[], int size);

/**
 * @brief MOVE instruction copies value of 1th reg to 2nd reg OR constant to r1
 * @param __rgArr Register array in memory includes reg locations
 * @param __token tokens string includes register name or constants
 * @return true if parameters valid. false if param invalid
 */
bool MOV(int rgArr[], string token[]);

/**
 * @brief ADD instruction adds value of 1th reg to 2nd reg OR constant to r1
 * @param __rgArr Register array in memory includes reg locations
 * @param __token tokens string includes register name or constants
 * @return true if parameters valid. false if param invalid
 */
bool ADD(int rgArr[], string token[]);

/**
 * @brief SUB instruc subtracts the value of reg2 from reg1 and puts into reg1.
 * @param __rgArr Register array in memory includes reg locations.
 * @param __token tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool SUB(int rgArr[], string token[]);

/**
 * @brief PRN instruction print value of register or constant.
 * @param __rgArr Register array in memory includes reg locations.
 * @param __token tokens string includes register name or constants.
 * @return true if parameters valid. false if param invalid.
 */
bool PRN(int rgArr[], string token[]);

/**
 * @brief JMP instruction if register equals zero, jump to line. else contniue.
 * @param __rgArr Register array in memory includes reg locations.
 * @param __token tokens string includes register name or constants.
 * @return line number if parameters valid. false if param invalid.
 */
int JMP(int rgArr[], string token[]);

/**
 * @brief Overload of JMP jumps to given line
 * @param __token tokens string includes register name or constants.
 * @return line number if parameters valid. false if param invalid.
 */
int JMP(string token[]);

/**
 * @brief HLT instruc halts the program and prints the contents of all regs.
 */
void HLT(int rgArr[]);

int main(int argc, char** argv) {
    int line = 0, i = 0;
    int regArr[MAX_REG];
    string str[MAX_LINE];
    fstream inputFile;
   
    inputFile.open(argv[1]);
    if (!(inputFile.is_open())) {
        cerr << "File NOT found" << endl;
    }

    while (getline(inputFile, str[line])) { //find line number
        str[line] = ignoreComment(str[line]);
        str[line] = upCaseStr(str[line]);
        ++line;
    }
    inputFile.close();
   
    int exit = 0;
    i = 0;
    while (i < line && !exit) {
        string parses[MAX_LINE];
        int parseNum = parseStr(str[i], parses);
        if(strToInt(argv[2]) == 1){// MOV R1, 10 – R1=10, R2=0, R3=0, R4=0, R5=0
            cout << parses[0];
            if(parseNum >= 2)
                cout << " " << parses[1];
            if(parseNum >= 3)
                cout << ", " << parses[2]; 
            cout << " – ";
            for(int j=0;j < MAX_REG;++j){
                cout << "R" << j+1 << "=" << regArr[j];
                if(j != MAX_REG - 1)
                    cout << ", ";
                }
            cout << endl;
        }
        int status = process(parses, regArr, parseNum);
        if (status == -1) {
            cout << "main.cpp - ERROR LINE : " << i + 1 << endl;
            exit = 1;
        }
        else if (status != 0)
            i = status - 1;  // Line that JMP returns converts index 
        else ++i;
    }
//
//    cout << endl << "LAST CONTENT OF REGS" << endl;
//    for (int i = 0; i < 5; ++i)
//        cout << regArr[i] << " ";

    return 0;
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

// sadece ortada virgul olabilir

int parseStr(string line, string parse[]) {
    int k = 0;
    bool found = false;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] != ' ' && line[i] != ',') {
            parse[k] += line[i];
            found = true;
        }
        else if ((line[i] == ' ' || line[i] == ',') && found == true) {
            k++;
            found = false;
        }
        if (i == (line.size() - 1))
            k++;
    }
    return k;
}

int checkReg(string reg) {
    int regID;
    if (reg[0] == 'R') {
        reg = reg.substr(1);
        regID = strToInt(reg);
        if (regID != INVALID)
            return regID;
    }
    return INVALID;
}

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

int process(string tokens[], int rgArr[], int tokenSize) {
    int status = 0;
    if (tokens[0] == "MOV" && tokenSize == 3) {
        if (MOV(rgArr, tokens))
            status = 0;
    }
    else if (tokens[0] == "ADD" && tokenSize == 3) {
        if (ADD(rgArr, tokens))
            status = 0;
    }
    else if (tokens[0] == "SUB" && tokenSize == 3) {
        if (SUB(rgArr, tokens))
            status = 0;
    }
    else if (tokens[0] == "PRN" && tokenSize == 2) {
        if (PRN(rgArr, tokens))
            status = 0;
    }
    else if (tokens[0] == "JMP") {
        if (tokenSize == 3) {
            status = JMP(rgArr, tokens);
        }
        else if (tokenSize == 2) {
            status = JMP(tokens);
        }
    }
    else if (tokens[0] == "HLT" && tokenSize == 1) {
        status = 0;
        HLT(rgArr);
    }
    else {
        status = -1;
        cerr << "--> Undeclared Instruction or Error in Using parameter\n";
    }
    return status;
}

bool MOV(int rgArr[], string token[]) {
    int r2ID;
    int r1ID = checkReg(token[1]);
    if (r1ID != INVALID) { // first param check
        int rVal = strToInt(token[2]); // second param num check
        if (rVal != INVALID) { // if second not num
            rgArr[r1ID - 1 ] = rVal;
        }
        else if ((r2ID = checkReg(token[2])) != INVALID) { // if second is reg
            rgArr[r2ID - 1] = rgArr[r1ID - 1];
        }
        else { // second param invalid
            cout << "MOV -> second parameter is invalid" << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "MOV -> first register is invalid" << endl;
        return false;
    }
}

bool PRN(int rgArr[], string token[]) {
    int p1ID;
    int pVal = strToInt(token[1]); // param num check
    if (pVal != INVALID) { // if param not num
        cout << pVal << endl;
    }
    else if ((p1ID = checkReg(token[1])) != INVALID) { // if param is reg
        cout << rgArr[p1ID - 1] << endl;
    }
    else { // param invalid
        cout << "PRN -> the parameter is invalid " << endl;
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
            cout << "ADD -> second parameter is invalid " << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "ADD -> first register is invalid" << endl;
        return false;
    }

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
            cout << "SUB -> second parameter is invalid " << endl;
            return false;
        }
        return true;
    }
    else {
        cerr << "SUB -> first register is invalid" << endl;
        return false;
    }
}

int JMP(int rgArr[], string token[]) {
    int line;
    int regID = checkReg(token[1]);
    if (regID != INVALID) { // first param check
        int line = strToInt(token[2]); // second param num check
        if (line != INVALID && regID != 0) { // if second is num
            if (rgArr[regID - 1] == 0)
                return line;
            else
                return false; // if register is not zero, continue
        }

        else { // second param invalid
            cout << "JMP -> second parameter is invalid " << endl;
            return INVALID;
        }

    }
}

int JMP(string token[]) {
    int line = strToInt(token[1]);
    if (line != INVALID && line != 0)
        return line;
    else {
        cerr << "JMP ->  The parameter is invalid";
        return INVALID;
    }

}

void HLT(int rgArr[]) {
    cout << "CONTENT OF REGISTERS" << endl;
    for (int i = 0; i < MAX_REG; ++i) {
        cout << rgArr[i] << " ";
    }
    cout << endl;
    return;
}