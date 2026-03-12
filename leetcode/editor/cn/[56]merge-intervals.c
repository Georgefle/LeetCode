/*************************************************
 * 题目编号: 56
 * 题目标题: 合并区间
 * 题目标记: merge-intervals
 * 生成时间: 2026-03-12 20:18:34
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils.h"
#include "utils.c" //这里为了便捷就这么写了

/* 算法核心函数区域 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
// region
void swap(int* a, int* b) {
    int start = a[0];
    int end = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[0] = start;
    b[1] = end;
}

bool compare(int* a, int* b) {
    if (a[0] > b[0]) return true;
    return false;
}

int partition(int** array, int low, int high) {
    int* pivot = *(array + low);
    while (1) {
        while (compare(pivot, *(array + low))) {
            low++;
        }
        while (compare(*(array + high), pivot)) {
            high--;
        }

        if (low >= high) return high;

        swap(*(array + low), *(array + high));
    }
}

void quickSort(int** intervals, int low, int high) {

    if (low == high) return;

    int bound = partition(intervals, low, high);
    quickSort(intervals, low, bound);
    quickSort(intervals, bound + 1, high);
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    // 首先比较自然的想法就是将这若干个区间按照start的大小进行排序，然后后续应该就比较简单了
    // 于是我们考虑给一组指向具体区间的指针构成的数组进行排序，这个排序的比较方式与交换逻辑和常规的数组不同
    quickSort(intervals, 0, intervalsSize - 1);
    int** ret = malloc(sizeof (int*) * intervalsSize);
    *returnColumnSizes = malloc(sizeof (int) * intervalsSize);

    int* current = intervals[0]; // current保存结算时的区间信息
    int retIndex = 0; // 记录已经结算的区间个数

    for (int i = 1; i < intervalsSize; i++) {
        int * next = intervals[i];
        if (current[1] >= next[0]) {
            // 有重叠，将结束值保存到current中
            if (current[1] < next[1]) {
                current[1] = next[1];
            }
        }
        else { // 没有重叠，进行结算
            ret[retIndex] = malloc(sizeof (int) * 2);
            ret[retIndex][0] = current[0];
            ret[retIndex][1] = current[1];
            (*returnColumnSizes)[retIndex] = 2;
            retIndex++; // 已结算区间加1
            current = next; // 未重叠并且结算后，将下一个需要结算的头区间赋值到current中，使后续操作得以进行
        }
    }

    // 结算最后一个区间
    ret[retIndex] = (int*)malloc(sizeof(int) * 2);
    ret[retIndex][0] = current[0];
    ret[retIndex][1] = current[1];
    (*returnColumnSizes)[retIndex] = 2;
    retIndex++;

    // 最后处理一下赋值
    *returnSize = retIndex;

    return ret;
}
// endregion
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);
    // 解析元素为数组的数组
    int arraySize;
    int* arrayColSize;
    int** numsSet = parseArraySet(input, &arraySize, &arrayColSize);
    printf("%d\n", arraySize);
    printIntArray(arrayColSize, arraySize);
    printf("\n");
    printArrSet(numsSet, arraySize, arrayColSize);
    freeArrSet(numsSet, arraySize, arrayColSize);

    
    return 0;
}