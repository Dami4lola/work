#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "defs.h"

using namespace std;
template <typename T>
class Array {

	public:
		//constructor
		Array();
				
		//destructor
		~Array();
		
		//other
		void add(const T&);
		void remove(const T&);
        const T& operator[](int index) const;
        T& operator[](int index);
		int getSize() const;
		bool isFull() const;
	
	
	private:
		int numElements;
		T* elements;
	
};
template <typename T>
Array<T>::Array(){
	elements = new T[MAX_ARRAY];
	numElements = 0;
}

template <typename T>
Array<T>::~Array(){
	delete [] elements;
}

template <typename T>
void Array<T>::add(const T& t){
	if (numElements >= MAX_ARRAY);
  	elements[numElements++] = t;
}

template <typename T>
void Array<T>::remove(const T& t){
	int index = 0;
	while (index < numElements){
		if (t == elements[index]){
			--numElements;
			break;
		}
		++index;
	}

	while (index < numElements){
		elements[index] = elements[index + 1];
		++index;
	}
}

template <typename T>
int Array<T>::getSize() const{
	return numElements;
}

template <typename T>
bool Array<T>::isFull() const {
	return numElements >= MAX_ARRAY;
}

template <typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >= numElements) {
        cerr << "Array index out of bounds" << endl;
        exit(1);
    }
    return elements[index];
}

template <class T>
const T& Array<T>::operator[](int index) const {
    return elements[index];
}

#endif
