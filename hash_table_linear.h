#pragma once
#ifndef HASH_TABLE_LINEAR_H
#define HASH_TABLE_LINEAR_H

#include <iostream>
#include "map.h"
using namespace std;

class hash_table_linear : public map {
private:
	int* table;
	size_t size;
	size_t capacity;
	void resize(size_t newCapacity);

public:
	hash_table_linear(size_t capacity);
	~hash_table_linear();
	int hash(int key);
	void insert(int key, int value) override;
	int find(int key) override;
	int remove(int key) override;
	void display() override;
};

#endif
