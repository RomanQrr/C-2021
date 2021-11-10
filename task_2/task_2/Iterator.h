#ifndef INC_2_CPP_ITERATOR_H
#define INC_2_CPP_ITERATOR_H

#include "RingBuffer.h"

template<typename T>
class Iterator {
private:
    RingBuffer<T> queue;
    long curIdx;
    bool allIterated;

    Iterator() {}

public:
    // Привязка буфера к итератору
    Iterator(RingBuffer<T> &rBuf) {
        queue = rBuf;
        curIdx = rBuf.start;
        allIterated = false;
    }

    // начать перебор элементов
    void start() {
        if (queue.start == queue.end)
            throw std::length_error("Queue is empty!");
        curIdx = queue.start;
        allIterated = false;
    }

    // перейти к следующему элементу
    void next() {
        if (curIdx == queue.end)
            throw std::length_error("Iterator is at the end of the queue!");
        curIdx = ++curIdx % queue.size;
        if (curIdx == queue.end)
            allIterated = true;
    }

    // проверка, все ли проитерировано
    bool finish() {
        return allIterated;
    }

    // получить очередной элемент очереди
    T getValue() {
        return queue.arr[curIdx];
    }
};

#endif