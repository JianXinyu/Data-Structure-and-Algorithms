#pragma once

#include <vector>
#include <unordered_map>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>

using std::vector;
using std::unordered_map;
using std::string;
using std::unordered_set;

using std::max;
using std::min;
using std::minmax_element;

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

int minFallingPathSum(vector<vector<int>>& A);

//! Maximal Rectangle
int maximalSquare(vector<vector<char>>& matrix);

class NumMatrix {
public:
    NumMatrix(const vector<vector<int>>& matrix);

    int sumRegion(int row1, int col1, int row2, int col2);
private:
    vector<vector<int>> sums_;
};

int countSquares(vector<vector<int>>& matrix);

int maximalRectangle(vector<vector<char> > &matrix);

//! House Robber
//------------------198 House Robber----------------------//
// recursion
class Robber {
public:
    int rob(vector<int>& nums);
private:
    int rob(const vector<int>& num, int i);
    vector<int> m_;
};
// dp
int rob(vector<int>& nums);

//---------------------------213. House Robber II-----------------------//
int rob2(vector<int>& nums); // dp

//------------309. Best Time to Buy and Sell Stock with Cooldown------------------//
int maxProfit(vector<int>& prices);

//--------------740. Delete and Earn------------------//
int deleteAndEarn(vector<int>& nums);

//--------------790. Domino and Tromino Tilling-----------------//
int numTiling(int N);

//------------801. Minimum Swaps To Make Sequences Increasing-------------//
int minSwap(vector<int>& A, vector<int>& B);

//! Perfect Squares
//-------------279. Perfect Squares-------------//
int numSquares(int n);

//! Word Break
//------------ 139. Word Break-----------------//
class wordBreak
{
public:
  bool wordbreak(string s, vector<string>& wordDict);
private:
  unordered_map<string, bool> mem_;
  bool wordbreak(const string& s);
};
//------------140. Word Break II------------//
class wordBreak2 {
public:
  vector<string> wordBreak(string s, vector<string>& wordDict);
private:
  vector<string> append(const vector<string>& prefixes, const string& word);
  const vector<string>& wordBreak(string s, unordered_set<string>& dict);
  unordered_map<string, vector<string>> mem_;
};

//! Longest Increasing Subsequence
//-------------300-------------------//
int lengthOfLIS(vector<int>& nums);

//----673 Number of Longest Increasing Subsequence-----//
int findNumberOfLIS(vector<int>& nums);