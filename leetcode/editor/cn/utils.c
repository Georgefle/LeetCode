//
// Created by windows on 12/3/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils.h"

int push(struct DynamicArr* a, int num) {
    if (a->capacity == 0) {
        a->capacity = 8;
        a->index = 0;
        a->arr = malloc(sizeof(*a->arr) * a->capacity);
        if (!a->arr) return -1;
    }
    if (a->index == a->capacity) {
        a->capacity *= 2;
        int* tmp = realloc(a->arr, sizeof(*a->arr) * a->capacity);
        if (tmp == NULL) {
            return -1; // 返回错误
        }
        a->arr = tmp;
    }
    a->arr[a->index++] = num;
    return 0; // 正常返回
}

// 解析形如 [1,2,3,4] 的数组,不能够识别负数
// 比较好的处理负号的方式
int* parseIntArray(char* input, int len, int* returnSize) {
    struct DynamicArr a = {0};

    int num = 0;
    bool isNum = false;

    // 处理负号，解析数字开始时的sign由pendingSign维护
    int sign = 1;
    bool pendingSign = false;
    while (*input && len) {
        if (*input == '-' && !isNum) {
            pendingSign = true;
        }
        else if (isdigit((unsigned char)*input)) {
            if (!isNum) {
                sign = pendingSign ? -1 : 1;
                pendingSign = false;
            }

            isNum = true;
            num = num * 10 + (num >= 0 ? (*input - '0') : -(*input - '0'));
        }
        else {
            pendingSign = false;

            if (isNum) {
                // 结算
                push(&a, num * sign);  // 这里没有处理返回值了
                num = 0;
                isNum = false;
            }
        }
        input++;
        len--;
    }

    if (isNum) {
        // 意味着最后没有结算到,字符串就已经结束了，结算这最后的一次
        push(&a, num * sign);
        num = 0;
        isNum = false;
    }

    *returnSize = a.index;
    return a.arr;
}

// region
// 处理负号时提前消费，导致parser稍微有点不够优雅
// // 解析形如 [1,2,3,4] 的数组,不能够识别负数
// int* parseIntArray(char* input, int len, int* returnSize) {
//     struct DynamicArr a = {0};
//
//     int num = 0;
//     bool isNum = false;
//     while (*input && len) {
//         if (isdigit((unsigned char)*input)) {
//             isNum = true;
//             num = num * 10 + (num >= 0 ? (*input - '0') : -(*input - '0'));
//         }
//         else {
//             if (isNum) {
//                 // 结算
//                 push(&a, num);  // 这里没有处理返回值了
//                 num = 0;
//                 isNum = false;
//             }
//             if (*input == '-' && len > 1) {
//                 if (isdigit((unsigned char)input[1])) {
//                     isNum = true;
//                     num = -(input[1] - '0');
//                     input++;
//                     len--;
//                 }
//             }
//
//         }
//         input++;
//         len--;
//     }
//
//     if (isNum) {
//         // 意味着最后没有结算到,字符串就已经结束了，结算这最后的一次
//         push(&a, num);
//         num = 0;
//         isNum = false;
//     }
//
//     *returnSize = a.index;
//     return a.arr;
// }
// endregion

// 解析元素为数组的数组，形如[[1,3],[2,6],[8,10],[15,18]]
int** parseArraySet(char* input, int* arraySize, int** arrayColSize) {
    int capacity = 8;
    int index = 0;
    int** arrSet = malloc(sizeof(*arrSet) * capacity);
    *arrayColSize = malloc(sizeof(**arrayColSize) * capacity);

    int depth = 0;
    while (*input) {
        if (*input == '[') {
            depth++;
            if (depth == 2) {
                // 这里进入一个结算过程,解析一段[...]
                char* start = input;
                input++;
                while (*input && depth != 1) {
                    if (*input == '[') depth++;
                    else if (*input == ']') depth--;
                    input++;
                }

                int len = input - start;

                int colSize;
                int* subArr = parseIntArray(start, len, &colSize);

                // 赋值过程
                if (index == capacity) {
                    capacity *= 2;
                    int** tmp1 = realloc(arrSet, sizeof(*tmp1) * capacity);
                    int* tmp2 = realloc(*arrayColSize, sizeof(**arrayColSize) * capacity);
                    if (!tmp1 || !tmp2) {
                        return NULL; // 返回错误，但是一般就没有处理，处理的过程会有点复杂
                    }
                    arrSet = tmp1;
                    *arrayColSize = tmp2;
                }
                arrSet[index] = subArr;
                (*arrayColSize)[index] = colSize;
                index++;

                continue; // 结算过程完成后当前的input指向一个还没有被处理过的字符，不能够执行最后的input++，所以跳过
            }
        }
        else if (*input == ']') depth--;
        input++;
    }
    *arraySize = index;
    return arrSet;
}

// 释放为元素为数组的数组分配的空间
void freeArrSet(int** arrSet, int arraySize, int* arrayColSize) {
    for (int i = 0; i < arraySize; i++) {
        free(arrSet[i]);
    }
    free(arrSet);
    free(arrayColSize);
}

// 打印数组
void printIntArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i != size - 1) printf(", ");
    }
    printf("]");
}

// 打印元素为数组的数组
void printArrSet(int** arrSet, int arrSize, int* arrayColSize) {
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printIntArray(arrSet[i], arrayColSize[i]);
    }
    printf("]");
}