#ifndef IN_PLACE_RANDOMIZED_QUICK_SORT_H
#define IN_PLACE_RANDOMIZED_QUICK_SORT_H

using namespace std;

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

    #endif // MY_SWAP_FUNCTION


/* Partition is the key-point of every quicksort algorithm implementation. Here, the pivot is
   chosen randomly and all exchanges are done in-place. Two indices are used, one parsing the
   array from left to right and the other the opposite way. Partition is executed while the two
   indices have not crossed each other.
   ~ ASCENDING ORDER: The right index parses to the left until an item greater (or equal) than
   the pivot is found. Then, the right index starts its parse to the left, until an iten smaller
   (or equal) than the pivot is found. The two values are exnchanged and the procedure is
   repeated (the right parses to the left ...) until indices cross.
   ~ DESCENDING ORDER: Swap "greater" and "smaller" in the above paragraph.*/

template<typename dataType>
long long int partition(dataType array[], long long int start, long long int finish, bool ascendingOrder) {

    // pivot is chosen randomly as one of the items of the array, in range [start, finish]
    dataType pivot = array[(rand() % (finish + 1 - start)) + start];

    long long int leftParsingIndex = start - 1;
    long long int rightParsingIndex = finish + 1;

    // if statement is checked only once at every execution of partition, driving execution to the appropriate while block
    if (ascendingOrder) {
        while (leftParsingIndex < rightParsingIndex) {

            // left index parses to the right, until greater (or equal) is found
            do  leftParsingIndex++;
            while (array[leftParsingIndex] < pivot);

            // right index parses to the left, until smaller (or equal) is found
            do  rightParsingIndex--;
            while (array[rightParsingIndex] > pivot);

            // if indices have not crossed, swap items
            if (leftParsingIndex < rightParsingIndex)
                mySwap(array[leftParsingIndex], array[rightParsingIndex]);
        }
    }
    else {
        while (leftParsingIndex < rightParsingIndex) {

            // left index parses to the right, until smaller (or equal) is found
            do  leftParsingIndex++;
            while (array[leftParsingIndex] > pivot);

            // right index parses to the left, until greater (or equal) is found
            do  rightParsingIndex--;
            while (array[rightParsingIndex] < pivot);

            // if indices have not crossed, swap items
            if (leftParsingIndex < rightParsingIndex)
                mySwap(array[leftParsingIndex], array[rightParsingIndex]);
        }
    }

    /* at the end of partition, in the right index is stored the partition key-point.
       All items on left of this point have smaller (greater) value than the pivot,
       while all items placed on the right of this point have greater (smaller) value.*/
    return rightParsingIndex;
}


/* The classic idea of the in-place randomized quicksort algorithm, implemented as a recursive template driver function.
   The function sorts the array in range [start, finish] in ascending or descending order. BY DEFAULT the sorting order is ascending.
   The array (or subarray of it) we want to sort is partitioned into two parts, according to known requirements.
   The algorithm is recursively executed for each one of the parts, until the array is completely sorted. */

template <typename dataType>
void inPlaceRandomizedQuickSort(dataType array[], long long int start, long long int finish, bool ascendingOrder = true) {

    if (start < finish) {
        long long int partitionPosition = partition(array, start, finish, ascendingOrder);
        inPlaceRandomizedQuickSort(array, start, partitionPosition, ascendingOrder);
        inPlaceRandomizedQuickSort(array, partitionPosition + 1, finish, ascendingOrder);
    }
}
#endif // IN_PLACE_RANDOMIZED_QUICK_SORT_H