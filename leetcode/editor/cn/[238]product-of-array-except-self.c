/*************************************************
 * 题目编号: 238
 * 题目标题: 除了自身以外数组的乘积
 * 题目标记: product-of-array-except-self
 * 生成时间: 2026-03-13 15:44:52
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int* ret = malloc(sizeof(*ret) * numsSize);

    ret[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        ret[i] = ret[i - 1] * nums[i - 1];
    }

    int currentFactor = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        ret[i] *= currentFactor;
        currentFactor *= nums[i];
    }

    *returnSize = numsSize;
    return ret;
}


// int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
//     int* ret = malloc(sizeof(*ret) * numsSize);
//     int* arrLeft = malloc(sizeof(*arrLeft) * numsSize);
//     int* arrRight = malloc(sizeof(*arrRight) * numsSize);
//
//     arrLeft[0] = 1;
//     for (int i = 1; i < numsSize; i++) {
//         arrLeft[i] = arrLeft[i - 1] * nums[i - 1];
//     }
//
//     arrRight[numsSize - 1] = 1;
//     for (int i = numsSize - 2; i >= 0; i--) {
//         arrRight[i] = arrRight[i + 1] * nums[i + 1];
//     }
//
//     for (int i = 0; i < numsSize; i++) {
//         ret[i] = arrLeft[i] * arrRight[i];
//     }
//     free(arrRight);
//     free(arrLeft);
//     *returnSize = numsSize;
//     return ret;
// }
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    int returnSize;
    int* ret = productExceptSelf(nums, numsSize, &returnSize);
    free(nums);
    printIntArray(ret, numsSize);
    free(ret);
    
    return 0;
}