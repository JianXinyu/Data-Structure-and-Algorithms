// two pointers
class Solution {
public:
    int trap(vector<int>& height) {
        const int n = height.size();
        if(n < 3) return 0;
        int ans = 0;
        int l = 0, r = n -1;
        int maxl = height[l], maxr = height[r];
        while(l < r){
            if(maxl < maxr){
                ans += maxl - height[l++];
                maxl = max(maxl, height[l]);
            }
            else{
                ans += maxr - height[r--];
                maxr = max(maxr, height[r]);
            }
        }
        return ans;
    }
};

// DP, prefix max
// 空间换时间
// class Solution {
// public:
//     int trap(vector<int>& height) {
//         const int n = height.size();
//         if(n < 3) return 0;
//         int ans = 0;
//         vector<int> maxl(n);
//         vector<int> maxr(n);

//         for(int i = 0; i < n; ++i){
//             maxl[i] = (i == 0 ? height[0] : max(maxl[i-1], height[i]) );
//             maxr[n - 1 - i] = (i == 0 ? height[n-1] : max(maxr[n - i], height[n - 1 -i]));
//         }
//         for(int i = 0; i < n; ++i){
//             ans += min(maxl[i], maxr[i]) - height[i];
//         }

//         return ans;
//     }
// };

// brute force
// class Solution {
// public:
//     int trap(vector<int>& height) {
//         const int n = height.size();
//         if(n < 3) return 0;

//         int ans = 0;
//         auto start = height.begin();
//         auto end = height.end();
//         for(int i = 0; i < n; ++i){
//             int maxl = *max_element(start, start+i+1);
//             int maxr = *max_element(start+i, end);
//             ans += min(maxl, maxr) - height[i];
//         }
//         return ans;
//     }
// };

// own solution: wrong
// class Solution {
// public:
//     int trap(vector<int>& height) {
//         const int n = height.size();
//         int ans = 0;
//         if(n < 3) return 0;

//         int l = -1, r = -1;
//         for(int i = 0; i < n - 1; ++i){
//             if(height[i] > height[i+1] && l < 0)
//                 l = i;
//             else if(height[i] < height[i+1] && l >= 0 && r < 0){
//                 r = (i == n-2 ? i+1 : 0);
//             }
//             else if(height[i] > height[i+1] && l >= 0 && r == 0){
//                 r = i;
//             }
//             if(l >= 0; r > 0){
//                 printf("l=%d, r=%d\n", l, r);
//                 int edge = min(height[l], height[r]);
//                 for(int j = l+1; j < r; ++j)
//                     ans += edge - height[j];
//                 l = -1; r = -1;
//                 --i;
//             }

//         }
//         return ans;

//     }
// };


