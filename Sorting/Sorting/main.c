//
//  main.c
//  Sorting
//
//  Created by Mustajab Azam  on 2019-04-22.
//  Copyright © 2019 mustajabazam. All rights reserved.
//

#include <stdio.h>

void bubbleSort(int array[], int size);
void printArray(int array[], int size);
void insertionSort(int array[], int size);


int main(int argc, const char * argv[]) {
    // insert code here...
    int numbers [] = {5,8,4,7,8,4,2,5,7,9,65,3,5,7,8,4,6,7,0,1};
    int size = sizeof(numbers) / sizeof(int);
    
    bubbleSort(numbers, size);
    // insertionSort(numbers, size);
    printArray(numbers, size);
    
    return 0;
}

void bubbleSort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}



void insertionSort(int array[], int size) {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && array[j] < array[j - 1]) {
            if (array[j] < array[j - 1]) {
                int temp = array[j];
                array[j] = array [j - 1];
                array[j - 1] = temp;
                j--;
            }
        }
    }
}
