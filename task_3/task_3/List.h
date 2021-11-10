#pragma once
#include "AbstractIterator.h"
#include "AbstractList.h"
#include <iostream>

template <typename T>
class List : virtual public AbstractList<T> {
private:
    class Data;
public:

    class ListIterator : virtual public AbstractIterator<T> {
    private:
        Data* cur;
        Data* begin;
        friend class List<T>;
    public:
        ListIterator() : begin(0), cur(0) {}
        ListIterator(Data* data) : begin(data), cur(data) {}
        ListIterator(ListIterator& iter) : cur(cur), begin(begin) {}

        void start() override {
            cur = begin->next;
        }

        T see() override {
            return cur->temp;
        }

        bool finish() override {
            return cur == begin;
        }

        void next() override {
            if (!finish())
                cur = cur->next;
        }
    };

private:

    class Data {
        friend class List;
        friend class ListIterator;
        T temp;
        Data* next;
        Data* prev;
    public:
        Data(T temp, Data* next, Data* prev) :
            temp(temp), next(next), prev(prev) {}

        Data() {}
        friend std::ostream& operator<< (std::ostream& out, const List<T>& list);
    };

    friend class Data;

    Data* tail;

    int size;

public:


    friend class ListIterator;

private:
    ListIterator first;
public:

    List();
    void insert(AbstractIterator<T>* iterator, T temp) override;
    T remove(AbstractIterator<T>* iterator) override;
    AbstractIterator<T>* findFirst(T temp) override;
    void clear() override;
    bool isEmpty() override;
    int getSize() override;
    AbstractIterator<T>* begin() override;

    friend std::ostream& operator<< (std::ostream& out, const List<T>& list) {
        out << "List:\n";
        List<T>::Data* temp = list.tail->next;
        while (temp != list.tail) {
            out << temp->temp << " ";
            temp = temp->next;
        }
        return out;
    }
};

template<typename T>
List<T>::List() {
    tail = new Data();
    tail->prev = tail;
    tail->next = tail;

    first = ListIterator(tail);
}

template<typename T>
void List<T>::insert(AbstractIterator<T>* iterator, T temp) {
    List<T>::ListIterator* iter = dynamic_cast<List<T>::ListIterator*>(iterator);
    Data* it = iter->cur;
    //текущий элемент
    Data* t = tail;
    do {
        if (t == it) {
            Data* data = new Data(temp, nullptr, nullptr);

            data->next = it->next;
            it->next->prev = data;
            data->prev = it;
            it->next = data;

            first = ListIterator(tail);
            size++;
        }
        t = t->next;
    } while (t != tail);
}

template<typename T>
T List<T>::remove(AbstractIterator<T>* iterator) {
    Data* it = (dynamic_cast<List<T>::ListIterator*>(iterator))->cur->next;;

    Data* temp = tail->next;

    while (temp != tail) {
        if (temp == it) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            size--;
            return temp->temp;
        }
        temp = temp->next;
    }
    return NULL;
}

template<typename T>
AbstractIterator<T>* List<T>::findFirst(T temp) {
    Data* it = tail;

    do {
        it = it->next;
    } while (it->temp != temp && it != tail);


    ListIterator* t = new ListIterator(it);
    t->begin = tail;

    return t;
}

template<typename T>
void List<T>::clear() {
    Data* temp = tail->next;
    for (Data* sn = tail->next; sn != tail;) {
        sn = sn->next;
        delete temp;
        temp = sn;
    }
    tail->next = tail;
    tail->prev = tail;
    size = 0;
}

template<typename T>
bool List<T>::isEmpty() {
    return tail->next == tail;
}

template<typename T>
int List<T>::getSize() {
    return size;
}

template<typename T>
AbstractIterator<T>* List<T>::begin() {
    AbstractIterator<T>* temp = new ListIterator(tail->next);
    return temp;
}
