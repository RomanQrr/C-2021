#include <iostream>
#include <Windows.h>
#include "DynamicArray.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	DynamicArray d1(10, 2);
	DynamicArray d2(10, 2);

	// Œœ≈–¿“Œ–€

	std::cout << d1 << std::endl << d2 << std::endl;

	if (d1 == d2) {
		std::cout << "Arrays are equal\n";
	}
	else std::cout << "Arrays are not equal\n";

	if (d1 != d2) {
		std::cout << "Arrays are 'not equal'\n";
	}
	else std::cout << "Arrays are not 'not equal'\n";

	if (d1 <= d2) {
		std::cout << "First array is smaller or equal to the second\n";
	}
	else std::cout << "First array is not smaller or equal to the second\n";

	if (d1 >= d2) {
		std::cout << "First array is bigger or equal to the second\n";
	}
	else std::cout << "First array is not bigger or equal to the second\n";

	if (d1 < d2) {
		std::cout << "First array is smaller than the second\n";
	}
	else std::cout << "First array is not smaller than the second\n";

	if (d1 > d2) {
		std::cout << "First array is bigger than the second\n";
	}
	else std::cout << "First array is not bigger than the second\n";

	std::cout << "Array's sum equals to: \n" << d1 + d2 << std::endl;

	// Œœ≈–¿“Œ–€  ŒÕ≈÷
	// ‘”Õ ÷»»
	d1.reserve(10);
	d2.reserve(0);
	std::cout << d1 << "\n\n" << d2 << "\n\n";

	d1.pushBack(123);
	int k = d2.popBack();
	std::cout << "Added 123 into first array: \n" << d1 << "\n\nRemoved " << k << " out of second array\n" << d2 << "\n";

	d1.resize(3);
	d2.resize(7);
	std::cout << d1 << "\n\n" << d2;
}