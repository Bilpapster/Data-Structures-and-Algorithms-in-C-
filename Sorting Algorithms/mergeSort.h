#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <iostream>
#include <limits>

using namespace std;

    #ifndef MY_SWAP_FUNCTION
    #define MY_SWAP_FUNCTION

        template<typename dataType>
        void mySwap(dataType &itemA, dataType &itemB) {
            dataType temp = itemA;
            itemA = itemB;
            itemB = temp;
        }

    #endif //MY_SWAP_FUNCTION


template<typename dataType>
void merge(dataType array[], long long int start, long long int finish, bool ascendingOrder) {

    long long int middleIndex = (start + finish) / 2;
    dataType *leftSubArray = new dataType[(middleIndex - start + 1) + 1];     // the left sub-array contains (middleIndex-start+1) elements, plus one for the sort quard
    dataType *rightSubArray = new dataType[(finish - middleIndex + 1) + 1];   // the right sub-array contains (finish-middleIndex+1) elements, plus one for the sort quard

    // STEP 1: copy content from the initial array to 2 auxiliary arrays, left and right sub-array */

    /*                                        LEFT SUB-ARRAY                                        */
    // the left sub-array contains the elements of the initial array in range [start, middleIndex]
    long long int leftParsingIndex = 0;

    for (long long int arrayIndex = start; arrayIndex <= middleIndex; arrayIndex++)
        leftSubArray[leftParsingIndex++] = array[arrayIndex];

    // the sort guard gets the highest (on ascending order) or lowest (on descending order) value a long long int variable can store
    leftSubArray[leftParsingIndex] = (ascendingOrder) ? numeric_limits<long long int>::max(): numeric_limits<long long int>::min();  


    /*                                        RIGHT SUB-ARRAY                                        */
    // the right sub-array contains the elements of the initial array in range [middleIndex + 1, finish]
    long long int rightParsingIndex = 0;

    for (long long int arrayIndex = middleIndex + 1; arrayIndex <= finish; arrayIndex++)
        rightSubArray[rightParsingIndex++] = array[arrayIndex];

    // the sort guard gets the highest (on ascending order) or lowest (on descending order) value a long long int variable can store   
    rightSubArray[rightParsingIndex] = (ascendingOrder) ? numeric_limits<long long int>::max(): numeric_limits<long long int>::min(); 


    // STEP 2: fill back the initial array, by chosing the min of the two sub-arrays at each time */

    rightParsingIndex = leftParsingIndex = 0;
    for (long long int finalArrayIndex = start; finalArrayIndex <= finish; finalArrayIndex++) {
        
        if (ascendingOrder) {
            if  (leftSubArray[leftParsingIndex] < rightSubArray[rightParsingIndex])
                array[finalArrayIndex] = leftSubArray[leftParsingIndex++];

            else array[finalArrayIndex] = rightSubArray[rightParsingIndex++];
        }

        else {
            if  (leftSubArray[leftParsingIndex] > rightSubArray[rightParsingIndex])
                array[finalArrayIndex] = leftSubArray[leftParsingIndex++];

            else array[finalArrayIndex] = rightSubArray[rightParsingIndex++];
        } 
    }

    // STEP 3: Delete dynamically allocated space, since the 2 auxiliary subarrays are no longer needed
    delete [] leftSubArray;
    delete [] rightSubArray;
}

template<typename dataType>
void mergeSort(dataType array[], long long int start, long long int finish, bool ascendingOrder = true) {
    long long int middleIndex;
    if (start < finish) {

        if (finish == start + 1) {
            if (ascendingOrder){
                if (array[start] > array[finish])   mySwap(array[start], array[finish]);
            }
            else {
                if (array[finish] > array[start])   mySwap(array[start], array[finish]);
            }
        }

        else {
            middleIndex = (start + finish) / 2;
            mergeSort(array, start, middleIndex, ascendingOrder);
            mergeSort(array, middleIndex + 1, finish, ascendingOrder);
            merge(array, start, finish, ascendingOrder);
        }
    }
}

#endif //MERGE_SORT_H