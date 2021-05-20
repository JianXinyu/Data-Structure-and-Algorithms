题目分类：[Link](https://docs.google.com/spreadsheets/d/1yRCOJ8KysRVkq0O9IlDriT01tC6lzPapmFO4PCmDJQA/edit#gid=1674276502)

# 1-D

### 54.Maximum Subarray

​	calculate the max sum so far

​	f[i] := max sum to i-th entry

​	f[i] = max(f[i-1]+num[i], num[i])



### 121.Best time to buy and sell stock

![img](.\figures\121stock.png)

# Unique Paths 

I: O(mn), S = O(mn), T = O(mn)

### 62.Unqiue Paths

- memoization recursion:

  

### 63.Unique Paths 2

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

### 221.Maximal Square

![img](.\figures\221MaximalSquare1.png)

Brute force can be reduced to $O(n^3)$ if check() can be reduced to $O(1)$

We use the following DP method to pre-compute the every element's size

![img](A:\Programming\LeetCode\doc\figures\221MaximalSquare2.png)

![img](.\figures\221MaximalSquare3.png)

$O(n^2)$ solution:

dp\[i][j] = 以(i,j)为右下角的，最大的全1子矩阵。

![img](.\figures\221MaximalSquare4.png)

### 85.Maximal Rectangle

### ![image-20200920110134189](.\figures\85MaximalRectangle.png)

so now the question is how to calculate dp?

appearently, if martix\[i][j] == 0, dp\[i][j] = 0; else, dp\[i][j] = dp\[i][j-1] + 1

note, for horizontal case, the first column, dp\[i][0] = martix\[i][0]

### 304. Range Sum Query 2D - Immutable

### 1277. Count Square Submatrices with All Ones

dp\[i][j] := edge of largest square with right bottom corner at (i, j)

dp的定义同221，但这里有一个trick，dp显示size 为 4 的square，则以这个格子为右下角的square就有4个。所以ans可直接+=dp

另外注意先将matrix的值赋给dp，边界条件时，第一行和第一列的无需操作。

# House Robber

---- S:O(3n) T:O(3n)

### 198. house robber

dp[n]取决于dp[n-2]和dp[n-1]

### 213. House Robber II

circle与line的区别仅在第一个和最后一个相邻，二者只能取其一。因此可以分别计算以第一个为起点、倒数第二个为重点和以第二个为起点、最后一个为终点的最大值，再比较即可。

### 309. Best Time to Buy and Sell Stock with Cooldown

<font color='red'> 好题！</font>

**状态转移**：三种状态及以上需要考虑

先判断有几种状态，画出状态机

再用代码表示出状态转移

最后考虑边界条件

逻辑: 对于每个状态，考虑从上一时刻状态转移过来时，取相对的最大值。一直这样维护最大值，那么结果就是最终这几个状态的最大值。

因此dp[i]表示第i天后在这个状态下能获得的最大收益。

sold[i] 表示在第i天卖出股票后能够获得的最大利润。 

hold[i] 表示在第i天（或之前）买入股票后能够获得的最大利润。即第i天结束后手里持有股票。

为什么必须有一个rest状态？因为题目条件的限制。能去 hold 的只有 rest (不能由 sold 直接去 rest) ，所以至少必須休息一天後才能買。

![img](.\figures\309Best Time to Buy and Sell Stock with Cooldown.png)

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

## 300.Longest Increasing Subsequence

Solution 1:

​	T: O(n^2)

​     我们可以这样简化问题，找到前n-1位的LIS，那么第n位的LIS该怎么计算?

​		遍历前n-1位，

- 如果nums[n] > nums[i]， 那么就有可能是前i+1位的LIS+1；但是遇到这样的情况怎么办？[8, 9, 3, 4] 显然nums[3] > nums[2]， 那么前3位的LIS+1不就等于3了吗？所以DP不能仅仅定义为前i+1位的LIS，如图二，LIS必需包括最后一位。我们把DP数组初始化为1，由于以上判断条件的存在，DP[2]=1而不是2。所以这个地方应该是一个又复杂又自然简单的点，不需要额外处理，相反如果多考虑了反而会错。

- 如果<=，则肯定不用计算了，本来都有更大的了，不用再和一个较小的比了。

  

![img](.\figures\300Longest Increasing Subsequence.png)

![img](.\figures\300Longest Increasing Subsequence2.png)