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

# 0-1 Knapsack Problem 0-1背包问题
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

# 1-D
[[53. Maximum Subarray]]
[[121. Best Time to Buy and Sell Stock]]
[[42. Trapping Rain Water]] 预先求最大值

# Unique Paths 

I: O(mn), S = O(mn), T = O(mn)

[[62. Unique Paths]]: memoization recursion:

 [[63. Unique Paths II]]

### 120.Triangle

这题直接自己想，time 24min, submit once，结果：

Runtime: 8 ms, faster than 97.43% of C++ online submissions for Triangle.
Memory Usage: 8.5 MB, less than 80.36% of C++ online submissions for Triangle.

哈哈哈，我好厉害。

思路：求出到达每一行中的每个元素的minimum path sum

​	f[j] := minmum path sum to jth entry at current row

​	f[j] = min(f[j], f[j-1]) + triangle\[i][j]

S: O(n), T: O(n^2)

Improve:

​	直接使用给的数组t, i.e. triangle, 这样还能避免新建数组f必须用倒序的问题。

​	t\[i][j] := minTotalOf(i,j)

​	t\[i][j] += min(t\[i - 1][j], t\[i - 1][j - 1])

另外一个S: O(n)的解法是使用滚动数组

### 174.

### 931.



### 1210.Minimum Moves to Reach Target with Rotations 

太难，没做。



# Maximal Rectangle 

----- I: O(mn), S = O(mn), T = O(mn)

[[221. Maximal Square]]

[[85. Maximal Rectangle]]





### 304. Range Sum Query 2D - Immutable

### 1277. Count Square Submatrices with All Ones

dp\[i][j] := edge of largest square with right bottom corner at (i, j)

dp的定义同221，但这里有一个trick，dp显示size 为 4 的square，则以这个格子为右下角的square就有4个。所以ans可直接+=dp

另外注意先将matrix的值赋给dp，边界条件时，第一行和第一列的无需操作。

# House Robber
T:O(3n)
S:O(3n) 

- [[309. Best Time to Buy and Sell Stock with Cooldown]]<font color='red'> 好题！</font> 多种状态的DP

### 198. house robber

dp[n]取决于dp[n-2]和dp[n-1]

### 213. House Robber II

circle与line的区别仅在第一个和最后一个相邻，二者只能取其一。因此可以分别计算以第一个为起点、倒数第二个为重点和以第二个为起点、最后一个为终点的最大值，再比较即可。



### 740. Delete and Earn

Reduce the problem to [House Robber Problem](http://zxi.mytechroad.com/blog/dynamic-programming/leetcode-198-house-robber/)

Key observations: If we take nums[i]

1. We can safely take all of its copies.
2. We can’t take any of copies of nums[i – 1] and nums[i + 1]

This problem is reduced to 198 House Robber.

Houses[i] has all the copies of num whose value is i.

[3 4 2] -> [0 2 3 4], rob([0 **2** 3 **4**]) = 6       

[2, 2, 3, 3, 3, 4] -> [0 2*2 3*3 4], rob([0 2*2 **3\*3** 4]) = 9

Time complexity: O(n+r) reduction + O(r) solving rob = O(n + r)

Space complexity: O(r)

r = max(nums) – min(nums) + 1

如何转为house robber problem？先求出旧数组的范围，根据范围确定新数组的长度，再迭代旧数组，给新数组赋值。注意由于同样的整数可以重复计算，所以累加即可，这其实降低了难度。

### 790. Domino and Tromino Tiling 

<font color='red'>这题不会做，答案看明白了。</font> 感觉不应该归类于house robber

### 801. Minimum Swaps To Make Sequences Increasing



# Perfect Squares

1. DP解法

dp[n]定义为n的perfect squares number，那么dp[i]可以通过遍历所有比i小的平方数来确定：

````C++
for(int j = 1; j*j <= i; j++)
	dp[i] = min(dp[i], dp[i-j*j]+1);
````

S: O(n) T: O(n*sqrt(n))

2. 四平方和定理 Lagrange's four-square theorem / Bachet's conjecture

- *Every natural number can be represented as the sum of four integer squares.*

$$p = a_1^2 + a_2^2 + a_3^2 + a_4^2$$

- *a positive integer can be expressed as the sum of **three** squares if and only if **it is not** of the form* $4^k(8m+7)$ *for integers* `k` *and* `m`

```pseudocode
1. divid the number by 4 until can't 
2. calculate the mod, if mod == 7, return 4
3. now the number is small, we can iterate i
	1. if i^2 = n^2, return 1
	2. if i^2 + j^2 = n^2,return 2
	3. else, return 3
```

S: O(1), T: $O(log_4n+sqrt(log_4n))$

# Word Break

139	140	818 均未仔细研究



# Longest Increasing Subsequence
[[300. Longest Increasing Subsequence]]
[[673. Number of Longest Increasing Subsequence]]