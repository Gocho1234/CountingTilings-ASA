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
#include <vector>

typedef unsigned long long ull;

struct vector_hasher {
    int operator()(const std::vector<int> &v) const {
        int hash = v.size();
        for (auto &i : v) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

ull solve(std::vector<int> &stair);
int get_top_right(std::vector<int> &stair);
int get_max_tiling_size(const int top_right, std::vector<int> &stair);

int n, m;
std::unordered_map<std::vector<int>, ull, vector_hasher> dp;

int main() {
    std::vector<int> stair(n);

    std::cin >> n >> m;

    int value = m;
    for (int i = 0; i < n; i++) {
        std::cin >> value;
        if (value > m) {
            value = m;
        }
        stair.push_back(value);
    }

    if (n <= 0 || m <= 0 || stair.at(n - 1) <= 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << solve(stair) << "\n";
    }

    return 0;
}

ull solve(std::vector<int> &stair) {
    if (dp.find(stair) != dp.end()) {
        return dp.at(stair);
    }

    for (int i = 0; i < n; i++) {
        if (stair.at(i)) {
            break;
        } else if (i == n - 1) {
            return dp[stair] = 1;
        }
    }

    int top_right = get_top_right(stair);
    int tiling_size = get_max_tiling_size(top_right, stair);

    std::vector<int> new_stair(n);
    for (int i = 1; i <= tiling_size; i++) {
        memcpy(new_stair.data(), stair.data(), n * sizeof(int));
        for (int j = 0; j < i; j++) {
            new_stair.at(top_right + j) -= i;
        }
        dp[stair] += solve(new_stair);
    }

    return dp.at(stair);
}

int get_top_right(std::vector<int> &stair) {
    int top_right = 0;

    for (int i = 1; i < n; i++) {
        if (stair.at(top_right) < stair.at(i)) {
            top_right = i;
        }
    }

    return top_right;
}

int get_max_tiling_size(const int top_right, std::vector<int> &stair) {
    int tiling_size = 1;

    for (int i = top_right + 1; i < n; i++) {
        if (stair.at(i) == stair.at(top_right) &&
            stair.at(i) == stair.at(i - 1)) {
            tiling_size++;
        } else {
            break;
        }
    }

    return std::min(stair.at(top_right), tiling_size);
}
