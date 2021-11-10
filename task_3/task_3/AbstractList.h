#pragma once
#include "AbstractIterator.h"

template <typename T>
class AbstractList
{
public:
	virtual void insert(AbstractIterator<T>*, T x) = 0;
	virtual T remove(AbstractIterator<T>*) = 0;
	virtual AbstractIterator<T>* findFirst(T x) = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
	virtual int getSize() = 0;
	virtual AbstractIterator<T>* begin() = 0;
};

