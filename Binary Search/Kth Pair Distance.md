https://binarysearch.com/problems/Kth-Pair-Distance

求数组 nums 第 k 大的**任意两个数的差的绝对值**。

使用堆的时间复杂度会很高

解空间就是从 0 到数组 nums 中最大最小值的差，用区间表示就是 \[0, max(nums) - min(nums)\]。明确了解空间之后，我们就需要对解空间进行二分。对于这道题来说，可以选当前解空间的中间值 mid ，然后计算小于等于这个中间值的**任意两个数的差的绝对值**有几个，我们不妨令这个数字为 x。

-   如果 x 大于 k，那么解空间中大于等于 mid 的数都不可能是答案，可以将其舍弃。
-   如果 x 小于 k，那么解空间中小于等于 mid 的数都不可能是答案，可以将其舍弃。
-   如果 x 等于 k，那么 mid 就是答案。
    

基于此，我们可使用**计数二分**。
```python
class Solution:
    def solve(self, A, k):
        A.sort()
        def count_not_greater(diff):
            i = ans = 0
            for j in range(1, len(A)):
                while A[j] - A[i] > diff:
                    i += 1
                ans += j - i
            return ans
        l, r = 0, A[-1] - A[0]

        while l <= r:
            mid = (l + r) // 2
            if count_not_greater(mid) > k:
                r = mid - 1
            else:
                l = mid + 1
        return l
```