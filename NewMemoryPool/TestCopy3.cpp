#include <iostream>
#include "MyMemoryPool.hpp"

int main()
{
	MyMemoryPool m;
	m.init(4, 11);

	int * val = reinterpret_cast<int*> (m.alloc());
	if (val != nullptr){
		*val = 10;
		std::cout << "Alloc : " << *val << std::endl;
	}
	int * val2 = reinterpret_cast<int*> (m.alloc());
	if (val2 != nullptr){
		*val2 = 11;
		std::cout << "Alloc : " << *val2 << std::endl;
	}
	int * val3 = reinterpret_cast<int*> (m.alloc());
	if (val3 != nullptr){
		*val3 = 12;
		std::cout << "Alloc : " << *val3 << std::endl;
	}
	int * val4 = reinterpret_cast<int*> (m.alloc());
	if (val4 != nullptr){
		*val4 = 13;
		std::cout << "Alloc : " << *val4 << std::endl;
	}

	m.printMemory();

	m.release(val3);
	m.release(val4);
	m.release(val);

	m.printMemory();

	int * val5 = reinterpret_cast<int*> (m.alloc());
	if (val5 != nullptr){
		*val5 = 20;
		std::cout << "Alloc : " << *val5 << std::endl;
	}
	int * val6 = reinterpret_cast<int*> (m.alloc());
	if (val6 != nullptr){
		*val6 = 21;
		std::cout << "Alloc : " << *val6 << std::endl;
	}
	int * val7 = reinterpret_cast<int*> (m.alloc());
	if (val7 != nullptr){
		*val7 = 22;
		std::cout << "Alloc : " << *val7 << std::endl;
	}
	int * val8 = reinterpret_cast<int*> (m.alloc());
	if (val8 != nullptr){
		*val8 = 23;
		std::cout << "Alloc : " << *val8 << std::endl;
	}

	m.printMemory();


	int * val9 = reinterpret_cast<int*> (m.alloc());
	if (val9 != nullptr) {
		*val9 = 24;
		std::cout << "Alloc : " << *val9 << std::endl;
	}

	m.release(val2);
	m.release(val6);

	m.printMemory();

	int * val10 = reinterpret_cast<int*> (m.alloc());
	if (val10 != nullptr) {
		*val10 = 24;
		std::cout << "Alloc : " << *val10 << std::endl;
	}

	m.printMemory();

	m.release(val5);
	m.release(val7);
	m.release(val10);
	m.release(val8);

	m.printMemory();

	val = reinterpret_cast<int*> (m.alloc());
	if (val != nullptr) {
		*val = 10;
		std::cout << "Alloc : " << *val << std::endl;
	}
	val2 = reinterpret_cast<int*> (m.alloc());
	if (val2 != nullptr) {
		*val2 = 11;
		std::cout << "Alloc : " << *val2 << std::endl;
	}
	val3 = reinterpret_cast<int*> (m.alloc());
	if (val3 != nullptr) {
		*val3 = 12;
		std::cout << "Alloc : " << *val3 << std::endl;
	}
	val4 = reinterpret_cast<int*> (m.alloc());
	if (val4 != nullptr) {
		*val4 = 13;
		std::cout << "Alloc : " << *val4 << std::endl;
	}
	val5 = reinterpret_cast<int*> (m.alloc());
	if (val5 != nullptr) {
		*val5 = 14;
		std::cout << "Alloc : " << *val5 << std::endl;
	}

	m.printMemory();

	getchar();
}