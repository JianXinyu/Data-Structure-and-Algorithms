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

### 198. house robber

dp[n]取决于dp[n-2]和dp[n-1]