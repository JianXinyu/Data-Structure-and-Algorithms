动态规划的典型例子

Unsovled:

```
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int result = 0;
        cost.push_back(0);
        int n = cost.size() - 1;
        while(n > 1)
        {
            result += cost[n];
            if(cost[n-1] >= cost[n-2])
                n = n - 2;
            else
                n = n - 1;
            
        }
        result += cost[n];
        return result;
    }
};
```

Correct solution: 

dp有两种定义

- min cost before leaving n-th step: 
  - $dp(n) = min(dp(n-1), dp(n-2)) + cost(n)$
  - $ans = min(dp(n-1), dp(n-2))$

- min cost to climb to n-th step:
  - $dp(n) = min(dp(n-1)+cost(n-1), dp(n-2)+cost(n-2))$
  - $ans = dp(n)$

```C++
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int dp1 = 0;
        int dp2 = 0;
        for(int i = 2; i <= cost.size(); i++)
        {
            int dp = min(dp1 + cost[i-1], dp2 + cost[i-2]);
            dp2 = dp1;
            dp1 = dp;
        }
        
        return dp1;
    }
};
```

