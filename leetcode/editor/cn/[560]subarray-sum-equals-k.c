/*************************************************
 * 题目编号: 560
 * 题目标题: 和为 K 的子数组
 * 题目标记: subarray-sum-equals-k
 * 生成时间: 2026-03-25 19:21:15
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "utils.h"
#include "utils.c" //这里为了便捷就这么写了
#include "uthash.h"

/* 算法核心函数区域 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//leetcode submit region begin(Prohibit modification and deletion)

struct hashNode {
    int key; // 前缀和
    int times;
    UT_hash_handle hh;
};

struct hashNode* hashNode = NULL;

struct hashNode* find(int key) {
    struct hashNode* tmp;
    HASH_FIND_INT(hashNode, &key, tmp);
    return tmp;
}

// 根据key值插入，如果已经存在则times + 1
void insert(int key) {
    struct hashNode* node = find(key);
    if (node == NULL) {
        struct hashNode* tmp = malloc(sizeof(struct hashNode));
        tmp->key = key;
        tmp->times = 1;
        HASH_ADD_INT(hashNode, key, tmp);
    }
    else {
        node->times++;
    }
}

void freeHashTable() {
    struct hashNode* current, * tmp;
    HASH_ITER(hh, hashNode, current, tmp) {
        HASH_DEL(hashNode, current);
        free(current);
    }
    hashNode = NULL;
}

int subarraySum(int* nums, int numsSize, int k) {
    int prefixSumOfI = 0;
    insert(prefixSumOfI);
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSumOfI += nums[i];
        struct hashNode* node = find(prefixSumOfI - k);
        if (node != NULL) {
            count += node->times;
        }
        insert(prefixSumOfI);
    }
    freeHashTable();
    return count;
}

// // 这个方法超时了
// int subarraySum(int* nums, int numsSize, int k) {
//     // int count = 0;
//     // // 在这里与前缀和数组中分析，以数组首元素开头的连续序列是否符合条件
//     // if (nums[0] == k) count++;
//     // // 将数组变成前缀和数组，方便后续计算
//     // for (int i = 1; i < numsSize; i++) {
//     //     nums[i] += nums[i - 1];
//     //     if (nums[i] == k) count++;
//     // }
//     // // 判断不以首元素开头，以非首元素结尾的连续序列是否符合条件
//     // for (int end = 1; end < numsSize; end++) {
//     //     for (int start = 0; start < end; start++) {
//     //         if (nums[end] - nums[start] == k) count++;
//     //     }
//     // }
//     // return count;
//     int count = 0;
//     // 直接考虑枚举出以end元素结尾的所有满足条件的连续序列
//     for (int end = 0; end < numsSize; end++) {
//         int sum = 0;
//         for (int start = end; start >= 0; start--) {
//             sum += nums[start];
//             if (sum == k) count++;
//         }
//     }
//     return count;
// }
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    // 这里写死了k，后续需要根据输入修改
    int k = 3;

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    int result = subarraySum(nums, numsSize, k);

    printf("The result is: %d", result);

    return 0;
}