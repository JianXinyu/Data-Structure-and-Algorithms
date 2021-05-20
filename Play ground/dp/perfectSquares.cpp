//
// Created by jianx on 10/2/2020.
//

#include "dp.h"

//int numSquares(int n)
//{
//  vector<int> dp(n+1, INT_MAX >> 1);
//  dp[0] = 0;
//  for(int i = 1; i <= n; i++)
//    for(int j = 1; j * j <= i; j++)
//      dp[i] = min(dp[i], dp[i - j*j]+1);
//  return dp[n];
//}

int numSquares(int n) {
  while(n % 4 == 0) n/= 4;
  if(n % 8 == 7) return 4;
  //从0开始是因为n此时可能表示为一个数的平方
  for(int a = 0; a * a <= n; a++)
  {
    int b = floor(sqrt(n - a*a));
    if((a*a + b*b) == n)
      return (a != 0) + (b != 0); // check if a or b is positive integer
  }
  return 3;
}