#include "dp.h"

int uniquePath2::uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid)
{
    int m = obstacleGrid.size();
    if(m == 0) return 0;
    int n = obstacleGrid[0].size();

    f_ = vector<vector<int>>(m+1, vector<int>(n+1, INT_MAX));
    return paths(m, n, obstacleGrid);
}

int uniquePath2::paths(int m, int n, vector<vector<int> > &o)
{
    if(m <= 0 || n <= 0)
        return 0;
    if(m == 1 && n == 1)
        return 1-o[0][0];
    if(f_[m][n] != INT_MAX)
        return f_[m][n];
    if(o[m-1][n-1] == 1)
        return 0;
    else
        f_[m][n] = paths(m-1, n, o) + paths(m, n-1, o);
    return f_[m][n];
}