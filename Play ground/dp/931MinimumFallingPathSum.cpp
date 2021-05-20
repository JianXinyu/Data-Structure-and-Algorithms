//
// Created by jianx on 9/13/2020.
//

#include "dp.h"

//! T: O(mn)
int minFallingPathSum(vector<vector<int>>& A) {
    int m = A.size();
    int n = A[0].size();

    //! S: O(mn)
//    vector<vector<int>> s(m, vector<int>(n+2, INT_MAX));
//
//    for(int x = 0; x < m; x++)
//        for(int y = 1; y <= n; y++)
//        {
//            if(x == 0)
//                s[x][y] = A[x][y-1];
//            else
//            {
//                s[x][y] = min({s[x-1][y-1], s[x-1][y], s[x-1][y+1]}) + A[x][y-1];
//            }
//        }
//
//    return *min_element(s[m-1].begin() + 1, s[m-1].end() - 1);

    //! S: O(1)
    for(int i = 1; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            int sum = A[i-1][j];
            if(j > 0) sum = min(sum, A[i-1][j-1]);
            if(j < m - 1) sum = min(sum, A[i-1][j+1]);
            A[i][j] += sum;
        }
    }

    return *min_element(begin(A.back()), end(A.back()));
}
