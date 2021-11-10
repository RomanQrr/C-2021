#include <iostream>
#include "List.h"
#include <Windows.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    List<int> list;
    AbstractIterator<int>* listIter = list.begin();

    list.insert(listIter, 3);
    list.insert(listIter, 2);
    list.insert(listIter, 1);

    cout << list << endl;

    list.clear();
    cout << list << endl;

    list.insert(listIter, 5);
    cout << list << endl;

    list.remove(listIter);
    cout << list << endl << endl;
    if (list.isEmpty()) cout << "Empty\n\n" << endl;

    list.insert(listIter, 3);
    list.insert(listIter, 2);
    list.insert(listIter, 1);
    list.insert(listIter, -1);
    list.insert(listIter, -6);

    cout << "List size:" << list.getSize() << endl;

    listIter->start();
    while (!listIter->finish()) {
        cout << listIter->see() << endl;
        listIter->next();
    }

    cout << endl;

    AbstractIterator<int>* iterator = list.findFirst(-1);

    while (!iterator->finish()) {
        cout << iterator->see() << endl;
        iterator->next();
    }

}
