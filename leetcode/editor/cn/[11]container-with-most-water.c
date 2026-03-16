/*************************************************
 * 题目编号: 11
 * 题目标题: 盛最多水的容器
 * 题目标记: container-with-most-water
 * 生成时间: 2026-03-13 15:44:59
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

// 双指针，
int maxArea(int* height, int heightSize) {
    int max = 0; // 初始化为0，面积不会小于0
    int l = 0;
    int r = heightSize - 1;
    int interval = heightSize - 1;
    while (l <= r) {
        if (height[l] > height[r]) {
            max = height[r] * interval > max ? height[r] * interval : max;
            r--;
        }
        else {
            max = height[l] * interval > max ? height[l] * interval : max;
            l++;
        }
        interval--;
    }
    return max;
}

// 最直接的思路，超时！
// int maxArea(int* height, int heightSize) {
//     int max = 0;
//     for (int i = 1; i <= heightSize; i++) {
//         for (int j = 0; j + i <heightSize; j++) {
//             if (height[j] > height[j + i]) {
//                 max = height[j + i] * i > max ? height[j + i] * i : max;
//             }
//             else max = height[j] * i > max ? height[j] * i : max;
//         }
//     }
//     return max;
// }
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    printf("%d", maxArea(nums, numsSize));

    free(nums);
    
    return 0;
}