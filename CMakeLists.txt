cmake_minimum_required(VERSION 4.1)
project(LeetCode C)

set(CMAKE_C_STANDARD 11)

add_definitions(-DLOCAL)

add_executable(LeetCode main.c)

add_executable(LeetCode_1 leetcode/editor/cn/[1]两数之和.c)
