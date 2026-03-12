/*************************************************
 * 题目编号: 1
 * 题目标题: 两数之和
 * 题目标记: two-sum
 * 生成时间: 2026-03-12 20:59:43
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
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                * returnSize = 2;
                int* ret = malloc(sizeof(int) * 2);
                ret[0] = i;
                ret[1] = j;
                return ret;
            }
        }
    }
    * returnSize = 0;
    return NULL;
}
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);
    
    return 0;
}