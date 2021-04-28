int maxProduct(vector<int>& nums) {
    int n = nums.size();
    if(n <= 1)
        return nums[0];
    int product = nums[0];
    int lastMax = nums[0];
    int lastMin = nums[0];
    for(int i = 1; i < n; ++i){
        int currentMax = max(nums[i], max(lastMax*nums[i], lastMin*nums[i]));
        int currentMin = min(nums[i], min(lastMax*nums[i], lastMin*nums[i]));
        product = max(product, currentMax);
        lastMax = currentMax;
        lastMin = currentMin;
    }
    return product;
}
// to calculate the max product of all elements
// int maxProduct(vector<int>& nums) {
//     if(nums.size() == 1)
//         return nums[0];
//     return maxmin(nums, nums.size()-1).first;
// }
// pair<int, int> maxmin(vector<int>&nums, int r){
//     int p = nums[r];
//     if(r<=1)
//         return {max(nums[0], nums[1]), min(nums[0], nums[1])};
//     pair<int, int> ret = maxmin(nums, r-1);
//     if(p < 0)
//         return {max(ret.first, ret.second*p), min(ret.second, ret.first*p)};
//     else if(p == 0)
//         return {max(0, ret.first), min(0, ret.second)};
//     return {max(p, ret.first*p), min(ret.second, ret.second*p)};
// }
