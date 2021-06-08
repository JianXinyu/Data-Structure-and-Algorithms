https://binarysearch.com/problems/Triple-Inversion
Given a list of integers nums, return the number of pairs i < j such that nums\[i\] > nums\[j\] \* 3.  
  
Constraints： n ≤ 100,000 where n is the length of nums  
Example 1  
Input：  
nums = \[7, 1, 2\]  
Output：  
2  
Explanation：  
We have the pairs (7, 1) and (7, 2)

# Brutal Force
```cpp
int solve(vector<int>& nums) {
    int ans = 0;
    for(int i = 0; i < nums.size(); ++i){
        for(int j = i+1; j < nums.size(); ++j){
            if(nums[i] > (3 * nums[j]))
                ans++;
        }
    }
    return ans;
}
```
TLE

# Binary Search
## 思路
构造有序序列.

参考[题解](https://binarysearch.com/problems/Triple-Inversion)
在把一个element插入sorted array时, 我们想得到它的位置. 用STL`set`的问题在于, 为了得到位置, 还得把再subtract iterators and this operation is O(n). 可以自定义一个`indexed_set`, 只有O(logn).

- go from the end of the array
- use the function `order_of_key()` to determine how many elements to the right satisfy the requirement in the problem statement. 
- When inserting an element into the `indexed_set`, we multiply it's value by 3. Since elements in the array may have the same value, we insert a pair instead(with the second element of the pair being the position of the element) in order to avoid the removal of duplicates since an  `indexed_set` acts like a set (not a multiset).

## Code
```cpp
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
             tree_order_statistics_node_update>
    indexed_set;

int solve(vector<int>& nums) {
    indexed_set sett;
    int ans = 0;
    for (int i = nums.size() - 1; i >= 0; i--) {
        ans += sett.order_of_key(make_pair(nums[i], i));
        sett.insert(make_pair(3 * nums[i], i));
    }

    return ans;
}
```

**Complexity Analysis:**
T: $O(nlogn)$  For every element in the array, we use the function `order_of_key()` which is an additional factor of O(logn)
S: O(n)