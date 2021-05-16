
//找规律，定边界

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size(); // row = column
    // 边界怎么确定的？
    for(int x = 0; x < (n+1)/2; ++x){
        for(int y = 0; y < n/2; ++y){
            swap(matrix[x][y], matrix[y][n-x-1]);
            swap(matrix[x][y], matrix[n-x-1][n-y-1]);
            swap(matrix[x][y], matrix[n-y-1][x]);
        }
    }
}