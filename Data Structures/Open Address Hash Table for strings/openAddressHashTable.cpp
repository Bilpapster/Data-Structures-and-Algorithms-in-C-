#include "openAddressHashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>


// constructor - destructor

openAddressHashTable::openAddressHashTable(unsigned long int preferredSize) {
    this->tableSize = findMinPrimeGreaterThan(preferredSize);       // hashTable size has to be a prime number, to avoid endless loops due to collisions
    this->table = new HashTableEntry[this->tableSize];
}

openAddressHashTable::~openAddressHashTable() { delete [] this->table; }


//basic operations

void openAddressHashTable::insert(const string &givenWord, unsigned long int givenFrequency) {

    unsigned long int index;
    int i = -1;
    unsigned long int hashValue1 = hashFunction1(givenWord);
    unsigned long int hashValue2 = hashFunction2(givenWord);
    bool keyFound = false;

    do {
         i++;          // at the very first check, i has value -1+1=0, and increases by 1 at every "collision"
         index = (hashValue1 + i * hashValue2) % tableSize;             // double hashing

         if (table[index].getWord() == givenWord) keyFound = true;      // if the cell checked contains the word, then it already exists

    } while (table[index].isOccupied() && !keyFound);                    // loop stops when an unoccupied position is found or the key to insert already exists. This position is stored to "index" by the end of the loop

    if (keyFound) {                                         // if the word already exists, then just increase its frequency
        table[index].increaseFrequencyBy(givenFrequency);
        return;
    }

    /* else if the word does not already exists */
    table[index].setData(givenWord);
}

/* Searches the given word in the hash table and returns its frequency
   if the word is not found, it returns 0 */
int openAddressHashTable::search(const string &givenWord) {

    unsigned long int index;
    unsigned long int hashValue1 = hashFunction1(givenWord);
    unsigned long int hashValue2 = hashFunction2(givenWord);

    int i = -1;
    do {
        i++;    // at the very first check, i has value -1+1=0, and increases by 1 every time the cell checked is not the one we search for
        index = (hashValue1 + i * hashValue2) % tableSize;

        if (table[index].isOccupied()) {
            if (table[index].getWord() == givenWord) /* then the word is found, so just return its frequency */
                return table[index].getFrequency();
        }
    } while (table[index].isOccupied());

    /* else if the loop ends without finding the word */ return 0;
}


// hash functions used for double hashing

// h1(key) = 37^n*c0 + 37^(n-1)*c1 + ... + 37*c(n-1) + cn
unsigned long int openAddressHashTable::hashFunction1(const string &givenWord) {
    unsigned long int hashValue1 = 0;

    for (int i=0; givenWord[i]!='\0'; i++)
        hashValue1 = 37*hashValue1 + (unsigned long int) givenWord[i];

    return hashValue1 % (this->tableSize);
}

// h1(key) = 13^n*c0 + 13^(n-1)*c1 + ... + 13*c(n-1) + cn
unsigned long int openAddressHashTable::hashFunction2(const string &givenWord) {
        unsigned long int hashValue2 = 0;

        for (int i=0; givenWord[i]!='\0'; i++)
            hashValue2 = 13*hashValue2 + (unsigned long int) givenWord[i];

        return hashValue2 % (this->tableSize);
}

// based on a data (binary) file (.dat) that contains prime numbers, returns the minimum prime number that is greater than the given number
unsigned long int findMinPrimeGreaterThan(const unsigned long int &givenNumber) {
    ifstream primesFile;
    string temp;
    unsigned long int number;

    primesFile.open(PRIMES_FILE, ios::in|ios::binary);              // open the binary file containing the prime numbers for input operations
    if (! primesFile.is_open()) {
        cout << "Primes File not found in directory. I was expecting to find "<< PRIMES_FILE <<" but I couldn't! Hash Table Size is set to given number."<< endl;
        return givenNumber;
    }

    do
        primesFile.read((char *) &number, sizeof(number));      // read a prime number (unsigned long int) from the data file
    while (number < givenNumber);         // searching for the desired prime stops at the first prime number found greater (or equal) than the given number.
                                          // The desired prime that meets the conditions, is stored in variable "number" at the end of the loop

    primesFile.close();
    return number;
}
