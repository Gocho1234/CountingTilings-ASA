/*
 *      File: main.cpp
 *      Author: Gonçalo Sampaio Bárias (ist1103124)
 *      Group: al013
 *      Description: Counting tilings problem solved in c++.
 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

typedef unsigned long long ull;

#define MAP_INITIAL_SIZE 33554432

ull solve(int *stair, const int width);
int get_top_right(int *stair, const int width);
int get_max_tiling_size(int *stair, const int width, const int top_right);
const ull vector_hasher(const int *v);

int width, length; // width = n, length = m
std::unordered_map<ull, ull> dp(MAP_INITIAL_SIZE);

int main() {
    std::cin >> width >> length;

    int stair[width];

    int max_line = length;
    for (int i = 0; i < width; i++) {
        std::cin >> max_line;
        if (max_line > length) { // if c_i > m then it defaults value to length
            max_line = length;
        }
        stair[i] = max_line;
    }

    // when the stair doesn't exist we have 0 ways to tile
    if (width <= 0 || length <= 0 || stair[width - 1] <= 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << solve(stair, width) << "\n";
    }

    return 0;
}

ull solve(int *stair, const int width) {
    const ull hash = vector_hasher(stair);

    if (dp.find(hash) != dp.end()) {
        return dp.at(hash);
    }

    // base case
    for (int i = 0; i < width; i++) {
        if (stair[i]) {
            break;
        } else if (i == width - 1) {
            return dp[hash] = 1;
        }
    }

    // gets the corner to remove tiles from and the corresponding max tile size
    int top_right = get_top_right(stair, width);
    int tiling_size = get_max_tiling_size(stair, width, top_right);

    int new_stair[width];
    for (int i = 1; i <= tiling_size; i++) {
        std::memcpy(new_stair, stair, width * sizeof(int));
        for (int j = 0; j < i; j++) {
            new_stair[top_right + j] -= i;
        }
        dp[hash] += solve(new_stair, width);
    }

    return dp.at(hash);
}

int get_top_right(int *stair, const int width) {
    int top_right = 0;

    for (int i = 1; i < width; i++) {
        if (stair[top_right] < stair[i]) {
            top_right = i;
        }
    }

    return top_right;
}

int get_max_tiling_size(int *stair, const int width, const int top_right) {
    int tiling_size = 1;

    for (int i = top_right + 1; i < width; i++) {
        if (stair[i] == stair[top_right] && stair[i] == stair[i - 1]) {
            tiling_size++;
        } else {
            break;
        }
    }

    return std::min(stair[top_right], tiling_size);
}

const ull vector_hasher(const int *v) {
    ull hash = width;

    // takes any array of integers and creates an unique hash
    for (int i = 0; i < width; i++) {
        hash ^= v[i] + 0x9e3779b9 + (hash << 6) + (hash >> 2) + (hash << v[i]);
    }

    return hash;
}
