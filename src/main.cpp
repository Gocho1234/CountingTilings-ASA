/*
 *      File: main.cpp
 *      Author: Gonçalo Sampaio Bárias (ist1103124)
 *      Group: 13
 *      Description: Counting tilings problem solved in c++.
 */

#include <iostream>
#include <map>
#include <vector>

typedef long long ll;
typedef std::vector<std::vector<short>> matrix;

ll n, m;
matrix rectangle;
std::vector<ll> max_columns;
std::map<matrix, ll> dp;

void tile(short num, ll size, ll column, ll line) {
    for (ll i = 0; i < size; i++) {
        for (ll j = 0; j < size; j++) {
            rectangle.at(column + i).at(line + j) = num;
        }
    }
}

ll solve(ll column, ll line) {
    ll max_line = n, answer = 0;

    if (line == n) {
        column++;
        line = 0;
    }

    if (dp[rectangle]) {
        return dp[rectangle];
    }

    if (column == m) {
        return 1;
    }

    if (column >= max_columns.at(line)) {
        return solve(column, line + 1);
    }

    for (ll i = line + 1; i < n; i++) {
        if (rectangle.at(column).at(i)) {
            max_line = i;
            break;
        }
    }

    for (ll size = 1;
         size <= max_columns.at(line) - column && size <= max_line - line;
         size++) {
        bool tiled = false;
        if (!rectangle.at(column).at(line)) {
            tile(1, size, column, line);
            tiled = true;
        }

        answer += solve(column, line + 1);

        if (tiled) {
            tile(0, size, column, line);
        } else {
            break;
        }
    }

    return dp[rectangle] = answer;
}

int main() {
    bool has_area = false;
    std::cin >> n >> m;

    for (ll i = 0; i < n; i++) {
        ll value = m;
        std::cin >> value;
        if (value > 0) {
            has_area = true;
        }
        max_columns.push_back(value);
    }

    for (ll i = 0; i < m; i++) {
        std::vector<short> vec = {};
        for (ll j = 0; j < n; j++) {
            vec.push_back(0);
        }
        rectangle.push_back(vec);
    }

    if (n <= 0 || m <= 0 || !has_area) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::cout << solve(0, 0) << std::endl;

    return 0;
}
