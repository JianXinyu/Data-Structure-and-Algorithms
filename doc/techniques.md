## Sliding window

A **sliding window** is an abstract concept commonly used in array/string problems. A window is a range of elements in the array/string which usually defined by the start and end indices, i.e. $[i, j)$(left-closed, right-open). A sliding window is a window "slides" its two boundaries to the certain direction. For example, if we slide $[i, j)$ to the right by 1 element, then it becomes $[i+1, j+1)$ (left-closed, right-open).



## Dynamic Programming (DP)



# Two Pointers

16. 3Sum Closest

    best conceivable runtime (BCR) $O(n^2)$

```c++
    int threeSumClosest(vector<int>& nums, int target) {
        int diff = INT_MAX;
        int len = nums.size();
        sort(nums.begin(), nums.end());
        for( int i = 0; i < len && diff != 0; ++i)
        {
            int lo = i + 1, hi = len - 1;
            while( lo < hi)
            {
                int sum = nums[i] + nums[lo] + nums[hi];
                if(abs(target - sum) < abs(diff))
                    diff = target - sum;
                if(sum < target)
                    ++lo;
                else
                    --hi;
            }
        }
        
        return target - diff;
    }
```

