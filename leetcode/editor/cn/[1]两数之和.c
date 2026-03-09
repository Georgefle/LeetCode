/*************************************************
 * 题目编号: ${question.frontendQuestionId}
 * 题目标题: ${question.title}
 * 题目标记: ${question.titleSlug}
 * 生成时间: $!velocityTool.date()
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*************************************************
 *              工具函数区域
 *************************************************/

// 去除字符串首尾空格
void trim(char *str) {
    int len = strlen(str);
    int start = 0, end = len - 1;

    while (start < len && isspace(str[start])) start++;
    while (end >= 0 && isspace(str[end])) end--;

    if (start > 0 || end < len - 1) {
        memmove(str, str + start, end - start + 1);
        str[end - start + 1] = '\0';
    }
}

// 解析形如 [1,2,3,4] 的数组
int* parseIntArray(char *input, int *returnSize) {
    trim(input);

    if (input[0] == '[') input++;
    int len = strlen(input);
    if (input[len - 1] == ']') input[len - 1] = '\0';

    int *arr = malloc(sizeof(int) * 10000);
    int count = 0;

    char *token = strtok(input, ",");
    while (token != NULL) {
        arr[count++] = atoi(token);
        token = strtok(NULL, ",");
    }

    *returnSize = count;
    return arr;
}

// 打印数组
void printIntArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i != size - 1) printf(", ");
    }
    printf("]\n");
}

/*************************************************
 *           算法核心函数区域
 *************************************************/

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

/*************************************************
 *                 主函数
 *************************************************/

int main() {
    char input[10000];

    // 支持多测试用例
    while (fgets(input, sizeof(input), stdin)) {

        // 解析第一行数组
        int numsSize;
        int* nums = parseIntArray(input, &numsSize);

        // 读取 target
        fgets(input, sizeof(input), stdin);
        int target = atoi(input);

        int returnSize = 0;

        // 调用算法函数
        int* result = twoSum(nums, numsSize, target, &returnSize);

        // 输出结果
        printIntArray(result, returnSize);

        // 释放内存
        free(nums);
        free(result);
    }

    return 0;
}


