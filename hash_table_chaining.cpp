#include "hash_table_chaining.h"

// Zmiana rozmiaru tablicy mieszającej
void hash_table_chaining::resize(size_t newCapacity)
{
	// Nowa tablicy o nowej pojemności
	NodeHT** newTable = new NodeHT * [newCapacity];
	// Wypelnienie nowej tablicy nullami
	for (size_t i = 0; i < newCapacity; i++) {
		newTable[i] = nullptr;
	}
	// Przeniesienie elementów starej tablicy do nowej
	for (size_t i = 0; i < capacity; i++) {
		NodeHT* current = table[i];
		while (current != nullptr) {
			NodeHT* next = current->next; // Wskaźnik do następnego elementu
			int index = current->key % newCapacity; // Nowy indeks dla elementu w nowej tablicy
			if (newTable[index] == nullptr) {
				newTable[index] = current;
				current->next = nullptr;
			}
			else {
				NodeHT* temp = newTable[index];
				while (temp->next != nullptr) {
					temp = temp->next;
				}
				temp->next = current;
				current->next = nullptr;
			}
			current = next; // Przejście do następnego elementu
		}
	}
	delete[] table;
	table = newTable;
	capacity = newCapacity;
}

// Konstruktor inicjalizujący tablicę mieszającą o podanej pojemności
hash_table_chaining::hash_table_chaining(int capacity)
{
	this->capacity = capacity;
	table = new NodeHT * [capacity];
	for (size_t i = 0; i < capacity; i++) {
		table[i] = NULL;
	}
	size = 0;
}

// Destruktor usuwający wszystkie elementy z tablicy mieszającej
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

// Funkcja haszująca
int hash_table_chaining::hash(int key)
{
	return key % capacity;
}

// Wstawienie nowej pary klucz-wartość do tablicy mieszającej
void hash_table_chaining::insert(int key, int value)
{
	int index = hash(key);
	NodeHT* newNodeHT = new NodeHT;
	newNodeHT->key = key;
	newNodeHT->value = value;
	newNodeHT->next = nullptr;
	// Jeśli miejsce jest puste, przypisz do niego nowy węzeł
	if (table[index] == NULL) {
		table[index] = newNodeHT;
	}
	else { // Jeśli miejsce nie jest puste, dodaj nowy węzeł na końcu listy
		NodeHT* current = table[index];
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newNodeHT;
	}
	size++;

	// Jeśli liczba elementów przekracza pojemność, podwój pojemność
	if (size >= capacity) {
		resize(capacity * 2);
	}
}

// Wyszukanie wartości na podstawie klucza
int hash_table_chaining::find(int key)
{
	int index = hash(key);
	// Jeśli tablica jest pusta, zakończ metode
	if (table[index] == NULL) {
		return -1;
	}
	else { // Jeśli tablica nie jest pusta, sprawdź czy klucz się zgadza
		NodeHT* current = table[index];
		while (current != nullptr) {
			if (current->key == key)
				return current->value;
			current = current->next;
		}
	}
	return -1;
}

// Usuwanie elementu na podstawie klucza i zwrot jego wartości
int hash_table_chaining::remove(int key)
{
	int index = hash(key);
	// Jeśli tablica jest pusta, zakończ metode
	if (table[index] == NULL) {
		return -1;
	}
	// Jeśli tablica nie jest pusta, sprawdź klucz
	else {
		NodeHT* current = table[index];
		NodeHT* prev = nullptr;
		while (current != nullptr) {
			if (current->key == key) {
				int value = current->value;
				if (prev == nullptr) // Jesli to pierwszy wezel w łańcuchu
					table[index] = current->next;
				else
					prev->next = current->next;
				delete current;
				size--;
				// Jeśli ilość elementów spadnie do 1/4 pojemności, pomniejsz pojemnośc
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

// Wyświetlenie zawartości tablicy
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
