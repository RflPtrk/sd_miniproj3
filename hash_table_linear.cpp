#include "hash_table_linear.h"

// Zmiana pojemnosci tablicy
void hash_table_linear::resize(size_t new_capacity)
{
	// Dotychczasowa tablica i pojemnosc
	int* old_table = table;
	int old_capacity = capacity;

	// Nowa tablica
	size = 0;
	capacity = new_capacity;
	table = new int[capacity];
	for (size_t i = 0; i < capacity; i++) {
		table[i] = -1;
	}
	// Przeniesienie elementów do nowej tablicy
	for (size_t i = 0; i < old_capacity; i++) {
		if (old_table[i] != -1) {
			insert(i, old_table[i]);
		}
	}
	delete[] old_table;
}

// Konstruktor inicjalizujący tablicę mieszającą o podanej pojemności
hash_table_linear::hash_table_linear(size_t capacity)
{
	this->capacity = capacity;
	table = new int[capacity];
	for (size_t i = 0; i < capacity; i++) {
		table[i] = -1; // -1 to puste miejsce
	}
	size = 0;
}

// Destruktor usuwajacy wszystkie elementy
hash_table_linear::~hash_table_linear()
{
	delete[] table;
	size = 0;
	capacity = 0;
}

// Funkcja haszujaca
int hash_table_linear::hash(int key)
{
	return key % capacity;
}

// Wstawienie nowej pary klucz-wartość do tablicy mieszającej
void hash_table_linear::insert(int key, int value)
{
	int index = hash(key);
	// Liniowe próbkowanie w celu znalezienia wolnego miejsca
	while (table[index] != -1) {
		index = (index + 1) % capacity;
	}
	table[index] = value;
	size++;
	// Jeśli liczba elementów przekracza pojemność, podwój pojemność
	if (size >= capacity) {
		resize(capacity * 2);
	}
}

// Wyszukanie wartości na podstawie klucza
int hash_table_linear::find(int key)
{
	int index = hash(key);
	int startIndex = index;
	// Liniowe próbkowanie w celu znalezienia klucza
	do {
		if (index == key) {
			return table[index];
		}
		index = (index + 1) % capacity;
	} while (index != startIndex);
	return -1;
}

// Usuwanie elementu na podstawie klucza i zwrot jego wartości
int hash_table_linear::remove(int key)
{
	int index = hash(key);
	// Liniowe próbkowanie w celu znalezienia klucza
	while (table[index] != -1) {
		if (index == key) {
			int value = table[index];
			table[index] = -1; // Ustawienie usuniętego miejsca na -1
			size--;
			// Jeśli ilość elementów spadnie do 1/4 pojemności, pomniejsz pojemnośc
			if (size == capacity / 4)
				resize(capacity / 2);
			return value;
		}
		index = (index + 1) % capacity;
	}
	return -1;
}

// Wyświetlenie zawartości tablicy
void hash_table_linear::display()
{
	for (size_t i = 0; i < capacity; i++) {
		cout << i << ": ";
		if (table[i] != -1)
			cout << table[i];
		cout << endl;
	}
	cout << endl;
}
