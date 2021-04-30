class Solution {
public:
    int median3(vector<int>& nums, int l, int r){
        int mid = (l+r) / 2;
        if(nums[l] < nums[mid])
            swap(nums[l], nums[mid]);
        if(nums[l] < nums[r])
            swap(nums[l], nums[r]);
        if(nums[mid] < nums[r])
            swap(nums[mid], nums[r]);
        swap(nums[mid], nums[l+1]);
        return nums[l+1];
    }


    void quicksort(vector<int>& nums, int l, int r){
        if(l+10 >= r){
            if(nums[l] < nums[r])
                swap(nums[l], nums[r]);
            return;
        }
        int pivot = median3(nums, l, r);
        int i = l + 1, j = r;
        for(;;){
            while(nums[++i] > pivot){}
            while(nums[--j] < pivot){}
            if(i < j)
                swap(nums[i], nums[j]);
            else
                break;
        }
        swap(nums[j], nums[l+1]);
        quicksort(nums, l, j-1);
        quicksort(nums, j+1, r);
    }

    int findKthLargest(vector<int>& nums, int k) {
        quicksort(nums, 0, nums.size()-1);
        for(int i = 0; i < nums.size(); ++i){
            cout << nums[i] << ' ';
        }
        return nums[k-1];
    }

};