#pragma once
#ifndef SD3_MAP_H
#define SD3_MAP_H

class map {
	virtual void insert(int key, int value) = 0;
	virtual int remove(int key) = 0;
	virtual void display() = 0;
	virtual int find(int key) = 0;
};

#endif