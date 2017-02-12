/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 7
 */
/* 
 * File:   BigramDyn.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * 
 * Created on 18 Aralık 2016 Pazar, 21:48
 */

#include <cstddef>
#include <istream>
#include <ostream>

#include "BigramDyn.h"



template<class T>
BigramDyn<T>::BigramDyn() : BigramDyn(1) { }

template<class T>
BigramDyn<T>::BigramDyn(int datatype) : dataType(datatype), 
    size(0), sameBigrams(0) { 
    pairArr = nullptr;
}


template<class T>
BigramDyn<T>::BigramDyn(const BigramDyn& orig) {
    orig.pairArr = new pair<pair<T,T>,int> [this->size];
    for(int i = 0; i < this->size; ++i){
        orig.pairArr[i].first.first = this->pairArr[i].first.first;
        orig.pairArr[i].first.second = this->pairArr[i].first.second;
        orig.pairArr[i].second = this->pairArr[i].second;
    }
}

template<class T>
BigramDyn<T>::~BigramDyn() { 
    delete [] pairArr;
    pairArr = nullptr;
}



template<class T>
void BigramDyn<T>::readFile(string filename) throw (exception){
    
    if(pairArr != nullptr){
        delete [] pairArr;
        pairArr = nullptr;
    }
    
    fstream file (filename);
    if (file.fail())
        throw runtime_error("The File NOT found!\n");
    
    char c;
    int count = 0;
    
    while(file.get(c)){
        if(c == ' ' && file.peek() != EOF)
            ++count;
    }
    
    file.close();
    file.open(filename);
    
    setSize(count);
    
    if(getSize() <= 1)
        throw runtime_error("Insufficient element for a bigram!\n");
    
    pairArr = new pair<pair<T,T>,int> [getSize()];
    
    
    int i = 0;
        file >> first;
        file >> second;
     do{   
        if(file.fail())
            throw runtime_error("Input contains Inappropriate Datatype !\n");
        if(numOfGrams(first,second) == 0){
            pairArr[i].first.first = first;
            pairArr[i].first.second = second;   
            pairArr[i].second = 1;
            ++i;
        }
        else{
            int j = findPair(first,second);
            ++pairArr[j].second;
            ++sameBigrams;
        }
        
        first = second;
        file >> second;
        
    }while(!file.eof());
        
        if(file.fail())
        throw runtime_error("Input contains Inappropriate Datatype !\n");
    
    p.first=first, p.second= second;
    
        if(numOfGrams(first,second) == 0){
            pairArr[i].first.first = first;
            pairArr[i].first.second = second;   
            pairArr[i].second = 1;
        }
        else{
            int j = findPair(first,second);
            ++pairArr[j].second;
            ++sameBigrams;
        }
    
     sortPairArr(pairArr);
    
}
template <class T>
int BigramDyn<T>::findPair(T first, T second){
    for(int i = 0; i < getSize(); ++i){
        if(pairArr[i].first.first == first && 
            pairArr[i].first.second == second)
            return i;       
    }
    return -1;
}    
template <class T>
void BigramDyn<T>::swapPair(int index1, int index2){
    T temp;
    int tmp;
    temp = pairArr[index1].first.first;
    pairArr[index1].first.first = pairArr[index2].first.first;
    pairArr[index2].first.first = temp;
    
    temp = pairArr[index1].first.second;
    pairArr[index1].first.second = pairArr[index2].first.second;
    pairArr[index2].first.second = temp;
    
    tmp = pairArr[index1].second;
    pairArr[index1].second = pairArr[index2].second;
    pairArr[index2].second = tmp;
}

template <class T>
void BigramDyn<T>::sortPairArr(pair<pair<T,T>,int> *p){
   /* Bubble Sort
    * for(int i = 0; i < getSize() - sameBigrams ; ++i){
        for(int j = i + 1 ; j < getSize() - sameBigrams ; ++j){
            if(p[i].second < p[j].second){ //sort by value
                swapPair(i,j);               
            }
            else if(p[i].second == p[j].second){
                if(p[i].first.first > p[j].first.first)
                    swapPair(i,j);
                else if(p[i].first.first == p[j].first.first)
                    if(p[i].first.second > p[j].first.second)
                        swapPair(i,j);
            }
        }
    } */
    
    //Insertion sort
    int j;
		
    for (int i = 0; i < getSize() - sameBigrams; i++){
            j = i;

            while (j > 0 && p[j].second > p[j-1].second){
                      swapPair(j,j-1);
                      j--;
                      }
            }
    // sorts same amount repeated bigrams 
    for (int i = 1; i < getSize() - sameBigrams; i++){
        j = i;

        while (j > 0 && p[j].second == p[j-1].second 
            && p[j].first.first < p[j-1].first.first){

                    swapPair(j,j-1);
                    j--;

                  }
        }  
}

template<class T>
int BigramDyn<T>::numGrams(){
    
    return getSize();
}
    
template<class T>
int BigramDyn<T>::numOfGrams(T first, T second){
    
    for(int i = 0; i < getSize() - sameBigrams; ++i){
        if(pairArr[i].first.first == first && pairArr[i].first.second == second)
            return pairArr[i].second;       
    }
    return 0;
    
}
    
template<class T>
ostream& BigramDyn<T>::printAll(ostream& other) const {
    
    other << "_Bigrams_\n";
    for(int i = 0 ; i < size - sameBigrams;++i){
        for(int j = pairArr[i].second; j != 0; -- j)
        other << "(" << pairArr[i].first.first << " , " 
            << pairArr[i].first.second << ")" << endl;
    }
    
    
    
    return other;
}  
    
template<class T>
pair<T, T> BigramDyn<T>::maxGrams(){
    int max = 0;
    int index = 0;;
    for(int i= 0; i < size - sameBigrams;++i){
        if(max < pairArr[i].second){
            max = pairArr[i].second;
            index = i;
        }
    }
    return pairArr[index].first;
}