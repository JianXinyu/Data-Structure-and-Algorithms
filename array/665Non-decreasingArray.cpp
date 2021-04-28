// Crux: modify which element when nums[i] > nums[i+1]?
// [4,5,2,7] i = 1, nums[i-1] > nums[i+1], modify i+1
// [1,5,2,3] i = 1, nums[i-1] < nums[i+1], modify i
// what if nums[i-1] = nums[i+1]?

bool checkPossibility(vector<int>& nums) {
    int n = nums.size();
    if (n == 1)
        return true;
    int count = 0;
    for(int i = 0; i < n-1 && count < 2; ++i){
        if(nums[i] > nums[i+1]){
            count++;
            if( i-1<0 || nums[i-1] <= nums[i+1]) nums[i]=nums[i+1];
            else
                nums[i+1] = nums[i];
        }
    }

    return count<=1;
}