#include "hash_table_chaining.h"

// Zmiana rozmiaru tablicy mieszaj�cej
void hash_table_chaining::resize(size_t newCapacity)
{
	// Nowa tablicy o nowej pojemno�ci
	NodeHT** newTable = new NodeHT * [newCapacity];
	// Wypelnienie nowej tablicy nullami
	for (size_t i = 0; i < newCapacity; i++) {
		newTable[i] = NULL;
	}
	// Przeniesienie element�w starej tablicy do nowej
	for (size_t i = 0; i < capacity; i++) {
		NodeHT* current = table[i];
		while (current != nullptr) {
			NodeHT* next = current->next; // Wska�nik do nast�pnego elementu
			int index = current->key % newCapacity; // Nowy indeks dla elementu w nowej tablicy
			if (newTable[index] == NULL) {
				newTable[index] = table[i];
				current->next = nullptr;
			}
			else {
				NodeHT* temp = table[index];
				while (temp->next != nullptr) {
					temp = temp->next;
				}
				temp->next = newTable[i];
				current->next = nullptr;
			}
			current = next; // Przej�cie do nast�pnego elementu
		}
	}
	delete[] table;
	table = newTable;
	capacity = newCapacity;
}

// Konstruktor inicjalizuj�cy tablic� mieszaj�c� o podanej pojemno�ci
hash_table_chaining::hash_table_chaining(int capacity)
{
	this->capacity = capacity;
	table = new NodeHT * [capacity];
	for (size_t i = 0; i < capacity; i++) {
		table[i] = NULL;
	}
	size = 0;
}

// Destruktor usuwaj�cy wszystkie elementy z tablicy mieszaj�cej
hash_table_chaining::~hash_table_chaining()
{
	NodeHT* current = table[0];
	NodeHT* next = nullptr;
	while (current != nullptr) {
		next = current->next;
		delete current;
		current = next;
	}
	delete[] table;
	size = 0;
	capacity = 0;
}

// Funkcja haszuj�ca
int hash_table_chaining::hash(int key)
{
	return key % capacity;
}

// Wstawienie nowej pary klucz-warto�� do tablicy mieszaj�cej
void hash_table_chaining::insert(int key, int value)
{
	int index = hash(key);
	NodeHT* newNodeHT = new NodeHT;
	newNodeHT->key = key;
	newNodeHT->value = value;
	newNodeHT->next = nullptr;
	// Je�li miejsce jest puste, przypisz do niego nowy w�ze�
	if (table[index] == NULL) {
		table[index] = newNodeHT;
	}
	else { // Je�li miejsce nie jest puste, dodaj nowy w�ze� na ko�cu listy
		NodeHT* current = table[index];
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNodeHT;
	}
	size++;

	// Je�li liczba element�w przekracza pojemno��, podw�j pojemno��
	if (size >= capacity) {
		resize(capacity * 2);
	}
}

// Wyszukanie warto�ci na podstawie klucza
int hash_table_chaining::find(int key)
{
	int index = hash(key);
	// Je�li tablica jest pusta, zako�cz metode
	if (table[index] == NULL) {
		return -1;
	}
	else { // Je�li tablica nie jest pusta, sprawd� czy klucz si� zgadza
		NodeHT* current = table[index];
		while (current != nullptr) {
			if (current->key == key)
				return current->value;
			current = current->next;
		}
	}
	return -1;
}

// Usuwanie elementu na podstawie klucza i zwrot jego warto�ci
int hash_table_chaining::remove(int key)
{
	int index = hash(key);
	// Je�li tablica jest pusta, zako�cz metode
	if (table[index] == NULL) {
		return -1;
	}
	// Je�li tablica nie jest pusta, sprawd� klucz
	else {
		NodeHT* current = table[index];
		NodeHT* prev = nullptr;
		while (current != nullptr) {
			if (current->key == key) {
				int value = current->value;
				if (prev == nullptr) // Jesli to pierwszy wezel w �a�cuchu
					table[index] = current->next;
				else
					prev->next = current->next;
				delete current;
				size--;
				// Je�li ilo�� element�w spadnie do 1/4 pojemno�ci, pomniejsz pojemno�c
				if (size == capacity / 4 && capacity > 1)
					resize(capacity / 2);
				return value;
			}
			prev = current;
			current = current->next;
		}
	}
	return -1;
}

// Wy�wietlenie zawarto�ci tablicy
void hash_table_chaining::display()
{
	for (size_t i = 0; i < capacity; i++) {
		NodeHT* current = table[i];
		cout << "Key: " << i << ": ";
		while (current != nullptr) {
			if (current->value != NULL)
				cout << " Value: " << current->value;
			else cout << " Value: NULL";
			current = current->next;
		}
		cout << endl;
	}
	cout << endl;
}
