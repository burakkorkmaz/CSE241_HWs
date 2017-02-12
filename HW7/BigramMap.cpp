/* 
 *      Gebze Technical University
 *  Department of Computer Engineering
 * CSE 241/505 Object Oriented Programming
 *          Homework # 7
 */
/* 
 * File:   BigramMap.cpp
 * Author: Burak Kağan Korkmaz <bkorkmaz@gtu.edu.tr>
 * 
 * Created on 18 Aralık 2016 Pazar, 21:48
 */

#include "BigramMap.h"

template <class T>
BigramMap<T>::BigramMap() { }

template<class T>
BigramMap<T>::BigramMap(int datatype) {
    this->dataType = datatype;
}

template <class T>
void BigramMap<T>::readFile(string filename) throw (exception) {

    fstream file(filename);
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
    if(count <= 1)
        throw runtime_error("Insufficient element for a bigram!\n");

        file >> first;
        file >> second;
    do {
        if(file.fail())
            throw runtime_error("Input contains Inappropriate Datatype !\n");
        if (myMap.find(pair<T, T>(first, second)) == myMap.end()){
            // aynısı   pair<pair<T,T>,int>(pair<T,T>(first,second),1)
            myMap.insert(make_pair(make_pair(first, second), 1));}
        else{
            myMap[pair<T, T>(first, second)] += 1;}
        
        first = second;
        file >> second;
        
    } while (!file.eof());
    
    if (myMap.find(pair<T, T>(first, second)) == myMap.end())
        myMap.insert(make_pair(make_pair(first, second), 1));
    else
        myMap[pair<T, T>(first, second)] += 1;
    
    file.close();
  
}


template<class T>
int BigramMap<T>::numGrams() {
    int size = 0;
    for(auto it = myMap.begin(); it != myMap.end();++it){
        size += it->second;
    }
    return size;
}

template<class T>
int BigramMap<T>::numOfGrams(T first, T second) {
    return myMap[pair<T, T>(first, second)];
}

template<class T>
ostream& BigramMap<T>::printAll( ostream& other) const{

    other << "_Bigrams_\n";
    map<pair<T,T>, int> copy;
    //copying myMap
    for(auto it = myMap.begin(); it != myMap.end(); ++it){
        copy.insert(make_pair(make_pair(it->first.first,
            it->first.second), it ->second));
    }
       
    bool endOf = true;

  // Sorting Process
    for(auto itt = copy.begin(); itt != copy.end() && endOf; ){
        int counter = 0;
        int tempCounter = 0;
        int maxValue = 0;
        
        for(auto it = copy.begin(); it != copy.end(); ++it){
            
            if(it->second > maxValue){
                
                maxValue = it->second;
                counter = tempCounter;
            }      
            ++tempCounter;  
        }
        auto itm= copy.begin();
        int a;
        
         for( a = 0 ; a < counter;  ++a ){
            
             ++itm;
         }
        
        if (itm != copy.end()){
            for(int a = itm->second; a != 0 ; --a)
                other << "(" << itm->first.first << " , " << itm->first.second 
                    << ")\n";
            copy.erase(itm);
        }else{
            endOf = false;
        }
    }
    return other;
}
template<class T>
pair<T, T> BigramMap<T>::maxGrams() {

    auto a = myMap.begin();
    for(auto it = myMap.begin(), x = it->second;
        it != myMap.end();
        ++it){
        
        if(x < it->second){
            x = it->second;
            a = it;
        }
    }
    return a->first;

    //    for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    //    std::cout << it->first << " => " << it->second << '\n';
}