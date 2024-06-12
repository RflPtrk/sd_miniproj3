#pragma once
#ifndef HASH_TABLE_CUCKOO_H
#define HASH_TABLE_CUCKOO_H

#include <iostream>
#include "map.h"
using namespace std;

class hash_table_cuckoo: public map {
private:
	int* table1;
	int* table2;
	int size;
	int capacity;
	int hash1(int key);
	int hash2(int key);
	void rehash(int newCapacity);
public:
	hash_table_cuckoo(int capacity);
	~hash_table_cuckoo();
	void insert(int key, int value)override;
	int remove(int key)override;
	int find(int key)override;
	void display()override;
};

#endif
