// Two pointers
// 既然nums1后面是空的，那就逆序迭代
// 注意迭代后nums2还有元素的情况
// T: O(n), S: O(1)

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n -1;
        int last = m + n - 1;
        while(i >= 0 && j >= 0){
            if(nums1[i] <= nums2[j])
                nums1[last--] = nums2[j--];
            else
                nums1[last--] = nums1[i--];
        }
        while(j >= 0)
            nums1[last--] = nums2[j--];

    }
};