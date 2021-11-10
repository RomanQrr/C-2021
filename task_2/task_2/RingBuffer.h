#ifndef INC_2_CPP_RINGBUFFER_H
#define INC_2_CPP_RINGBUFFER_H

#include <new>
#include <stdexcept>

template<typename T>
class Iterator;

template<typename T>
class RingBuffer {

private:
    T *arr;                   // массив для хранения элементов
    long start;      // хвост
    long end;        // голова
    long size;       // длина массива (не очереди)

    RingBuffer() {}

public:
    RingBuffer(long len);

    ~RingBuffer();

    RingBuffer<T> &push(T elem);

    T pop();

    T peek();

    inline unsigned long len();

    inline void makeEmpty();

    inline bool isEmpty();

    inline bool isFull();

    friend class Iterator<T>;
};

#endif