//index:   0        1       .....   n-1-k       n-k     n-k+1           n-1
//nums: [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]

// 因为要求 T； O(log n), 那肯定要用二分查找或递归
// 选用中点划分
//Solution 1: recursion
// 左右边界有三种情况: ==, >, < 分类讨论即可
// 但要注意nums.size() == 2 的 corner case: (0+1)/2 == 0, 会陷入无穷递归
int searchsub(vector<int>& nums, int target, int l, int r){
    if(l > r) return -1;
    // corner case
    if(r - l == 1 && (nums[l] != target && nums[r] != target))
        return -1;

    if(nums[l] == target) return l;
    if(nums[r] == target) return r;

    if(nums[l] == nums[r]) return -1;
    if(nums[l] < nums[r]){
        if(target < nums[l]) return -1;
        if(target > nums[r]) return -1;
    }
    if(nums[l] > nums[r]){
        if(nums[l] > target && nums[r] < target)
            return -1;
    }

    return max(searchsub(nums, target, l, (l+r)/2 - 1),
               searchsub(nums, target, (l+r)/2, r));
}

int search(vector<int>& nums, int target) {
    if(nums.empty()) return -1;
    return searchsub(nums, target, 0, nums.size()-1);

}

// Solution 2: iterative search
// 中点划分后，必有一边是升序的
int search2(vector<int>& nums, int target) {
    int n = (int)nums.size();
    if (!n) {
        return -1;
    }
    if (n == 1) {
        return nums[0] == target ? 0 : -1;
    }
    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (nums[mid] == target) return mid;
        // 如果左边是升序
        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        // 那么右边是升序
        else {
            if (nums[mid] < target && target <= nums[n - 1]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}
