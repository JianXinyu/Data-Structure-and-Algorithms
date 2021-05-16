// 暴力迭代，考虑所有情况，尚未总结huahua
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;
    const int m = matrix.size();
    const int n = matrix[0].size();
    // corner case
    if(m == 1) return matrix[0];
    if(n == 1){
        for(int j = 0; j < m; ++j)
            ans.push_back(matrix[j][0]);
        return ans;
    }
    int s = 0; // shrink
    while((2*s) < min(m, n) - 1){
        for(int j = s; j <= n-1-s; ++j)
            ans.push_back(matrix[s][j]);
        for(int i = s+1; i <= m-1-s; ++i)
            ans.push_back(matrix[i][n-1-s]);
        for(int j = n-2-s; j >= s; --j)
            ans.push_back(matrix[m-1-s][j]);
        for(int i = m-2-s; i > s; --i)
            ans.push_back(matrix[i][s]);
        ++s;
    }
    if((2*s) > min(m, n) - 1)
        return ans;
    if(m <= n){
        for(int j = s; j <= n-1-s; ++j)
            ans.push_back(matrix[s][j]);
    }
    if(m > n){
        for(int i = s; i <= m-1-s; ++i)
            ans.push_back(matrix[i][n-1-s]);
    }
    return ans;
}
