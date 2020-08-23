首次尝试花了35分钟，效率很低

Runtime: 88 ms, faster than 21.52% of C++ online submissions for Longest Substring Without Repeating Characters.

Memory Usage: 20.8 MB, less than 7.32% of C++ online submissions for Longest Substring Without Repeating Characters.

时间是由于for loop里的find, time complexity is $O(n^2)$

空间是由于额外的string tmp

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string tmp;
        int max_size = 0;
        for(char i : s)
        {
            size_t found = tmp.find(i);
            if(found==string::npos)
            {
                tmp.push_back(i);
            }
            else
            {
                if(tmp.size() > max_size) max_size = tmp.size();
                tmp=tmp.substr(found+1);
                tmp.push_back(i);
            }
        }
        if(tmp.size() > max_size) max_size = tmp.size();
        return max_size;
    }
};
```

Better solution provided:

using sliding window

logic:

1. use HashSet to store the sliding window $[i, j]$ characters. initially, $i==j$

2. slide the index $j$ to the right

3. - if $str[j]$  isn't in the HashSet, slide $j$ further. Repeat this.
   - if $str[j] == str[i'],i'\in[i,j)$ , make $i=i'+1$

   

```C++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int len = 0;
        int i = 0;
        map<char, int> window;
        for(int j = 0; j<n; j++)
        {
            if(window.find(s[j]) != window.end())
            {
                len = max(len, j - i);
                i = max(i, window[s[j]]+1);
            }
            // note that s[j]'s index should be updated anyway
            window[s[j]] = j;
        }
        len = max(len, n - i);
        return len;
    }
};
```

