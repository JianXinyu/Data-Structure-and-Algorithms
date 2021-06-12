## 思路
- 能力检测+二分
- dfs，记忆化递归

## Code
```cpp
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        const int n = grid.size();
        int l = 2*n-2, r = n*n-1;
        while(l <= r){
            int mid = (l+r) / 2;
            if(possible(grid, mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        return l;
    }

    bool possible(vector<vector<int>>& grid, int max){
        vector<vector<int>> seen(grid.size(), vector<int>(grid.size(),0));
        function<bool(int, int)> dfs = [&](int i, int j){
            if(i < 0 || j < 0 || i >= grid.size() || j >= grid.size())
                return false;
            if(grid[i][j] > max)
                return false;
            if(i == grid.size()-1 && j == grid.size()-1)
                return true;
            if(seen[i][j] != 0)
                return false;
            seen[i][j] = 1;
            return (dfs(i+1, j) || dfs(i, j+1) || dfs(i-1, j) || dfs(i, j-1));
        };
        return dfs(0,0);
    }
};
```
**Complexity Analysis:**
T: $O(n^2logn)$ dfs是$O(n^2)$
S: $O(n^2)$ seen二维数组