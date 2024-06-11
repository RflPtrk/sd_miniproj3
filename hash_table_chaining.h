#pragma once
#ifndef HASH_TABLE_CHAINING_H
#define HASH_TABLE_CHAINING_H

#include <iostream>
#include "map.h"
using namespace std;

struct NodeHT {
	int key;
	int value;
	NodeHT* next;
};

class hash_table_chaining: public map {
private:
	NodeHT** table;
	size_t size;
	size_t capacity;
	void resize(size_t newCapacity);
public:
	hash_table_chaining(int capacity);
	~hash_table_chaining();
	int hash(int key);
	void insert(int key, int value)override;
	int find(int key)override;
	int remove(int key)override;
	void display()override;
};

#endif