#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include <fstream>
#define INITIAL_SIZE 10

using namespace std;

template<typename dataType>
class PriorityQueue {
public:
    PriorityQueue();
    ~PriorityQueue();
    void enQueue(const dataType &itemToEnqueue);
    void deQueue(dataType &itemToDequeue, bool dummy=0);
    void show();

protected:
    dataType *table;
    int queueSize;
    int indexLast;
    void mySwap(dataType &itemA, dataType &itemB);
    void resize(int newSize);
};

template <typename dataType>
void quickSort(dataType *array, int startPosition, int endPosition) {

    dataType temp;

    if (startPosition < endPosition) {
        int lowerRankIndex = startPosition - 1;
        dataType pivot;
        pivot = array[endPosition];


        for (int parsingIndex = startPosition; parsingIndex <= endPosition - 1; parsingIndex++) {
            if ((array[parsingIndex] > pivot) || (array[parsingIndex] == pivot)){
                lowerRankIndex++;
                /*swap(array[parsingIndex], array[lowerRankIndex]); */
                temp = array[parsingIndex];
                array[parsingIndex] = array[lowerRankIndex];
                array[lowerRankIndex] = temp;

            }
        }

        swap(array[++lowerRankIndex], array[endPosition]);
        quickSort(array, startPosition, lowerRankIndex - 1);
        quickSort(array, lowerRankIndex + 1, endPosition);
    }
}

template<typename dataType>
PriorityQueue<dataType>::PriorityQueue() {
    this->table = new dataType[INITIAL_SIZE];
    this->queueSize = INITIAL_SIZE;
    this->indexLast = -1;
}

template<typename dataType>
PriorityQueue<dataType>::~PriorityQueue() {
    delete [] this->table;
}

template<typename dataType>
void PriorityQueue<dataType>::mySwap(dataType &itemA, dataType &itemB) {
    dataType temp = itemA;
    itemA = itemB;
    itemB = temp;
}

template<typename dataType>
void PriorityQueue<dataType>::resize(int newSize) {
    dataType *newTable;
    int limit = (this->queueSize < newSize)? (this->queueSize): newSize;
    newTable = new dataType[newSize];
    for (int i = 0; i < limit; i++)
        newTable[i] = this->table[i];

    delete this->table;
    this->table = newTable;
    this->queueSize = newSize;
    this->indexLast = limit-2;
}

template<typename dataType>
void PriorityQueue<dataType>::enQueue(const dataType &itemToEnqueue) {
    if (this->indexLast+1 == this->queueSize) {
        cout<<"Not enough space. Requesting more..."<<endl;
        cout<<"Space found. Moving data..."<<endl;
        this->resize(this->queueSize+5);
    }

    table[++(this->indexLast)] = itemToEnqueue;

    int currentIndex = this->indexLast;

    while ((currentIndex-1)/2 >= 0) {
        if (table[currentIndex] > table[(currentIndex-1)/2]) {
            mySwap(table[(currentIndex-1)/2], table[currentIndex]);
            currentIndex = (currentIndex-1)/2;
        }
        else break;
    }
}

template<typename dataType>
void PriorityQueue<dataType>::deQueue(dataType &itemToDequeue, bool dummy) {
    if (indexLast==-1) {
        cout<<"Array Empty..."<<endl;
        this->resize(0);
        return;
    }

    itemToDequeue = this->table[0];
    mySwap(table[indexLast], table[0]);
    indexLast--;

    bool done = 0;
    int currentIndex = 0;
    int indexLeft = 2*currentIndex + 1;
    int indexRight = 2*currentIndex + 2;
    while (indexLeft <= indexLast && !done) {

        if (indexRight <= indexLast) {

            if (table[indexRight] > table[indexLeft]) {
                if (table[indexRight] > table[currentIndex]) {
                    mySwap(table[indexRight], table[currentIndex]);
                    currentIndex = indexRight;
                }
                else done=1;
            }
            else {
                if (table[indexLeft] > table[currentIndex]) {
                    mySwap(table[indexLeft], table[currentIndex]);
                    currentIndex = indexLeft;
                }
                else done=1;
            }
        }
        else {
            if (table[indexLeft] > table[currentIndex]) {
                mySwap(table[indexLeft], table[currentIndex]);
                currentIndex = indexLeft;
            }
            else done=1;
        }
        indexLeft = 2*currentIndex + 1;
        indexRight = 2*currentIndex + 2;
    }

    if (! dummy) {
        if ((queueSize - indexLast - 1) > 5) {
            cout<<"Too much available space. Deleting extra memory..."<<endl;
            resize(this->queueSize - 5);
            cout<<"Extra space deleted."<<endl;
        }
    }
}

template<typename dataType>
void PriorityQueue<dataType>::show() {
    dataType *temp;
    dataType item;

    temp = new dataType[indexLast+1];

    for (int i=0; i<=indexLast; i++)
        temp[i] = table[i];

    quickSort(temp, 0, indexLast);
    int temporaryIndex=indexLast+1;

    cout<<"--------------"<<endl;
    cout<<"Size = "<<indexLast+1<<endl;
    cout<<"maxSize = "<<queueSize<<endl;

    for (int i = 0; i < temporaryIndex; i++) {
        cout<<temp[i]<<endl;
    }
    cout<<"--------------"<<endl;

    delete []temp;

}

#endif // PRIORITY_QUEUE_H