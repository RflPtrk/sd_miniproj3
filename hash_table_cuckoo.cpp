#include "hash_table_cuckoo.h"

// Funkcja haszująca 1
int hash_table_cuckoo::hash1(int key)
{
    return key % capacity;
}

// Funkcja haszująca 2
int hash_table_cuckoo::hash2(int key)
{
    return 1 + (key % (capacity - 1));
}

// Zmiana pojemnosci tablicy
void hash_table_cuckoo::rehash(int newCapacity)
{
	// Dotychczasowe tablice i pojemnosc
	int* old_table1 = table1;
	int* old_table2 = table2;
	int old_capacity = capacity;

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
	for (int i = 0; i < old_capacity; i++)
	{
		if (old_table1[i] != -1)
		{
			insert(i, old_table1[i]);
		}
		if (old_table2[i] != -1)
		{
			insert(i, old_table2[i]);
		}
	}
	delete[] old_table1;
	delete[] old_table2;
}

// Konstruktor
hash_table_cuckoo::hash_table_cuckoo(int capacity)
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
hash_table_cuckoo::~hash_table_cuckoo()
{
	delete[] table1;
	delete[] table2;
	capacity = 0;
	size = 0;
}

// Wstawienie elementu
void hash_table_cuckoo::insert(int key, int value)
{
	int index = hash1(key);
	int* current_table = table1;

	// próbuje wstawić element do ktorejs tablicy
	for (int i = 0; i < 10; i++) {
		if (current_table[index] == -1) {
			current_table[index] = value;
			size++;
			return;
		}

		// Zamiana wartości i przesunięcie
		std::swap(current_table[index], value);

		// Przełącza tablice i oblicza nowy indeks
		if (current_table == table1) {
			current_table = table2;
			index = (index + hash2(key)) % capacity;
		}
		else {
			current_table = table1;
			index = hash1(key);
		}
	}

	// Jeśli nie uda się znalezc wolnego miejsca, zmienia rozmiar i ponawia próbę
	rehash(capacity * 2);
	insert(key, value);
}

// Usuwanie elementu
int hash_table_cuckoo::remove(int key)
{
	int index1 = hash1(key);
	int index2 = hash2(key);

	// Sprawdź pierwszy indeks w table1
	if (table1[index1] == key) {
		table1[index1] = -1; // lub inna wartość oznaczająca pustą komórkę
		size--;
	}
	// Sprawdź drugi indeks w table2
	else if (table2[index2] == key) {
		table2[index2] = -1; // lub inna wartość oznaczająca pustą komórkę
		size--;
	}
	else {
		//cout << "Key not found" << endl;
		return -1;
	}

	// Jeśli liczba elementów jest zbyt mała, zmniejsza rozmiar tablicy
	if (size <= capacity * 0.3) {
		rehash(capacity / 2);
	}

	return 0;
}


// Wyszukanie wartości na podstawie klucza
int hash_table_cuckoo::find(int key)
{
	int index = hash1(key);
	int* current_table = table1;

	// Przeszukuje obie tablicy w poszukiwaniu klucza
	for (int i = 0; i < 10; i++) {
		if (current_table[index] != -1) {
			return 0;
		}

		// Przełącza tablice i oblicza nowy indeks
		if (current_table == table1) {
			current_table = table2;
			index = hash2(key);
		}
		else {
			current_table = table1;
			index = hash1(key);
		}
	}
	return -1;
}

// Wyświetlenie zawartosci tablic
void hash_table_cuckoo::display()
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
