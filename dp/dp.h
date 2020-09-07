#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using std::vector;
using std::string;
using std::queue;
using std::unordered_map;
using std::pair;
using std::unordered_set;
using std::max;
using std::min;
using std::sort;
using std::reverse;


/*
 * Patterns
 * https://leetcode.com/discuss/general-discussion/458695/dynamic-programming-patterns

Minimum (Maximum) Path to Reach a Target
Distinct Ways
Merging Intervals
DP on Strings
Decision Making

 */

int maxSubArray(vector<int>& nums);
int maxProfit(vector<int>& prices);
class uniquePath
{
public:
    int uniquePaths(int m, int n);

private:
    unordered_map<int, unordered_map<int, int>> f_;
};
