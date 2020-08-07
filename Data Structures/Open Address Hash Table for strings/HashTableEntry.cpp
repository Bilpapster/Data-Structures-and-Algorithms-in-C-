#include "HashTableEntry.h"

#include <iostream>


// constructors
HashTableEntry::HashTableEntry() {
    this->word = "";
    this->frequency = 0;
}

HashTableEntry::HashTableEntry(const string &givenWord, unsigned long int givenFrequency /*defaulted to 1*/) {
    this->word = givenWord;
    this->frequency = givenFrequency;
}


// accessors
string HashTableEntry::getWord() const  {return this->word;}

unsigned long int HashTableEntry::getFrequency() const  {return this->frequency;}

void HashTableEntry::setData(const string &givenWord, unsigned long int givenFrequency /*defaulted to 1*/) {
    this->word = givenWord;
    this->frequency = givenFrequency;
}

void HashTableEntry::decreaseFrequecyBy(unsigned long int givenFrequency /*defaulted to 1*/)   {this->frequency -= givenFrequency;}

void HashTableEntry::increaseFrequencyBy(unsigned long int givenFrequency /*defaulted to 1*/) {this->frequency += givenFrequency;}

// auxiliary method
bool HashTableEntry::isOccupied() const {return (this->frequency);}   /* frequency equal to 0 indicates that the entry is not occupied */
