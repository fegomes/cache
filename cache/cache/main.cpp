// cache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cache.h"

#include <iostream>

int main()
{
	std::cout << "-------------------------------<int,std::string>---------------------------------" << std::endl;

	cache<int, std::string> lru(4);


	lru.add(1, "A");
	lru.add(2, "B");
	lru.add(3, "C");
	lru.add(4, "D");

	lru.get(1);

	lru.dump();

	lru.get(2);

	lru.dump();

	lru.get(3);

	lru.dump();

	lru.get(4);

	lru.dump();

	lru.get(1);

	lru.dump();

	lru.get(3);

	lru.dump();

	lru.destroy();

	lru.dump();

	std::cout << "-------------------------------<int,long>---------------------------------" << std::endl;

	cache<int, long> lru2(4);

	lru2.add(1, 2);
	lru2.add(2, 4);
	lru2.add(3, 6);
	lru2.add(4, 8);

	lru2.get(1);

	lru2.dump();

	lru2.get(2);

	lru2.dump();

	lru2.get(3);

	lru2.dump();

	lru2.get(4);

	lru2.dump();

	lru2.get(1);

	lru2.dump();

	std::cout << "-------------------------------<std::string,int>---------------------------------" << std::endl;

	cache<std::string, int> lru3(4);

	lru3.add("A", 2);
	lru3.add("B", 4);
	lru3.add("C", 6);
	lru3.add("D", 8);

	lru3.get("A");

	lru3.dump();

	lru3.get("B");

	lru3.dump();

	lru3.get("C");

	lru3.dump();

	lru3.get("D");

	lru3.dump();

	lru3.get("A");

	lru3.dump();

	lru3.get("C");

	lru3.dump();


	int pause;
	std::cin >> pause;

    return 0;
}

