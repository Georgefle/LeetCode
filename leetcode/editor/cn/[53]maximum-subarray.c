/*************************************************
 * 题目编号: 53
 * 题目标题: 最大子数组和
 * 题目标记: maximum-subarray
 * 生成时间: 2026-03-12 20:16:27
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


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);
    
    return 0;
}