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
#include "uthash.h"

/* 算法核心函数区域 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct hashNode {
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashNode* hashNode;

struct hashNode* find(int nKey) {
    struct hashNode* tmp;
    HASH_FIND_INT(hashNode, &nKey, tmp);
    return tmp;
}

// 没有重复时插入节点
void insert(int key, int val) {
    struct hashNode* node = find(key);
    if (node == NULL) {
        struct hashNode* tmp = malloc(sizeof(struct hashNode));
        tmp->key = key;
        tmp->val = val;
        HASH_ADD_INT(hashNode, key, tmp);
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

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < numsSize; i++) {
        struct hashNode* node = find(target - nums[i]);
        if (node == NULL) {
            insert(nums[i], i);
        }
        else {
            *returnSize = 2;
            int* ret = malloc(sizeof(int) * 2);
            ret[0] = i;
            ret[1] = node->val;
            freeHashTable();
            return ret;
        }
    }
    *returnSize = 0;
    freeHashTable();
    return NULL;
}

// int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
//     for (int i = 0; i < numsSize; i++) {
//         for (int j = i + 1; j < numsSize; j++) {
//             if (nums[i] + nums[j] == target) {
//                 * returnSize = 2;
//                 int* ret = malloc(sizeof(int) * 2);
//                 ret[0] = i;
//                 ret[1] = j;
//                 return ret;
//             }
//         }
//     }
//     * returnSize = 0;
//     return NULL;
// }

//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    // target在此处写死，改变时需要手动修改
    int target = 9;

    int numsSize;
    int* nums = parseIntArray(input, strlen(input), &numsSize);

    int returnSize;
    int* returnArr = twoSum(nums, numsSize, target, &returnSize);

    printIntArray(returnArr, returnSize);

    free(nums);
    free(returnArr);
    
    return 0;
}