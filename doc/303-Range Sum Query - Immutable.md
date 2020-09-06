Time: 15mins, submit once.

Brutal force, very low efficient。注意题目中的“There are many calls to sumRange function”，暗示sumRange的时间复杂度越低越好，即便NumArray的时间复杂度高一些。

Runtime: 276 ms, faster than 12.28% of C++ online submissions for Range Sum Query - Immutable.

Memory Usage: 17 MB, less than 99.84% of C++ online submissions for Range Sum Query - Immutable.

```C++
class NumArray {
public:
    NumArray(vector<int>& nums) {
        nums_ = move(nums);
    }
    
    int sumRange(int i, int j) {
        sum_ = 0;
        while(i < j)
        {
            sum_ += nums_[i] + nums_[j];
            i++;
            j--;
        }
        if(i==j)
            sum_ += nums_[i];
        return sum_;
    }
private:
    vector<int> nums_;
    int sum_ = 0;
};

```

改进版：

先计算出$[0,i]$的所有和，需要时再用两个相应的和相减即可。

这样仅在初始化时计算sums_需要$O(n)$时间，后续只要$O(1)$。

空间复杂度$O(n)$

Runtime: 48 ms, faster than 71.68% of C++ online submissions for Range Sum Query - Immutable.

Memory Usage: 17.2 MB, less than 56.19% of C++ online submissions for Range Sum Query - Immutable.

```C++
class NumArray {
public:
    NumArray(vector<int>& nums) {
        int sum = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            sums_.push_back(sum);
        }
    }
    
    int sumRange(int i, int j) {
        if(i == 0)
            return sums_[j];
        else
            return sums_[j] - sums_[i-1];
    }
private:
    vector<int> sums_;
};
```

