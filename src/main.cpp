/*
 *      File: main.cpp
 *      Author: Gonçalo Sampaio Bárias (ist1103124)
 *      Group: 13
 *      Description: Counting tilings problem solved in c++.
 */

#include <iostream>
#include <vector>

typedef unsigned long long ull;
typedef std::vector<std::vector<int>> matrix;

ull n, m, value, answer;
matrix rectangle;
std::vector<ull> max_columns;

/*
void print_matrix() {
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < m; j++) {
            std::cout << rectangle.at(j).at(i) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
*/

void tile(int num, ull size, ull column, ull line) {
    for (ull i = 0; i < size; i++) {
        for (ull j = 0; j < size; j++) {
            rectangle.at(column + i).at(line + j) = num;
        }
    }
}

void solve(ull column, ull line) {
    ull max_line = n;
    bool tiled;

    if (line == n) {
        column++;
        line = 0;
    }

    if (column == m) {
        answer++;
        return;
    }

    if (column >= max_columns.at(line)) {
        return solve(column, line + 1);
    }

    for (ull i = line + 1; i < n; i++) {
        if (rectangle.at(column).at(i)) {
            max_line = i;
            break;
        }
    }

    for (ull size = 1;
         size <= max_columns.at(line) - column && size <= max_line - line;
         size++) {
        tiled = false;
        if (!rectangle.at(column).at(line)) {
            tile(1, size, column, line);
            tiled = true;
        }

        solve(column, line + 1);

        if (tiled) {
            tile(0, size, column, line);
        } else {
            break;
        }
    }
}

int main() {
    bool has_area = false;
    std::cin >> n >> m;

    for (ull i = 0; i < n; i++) {
        std::cin >> value;
        if (value) {
            has_area = true;
        }
        max_columns.push_back(value);
    }

    for (ull i = 0; i < m; i++) {
        std::vector<int> vec = {};
        for (ull j = 0; j < n; j++) {
            vec.push_back(0);
        }
        rectangle.push_back(vec);
    }

    if (n <= 0 || m <= 0 || !has_area) {
        std::cout << 0 << std::endl;
        return 0;
    }

    solve(0, 0);

    std::cout << answer << std::endl;

    return 0;
}
