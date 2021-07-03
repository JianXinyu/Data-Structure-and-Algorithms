背包问题是一个NP-complete的组合优化问题，Search的方法需要$O(2^N)$时间才能获得最优解。而使用动态规划，我们可以在**伪多项式（pseudo-polynomial time）**时间内获得最优解。

# 0-1 Knapsack Problem 0-1背包问题
Given N items, w\[i\] is the weight of the i-th item and v\[i\] is value of the i-th item. Given a knapsack with capacity W. Maximize the total value. Each item can be use **0 or 1 time**.

```cpp
dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i])
```

https://zxi.mytechroad.com/blog/tag/knapsack/


# 完全背包问题
[[322. Coin Change]]