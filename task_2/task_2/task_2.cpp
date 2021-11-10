#include "Iterator.h"
#include "RingBuffer.cpp"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	int size = 10;
	RingBuffer<int> destructorTest(size);
	destructorTest.~RingBuffer();
	RingBuffer<int> rb(size);
	rb.push(1);
	rb.push(2);
	rb.push(3);
	
	while (!rb.isEmpty()) {
		cout << rb.pop() << endl;
	}

	cout << "Current length of the buffer: " << rb.len() << endl << endl;

	rb.push(1);
	rb.push(2);
	rb.push(3);
	rb.makeEmpty();
	if (rb.isEmpty()) {
		cout << "Buffer is empty." << endl << endl;
	}
	else {
		cout << "Buffer is not empty." << endl << endl;
	}

	int i = 0;
	while (!rb.isFull()) {
		rb.push(i);
		i++;
	}
	if (rb.peek() == size - 1) {
		cout << "'isFull' works fine." << endl << endl;
	}
	else {
		cout << "What in tarnation... 'isFull' works wonky! \n\n";
	}
	cout << "Current length of the buffer: " << rb.len() << endl << endl;

	Iterator<int> iterator(rb);
	cout << "Current start of the queue: " << iterator.getValue() << endl << endl;

	cout << "Current contents of the queue: " << endl;

	while (!iterator.finish()) {
		cout << iterator.getValue() << endl;
		iterator.next();
	}

	iterator.start();
	if (iterator.finish())
		cout << "start function doesnt work";
	else
		cout << "start function works";

}