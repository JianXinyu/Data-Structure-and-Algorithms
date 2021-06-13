## 思路
统计每个字符出现的次数能整除n

```cpp
class Solution {
public:
    bool makeEqual(vector<string>& words) {
        const int n = words.size();
        unordered_map<char, int> m(24);
        for(int i = 0; i < n; ++i){
            for(char& c : words[i]){
                m[c]++;
            }
        }
        for(auto const &x : m){
            if(x.second % n != 0)
                return false;
        }
        return true;
    }
};
```

改进:
```cpp
class Solution {
public:
    bool makeEqual(vector<string>& words) {
        vector<int> cnt(26, 0);   // 每种字符的频数
        int n = words.size();
        for (const string& wd: words){
            for (char ch: wd){
                ++cnt[ch-'a'];
            }
        }
        return all_of(cnt.begin(), cnt.end(), [n](int x){ return x % n == 0; });
    }
};
```