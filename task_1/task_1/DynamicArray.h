#pragma once
#include <iostream>

class DynamicArray
{
private:
	int* arr;
	int size;
	int realSize;

public:
	DynamicArray();
	DynamicArray(int size);
	DynamicArray(int size, int n);
	DynamicArray(int size, int n, int reserve);
	DynamicArray(DynamicArray& dynArr);
	DynamicArray(DynamicArray&& dynArr);
	~DynamicArray();
	int getSize();
	int& operator [] (int id);
	void resize(int newSize);
	void reserve(int n);
	int capacity();
	void pushBack(int x);
	int popBack();

	DynamicArray& operator = (DynamicArray& dynArr);
	DynamicArray& operator = (DynamicArray&& dynArr);
	friend bool operator == (DynamicArray arr1, DynamicArray arr2);
	friend bool operator != (DynamicArray arr1, DynamicArray arr2);
	friend bool operator <= (DynamicArray arr1, DynamicArray arr2);
	friend bool operator >= (DynamicArray arr1, DynamicArray arr2);
	friend bool operator > (DynamicArray arr1, DynamicArray arr2);
	friend bool operator < (DynamicArray arr1, DynamicArray arr2);
	friend DynamicArray operator + (const DynamicArray& arr1, const DynamicArray& arr2);
	friend std::istream& operator >> (std::istream& in, DynamicArray& arr);
	friend std::ostream& operator << (std::ostream& out, const DynamicArray& arr);
};

