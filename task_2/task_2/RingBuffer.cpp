#include "RingBuffer.h"

template<typename T>
RingBuffer<T>::RingBuffer(long len) {
    try {
        if (len < 0)
            throw std::invalid_argument("Size < 0");
        arr = new T[len + 1];
        size = len + 1;
        start = 0;
        end = 0;
    }
    catch (std::bad_alloc &) {
        throw std::invalid_argument("There is no memory");
    }
}

template<typename T>
RingBuffer<T>::~RingBuffer() {
    delete[] arr;
    size = 0;
    start = 0;
    end = 0;
}

template<typename T>
RingBuffer<T> &RingBuffer<T>::push(T elem) {
    if (this->isFull())
        throw std::overflow_error("Buffer overflow!");
    arr[end] = elem;
    end = ++end % size;
    return *this;
}

template<typename T>
T RingBuffer<T>::pop() {
    if (this->isEmpty())
        throw std::invalid_argument("Buffer is empty!");
    T val = arr[start];
    start = ++start % size;
    return val;
}

template<typename T>
T RingBuffer<T>::peek() {
    if (this->isEmpty())
        throw std::invalid_argument("Buffer is empty!");
    return arr[start];
}

template<typename T>
inline unsigned long RingBuffer<T>::len() {
    int dif = end - start;
    return dif < 0 ? size - dif : dif;
}

template<typename T>
inline void RingBuffer<T>::makeEmpty() {
    start = 0;
    end = 0;
}

template<typename T>
inline bool RingBuffer<T>::isEmpty() {
    return start == end;
}

template<typename T>
inline bool RingBuffer<T>::isFull() {
    return (end + 1) % size == start;
}
