#include <iostream>
#include "LinckedHT.h"
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HashTable<int, char> table(5);
	table.add(3, 'c');
	table.add(8, 'd');
	table.add(2, 'b');
	table.add(1, 'e');
	table.add(4, 'k');
	table.add(9, 'y');
	table.add(6, 'n');
	table.add(11, 'g');
	table.add(6, 'h');
	table.add(17, 'L');
	std::cout << table.find(9) << std::endl;
	std::cout << table.find(6) << std::endl;
	table.remove(9);
	try {
		table.find(9);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	table.remove(3);
	table.remove(11);
	std::cout << table.find(17) << std::endl;

	HashTable<int, char> table1(2);
	table1 = table;
	table.doEmpty();
	HashTable<int, char>::Iterator<int, char>* it = table1.iterator();
	while (!it->isFinish())
	{
		std::cout << "[" << it->getKey() << " : " << it->getValue() << "], ";
		it->next();
	}

	cout << "\n\nLINKED\n\n" << endl;
	LinckedHT<int, char> table2(5);
	table2.add(3, 'c');
	table2.add(8, 'd');
	table2.add(2, 'b');
	table2.add(1, 'e');
	table2.add(4, 'k');
	table2.add(9, 'y');
	table2.add(6, 'n');
	table2.add(11, 'g');
	table2.add(6, 'h');
	table2.add(17, 'L');
	std::cout << table2.find(9) << std::endl;
	std::cout << table2.find(6) << std::endl;
	table2.remove(9);
	try {
		table2.find(9);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	try {
		table2.remove(99);
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	table2.remove(3);
	table2.remove(11);
	std::cout << table2.find(17) << std::endl;
	EntriesIterator<int, char>* it1 = table2.iterator();
	while (!it1->isFinish())
	{
		std::cout << "[" << it1->getKey() << " : " << it1->getValue() << "], ";
		it1->next();
	}
	std::cout << "[" << it1->getKey() << " : " << it1->getValue() << "]";
	std::cout << std::endl;
	LinckedHT<int, char> table3(2);
	table3 = table2;
	table2.doEmpty();
	EntriesIterator<int, char>* it1e = table2.iterator();
	while (!it1e->isFinish())
	{
		std::cout << "[" << it1e->getKey() << " : " << it1e->getValue() << "], ";
		it1e->next();
	}
	if (!table2.isEmpty())
		std::cout << "[" << it1e->getKey() << " : " << it1e->getValue() << "]";

}
