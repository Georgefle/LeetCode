//
// Created by windows on 12/3/2026.
//

#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H
struct DynamicArr {
    int* arr;
    int index;
    int capacity;
};

int* parseIntArray(char* input, int len, int* returnSize);

int** parseArraySet(char* input, int* arraySize, int** arrayColSize);

void printIntArray(int* arr, int size);

void printArrSet(int** arrSet, int arrSize, int* arrayColSize);

void freeArrSet(int** arrSet, int arraySize, int* arrayColSize);

#endif //LEETCODE_UTILS_H