https://binarysearch.com/problems/Kth-Pair-Distance
# Brute Force

```cpp
int solve(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    const int n = nums.size();
    vector<int> ans;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            ans.push_back(abs(nums[j]-nums[i]));
        }
    }
    sort(ans.begin(), ans.end());
    return ans[k];
}
```
TLE

# Binary Search
## 思路
能力检测二分
双指针

典型的计数二分：找到一个数 x，使得小于等于 x 的数恰好有 k 个。对本题来讲，就是找到一个绝对值差 diff，使得绝对值差小于等于 diff 的恰好有 k 个。

1. 解空间 $[0, max(nums)-min(nums)]$

2. 计算有多少对的差值小于等于diff
	1. 对排序好的数组双指针遍历
	2. 要注意int型的ans很容易越界

## Code
```cpp
int count_not_greater(vector<int>& nums, int diff){
    int i = 0, ans = 0;
    for(int j = 1; j < nums.size(); ++j){
        while((nums[j] - nums[i]) > diff)
            i++;
        if (0LL + j - i + ans >= INT_MAX) return INT_MAX;
        ans += (j - i);
    }
    return ans;
}

unsigned int count_not_greater(vector<int>& nums, int diff){
    int i = 0;
    unsigned int ans = 0;
    for(int j = 1; j < nums.size(); ++j){
        while((nums[j] - nums[i]) > diff)
            i++;
        ans += (j - i);
    }
    return ans;
}

int solve(vector<int>& nums, int k){
    sort(nums.begin(), nums.end());
    int l = 0, r = (nums.back() - nums[0]);
    while(l <= r){
        int mid = (l+r)/2; //l + ((r - l) >> 1);
        if(count_not_greater(nums, mid) > k)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}
```

T: $O(nlogn)$
S: $O(1)$