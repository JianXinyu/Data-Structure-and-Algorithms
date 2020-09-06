# 好题！

刚开始理解错题意，以为是连续的subsequence；

后来改进，但忽略了存在几组subsequence的情况。

**UNSUCCESSFUL**

```C++
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int length = 1;
        int last = 0;
        for(int i = 1; i < arr.size(); i++)
        {
            if(arr[i] - arr[last] == difference)
            {
                last = i;
                length++;                    
            }
            
            if(last == 0 && i > 1)
            {
                for(int j = 1; j < i; j++)
                {
                    if(arr[i] - arr[j] == difference)
                    {
                        last = i;
                        length++;
                    }
                }
            }
        }
        return length;
    }
};
```

### Solution

这题很妙，dp思想的使用与其他题目不同。需要使用hashtable，且**把元素作为key**，以该元素为结尾的subsequence的长度作为value。

How to re-use computation? 

​	e.g., we're checking number $x$, to see if $x$ is an entry in a subsequence, we only need to check if $x-diff$ is in a subsequence. So the length of the subsequence ending with $x$ equals to the length of the subsequence ending with $x-diff$ plus 1. $dp[x] = dp[x-diff] + 1$

```c++
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int diff) {
        int ans = 0;
        unordered_map<int, int> dp;
        for(int x : arr)
        {
            ans = max(ans, dp[x] = dp[x-diff] + 1);
        }
        return ans;
    }
};
```

Time complexity: $O(n)$

Space complexity: $O(n)$

​		 the worst case happens when every element is different and can't form a subsequence, now the size of hashtable is $2n$, since $dp[x-diff]$ isn't in the hashtable and needs to be created.