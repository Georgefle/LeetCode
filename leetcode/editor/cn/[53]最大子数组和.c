/*************************************************
 * 题目编号: 53
 * 题目标题: 最大子数组和
 * 题目标记: maximum-subarray
 * 生成时间: 2026-03-04 17:02:47
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

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

//使用分治的方法完成的第二种实现 start
struct Status {
    int isum; // 数组区间和
    int lsum; // 以l为左端点的最大子段和
    int rsum; // 以r为右端点的最大字段和
    int msum; // 数组中最大连续字段和
};

// 合并两个数组区间，维护这个新合并区间的状态
struct Status pushUp(struct Status l, struct Status r) {
    int isum = l.isum + r.isum;
    int lsum = fmax(l.isum + r.lsum, l.lsum);
    int rsum = fmax(r.isum + l.rsum, r.rsum);
    int msum = fmax(fmax(l.msum, r.msum), l.rsum + r.lsum);
    return (struct Status) {isum, lsum, rsum, msum};
}

// 获得想要区间的状态信息
struct Status get(int* a, int l, int r) {
    if (l == r) {
        return (struct Status){a[l], a[l], a[l], a[l]};
    }
    int mid = l + (r - l) / 2;
    struct Status left = get(a, l, mid);
    struct Status right = get(a, mid + 1, r);
    return pushUp(left, right);
}
// end


int maxSubArray(int* nums, int numsSize) {
    // 这个最大的连续子数组必然需要以整个数组中的某个数结尾
    // 设i属于n，每一个i中有一个以i结尾的最大的连续子数组，记为f(i)，我们可以把问题看成找到所有f(i)中的最大值
    // 另外可以证明出这样的关系： f(i) = MAX(f(i - 1) + nums[i], nums[i])
    int max = nums[0];
    int max_i = 0;
    for (int i = 0; i < numsSize; i++) {
        if (max_i + nums[i] > nums [i]) {
            max_i += nums[i];
        }
        else max_i = nums[i];
        if (max < max_i) max = max_i;
    }
    return max;

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
        // int* result = twoSum(nums, numsSize, target, &returnSize);

        // 输出结果
        // printIntArray(result, returnSize);

        // 释放内存
        free(nums);
        // free(result);
    }

    return 0;
}