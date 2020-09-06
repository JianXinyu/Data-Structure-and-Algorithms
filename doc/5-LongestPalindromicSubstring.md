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

Reference：[Link1](https://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html)(BIT祝威), [Link2](https://www.hackerrank.com/topics/manachers-algorithm)。图片及部分文字陈述参考自Link1, 数学推导参考自Link2。

### Introduction

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

   “想象你在"abaaba"中心画一道竖线，你是否注意到数组P围绕此竖线是中心对称的？再试试"aba"的中心，P围绕此中心也是对称的。这当然不是巧合，而是在某个条件下的必然规律。我们将利用此规律减少对数组P中某些元素的重复计算。” -- [Link1](https://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html)(BIT祝威)

   ### Derivation

   下面定义几个变量：

   1. $C$: the center of  the palindrome currently known to include the boundary closest to the right end of  $T$
   2. $R$: the rightmost boundary of the palindrome centered at $C$, $\therefore T[C+k]=T[C-k], k\in[0,R-C]$
   3. $L$: the leftmost boundary of the palindrome centered at $C$, $L=2C-R$
   4. $i$: the position of an element in $T$ whose palindromic span is being determined. $i$ is always to the right of $C$.
   5. $i'$: mirrored position of $i$ w.r.t. $C$. so $i'=2C-i$.

   我们可以根据已知的$P[i']$来加速计算$P[i]$. 对于每一个$i$, 有下面几种可能：

    1. Case 1: The length of the longest palindrome centered at $i'$ such that the left boundary of this palindrome does not extend **beyond or until** the left boundary of the longest palindrome centered at $C$, i.e., $P[i']<i'-L=R-i$.

       例如：S = "babcbabcbaccba"

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

       $\therefore T[i-k] != T[i+k] \quad k= P[i']+1$

   2. Case 2: the palindrome centred at $i'$ extends beyond the left boundary of the palindrome centred at $C$, i.e., $P[i']\ge i'-L=R-i$.

      ![image-20200830175315190](\figures\ManacherAlgorithm3.png)

      导致Case2 与 Case1不同的原因是，仿照Case1的推导，我们只能确定 $T[i-k] = T[i+k] \quad \forall k\leq i'-L$，却无法确定$k\in(i'-L, P[i']]$时$T[i-k],T[i+k]$的关系。即，只能知道$P[i]\ge R-i$, 至于具体是多少，只能再逐个字符检测了。如果$P[i]> R-i$， 即以$i$为中心的回文子串右边界超过了$R$， 那么以$C$为中心的回文子串就不再是其右边界最靠近$T$右边界的回文子串了，取而代之的是以$i$为中心的回文子串，因此$C=i$，同时相应改变$L, R$。

   3. Case 3: 如果$i>=R$, 那么先前得到的$P[i']$不能给我们提供有用的信息，只能逐个字符检测。

总结一下：

```
if(i<R)
{
	if(P[i']<R-i)
		P[i]=P[i']
	else
	{
		P[i]>=R-i #(此时要逐个验证R右边的字符)
		if(i处的回文超过了R) 
		{
			C=i;
            update R;
		}
	}
}
else
{
	check one by one;
}
```

### Complexity Analysis

#### 时间复杂度

引用自[Link1](https://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html)(BIT祝威)

图中i为索引，T为加入"#"、"^"和"$"后的字符串，P[i]就是算法里的P[i]，calc[i]是为了求出P[i]而需要执行比较的次数。Note: 首位加入不同的字符是为了防止考虑边界情况, 这样i就可以从1开始，到T.length-1结束。

"V"表示此列的字符与其左侧的字符进行了比较，在左侧用"X"对应。绿色的表示比较结果为两个字符相同（即比较结果为成功），红色的表示不同（即比较结果为失败）。

很显然"X"和"V"的数量是相等的。

你可以看到，所需的成功比较的次数（绿色的"V"，表现为横向增长）不超过N，失败的次数（红色的"V"，表现为纵向增长）也不超过N，所以这个算法的时间复杂度就是2N，即O(N)。

![ManacherAlgorithm4](\figures\ManacherAlgorithm4.png)

#### 空间复杂度

创建新字符串$T$，$T.length=2N+3$，数组P, $P.length=2N+3$。因此空间复杂度$O(N)$

### C++ Implementation

Runtime: 28 ms, faster than 91.09% of C++ online submissions for Longest Palindromic Substring.

Memory Usage: 7.7 MB, less than 66.76% of C++ online submissions for Longest Palindromic Substring.

```C++
string longestPalindrome(string s) {
    // preprocess
    string T = "^";
    for(int i = 0; i < s.length(); i++)
    {
        T.append("#");
        T.append(s.substr(i, 1));
    }
    T.append("#$");

    const int n = T.length();
    vector<int> P(n, 0);
    int C = 0, R = 0;
    int maxIdx = 0; // record the position of the longest palindrome

    for(int i = 1; i < n-1; i++)
    {
        int i_mirror = C - (i - C);
        if(R > i)
        {
            //Case 1
            if(P[i_mirror] < R - i)
                P[i] = P[i_mirror];
            //Case 2
            else{
                P[i] = R - i;
                while(T[i+P[i]+1] == T[i-P[i]-1])
                    P[i]++;
                C = i;
                R = i + P[i];
            }
        }
        //Case 3
        else{
            P[i] = 0;
            while(T[i+P[i]+1] == T[i-P[i]-1])
                P[i]++;
            C = i;
            R = i + P[i];
        }

        if(P[i] > P[maxIdx])
            maxIdx = i;
        cout << P[i] << ' ';
    }
    
    return s.substr((maxIdx-1-P[maxIdx]) / 2, P[maxIdx]);
}
```

