# Question
You have a large text file containing words. Given any two different words, find the shortest distance (in terms of number of words) between them in the file. 
-   `words.length <= 100000`

Input: words = ["I","am","a","student","from","a","university","in","a","city"], word1 = "a", word2 = "student"
Output: 1

# Analysis
对 `words` 进行遍历，使用两个指针 `p` 和 `q` 分别记录最近的两个关键字的位置，并维护更新最小距离
```cpp
class Solution {
public:
    int findClosest(vector<string>& words, string word1, string word2) {
        const int n = words.size();
        int ans = n;
        int p = -1, q = -1;
        for (int i = 0; i < n; i++) {
            if (words[i] == word1)
                p = i;
            else if (words[i] == word2)
                q = i;
            if (p >= 0 && q >= 0)
                ans = min(ans, abs(p - q));
        }
        return ans;
    }
};
```

T: O(n)
S: O(1)