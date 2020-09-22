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
//

