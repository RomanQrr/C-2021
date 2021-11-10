#include "DynamicArray.h"
#include <iostream>
#include <execution>
#include <algorithm>

#define DEFAULT_SIZE 10

// По умолчанию
DynamicArray::DynamicArray() {
	arr = new int[DEFAULT_SIZE];
	size = DEFAULT_SIZE;
	realSize = 0;

	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

// По размеру
DynamicArray::DynamicArray(int size) {
	arr = new int[size];
	this->size = size;
	realSize = size;

	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

// По размеру со значением по умолчанию
DynamicArray::DynamicArray(int size, int n) {
	arr = new int[size];
	this->size = size;
	realSize = size;

	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}

// С резервом
DynamicArray::DynamicArray(int size, int n, int reserve)
{
	arr = new int[size + reserve];
	this->size = size + reserve;
	realSize = size;

	for (int i = 0; i < size; i++) {
		arr[i] = n;
	}
}

// Конструктор копирования
DynamicArray::DynamicArray(DynamicArray& dynArr) {
	arr = new int[dynArr.size];
	this->size = dynArr.size;
	this->realSize = dynArr.realSize;

	for (int i = 0; i < realSize; i++) {
		arr[i] = dynArr.arr[i];
	}
}

// Конструктор перемещения
DynamicArray::DynamicArray(DynamicArray&& dynArr) :
	arr(dynArr.arr), size(dynArr.size), realSize(dynArr.realSize)
{
	dynArr.arr = nullptr;
}

DynamicArray::~DynamicArray() {
	delete[] arr;
	arr = nullptr;
}

int DynamicArray::getSize() {
	return realSize;
}

int& DynamicArray::operator [] (int id) {
	try {
		if (id < 0 || id >= realSize) {
			throw new std::exception("Incorrect id.");
		}
		return arr[id];
	}
	catch (std::exception exception) {
		std::cout << "(!) Error: " << exception.what();
	}
}

void DynamicArray::resize(int newSize) {
	if (newSize > size) {
		this->reserve(newSize - size);
	}
	for (int i = realSize; i < newSize; i++) {
		arr[i] = 0;
	}
	realSize = newSize;
}

void DynamicArray::reserve(int n)
{
	try {
		if (n <= 0) {
			throw std::exception("Incorrect reserved.");
		}
		int* ar = new int[size + n];
		int i;
		for (i = 0; i < size; i++) {
			ar[i] = arr[i];
		}
		for (; i < size + n; i++) {
			ar[i] = 0;
		}
		delete[] arr; arr = nullptr;
		arr = ar;
		size += n;
	}
	catch (std::exception exception) {
		std::cout << "(!) Error: " << exception.what() << std::endl;
	}
}

int DynamicArray::capacity()
{
	return size;
}

void DynamicArray::pushBack(int x)
{
	if (realSize == size) {
		this->reserve(DEFAULT_SIZE);
	}
	arr[realSize] = x;
	realSize++;
}

int DynamicArray::popBack()
{
	try {
		if (realSize <= 0) throw std::exception("Size is null");
		realSize--;
		return arr[realSize];
	}
	catch (std::exception exc) {
		std::cout << exc.what();
	}
}

DynamicArray& DynamicArray::operator = (DynamicArray& dynArr) {
	delete[] arr; arr = nullptr;

	arr = new int[dynArr.size];
	this->size = dynArr.size;
	this->realSize = dynArr.realSize;

	for (int i = 0; i < realSize; i++) {
		arr[i] = dynArr.arr[i];
	}
	return *this;
}

DynamicArray& DynamicArray::operator = (DynamicArray&& dynArr) {
	delete[] arr; arr = nullptr;

	arr = dynArr.arr;
	size = dynArr.size;
	realSize = dynArr.realSize;

	dynArr.arr = nullptr;
	return *this;
}

bool operator==(DynamicArray arr1, DynamicArray arr2)
{
	try {

		if (arr1.getSize() != arr2.getSize()) {
			throw std::exception("Different lengths DynamicArrays.");
		}

		for (int i = 0; i < arr1.getSize(); i++) {
			if (arr1.arr[i] != arr2.arr[i]) {
				return false;
			}
		}
		return true;
	}
	catch (std::exception exception) {
		std::cout << "(!) Error: " << exception.what() << std::endl;
	}
}

bool operator!=(DynamicArray arr1, DynamicArray arr2)
{
	try {

		if (arr1.getSize() != arr2.getSize()) {
			throw std::exception("Different lengths DynamicArrays.");
		}

		for (int i = 0; i < arr1.getSize(); i++) {
			if (arr1.arr[i] != arr2.arr[i]) {
				return true;
			}
		}
		return false;
	}
	catch (std::exception exception) {
		std::cout << "(!) Error: " << exception.what() << std::endl;
	}
}

bool operator<=(DynamicArray arr1, DynamicArray arr2)
{
	if (arr1.getSize() != arr2.getSize()) {
		return arr1.getSize() < arr2.getSize();
	}

	for (int i = 0; i < arr1.getSize(); i++) {
		if (arr1.arr[i] != arr2.arr[i]) {
			return arr1.arr[i] < arr2.arr[i];
		}
	}
	return true;
}

bool operator>=(DynamicArray arr1, DynamicArray arr2)
{
	if (arr1.getSize() != arr2.getSize()) {
		return arr1.getSize() > arr2.getSize();
	}

	for (int i = 0; i < arr1.getSize(); i++) {
		if (arr1.arr[i] != arr2.arr[i]) {
			return arr1.arr[i] > arr2.arr[i];
		}
	}
	return true;
}

bool operator>(DynamicArray arr1, DynamicArray arr2)
{
	if (arr1.getSize() != arr2.getSize()) {
		return arr1.getSize() > arr2.getSize();
	}

	for (int i = 0; i < arr1.getSize(); i++) {
		if (arr1.arr[i] != arr2.arr[i]) {
			return arr1.arr[i] > arr2.arr[i];
		}
	}
	return false;
}

bool operator<(DynamicArray arr1, DynamicArray arr2)
{
	if (arr1.getSize() != arr2.getSize()) {
		return arr1.getSize() < arr2.getSize();
	}

	for (int i = 0; i < arr1.getSize(); i++) {
		if (arr1.arr[i] != arr2.arr[i]) {
			return arr1.arr[i] < arr2.arr[i];
		}
	}
	return false;
}

DynamicArray operator+(const DynamicArray& arr1, const DynamicArray& arr2)
{
	DynamicArray arr;
	arr.size = arr1.size + arr2.size;
	arr.realSize = arr1.realSize + arr2.realSize;
	delete[] arr.arr; arr.arr = nullptr;
	arr.arr = new int[arr.size];

	int i = 0;
	for (i = 0; i < arr1.realSize; i++) {
		arr.arr[i] = arr1.arr[i];
	}
	for (i = 0; i < arr2.realSize; i++) {
		arr.arr[i + arr1.realSize] = arr2.arr[i];
	}

	return arr;
}

std::istream& operator>>(std::istream& in, DynamicArray& arr)
{
	delete[] arr.arr; arr.arr = nullptr;
	in >> arr.size;
	arr.realSize = arr.size;
	arr.arr = new int[arr.size];
	for (int i = 0; i < arr.size; i++) {
		in >> arr.arr[i];
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const DynamicArray& arr)
{
	out << "DynamicArray:\nSize = " << arr.realSize << "\nReserve = " << arr.size - arr.realSize << "\n";
	for (int i = 0; i < arr.realSize; i++) {
		out << arr.arr[i] << " ";
	}
	return out;
}
