/*************************************************
 * 题目编号: 189
 * 题目标题: 轮转数组
 * 题目标记: rotate-array
 * 生成时间: 2026-03-13 15:43:42
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

// gcd(a,b) * lcm(a,b) = a * b
// 推导过程（逐步向内）： -》 质数唯一性定义 -》 欧几里得引理 -》贝祖定理 -》辗转相除逆过程
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// 直接一步到位，使用最大公约数来控制终止条件
void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    int count = gcd(numsSize, k);
    for (int start = 0; start < count; start++) {
        int current = start;
        int prev = nums[start];
        do {
            int next = (current + k) % numsSize;
            // 交换
            int tmp = nums[next];
            nums[next] = prev;
            prev = tmp;

            current = next;
        } while (current != start);
    }
}

// 反转数组方法，[A | B] reverse whole-> [reverse(B) | reverse(A)] reverseA,B -> [B | A]
// void reverse(int* nums, int start, int end) {
//     while (start < end) {
//         int tmp = nums[start];
//         nums[start] = nums[end];
//         nums[end] = tmp;
//
//         start++;
//         end--;
//     }
// }

// void rotateOnce(int* nums, int numsSize) {
//     int* current = nums;
//     int tmp1;
//     int tmp2 = current[0];
//     while (current != nums + numsSize - 1) {
//         tmp1 = current[1];
//         current[1] = tmp2;
//         tmp2 = tmp1;
//         current++;
//     }
//     nums[0] = tmp2;
// }
//
// void rotate(int* nums, int numsSize, int k) {
//     // 如果为了安全，想法是前面加上一个数据有效性的验证
//     // 有一个比较暴力但是清晰的思路，就是每次都向右轮转一步，一共轮转k次
//     // 这个方法效率太低，中间的交换过程太多太耗时
//     k %= numsSize;
//     while (k) {
//         rotateOnce(nums, numsSize);
//         k--;
//     }
// }

//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);
    
    return 0;
}