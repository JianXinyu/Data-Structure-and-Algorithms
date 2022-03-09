[[0 Binary Indexed Tree#1 求逆序对]]

离散化一个序列的前提是我们只关心这个序列里面元素的相对大小，而不关心绝对大小（即只关心元素在序列中的排名）；离散化的目的是让原来分布零散的值聚集到一起，减少空间浪费。那么如何获得元素排名呢，我们可以对原序列排序后去重，对于每一个 $a_i$ 通过二分查找的方式计算排名作为离散化之后的值。当然这里也可以不去重，不影响排名。

```cpp
inline int lowbit(int x) {return x & (-x);}
class FenwickTree {
    vector<int> tree_;
    int n_;
public:
    FenwickTree(int n) : n_(n) {
        tree_.resize(n+1);
    }
    void Update(int index, int val) {
        for (int i = index; i <= n_; i += lowbit(i)) {
            tree_[i] += val;
        }
    }
    int Query(int index) {
        int sum = 0;
        for (int i = index; i > 0; i -= lowbit(i)) {
            sum += tree_[i];
        }
        return sum;
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        const int n = nums.size();
        // coordinate compression
        vector<int> tmp = nums;
        sort(tmp.begin(), tmp.end());
        for (int& num: nums) {
            num = lower_bound(tmp.begin(), tmp.end(), num) - tmp.begin() + 1;
        }

        FenwickTree bit(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            bit.Update(nums[i], 1);
            ans += i + 1 - bit.Query(nums[i]);
        }
        return ans;
    }
};
```

- 时间复杂度：离散化的过程中使用了时间代价为 $O(n \log n)$ 的排序，单次二分的时间代价为 $O(\log n)$，一共有 n 次，总时间代价为 $O(n \log n)$；循环执行 n 次，每次进行 $O(logn)$ 的修改和 $O(\log n)$ 的查找，总时间代价为 $O(n \log n)$。故渐进时间复杂度为 $O(n \log n)$。
- 空间复杂度：树状数组需要使用长度为 n 的数组作为辅助空间，故渐进空间复杂度为 O(n)。
