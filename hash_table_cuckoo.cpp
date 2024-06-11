#include "hash_table_cuckoo.h"

// Funkcja haszuj¹ca 1
int HashTableCuckoo::hash1(int key)
{
    return key % capacity;
}

// Funkcja haszuj¹ca 2
int HashTableCuckoo::hash2(int key)
{
    return 1 + (key % (capacity - 1));
}

// Zmiana pojemnosci tablicy
void HashTableCuckoo::rehash(int newCapacity)
{
	// Dotychczasowe tablice i pojemnosc
	int* oldTable1 = table1;
	int* oldTable2 = table2;
	int oldCapacity = capacity;

	// Nowe tablice
	size = 0;
	capacity = newCapacity;
	table1 = new int[capacity];
	table2 = new int[capacity];
	for (int i = 0; i < capacity; i++)
	{
		table1[i] = -1;
		table2[i] = -1;

	}
	// Przenoszenie elementów ze starych tablic do nowych
	for (int i = 0; i < oldCapacity; i++)
	{
		if (oldTable1[i] != -1)
		{
			insert(i, oldTable1[i]);
		}
		if (oldTable2[i] != -1)
		{
			insert(i, oldTable2[i]);
		}
	}
	delete[] oldTable1;
	delete[] oldTable2;
}

// Konstruktor
HashTableCuckoo::HashTableCuckoo(int capacity)
{
	this->capacity = capacity;
	this->size = 0;
	// Inicjalizacja tablic
	this->table1 = new int[capacity];
	this->table2 = new int[capacity];
	for (int i = 0; i < capacity; i++)
	{
		table1[i] = -1;
		table2[i] = -1;
	}
}

// Destruktor
HashTableCuckoo::~HashTableCuckoo()
{
	delete[] table1;
	delete[] table2;
	capacity = 0;
	size = 0;
}

// Wstawienie elementu
void HashTableCuckoo::insert(int key, int value)
{
	int index = hash1(key);
	int* currentTable = table1;

	// próbuje wstawiæ element do ktorejs tablicy
	for (int i = 0; i < 10; i++) {
		if (currentTable[index] == -1) {
			currentTable[index] = value;
			size++;
			return;
		}

		// Zamiana wartoœci i przesuniêcie
		std::swap(currentTable[index], value);

		// Prze³¹cza tablice i oblicza nowy indeks
		if (currentTable == table1) {
			currentTable = table2;
			index = (index + hash2(key)) % capacity;
		}
		else {
			currentTable = table1;
			index = hash1(key);
		}
	}

	// Jeœli nie uda siê znalezc wolnego miejsca, zmienia rozmiar i ponawia próbê
	rehash(capacity * 2);
	insert(key, value);
}

// Usuwanie elementu
int HashTableCuckoo::remove(int key)
{
	int index = hash1(key);
	int* currentTable = table1;

	// Przeszukuje obie tablicy w poszukiwaniu klucza
	for (int i = 0; i < 10; i++) {
		if (currentTable[index] != -1) {
			currentTable[index] = -1;
			size--;
			return;
		}

		// Prze³¹cza tablice i oblicza nowy indeks
		if (currentTable == table1) {
			currentTable = table2;
			index = (index + hash2(key)) % capacity;
		}
		else {
			currentTable = table1;
			index = (index + hash1(key)) % capacity;
		}
	}

	// Jesli liczba elementów jest zbyt ma³a, zmniejsza rozmiar tablicy
	if (size <= capacity * 0.3) {
		rehash(capacity / 2);
		remove(key);
	}
	else {
		cout << "Key not found" << endl;
	}
}

// Wyszukanie wartoœci na podstawie klucza
int HashTableCuckoo::find(int key)
{
	int index = hash1(key);
	int* currentTable = table1;

	// Przeszukuje obie tablicy w poszukiwaniu klucza
	for (int i = 0; i < 10; i++) {
		if (currentTable[index] != -1) {
			return 0;
		}

		// Prze³¹cza tablice i oblicza nowy indeks
		if (currentTable == table1) {
			currentTable = table2;
			index = hash2(key);
		}
		else {
			currentTable = table1;
			index = hash1(key);
		}
	}
	return -1;
}

// Wyœwietlenie zawartosci tablic
void HashTableCuckoo::display()
{
	cout << "Table 1: ";
	for (int i = 0; i < capacity; i++)
	{
		cout << table1[i] << " ";
	}
	cout << endl;

	cout << "Table 2: ";
	for (int i = 0; i < capacity; i++)
	{
		cout << table2[i] << " ";
	}
	cout << endl;
}
