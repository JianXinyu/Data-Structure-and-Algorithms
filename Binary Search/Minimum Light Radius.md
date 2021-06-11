https://binarysearch.com/problems/Minimum-Light-Radius
```
You are given a list of integers nums representing coordinates of houses on a 1-dimensional line. You have 3 street lights that you can put anywhere on the coordinate line and a light at coordinate x lights up houses in \[x - r, x + r\], inclusive. Return the smallest r required such that we can place the 3 lights and all the houses are lit up.  
  
Constraints  
  
n ≤ 100,000 where n is the length of nums  
Example 1  
Input  
nums = \[3, 4, 5, 6\]  
Output  
0.5  
Explanation  
If we place the lamps on 3.5, 4.5 and 5.5 then with r = 0.5 we can light up all 4 houses.
```

## 思路
-   排序
-   二分法: 能力检测 + 最左二分

1. 确定解空间: $[0, max(nums)-min(nums)]$

2. 二分查找符合条件的r:
	1. 从解空间中选取一个值开始迭代，比如中值 -> 有序序列进行枚举 -> 二分的典型应用
	2. 检查该值是否可以覆盖所有的房子: 显然，第一个灯应该放在$nums[0]+r$处，灯覆盖的范围为$2r$。 第二个灯没必要放在$nums[0]+3r$处，而应该是: 先找到最近没被覆盖的房子，比如$nums[i]$，放在$nums[i]+r$处。以此类推。
3. 如上分析，用diameter比radius更好
4. 从中值开始迭代，如果不能覆盖，那么就右移左边界；如果能，就左移右边界
5. 因为返回值是double，所以迭代停止条件靠大小判断不好用了，可以固定迭代次数，确保收敛就行。
## Code
```cpp
#define LIGHTS 3

bool possible(float diameter, vector<int>& nums){
    auto start = nums.begin();
    float end = *start + diameter;
    for(int i = 0; i < LIGHTS; ++i){
        start = lower_bound(start, nums.end(), end);
        if(start == nums.end())
            return true;
        end = *start + diameter;
    }
    return false;
}

double solve(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    float l = 0, r = static_cast<float>(nums.back() - nums[0]);
    for(int i = 1; i < 40; ++i){
        float mid = (l+r) / 2;
        if(possible(mid, nums))
            r = mid;
        else
            l = mid;
    }
    return l / 2.0;
}
```

**Complexity Analysis:**
T: sort $O(nlogn)$, possible用到了`lower_bound()`，其实质为二分查找，因此复杂度是$O(logn)$，迭代i次，总复杂度为$O(nlogn + ilogn)$
S: O(1)

[[475. Heaters]]