/*************************************************
 * 题目编号: 3
 * 题目标题: 无重复字符的最长子串
 * 题目标记: longest-substring-without-repeating-characters
 * 生成时间: 2026-03-25 19:07:33
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
struct HashNode {
    char key;
    int index;
    UT_hash_handle hh;
};

struct HashNode* hashNode = NULL;

struct HashNode* find(char key) {
    struct HashNode* tmp;
    HASH_FIND(hh, hashNode, &key, sizeof(char), tmp);
    return tmp;
}

void insert(char key, int index) {
    struct HashNode* tmp = malloc(sizeof(struct HashNode));
    tmp->key = key;
    tmp->index = index;
    HASH_ADD(hh, hashNode, key, sizeof(char), tmp);
}

void freeHashTable() {
    struct HashNode* current, * tmp;
    HASH_ITER(hh, hashNode, current, tmp) {
        HASH_DEL(hashNode, current);
        free(current);
    }
    hashNode = NULL;
}

int lengthOfLongestSubstring(char* s) {
    int max = 0;
    int left = 0;

    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        struct HashNode *node = find(s[i]);

        if (node == NULL) {
            insert(s[i], i);
        }
        else {  // 当前字符是重复的，node->index表示离当前字符最近的重复元素的下标
            // 当前维护的是一个由可能是数组中无重复字符最长子串的开头字符构成的无重复子串，判断新遇到的重复字符是否在这个维护的无重复子串里
            if (node->index >= left) {
                left = node->index + 1;
            }
            // 更新最近的重复字符的下标，后面遇到重复字符的时候就能够找到
            node->index = i;
        }
        int len = i - left + 1;
        max = max > len ? max : len;
    }
    freeHashTable();
    return max;
}
//leetcode submit region end(Prohibit modification and deletion)


/* 主函数 */

int main() {
    char input[10000];
    
    fgets(input, sizeof(input), stdin);

    printf("%d", lengthOfLongestSubstring(input));
    
    return 0;
}