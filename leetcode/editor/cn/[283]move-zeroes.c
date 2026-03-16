/*************************************************
 * 题目编号: 283
 * 题目标题: 移动零
 * 题目标记: move-zeroes
 * 生成时间: 2026-03-16 11:11:57
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

void swap(int* a, int* b) {
    if (a == b) return;
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void moveZeroes(int* nums, int numsSize) {
    int l = 0;
    for (int r = 0; r < numsSize; r++) {
        if (nums[r] != 0) {
            swap(&nums[l], &nums[r]);
            l++;
        }
    }
}
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    moveZeroes(nums, numsSize);
    printIntArray(nums, numsSize);

    free(nums);
    
    return 0;
}