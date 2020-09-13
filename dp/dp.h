#pragma once

#include <vector>
#include <unordered_map>
#include <cmath>
#include <bits/stdc++.h>

using std::vector;
using std::unordered_map;
using std::max;
using std::min;

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

class uniquePath2
{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);

private:
    vector<vector<int>> f_;
    int paths(int m, int n, vector<vector<int>> & o);
};

class uniquePath3
{
public:
    int minPathSum(vector<vector<int>>& grid);
private:
    vector<vector<int>> f_;
    int pathSum(int m, int n, vector<vector<int>> &g);
};

int minimumTotal(vector<vector<int>>& triangle);

int calculateMinimumHP(vector<vector<int>>& dungeon);