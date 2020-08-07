#ifndef OPEN_ADDRESS_HASH_TABLE_H
#define OPEN_ADDRESS_HASH_TABLE_H

#include "DefaultDefinitions.h"
#include "HashTableEntry.h"

class openAddressHashTable {
    public:
        // constructor - destructor
        openAddressHashTable(unsigned long int preferredSize);
        ~openAddressHashTable();

        // basic operations
        void insert(const string &givenWord, unsigned long int givenFrequency = 1);
        int search(const string &givenWord);

        // hash functions used for double hashing
        unsigned long int hashFunction1(const string &givenWord);
        unsigned long int hashFunction2(const string &givenWord);

    protected:
        HashTableEntry *table;
        unsigned long int tableSize;
};

// based on a text file that contains prime numbers, returns the minimum prime number that is greater than the given one
unsigned long int findMinPrimeGreaterThan(const unsigned long int &givenNumber);

#endif //OPEN_ADDRESS_HASH_TABLE_H