# Question
Problem Description  
很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，分数最高的是多少。这让很多学生很反感。不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。

Input  
本题目包含多组测试，请处理到文件结束。  
在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。学生 ID 编号分别从 1 编到 N。第二行包含 N 个整数，代表这 N 个学生的初始成绩，其中第 i 个数代表 ID 为 i 的学生的成绩。接下来有 M 行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数 A，B。当 C 为 'Q' 的时候，表示这是一条询问操作，它询问 ID 从 A 到 B(包括 A,B)的学生当中，成绩最高的是多少。当 C 为 'U' 的时候，表示这是一条更新操作，要求把 ID 为 A 的学生的成绩更改为 B。

Output  
对于每一次询问操作，在一行里面输出最高成绩。

```c
Sample Input
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5

Sample Output
5
6
5
9
```

# Analysis
单点增减 + 区间最大值，树状数组的应用之一

下面代码main函数中为什么要连用两次scanf？
[ref](https://blog.csdn.net/qq_38908061/article/details/78992526)

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int MAXN = 3e5;
int A[MAXN], t[MAXN];
int n, m;

int lowbit(int x) {return x & (-x);}

void Update(int index, int val){
    A[index] = val;
    for (int i = index; i <= n; i += lowbit(i)) {
        t[index] = A[index];
            for (int k = 1; k < lowbit(i); k <<= 1)
                t[i] = max(t[i-k], t[i]);
    }
}

int Query(int l, int r) {
    int ans = INT_MIN;
    while (l <= r) {
        ans = max(ans, A[r]);
        r--;
        for (; l <= r - lowbit(r); r -= lowbit(r))
            ans = max(ans, t[r]);
    }
    return ans;
}

int main() {
    char c;
    int a, b;
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        // initialize array and bit
        for (int i = 1; i <= n; i++) {
            scanf("%d", &A[i]);
            Update(i, A[i]);
        }

        for (int j = 1; j <= m; j++) {
            scanf("%c", &c);
            scanf("%c", &c);
            scanf("%d%d", &a, &b);
            if (c == 'Q') {
                int ans = Query(a, b);
                printf("%d  c = %c, a = %d, b = %d\n", ans, c, a, b);
                
            }
            else if (c == 'U') {
                Update(a, b);
            }
        }
    }

    return 0;
}
```

T: $O(max(n,m)\log n)$
S: $O(n)$