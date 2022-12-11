/*
 *      File: main.cpp
 *      Author: Gonçalo Sampaio Bárias (ist1103124)
 *      Group: al013
 *      Description: Counting tilings problem solved in c++.
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef unsigned long long ull;

ull solve(std::vector<int> *stair);
int get_top_right(std::vector<int> *stair);
int get_max_tiling_size(int top_right, std::vector<int> *stair);
std::vector<int> copy_vector(std::vector<int> *stair);
std::string generate_state(std::vector<int> *stair);

int n, m;
std::unordered_map<std::string, ull> dp;

int main() {
    std::vector<int> stair;

    std::cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int value = m;
        std::cin >> value;
        stair.push_back(value);
    }

    if (n <= 0 || m <= 0 || stair.at(n - 1) <= 0) {
        std::cout << 0 << "\n";
    } else {
        std::cout << solve(&stair) << "\n";
    }

    return 0;
}

ull solve(std::vector<int> *stair) {
    std::string state = generate_state(stair);

    if (dp[state]) {
        return dp[state];
    }

    for (int i = 0; i < n; i++) {
        if (stair->at(i)) {
            break;
        } else if (i == n - 1) {
            return dp[state] = 1;
        }
    }

    int top_right = get_top_right(stair);
    int tiling_size = get_max_tiling_size(top_right, stair);
    for (int i = 1; i <= tiling_size; i++) {
        std::vector<int> new_stair = copy_vector(stair);
        for (int j = 0; j < i; j++) {
            new_stair.at(top_right + j) -= i;
        }
        dp[state] += solve(&new_stair);
    }

    return dp[state];
}

int get_top_right(std::vector<int> *stair) {
    int top_right = 0;

    for (int i = 1; i < n; i++) {
        if (stair->at(top_right) < stair->at(i)) {
            top_right = i;
        }
    }

    return top_right;
}

int get_max_tiling_size(int top_right, std::vector<int> *stair) {
    int tiling_size = 1;

    for (int i = top_right + 1; i < n; i++) {
        if (stair->at(i) == stair->at(top_right) &&
            stair->at(i) == stair->at(i - 1)) {
            tiling_size++;
        } else {
            break;
        }
    }

    return std::min(stair->at(top_right), tiling_size);
}

std::vector<int> copy_vector(std::vector<int> *stair) {
    std::vector<int> new_stair(*stair);
    return new_stair;
}

std::string generate_state(std::vector<int> *stair) {
    std::string state(stair->begin(), stair->end());

    return state;
}
