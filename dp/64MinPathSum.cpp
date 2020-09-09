#include "dp.h"

int uniquePath3::minPathSum(vector<vector<int> > &grid)
{
    int m = grid.size();
    int n = grid[0].size();

    f_ = vector<vector<int>>(m+1, vector<int>(n+1, INT_MAX));

    return pathSum(m, n, grid);
}

int uniquePath3::pathSum(int m, int n, vector<vector<int> > &g)
{
    if(m <= 0 || n <= 0)
        return INT_MAX;
    if(m == 1 && n == 1)
        return g[0][0];
    if(f_[m][n] != INT_MAX)
        return f_[m][n];
    f_[m][n] = min(pathSum(m-1, n, g), pathSum(m, n-1, g))+g[m-1][n-1];
    return f_[m][n];
}
