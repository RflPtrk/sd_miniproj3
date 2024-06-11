#include "hash_table_chaining.h"

// Zmiana rozmiaru tablicy mieszaj¹cej
void hash_table_chaining::resize(size_t newCapacity)
{
	// Nowa tablicy o nowej pojemnoœci
	NodeHT** newTable = new NodeHT * [newCapacity];
	// Wypelnienie nowej tablicy nullami
	for (size_t i = 0; i < newCapacity; i++) {
		newTable[i] = NULL;
	}
	// Przeniesienie elementów starej tablicy do nowej
	for (size_t i = 0; i < capacity; i++) {
		NodeHT* current = table[i];
		while (current != nullptr) {
			NodeHT* next = current->next; // WskaŸnik do nastêpnego elementu
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
			current = next; // Przejœcie do nastêpnego elementu
		}
	}
	delete[] table;
	table = newTable;
	capacity = newCapacity;
}

// Konstruktor inicjalizuj¹cy tablicê mieszaj¹c¹ o podanej pojemnoœci
hash_table_chaining::hash_table_chaining(int capacity)
{
	this->capacity = capacity;
	table = new NodeHT * [capacity];
	for (size_t i = 0; i < capacity; i++) {
		table[i] = NULL;
	}
	size = 0;
}

// Destruktor usuwaj¹cy wszystkie elementy z tablicy mieszaj¹cej
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

// Funkcja haszuj¹ca
int hash_table_chaining::hash(int key)
{
	return key % capacity;
}

// Wstawienie nowej pary klucz-wartoœæ do tablicy mieszaj¹cej
void hash_table_chaining::insert(int key, int value)
{
	int index = hash(key);
	NodeHT* newNodeHT = new NodeHT;
	newNodeHT->key = key;
	newNodeHT->value = value;
	newNodeHT->next = nullptr;
	// Jeœli miejsce jest puste, przypisz do niego nowy wêze³
	if (table[index] == NULL) {
		table[index] = newNodeHT;
	}
	else { // Jeœli miejsce nie jest puste, dodaj nowy wêze³ na koñcu listy
		NodeHT* current = table[index];
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNodeHT;
	}
	size++;

	// Jeœli liczba elementów przekracza pojemnoœæ, podwój pojemnoœæ
	if (size >= capacity) {
		resize(capacity * 2);
	}
}

// Wyszukanie wartoœci na podstawie klucza
int hash_table_chaining::find(int key)
{
	int index = hash(key);
	// Jeœli tablica jest pusta, zakoñcz metode
	if (table[index] == NULL) {
		return -1;
	}
	else { // Jeœli tablica nie jest pusta, sprawdŸ czy klucz siê zgadza
		NodeHT* current = table[index];
		while (current != nullptr) {
			if (current->key == key)
				return current->value;
			current = current->next;
		}
	}
	return -1;
}

// Usuwanie elementu na podstawie klucza i zwrot jego wartoœci
int hash_table_chaining::remove(int key)
{
	int index = hash(key);
	// Jeœli tablica jest pusta, zakoñcz metode
	if (table[index] == NULL) {
		return -1;
	}
	// Jeœli tablica nie jest pusta, sprawdŸ klucz
	else {
		NodeHT* current = table[index];
		NodeHT* prev = nullptr;
		while (current != nullptr) {
			if (current->key == key) {
				int value = current->value;
				if (prev == nullptr) // Jesli to pierwszy wezel w ³añcuchu
					table[index] = current->next;
				else
					prev->next = current->next;
				delete current;
				size--;
				// Jeœli iloœæ elementów spadnie do 1/4 pojemnoœci, pomniejsz pojemnoœc
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

// Wyœwietlenie zawartoœci tablicy
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
