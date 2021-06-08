https://binarysearch.com/problems/Triple-Inversion

Given a list of integers nums, return the number of pairs i < j such that nums\[i\] > nums\[j\] \* 3.  
  
Constraints： n ≤ 100,000 where n is the length of nums  
Example 1  
Input：  
nums = \[7, 1, 2\]  
Output：  
2  
Explanation：  
We have the pairs (7, 1) and (7, 2)

这道题并没有限定数组 nums 是有序的，但是我们可以构造一个有序序列 d，进而在 d 上做二分。代码：

```python
class Solution:
    def solve(self, A):
        d = []
        ans = 0

        for a in A:
            i = bisect.bisect_right(d, a * 3)
            ans += len(d) - i
            bisect.insort(d, a)
        return ans
```