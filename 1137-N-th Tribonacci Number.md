DP的典型例子

Time 10min, submit once

Runtime: 0 ms, faster than 100.00% of C++ online submissions for N-th Tribonacci Number.

Memory Usage: 5.9 MB, less than 89.88% of C++ online submissions for N-th Tribonacci Number.

```c++
class Solution {
public:
    int tribonacci(int n) {
        int dp3 = 0;
        int dp2 = 1;
        int dp1 = 1;
        if(n == 0) return dp3;
        for(int i = 3; i <= n; i++)
        {
            int dp = dp3 + dp2 + dp1;
            dp3 = dp2;
            dp2 = dp1;
            dp1 = dp;
        }
        return dp1;
    }
};
```

