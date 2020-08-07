#ifndef HASH_TABLE_ENTRY_H
#define HASH_TABLE_ENTRY_H

#include <string>
using namespace std;

class HashTableEntry {
    public:
        // constructors
        HashTableEntry();
        HashTableEntry(const string &givenWord, unsigned long int givenFrequency = 1);

        // accessors
        string getWord() const;
        unsigned long int getFrequency() const;
        void setData(const string &givenWord, unsigned long int givenFrequency = 1);
        void increaseFrequencyBy(unsigned long int givenFrequency = 1);
        void decreaseFrequecyBy(unsigned long int givenFrequency = 1);

        // auxiliary method
        bool isOccupied() const;

    protected:
        string word;
        unsigned long int frequency;
};

#endif //HASH_TABLE_ENTRY_H
