#ifndef HEAP_SORT_H
#define HEAP_SORT_H

    /* simple template funcion to swap contents of 2 variables of any data type.
       The function is used in all sorting algorithms, that's why inclusion guards are used,
       to avoid frustraring compile errors of multiple definition.*/ 
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
void maxHeapify(dataType array[], long long int start, long long int finish, long long int violationIndex) {

    if (2 * violationIndex + 1 <= finish) { // violator Node has left child

        if (2 * violationIndex + 2 <= finish) {
            if ((array[2*violationIndex+1] > array[2*violationIndex+2])) {
                if (array[2*violationIndex+1] > array[violationIndex]) {
                    mySwap(array[violationIndex], array[2*violationIndex+1]);
                    maxHeapify(array, start, finish, 2*violationIndex+1);                    
                }
            }
            else {
                if (array[2*violationIndex+2] > array[violationIndex]) {
                    mySwap(array[violationIndex], array[2*violationIndex+2]);
                    maxHeapify(array, start, finish, 2*violationIndex+2);
                }
            }

        }
        else if (array[2*violationIndex+1] > array[violationIndex]) {
            mySwap(array[violationIndex], array[2*violationIndex+1]);
            maxHeapify(array, start, finish, 2*violationIndex+1);
        }
    }
}

// function that takes as input a random array and transforms it to a maxHeap
template<typename dataType>

void initializeHeap(dataType array[], long long int start, long long int finish) {
    for (long long int parsingIndex = (finish - start)/2; parsingIndex >= start; parsingIndex--)
        maxHeapify(array, start, finish, parsingIndex);
}

// sorts given array in range [start, finish] in ascending order
template<typename dataType>
void heapSort(dataType array[], long long int start, long long int finish) {

    // before we start, we have to transform the given array to a maxHeap
    initializeHeap(array, start, finish);

    /* The classic idea of ascending heap sort, implenented in-place and by using a maxHeap.
       For each item in the maxHeap, the max of the heap (always the item stored on array[0])
       is swapped with the item in the last (not-sorted) place of the array.
       Practically, it can be described like that: while the heap is not empty, the max of the
       heap is extracted and placed at the end of the array. At the same time, the item used to 
       be there arbitrarily goes to the place the max used to be and the heap shortens by one place. 
       However, this exchange may be violating the maxHeap properties, so we need to heapify again,
       indicating that the item on array[0] is the violator we want to re-arrange correctly. That's
       why every exchange is followed by a heapify and the heap shortens by one place.*/

    for (long long int parsingIndex = finish; parsingIndex > start; parsingIndex--) {
        mySwap(array[0], array[parsingIndex]);
        maxHeapify(array, start, parsingIndex-1, 0);
    }
}
#endif //HEAP_SORT_H