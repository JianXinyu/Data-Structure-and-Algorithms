//
// Created by jianx on 10/14/2020.
//
#include "dp.h"

int lengthOfLIS(vector<int>& nums) {
  if(nums.empty()) return 0;

  int n = nums.size();

  vector<int> f(n, 1);

  for(int i = 1; i < n; i++)
    for(int j = 0; j < i; j++)
      if(nums[i] > nums[j])
        f[i] = max(f[i], f[j]+1);

  return *max_element(f.begin(), f.end());
}

int findNumberOfLIS(vector<int>& nums)
{
  if(nums.empty()) return 0;

  int n = nums.size();

  vector<int> f(n,1);
  vector<int> number(n, 0);

  for(int i = 1; i < n; i++)
  {
    for(int j = 0; j < i; j++)
      if(nums[i] > nums[j])
      {
        f[i] = max(f[i], f[j]+1);
      }
    for(int j = 0; j < i; j++)
      if( ( nums[i] > nums[j] & f[i] == f[j]+1 )
              || ( nums[i] == nums[j] & f[i] == f[j] ) )
        number[i]++;
  }

  int idx = std::distance(f.begin(), max_element(f.begin(), f.end()));
  return number[idx];
}