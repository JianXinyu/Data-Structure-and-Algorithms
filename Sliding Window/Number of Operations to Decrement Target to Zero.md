https://binarysearch.com/problems/Number-of-Operations-to-Decrement-Target-to-Zero
题目说得不清楚，应该还有以下两个条件:
- $sum(nums) <= 2^{31}-1$
- 是恰好等于0，负数也不行
## 思路
滑动窗口
由于是从两边减，中间保证连续，不妨把中间的和设为target，也就是target = sum-target。
这样就可以从头遍历数组，累加得到ts
- 如果ts小于target，就继续累加
- 如果ts大于target，就从左端开始缩小
- 如果ts等于target，就记录其长度
## Code
```cpp
int solve(vector<int>& nums, int target) {
    const int n = nums.size();
    if(target == 0)
        return 0;
    if(n == 0 || (n == 1 && nums[0] < target))
        return -1;

    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    if(sum < target)
        return -1;

    target = sum - target;
    int ans = n+1, ts = 0, j = 0;
    
    for(int i = 0; i < n; ++i){
        ts += nums[i];
        while(i >= j && ts > target){
            ts -= nums[j++];
        }
        if(ts == target)
            ans = min(ans, n-(i-j+1));
    }
    return ans == n+1 ? -1 : ans;
}
```

T: average: O(n) worst: O(n^2) 最坏的情况是nums右端是特别大的数，比如$nums=[1,1,1,1,100], target = 100$
S: O(1)