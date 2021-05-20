#include "dp.h"

//! Time complexity: O(n)

int maxSubArray(vector<int>& nums) {
    vector<int> f(nums.size());
    // Space complexity: O(n)
    // nums: [-2,1,-3,4,-1,2,1,-5,4]
    // f   : [-2,1,-2,4, 3,5,6, 1,5]
//    f[0] = nums[0];
//    for(int i = 1; i < nums.size(); i++)
//    {
//        f[i] = max(f[i-1] + nums[i], nums[i]);
//    }
//    return *max_element(f.begin(), f.end());

    // Space complexity: O(1)
    int ans = nums[0];
    int sum = nums[0];
    for(int i = 1; i < nums.size(); i++)
    {
        sum = max(sum + nums[i], nums[i]);
        if(sum > ans)
            ans = sum;
    }

    return ans;
}

