// cache.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cache.h"

#include <iostream>

int main()
{
	cache<int, int> lru(10);


	lru.add(1, 10);
	lru.add(2, 10);
	lru.add(3, 10);
	lru.add(4, 10);
	lru.add(5, 10);
	lru.add(6, 10);

	lru.get(3);

	//std::cout << lru.first->key << std::endl;
	//std::cout << lru.last->key << std::endl;

	lru.dump();

	cache<int, int> lru2(2);

	lru2.add(1, 1);
	lru2.add(2, 2);
	lru2.get(1);
	lru2.get(2);
	lru2.add(4, 4);   
	lru2.get(1) ;
	lru2.get(3);
	lru2.get(4) ;
	lru2.get(2);
	lru2.add(3, 2);

	lru2.dump();
	int i;
	std::cin >> i;
    return 0;
}

