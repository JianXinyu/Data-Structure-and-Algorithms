#include "dp.h"

//T: O(mn) S: O(mn)

// Solution 1 memoization recursive
//int uniquePath::uniquePaths(int m, int n) {
//    if(m < 0 || n < 0)
//        return 0;
//    if(m == 1 && n == 1)
//        return 1;
//    if(f_[m][n] > 0)
//        return f_[m][n];
//
//    f_[m][n] = uniquePaths(m-1, n) + uniquePaths(m, n-1);
//
//    return f_[m][n];
//}

// Solution 2 DP
int uniquePath::uniquePaths(int m, int n) {
    vector<vector<int>> f(m+1, vector<int>(n+1, 0));
    f[1][1] = 1;

    for(int x = 1; x <= m; ++x)
        for(int y = 1; y <= n; ++y)
        {
            if(x == 1 && y == 1)
                continue;
            f[x][y] = f[x-1][y] + f[x][y-1];
        }

    return f[m][n];
}