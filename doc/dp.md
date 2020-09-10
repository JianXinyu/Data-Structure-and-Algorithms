# Dynamic Programming

题目分类：[Link](https://docs.google.com/spreadsheets/d/1yRCOJ8KysRVkq0O9IlDriT01tC6lzPapmFO4PCmDJQA/edit#gid=1674276502)

## 1-D

54.Maximum Subarray

​	calculate the max sum so far

​	f[i] := max sum to i-th entry

​	f[i] = max(f[i-1]+num[i], num[i])



121.Best time to buy and sell stock

![img](.\figures\121stock.png)

## I: O(mn), S = O(mn), T = O(mn)

### Unique Paths

62.Unqiue Paths

- memoization recursion:

  

63.Unique Paths 2

#### 120.Triangle

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