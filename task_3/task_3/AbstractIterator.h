#pragma once

template <typename T>
class AbstractIterator
{
public:
	virtual void start() = 0;
	virtual T see() = 0;
	virtual bool finish() = 0;
	virtual void next() = 0;
};

