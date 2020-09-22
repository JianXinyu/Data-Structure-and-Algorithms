//
// Created by jianx on 9/21/2020.
//
#include "dp.h"

//------------------198 House Robber----------------------//
//! Recursion + memorization
// S: O(n), T: O(n)
int Robber::rob(vector<int> &nums) {
    const int n = nums.size();
    m_ = vector<int>(n, -1);
    return rob(nums, n - 1);
}

int Robber::rob(const vector<int> &nums, int i) {
    if(i < 0)
        return 0;
    if(m_[i] >= 0)
        return m_[i];
    return max(rob(nums, i-2) + nums[i], rob(nums, i-1));
}

//! DP
// dp[i]: maximal money after leaving house[i]
// T: O(n)
int rob(vector<int>& nums)
{
    if (nums.empty()) return 0;

    const int n = nums.size();
    // S: O(n)
//    vector<int> dp(n, 0);
//    for(int i = 0; i < n; ++i)
//        dp[i] = max((i > 1 ? dp[i-2] : 0) + nums[i],
//                    (i > 0 ? dp[i-1] : 0));

    // S: O(1)
    int dp1 = 0, dp2 = 0;
    for(int i = 0; i < n; ++i)
    {
        int dp = max(dp2 + nums[i], dp1);
        dp2 = dp1;
        dp1 = dp;
    }
    return dp1;
}

