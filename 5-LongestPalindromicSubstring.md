用时: 1.5h, 提交6次且用了debug

Runtime: 1024 ms, faster than 6.24% of C++ online submissions for Longest Palindromic Substring.

Memory Usage: 495.6 MB, less than 5.03% of C++ online submissions for Longest Palindromic Substring.



logic: 

iterate string with index i, find same character with s[i] from the back, check if substr s[i]-s[j] is palindrome.

其中，check的时间复杂度是$O(n)$,  总时间复杂度是$O(n^3)$

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        string pal = s.substr(0,1);
        size_t j = 0;
        for(int i = 0; i < n; i++)
        {
            int len = pal.size();
            if( len+i >= n) break;

            j = s.rfind(s[i]);
            while (j > i)
            {
                string tmp = s.substr(i, j-i+1);
                if(checkPalindrome(tmp))
                {
                    if(tmp.size()>len)
                        pal = tmp;
                    break;
                }
                j = s.rfind(s[i], j-1);
            }
        }

        return pal;
    }
    
    bool checkPalindrome(string s)
    {
        int n = s.size();
        int mid = (n-1)/2;
        if(n%2==0)
        {
            for(int i = mid; i >=0; i--)
            {
                if(s[i]!=s[n-i-1]) return false;
            }
        }
        else
        {
            for(int i = 1; i <= mid; i++)
            {
                if(s[mid-i]!=s[mid+i]) return false;
            }
        }

        return true;
    }
};
```



## Better Solution

iterate the string, consider this character as the middle of a palindrome, expand towards both sides from this character and calculate the length of this palindrome. Since we don't the length of this palindrome, we have check both situations, i.e., odd and even. Then, compare the length.

getLen() is a lambda function.

```c++
// Author: Huahua, 16 ms, 8.7 MB
class Solution {
public:
  string longestPalindrome(string s) {
    const int n = s.length();
    auto getLen = [&](int l, int r) {
      while (l >= 0 && r < n 
             && s[l] == s[r]) {
        --l;
        ++r;
      }
      return r - l - 1;
    };
    int len = 0;
    int start = 0;
    for (int i = 0; i < n; ++i) {
      int cur = max(getLen(i, i), 
                    getLen(i, i + 1));
      if (cur > len) {
        len = cur;
        start = i - (len - 1) / 2;
      }
    }
    return s.substr(start, len);
  }
};
```

