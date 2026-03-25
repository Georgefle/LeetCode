/*************************************************
 * 题目编号: 15
 * 题目标题: 三数之和
 * 题目标记: 3sum
 * 生成时间: 2026-03-16 11:12:31
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

int partition(int* nums, int start, int end) {
    int pivot = nums[(end - start) / 2 + start];
    while (true) {
        while (nums[start] < pivot) start++;
        while (nums[end] > pivot) end--;

        if (start >= end) return end;

        int t = nums[start];
        nums[start] = nums[end];
        nums[end] = t;

        start++;
        end--;
    }
}

void quickSort(int* nums, int start, int end) {
    if (start >= end) return;

    int n = partition(nums, start, end);
    quickSort(nums, start, n);
    quickSort(nums, n + 1, end);
}

int moveNext(int* nums, int numsSize, int now) {
    int next = now + 1;
    while (next < numsSize && nums[now] == nums[next]) {
        next++;
    }
    return next;
}

int movePrev(int* nums, int now) {
    int prev = now - 1;
    while (prev >= 0 && nums[now] == nums[prev]) {
        prev--;
    }
    return prev;
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    quickSort(nums, 0, numsSize - 1);

    int capacity = 8;
    int** arrSet = malloc(sizeof(*arrSet) * capacity);
    *returnColumnSizes = malloc(sizeof(**returnColumnSizes) * capacity);
    int index = 0;

    for (int i = 0; i < numsSize; i = moveNext(nums, numsSize, i)) {
        // 一个比较清晰的版本
        int target = -nums[i];
        int l = i + 1;
        int r = numsSize - 1;

        while (l < r) {
            int sum = nums[l] + nums[r];

            if (sum < target) {
                l = moveNext(nums, numsSize, l);
            }
            else if (sum > target) {
                r = movePrev(nums, r);
            }
            else {
                // 赋值处理，动态数组
                if (index >= capacity) {
                        capacity *= 2;
                        int** tmp1 = realloc(arrSet, sizeof(*arrSet) * capacity);
                        int* tmp2 = realloc(*returnColumnSizes, sizeof(**returnColumnSizes) * capacity);
                        if (!tmp1 || !tmp2) return NULL; //返回错误
                        arrSet = tmp1;
                        *returnColumnSizes = tmp2;
                    }
                    // 赋值保存
                    arrSet[index] = malloc(sizeof(*arrSet[index]) * 3);
                    arrSet[index][0] = nums[i];
                    arrSet[index][1] = nums[l];
                    arrSet[index][2] = nums[r];
                    (*returnColumnSizes)[index] = 3;
                    index++;

                l = moveNext(nums, numsSize, l);
                r = movePrev(nums, r);
            }
        }

        // 这个版本也行，但是稍显混乱
        // int end = numsSize - 1;
        // for (int j = i + 1; j < numsSize; j = moveNext(nums, numsSize, j)) {
        //     int temp = nums[i] + nums[j];
        //     while (end > j && temp + nums[end] > 0) {
        //         end = movePrev(nums, end);
        //     }
        //     // 第一种情况没有找到就结束了，说明下标超过j的元素中，找不到一个和比零小的，第二层遍历就可以结束了
        //     if (end <= j) break;
        //     // 第二种情况，找到最大的end满足三数之和小于等于0，检验是否等于0，进行赋值结算
        //     if (temp + nums[end] == 0) {
        //         // 动态数组
        //         if (index >= capacity) {
        //             capacity *= 2;
        //             int** tmp1 = realloc(arrSet, sizeof(*arrSet) * capacity);
        //             int* tmp2 = realloc(*returnColumnSizes, sizeof(**returnColumnSizes) * capacity);
        //             if (!tmp1 || !tmp2) return NULL; //返回错误
        //             arrSet = tmp1;
        //             *returnColumnSizes = tmp2;
        //         }
        //         // 赋值保存
        //         arrSet[index] = malloc(sizeof(*arrSet[index]) * 3);
        //         arrSet[index][0] = nums[i];
        //         arrSet[index][1] = nums[j];
        //         arrSet[index][2] = nums[end];
        //         (*returnColumnSizes)[index] = 3;
        //         index++;
        //         // 赋值后的处理
        //         end = movePrev(nums, end);
        //     }
        // }
    }

    *returnSize = index;
    return arrSet;
}
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    int returnSize;
    int* returnColSize;
    int** returnArrSet = threeSum(nums, numsSize, &returnSize, &returnColSize);

    printArrSet(returnArrSet, returnSize, returnColSize);

    // 释放堆内存
    free(nums);
    freeArrSet(returnArrSet, returnSize, returnColSize);
    
    return 0;
}