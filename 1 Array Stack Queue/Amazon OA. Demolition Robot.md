#dfs
Given a 2D matrix with values 0 (trenches) , 1 (flat) , and 9 (obstacle). There is only one obstacle.
Return minimum distance to get the obstacle. If not possible then return -1.  

- The robot must start from the top left corner, which is always flat, and can move one block up, down, right, or left at a time.
 - The demolition robot cannot enter 0 trenches and cannot leave the lot.  
	
Constraints: $1\leq rows, columns \leq 1000$

Example:
Input :  
[[1, 0, 0],  
 [1, 0, 0],  
 [1, 9, 1]]  
Output :  3  
 
```cpp
int distanceTraversed(vector<vector<int>> &lot) {
    const int row = lot.size(), col = lot[0].size();
    int min_dist = INT_MAX;
    vector<vector<int>> dist(row, vector<int>(col, INT_MAX));
    function<void(int, int, int)> dfs = [&](int i, int j, int cur_dist) {
        if (i < 0 || j < 0 || i >= row || j >= col) return;
        if (lot[i][j] == 0) return;
        dist[i][j] = min(dist[i][j], cur_dist + 1);
        cur_dist = dist[i][j];
        if (lot[i][j] == 9) {
            min_dist = min(min_dist, cur_dist);
            return;
        }
        lot[i][j] = 0;
        dfs(i - 1, j, cur_dist);
        dfs(i, j - 1, cur_dist);
        dfs(i + 1, j, cur_dist);
        dfs(i, j + 1, cur_dist);
        lot[i][j] = 1;
    };
    dfs(0, 0, -1);
    return min_dist == INT_MAX ? -1 : min_dist;
}
```
 