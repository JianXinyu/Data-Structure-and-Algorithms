class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quicksort(nums, 0, nums.size()-1);
        return nums;
    }

    const int& median3(vector<int>& nums, int l, int r){
        int mid = (r+l)/2;
        if(nums[l] > nums[mid])
            swap(nums[l], nums[mid]);
        if(nums[l] > nums[r])
            swap(nums[l], nums[r]);
        if(nums[mid] > nums[r])
            swap(nums[mid], nums[r]);
        // place the pivot at position r-1
        swap(nums[mid], nums[r-1]);

        return nums[r-1];
    }

    void quicksort(vector<int>& nums, int l, int r){
        if (l+10 <= r){
            const int& pivot = median3(nums, l, r);

            int i = l, j = r - 1;
            for(;;){
                while(nums[++i] < pivot) {}
                while(nums[--j] > pivot) {}

                if(i < j)
                    swap(nums[i], nums[j]);
                else
                    break;
            }
            swap(nums[i], nums[r-1]);

            quicksort(nums, l, i-1);
            quicksort(nums, i+1, r);
        }
        else
            insertionSort(nums, l, r);
    }

    void insertionSort(vector<int> & a, int left, int right)
    {
        for(auto p = left; p <= right; p++)
        {
            int tmp = move(a[p]);
            int j;
            for(j=p; j>0&&tmp<a[j-1];--j){
                a[ j ] = move( a[ j - 1 ] );
            }
            a[ j ] = move( tmp );
        }
    }
};