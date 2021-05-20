//
// Created by jianx on 9/16/2020.
//
#include "dp.h"

//T: O(n^3)
int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix.size();
    int n = matrix[0].size();

    // sums[i][j] = sum(matrix[0][0] ~ matrix[i-1][j-1])
    vector<vector<int>> sums(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            sums[i][j] = matrix[i - 1][j - 1] - '0'
                         + sums[i - 1][j]
                         + sums[i][j - 1]
                         - sums[i - 1][j - 1];

    int ans = 0;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = min(m - i + 1, n - j + 1); k > 0; --k) {
                int sum = sums[i + k - 1][j + k - 1]
                          - sums[i + k - 1][j - 1]
                          - sums[i - 1][j + k - 1]
                          + sums[i - 1][j - 1];
                // full of 1
                if (sum == k*k) {
                    ans = max(ans, sum);
                    break;
                }
            }

    return ans;
}
//
//// T: O(n^2)
//int maximalSquare(vector<vector<char>>& matrix) {
//    if (matrix.empty()) return 0;
//    int m = matrix.size();
//    int n = matrix[0].size();
//
//    // S: O(n^2)
//    vector<vector<int>> sizes(m, vector<int>(n, 0));
//
//    int ans = 0;
//
//    for (int i = 0; i < m; ++i)
//        for (int j = 0; j < n; ++j) {
//            sizes[i][j] = matrix[i][j] - '0';
//            if (!sizes[i][j]) continue;
//
//            // horizontal conditions
//            // upper left element & 1st row & 1st column
//            if (i == 0 || j == 0) {
//                // do nothing
//            }
//            else {
//                sizes[i][j] = min(min(sizes[i - 1][j - 1],
//                                      sizes[i - 1][j]),
//                                  sizes[i][j - 1]) + 1;
//            }
//
//            ans = max(ans, sizes[i][j]*sizes[i][j]);
//        }
//    return ans;
//}