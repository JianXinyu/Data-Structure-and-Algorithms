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
//    return dp.back();

    // S: O(1)
    int dp1 = 0, dp2 = 0;
    for(int i = 0; i < n; ++i)
    {
        int dp = max(dp2 + nums[i], dp1);
        dp2 = dp1;
        dp1 = dp;
    }
    return dp;
}

//---------------------------213. House Robber II-----------------------//
//! DP
// T: O(n)
int rob2(vector<int>& nums) {
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];

    // S: O(n)
//    vector<int> sum(n, 0);
//    for(int i = 1; i < n; i++)
//    {
//        sum[i] = max((i > 1 ? sum[i-2] : 0) + nums[i],
//                     (sum[i-1] : 0));
//    }
//
//    for(int i = 0; i < n - 1; i++)
//    {
//        sum[i] = max((i > 1 ? sum[i-2] : 0) + nums[i],
//                     (i > 0 ? sum[i-1] : 0));
//    }
//
//    return max(sum.back(), sum[n-2]);

    // S: O(1)
    int dp1 = 0, dp2 = 0;
    int dpa = 0, dpb = 0;

    for(int i = 0; i < n - 1; i++)
    {
        dpa = max(dp2 + nums[i], dp1);
        dp2 = dp1;
        dp1 = dpa;
    }

    dp1 = 0, dp2 = 0;
    for(int i = 1; i < n; i++)
    {
        dpb = max(dp2 + nums[i], dp1);
        dp2 = dp1;
        dp1 = dpb;
    }
    return max(dpa, dpb);
}

//---------------309. Best Time to Buy and Sell Stock with Cooldown--------------//
//! state transition
// T: O(n)
int maxProfit(vector<int>& prices)
{
    // S: O(n)
//    int n = prices.size();
//    vector<int> rest(n+1, 0), sold(n+1, 0), hold(n+1, 0);
//
//    hold[0] = INT_MIN;
//
//    for(int i = 1; i < n+1; i++)
//    {
//        hold[i] = max(hold[i-1], rest[i-1] - prices[i-1]);
//        rest[i] = max(rest[i-1], sold[i-1]);
//        sold[i] = hold[i-1] + prices[i-1];
//    }
//
//    return max(rest.back(), sold.back());

    // S: O(1)
    int hold = INT_MIN, sold = 0, rest = 0;
    for( const auto price : prices)
    {
        int prev_hold = hold;
        hold = max(hold, rest - price);
        rest = max(rest, sold);
        sold = prev_hold + price;
    }

    return max(rest, sold);
}