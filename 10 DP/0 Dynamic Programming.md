# NP 问题
**P问题**是可以在多项式的时间复杂度($O(n^k),k$是一个常数)内**解决**的问题。

**NP问题**（Nondeterministic Polynomial time Problem）是可以在多项式的时间复杂度内**验证**的问题。
- 给定一个排序过的序列，判断是否有序。只需遍历一遍，线性时间复杂度。
- 给定一个大整数的因数分解，判断是否正确。只需求分解式的和即可，常数时间复杂度。但给定大整数做因式分解会很难。
---
- 显然**所有P问题都是NP问题**，既然我们可以$O(n^k)$内找到解，那么必然我们也可以在$O(n^k)$验证解是否正确。
- 但是反过来是否成立呢，在$O(n^k)$内可以验证解的问题，是否也可以通过某种算法可以在$O(n^k)$内被解决呢？
- 也就是说，**对于一个NP问题，究竟是我们暂时还没有想到算法，还是解法一开始就不存在呢？** $NP==P?$
---
 **NPC问题**：为了解决$NP==P?$，我们给问题做规约(Reducibility)。比如，解二元一次方程要比解一元一次方程难。如果能找到二元一次方程的解，必然可以用来解一元一次方程，只需要令第二个未知数等于0即可。同理，可以**将NP问题的难度增大，增大到极限成为一个终极问题**，那么就可以解出所有的NP问题。这个终极问题叫做NP Complete问题。

**NP-Hard问题**：所有NP问题可以经过转化得到它，但是它**本身并不是NP问题**，即无法在$O(n^k)$内判断它的解是否正确。

# 状压 DP 
- 状态：一个整数可以用它的二进制表示，比如int一般是32 bits，可以表示一个32个元素的集合，每一个bit是0还是1代表了对应集合元素的两种状态，那么每一个int**整数就代表了一个集合的状态**。并且整数和集合状态是一一对应的。
- 压缩：**将一个集合压缩成一个整数**，减少空间消耗，并且位运算要快得多。
- 状态转移：某一集合元素从无变为有，对应集合代表整数的bit（第$i$位）从0变为1，集合加上转移带来的变化=整数加上$2^i$。同理，集合元素从有变为无。即，**用整数的加减计算来代表集合状态的变化**。


https://zhuanlan.zhihu.com/p/131585177
- [[464. Can I Win]]
- [[1879. Minimum XOR Sum of Two Arrays]]
- [[2172. Maximum AND Sum of Array]]

背包问题是一个NP-complete的组合优化问题，Search的方法需要$O(2^N)$时间才能获得最优解。而使用动态规划，我们可以在**伪多项式（pseudo-polynomial time）**时间内获得最优解。

# 0-1 Knapsack Problem 
0-1背包问题
Given N items, w\[i\] is the weight of the i-th item and v\[i\] is value of the i-th item. Given a knapsack with capacity W. Maximize the total value. Each item can be use **0 or 1 time**.

```cpp
dp[i][j] = max(dp[i-1][j], dp[i][j-w[i]] + v[i])
```

https://zxi.mytechroad.com/blog/tag/knapsack/


# 完全背包问题
[[322. Coin Change]]


- LCS（最长公众子序列）- 典型的二维动态规划问题
	- [[1143. Longest Common Subsequence]]



数位 dp

[[837. New 21 Game]] dp + sliding window


题目分类：[Link](https://docs.google.com/spreadsheets/d/1yRCOJ8KysRVkq0O9IlDriT01tC6lzPapmFO4PCmDJQA/edit#gid=1674276502)

# 做题记录
- [[790. Domino and Tromino Tiling]] dp的理解有点trick
- [[5. Longest Palindromic Substring]]
## 1D
[[53. Maximum Subarray]]
[[121. Best Time to Buy and Sell Stock]]
[[42. Trapping Rain Water]] 预先求最大值

## 2D Path
I: O(mn), S = O(mn), T = O(mn)

Medium
- [[62. Unique Paths]]: memoization recursion:
- [[63. Unique Paths II]]
- [[64. Minimum Path Sum]]
- [[118. Pascal's Triangle]]
- [[120. Triangle]]
- [[931. Minimum Falling Path Sum]]

Hard
- [[174. Dungeon Game]] 逆向思维
- [[1210. Minimum Moves to Reach Target with Rotations]]

## Maximal Rectangle 
I: O(mn), S = O(mn), T = O(mn)

Medium
- [[85. Maximal Rectangle]]
- [[221. Maximal Square]]
- [[304. Range Sum Query 2D - Immutable]]
- [[1277. Count Square Submatrices with All Ones]]

## House Robber
T:O(tn)
S:O(tn) 
t是状态数目

- [[198. House Robber]] dp[n]取决于dp[n-2]和dp[n-1]
- [[213. House Robber II]] circle与line的区别
- [[740. Delete and Earn]] house robber的变种

- [[801. Minimum Swaps To Make Sequences Increasing]] 两种状态的DP
- [[309. Best Time to Buy and Sell Stock with Cooldown]]<font color='red'> 好题！</font> 三种状态的DP


## Perfect Squares
- [[Note/10 DP/279. Perfect Squares]]


## Word Break
- [[139. Work Break]]
- [[140. Word Break II]]

## Longest Increasing Subsequence
[[300. Longest Increasing Subsequence]]
[[673. Number of Longest Increasing Subsequence]]


未分类：
- [[818. Race Car]]