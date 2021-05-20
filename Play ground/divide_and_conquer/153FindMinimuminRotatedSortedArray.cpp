#include "divide_and_conquer.h"

// naive solution, it actually performs better
//int findMin(vector<int>& nums) {
//
//    auto last = nums.begin();
//    int ret = *last;
//    for (auto i = nums.begin() + 1; i != nums.end(); ++i){
//        if (*last > *i){
//            ret = *i;
//            break;
//        }
//        else
//            last = i;
//    }
//    return ret;
//}

int findMin(const vector<int>& num, int l, int r)
{
    // Only 1 or 2 elements
    if (l+1 >= r) return min(num[l], num[r]);

    // Sorted
    if (num[l] < num[r]) return num[l];

    int mid = l + (r-l)/2;

    return min(findMin(num, l, mid-1),
               findMin(num, mid, r));
}

int findMin(vector<int>& nums) {
    return findMin(nums, 0, nums.size()-1);
}
