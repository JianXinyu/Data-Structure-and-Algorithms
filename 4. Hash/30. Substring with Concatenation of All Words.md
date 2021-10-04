## 思路
题眼：words中的单词长度相同
遍历s中所有长度为 (words\[0\].length \* words.length) 的子串 Y，查看 Y 是否可以由 words 数组构造生成。
- 首先将words中的单词放入哈希表m，降低搜索复杂度
- 遍历s
- 新建一个临时哈希表temp，取出以当前字符开始的子串
- 遍历该字串
- 取出以当前字符开始的word
- 如果该word不在m中，肯定不行，直接退出检查下一个字串
- 放入temp
- 如果temp\[word\]出现的次数大于m\[word\]，也肯定不行，直接退出检查下一个字串
- 如果能完整遍历完子串，说明找到了符合条件的子串，将起始字符的index放入ans
## Code
```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> m;
        vector<int> ans;
        const int length = words[0].length();
        const int span = words.size() * length;
        const int n = s.length();
        for(auto const word : words){
            m[word]++;
        }
        // 注意这里要+1, 因为要到最后一个span的第一个字母
        for(int i = 0; i < n - span + 1; ++i){
            unordered_map<string, int> temp;
            string cur = s.substr(i, span);
            int j = 0;
            for(; j < span; j += length){
                string word = cur.substr(j, length);
                if(m.find(word) == m.end())
                    break;
                temp[word]++;
                if(temp[word] > m[word])
                    break;
            }
            if(j == cur.length())
                ans.push_back(i);
        }
        
        return ans;
    }
};
```
**Complexity Analysis:**
n=s.size()，m=words.size(), k=words\[0\].size()
T: $O(n*m*k)$ 因为substr的复杂度是O(N)
S: $O(m)$