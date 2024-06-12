
#include <iostream>
#include <random>
#include <vector>
#include "hash_table_chaining.h"
#include "hash_table_cuckoo.h"
#include "hash_table_linear.h"
#include "map.h"
#include <chrono>
#include <numeric>

void fill_map_rand_num(hash_table_cuckoo& hashTable, unsigned seed, int capacity) {
    std::mt19937 engine(seed);
    std::uniform_int_distribution<int> keyDistribution(0, INT32_MAX);
    std::uniform_int_distribution<int> valueDistribution(0, INT32_MAX);

    for (int i = 0; i < capacity; ++i) {
        int key = keyDistribution(engine);
        int value = valueDistribution(engine);
        hashTable.insert(key, value);
    }
}

double insert_test(hash_table_cuckoo& hashTable) {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> keyDistribution(0, INT32_MAX);
    std::uniform_int_distribution<int> valueDistribution(0, INT32_MAX);

    auto start = std::chrono::high_resolution_clock::now();

    int key = keyDistribution(engine);
    int value = valueDistribution(engine);
    hashTable.insert(key, value);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    //std::cout << "Time taken to add a single element: " << duration.count() << " nanoseconds" << std::endl;
    return duration.count();
}

double remove_test(hash_table_cuckoo& hashTable) {
    std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> keyDistribution(0, INT32_MAX);

    auto start = std::chrono::high_resolution_clock::now();

    int key = keyDistribution(engine);
    hashTable.remove(key);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    //std::cout << "Time taken to add a single element: " << duration.count() << " nanoseconds" << std::endl;
    return duration.count();
}

/*int main() {
    unsigned seed = 6281;
    int capacity = 100000; // pojemność słownika
    const int numDictionaries = 50; // Liczba słowników do wypełnienia

    double totalTime = 0.0;

    for (int i = 0; i < numDictionaries; ++i) {
        hash_table_cuckoo hashTable(capacity);

        // Wypełnianie słownika losowymi liczbami
        fill_map_rand_num(hashTable, seed, capacity);

        // Test dodania pojedynczego elementu
      //totalTime += insert_test(hashTable);
        totalTime +=  remove_test(hashTable);

    }

    double averageTime = totalTime / numDictionaries;
    std::cout << "Average time taken to add a single element across 50 dictionaries: " << averageTime << " nanoseconds" << std::endl;

    return 0;
}*/

void method_choice(map* map) {
    bool cond = true;
    while (cond) {
        unsigned int wybor;
        std::cout << "Wybierz jedna z opcji: (1-4) \n";
        std::cout << "1. Dodaj element do slownika. \n2. Usun element ze slownika. \n3. Znajdz element w slowniku. \n4. Wyswietl elementy slownika. \n";
        std::cin >> wybor;

        int value, key;
        switch (wybor) {
        case 1:
            std::cout << "Podaj wartosc elementu: \n";
            std::cin >> value;
            std::cout << "Podaj klucz elementu: \n";
            std::cin >> key;
            map->insert(key, value);
            break;
        case 2:
            std::cout << "Podaj wartosc klucza: \n";
            std::cin >> key;
            map->remove(key);
            break;
        case 3:
            std::cout << "Podaj wartosc klucza: \n";
            std::cin >> key;
            map->find(key);
            break;
        case 4:
            map->display();
            break;
        default:
            std::cout << "Powrot do menu. \n";
            cond = false;
            break;

        }
    }
}

void implem_choice() {
    std::cout << "Wybierz rodzaj implementacji: (1-3)\n";
    std::cout << "1. Linear \n2. Chaining \n3. Cuckoo \n";
    unsigned int wybor;
    std::cin >> wybor;
    map* map = nullptr;

    switch (wybor) {
    case 1:
        std::cout << "Linear. \n";
        map = new hash_table_linear(10);
        method_choice(map);
        delete map;
        break;
    case 2:
        std::cout << "Chaining. \n";
        map = new hash_table_chaining(10);
        method_choice(map);
        delete map;
        break;
    case 3:
        std::cout << "Cuckoo. \n";
        map = new hash_table_cuckoo(10);
        method_choice(map);
        delete map;
        break;
    default:
        std::cout << "Opuszczanie programu. \n";
        return;
    }
}

int main() {
    while (true) {
        implem_choice();
    }
    return 0;
}