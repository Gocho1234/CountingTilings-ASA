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

ull solve(int *stair);
int get_top_right(int *stair);
int get_max_tiling_size(int top_right, int *stair);
std::string generate_state(int *stair);

int n, m;
std::unordered_map<std::string, ull> dp;

int main() {
    std::cin >> n >> m;

    int stair[n + 1];

    stair[n] = 0;
    for (int i = 0; i < n; i++) {
        int value = m;
        std::cin >> value;
        stair[i] = value;
        stair[n] += value;
    }

    if (n <= 0 || m <= 0 || stair[n - 1] <= 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << solve(stair) << "\n";
    }

    return 0;
}

ull solve(int *stair) {
    std::string state = generate_state(stair);

    if (dp[state]) {
        return dp[state];
    }

    if (!stair[n]) {
        return dp[state] = 1;
    }

    // TODO: this needs to be more efficient
    int top_right = get_top_right(stair);
    int tiling_size = get_max_tiling_size(top_right, stair);

    int new_stair[n];
    for (int i = 1; i <= tiling_size; i++) {
        memcpy(new_stair, stair, (n + 1) * sizeof(int));
        for (int j = 0; j < i; j++) {
            new_stair[top_right + j] -= i;
            new_stair[n] -= i;
        }

        dp[state] += solve(new_stair);
    }

    return dp[state];
}

int get_top_right(int *stair) {
    int top_right = 0;

    for (int i = 1; i < n; i++) {
        if (stair[top_right] < stair[i]) {
            top_right = i;
        }
    }

    return top_right;
}

int get_max_tiling_size(int top_right, int *stair) {
    int tiling_size = 1;

    for (int i = top_right + 1; i < n; i++) {
        if (stair[i] == stair[top_right] && stair[i] == stair[i - 1]) {
            tiling_size++;
        } else {
            break;
        }
    }

    return std::min(stair[top_right], tiling_size);
}

std::string generate_state(int *stair) {
    std::string state = "";

    for (int i = 0; i < n; i++) {
        state += std::to_string(stair[i]);
    }

    return state;
}
