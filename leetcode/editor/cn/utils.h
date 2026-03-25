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

/**
 *
 * @param input 传入的字符序列
 * @param len 字符序列中的有效字符
 * @param returnSize 一个int的地址，用于反应返回的int数组的长度,长度为0则返回0
 * @return 返回一个int数组，为堆内存需要free
 */
int* parseIntArray(char* input, int len, int* returnSize);

/**
 *
 * @param input 传入的字符序列
 * @param arraySize int的地址，程序中修改int值，反应元素为数组的数组的长度
 * @param arrayColSize 指向int的指针的地址，程序中修改指针值，指向一个数组，反应数组集合中每一个数组的长度
 * @return 一个解析好的数组集合。或者说返回值指向int*类型的数组。需要逐层free（调用freeArrSet）
 */
int** parseArraySet(char* input, int* arraySize, int** arrayColSize);

/**
 *
 * @param arr 传入的int数组
 * @param size int数组的长度
 */
void printIntArray(int* arr, int size);

/**
 *
 * @param arrSet 元素为数组的数组
 * @param arrSize 数组集合的长度
 * @param arrayColSize 数组集合中每一个数组的长度
 */
void printArrSet(int** arrSet, int arrSize, int* arrayColSize);

/**
 *
 * @param arrSet 需要free的int*数组
 * @param arraySize 数组的大小
 * @param arrayColSize 由每一个数组元素大小组成的数组，需要free
 */
void freeArrSet(int** arrSet, int arraySize, int* arrayColSize);

#endif //LEETCODE_UTILS_H