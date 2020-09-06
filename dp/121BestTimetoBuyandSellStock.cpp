#include "dp.h"

//! Solution 1
//! Time complexity: O(n)
//int maxProfit(vector<int>& prices)
//{
//    int n = prices.size();
//    if(n < 2) return 0;
//    // Space Complexity: O(n)
////    vector<int> max_profit(n);
////    vector<int> min_price(n);
////    max_profit[0] = 0;
////    min_price[0] = prices[0];
////    for(int i = 1; i < n; i++)
////    {
////        min_price[i] = min(min_price[i-1], prices[i]);
////        max_profit[i] = max(max_profit[i-1], prices[i] - min_price[i]);
////    }
////    return max_profit[n-1];
//
//    // Space Complexity: O(1)
//    int max_profit = 0;
//    int lowest_price = prices[0];
//    for(int i = 1; i < n; i++)
//    {
//        if(prices[i] < lowest_price)
//            lowest_price = prices[i];
//        if(prices[i] - lowest_price > max_profit)
//            max_profit = prices[i] - lowest_price;
//    }
//
//    return max_profit;
//}

//! Solution 2
//! Reduce to the 53Maximum subarray case
// Time complexity: O(n)
// S: O(n)
int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    if(n < 2) return 0;

    // calculate difference between two days
    vector<int> diff(n-1);
    for(int i = 1; i < n; i++)
    {
        diff[i-1] = prices[i] - prices[i-1];
    }

    // solve maximum subarray problem
    int sum = 0;
    int ans = 0;
    for(int &entry : diff)
    {
        sum = max(sum + entry, entry);
        if(sum > ans)
            ans = sum;
    }
    return ans;
}