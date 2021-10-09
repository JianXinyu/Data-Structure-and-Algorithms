https://binarysearch.com/problems/Delete-Sublist-to-Make-Sum-Divisible-By-K

Intuition

We can rephrase the problem as "finding the smallest sublist whose sum is equivalent to the sum of the whole array modulo kk". Suppose that value is tt.

We use a hash table to save the available modulos. Then we enumerate the numbers and accumulate the value (modulo kk). If the current prefix sum is ss, then we need to check whether s-ts−t exists in the hash table. We always update the hash table with the current position, since we want the shortest sublist.

Implementation

There are several edge cases.

-   First, the array can be empty, in which case we have no answer.
-   Second, the sum of the whole array can be divided by kk, in which case the answer is 00.
-   Third, we cannot remove the whole array while leaving an empty array. So if our final answer is nn, that is invalid and we need to return -1−1.

Time Complexity

The time complexity is \mathcal{O}(n)O(n) since hash table operations are \mathcal{O}(1)O(1).

Space Complexity

The space complexity is \mathcal{O}(\min(n,k))O(min(n,k)) because there can be at most \mathcal{O}(\min(n,k))O(min(n,k)) elements in the hash table

理解Solution
```cpp
int solve(vector<int>& nums, int k) {
    if (nums.empty()) return -1;

    int target = 0;
    for (int num : nums) target = (target + num) % k;
    if (target == 0) return 0;

    unordered_map<int, int> memo;
    memo[0] = 0;
    int pos = 0, now = 0, ans = nums.size();
    for (int num : nums) {
        pos++;
        now = (now + num) % k;
        if (memo.count((now + k - target) % k)) ans = min(ans, pos - memo[(now + k - target) % k]);
        memo[now] = pos;
    }
    return ans == nums.size() ? -1 : ans;
}
```