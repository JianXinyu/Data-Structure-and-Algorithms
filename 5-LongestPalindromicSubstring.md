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

## Manacher's Algorithm

参考：[Link1](https://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html), [Link2](https://www.hackerrank.com/topics/manachers-algorithm)

Given a string **S** with the length of **N**.

1. 化一般为特殊。

   在字符串S的每个字符之间以及S的首位都插入一个特殊字符，该字符绝不会在S中出现，比如"#"。得到字符串**T**。$T.length = 2N+1$。

   例如: S="abaaba"，T="#a#b#a#a#b#a#"。

   如此一来，T的长度必定是奇数，这样就无需讨论S的长度是奇是偶了。此外，还有一个好处。

2. Calculate a table **P[]**, where $P[i]$ is the **radius** of the longest palindromic substring of T centered at $T[i], i\in[0,2N]$.

   例如：S="abaaba"

   | $i$  | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   |
   | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
   | T    | #    | a    | #    | b    | #    | a    | #    | a    | #    | b    | #    | a    | #    |
   | P    | 0    | 1    | 0    | 3    | 0    | 1    | 6    | 1    | 0    | 3    | 0    | 1    | 0    |

   观察发现：

   - 当T[i]在S中时，$P[i]$ is the **length** of the longest palindromic substring of S centered at this character. ------odd case

   - 当T[i]是插入的特殊字符时，$P[i]$ is the **length** of the longest palindromic substring of S centered at the middle of two characters. -------even case

     所以$P[]$可以直接用于求$S$中所有回文子串的长度，自然也就容易求出最长回文子串的长度及中心位置了。这便是T的好处之二。

   为了计算$P[i]$, 就必须以$T[i]$左右扩展，那么有什么办法节省扩展的时间吗？

   “想象你在"abaaba"中心画一道竖线，你是否注意到数组P围绕此竖线是中心对称的？再试试"aba"的中心，P围绕此中心也是对称的。这当然不是巧合，而是在某个条件下的必然规律。我们将利用此规律减少对数组P中某些元素的重复计算。” -- BIT祝威

   下面定义几个变量：

   1. $C$: the center of  the palindrome currently known to include the boundary closest to the right end of  $T$
   2. $R$: the rightmost boundary of the palindrome centered at $C$, $\therefore T[C+k]=T[C-k], k\in[0,R-C]$
   3. $L$: the leftmost boundary of the palindrome centered at $C$, $L=2C-R$
   4. $i$: the position of an element in $T$ whose palindromic span is being determined. $i$ is always to the right of $C$.
   5. $i'$: mirrored position of $i$ w.r.t. $C$. so $i'=2C-i$.

   我们可以根据已知的$P[i']$来加速计算$P[i]$. 对于每一个$i$, 有下面几种可能：

    1. Case 1: The length of the longest palindrome centered at $i'$ such that the left boundary of this palindrome does not extend **beyond or until** the left boundary of the longest palindrome centered at $C$, i.e., $P[i']<i'-L$

       例如：

       ![image-20200830175043135](\figures\ManacherAlgorithm1.png)

       此时$i=13$，显然， $P[13]=P[9]=1$. 直观上，因为对称，所以必然成立$P[i]=P[i']$。 我们也可以严格证明在case 1情形下，此规律必然成立。

       证明分为两部分：

       1. 中心位于$i'$的回文子串P1，关于$C$的镜像子串P2(中心位于$i$)也是回文字符串

       2. 在P1之外的字符，关于$C$的镜像字符，不在中心位于$i$的回文子串中。

          ![image-20200830175411940](\figures\ManacherAlgorithm2.png)

       Consider $T[i'-k], T[i+k]\quad and \quad T[i'+k], T[i-k] \quad \forall k \leq P[i']$:
       $$
       \because k\leq P[i'] \quad \therefore k< i'-L=R-i \\
       \begin{align}
       T[i'-k]&=T[2C-i-k]=T[C-(i+k-C)]\\
       T[i+k] &= T[C+(i+k-C)]\\
       
       \end{align}
       $$
       Let $k'=i+k-C, \therefore k'<i+R-i-C=R-C$
       $$
       \begin{align}
       \therefore T[i'-k]&=T[C-k']\\
       T[i+k]&=T[C+k']\\
       \because T[C+k']&=T[C-k'], k'\in[0,R-C)\\
       \therefore T[i'-k]&=T[i+k] \quad \forall k\leq P[i'] \tag{1}
       \end{align}
       $$
       Same with $ T[i'+k]=T[i-k] \quad \forall k\leq P[i'] \tag{2}$

       $\because T[i'-k]=T[i'+k] \quad \forall k \leq P[i']$

       $\therefore T[i-k] = T[i+k] \quad \forall k\leq P[i']$

       when $k=P[i']+1$, formula (1) and (2) still exist. however, $T[i'-k]!=T[i'+k]$. 

       $\therefore T[i-k] != T[i+k] \quad \forall k= P[i']+1$

   2. Case 2: the palindrome centred at $i'$ extends beyond the left boundary of the palindrome centred at $C$.

      ![image-20200830175315190](\figures\ManacherAlgorithm3.png)

同样可以容易得到$P[14],P[15]$.