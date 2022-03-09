树状数组或二叉索引树（Binary Indexed Tree），又以其发明者命名为 Fenwick 树。

多用于高效计算数列的前缀和， 区间和。
- $O(log n)$ 时间得到任意前缀和 $\sum^j_{i=1}A[i],1<=j<=N$
- $O(log n)$ 时间内支持动态单点值的修改(增加或者减少)。
- 空间复杂度 O(n)。

> 利用数组实现前缀和，查询本来是 O(1)，但是对于频繁更新的数组，每次重新计算前缀和，时间复杂度 O(n)。此时树状数组的优势便立即显现。

# 一维树状数组
树状数组在物理形式上还是数组，不过每个元素的含义是树的节点。

树状数组中**父子节点index关系**是 $parent=son+2^k$，其中 $k$ 是子节点index对应二进制末尾 0 的个数。注意这里的index是从1开始的。

Example: A 数组正常存储数据，B 数组是树状数组。
$B4, B6, B7$ 是 $B8$ 的子节点。
$4 = (100)_2, 4+2^2=8$，所以$B8$是$B4$的父节点；
$7 = (111)_2, 7+2^0=8$，所以$B8$是$B7$的父节点。
![[bit1.png]]

## 节点含义
### sum
- 奇数下标的节点表示叶子节点，其值就是原数组中相同下标存的值。
	- e.g., B1，B3，B5，B7 分别存的值是 A1，A3，A5，A7
- 偶数下标的节点表示父节点，其值是区间和。这个区间的左边界是该父节点最左边叶子节点对应的下标，右边界就是自己的下标
	-  e.g., B8 表示的区间左边界是 1，右边界是 8，所以它表示的区间和是 A1 + A2 + …… + A8

$$\begin{aligned}
B_{1} &= A_{1} \\
B_{2} &= B_{1} + A_{2} = A_{1} + A_{2} \\
B_{3} &= A_{3} \\
B_{4} &= B_{2} + B_{3} + A_{4} = A_{1} + A_{2} + A_{3} + A_{4} \\
B_{5} &= A_{5} \\
B_{6} &= B_{5} + A_{6} = A_{5} + A_{6} \\
B_{7} &= A_{7} \\
B_{8} &= B_{4} + B_{6} + B_{7} + A_{8} = A_{1} + A_{2} + A_{3} + A_{4} + A_{5} + A_{6} + A_{7} + A_{8} \\
\end{aligned}$$

由数学归纳法可得，左边界的下标必然是$i-2^k+1$，其中$i$是父节点的下标，$k$是$i$二进制表示中末尾0的个数。因此可以计算偶数节点的区间和(奇数节点也一样)：
$$B_{i} = \sum_{j = i - 2^{k} + 1}^{i} A_{j}$$

根据节点的关系和含义，可以用以下两种方式根据原始数组初始化树状数组。
1. 遍历原始数组元素a，考虑树状数组中哪些元素会计入该元素a
```cpp
inline int lowbit(int x) { return x & (-x); }

int A[] = {1,2,3,4,5,6,7,8};
#define N sizeof(A) / sizeof(*A) + 1
int t[N];

void init() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += lowbit(j))
            t[j] += A[i - 1];
    }
}
```
T: $O(n\log n)$
> Note：树状数组的下标从1开始，而原始数组的下标从0开始
> $lowbit(x)$的定义见[[0 Bit manipulation]]

2. $O(n)$建树：每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲。
```cpp
void init() {
    for (int i = 1; i < N; i++) {
        t[i] += A[i-1];
        int j = i + lowbit(i);
        if (j < N) t[j] += t[i];
    }
}
```
T: $O(n)$
### max
将求和$\sum$改为比较$max$， 树状数组节点的含义就改变了。

- 奇数下标的节点表示叶子节点，其值就是原数组中相同下标存的值。
	- e.g., B1，B3，B5，B7 分别存的值是 A1，A3，A5，A7
- 偶数下标的节点表示父节点，其值是区间最大值。这个区间的左边界是该父节点最左边叶子节点对应的下标，右边界就是自己的下标
	-  e.g., B8 表示的区间左边界是 1，右边界是 8，所以它表示的区间最大值是 max(A1, A2, ……, A8)

$$B_{i} = \max_{j = i - 2^{k} + 1}^{i} A_{j}$$

根据节点的关系$parent = son + lowbit(son)$和节点含义，给出如下初始化：遍历原始数组元素a，考虑树状数组中哪些元素会计入该元素a。
```cpp
void init() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += lowbit(j))
            t[j] = max(t[j], A[i-1]);
    }
}
```
T: $O(n\log n)$
## 单点修改操作 Update/Add
### sum
原始数组单点修改操作可以实现树状数组节点值的增加或减少。

比如将$A_i$加上$delta$，需要更新$B_i$及以上的所有关联的节点。

树状数组中父子节点index关系是 $parent=son+2^k$，其中 $k$ 是子节点index对应二进制末尾 0 的个数。所以可以据此从节点$x$往上，直到最大节点为止。

```cpp
void Add(int index, int delta) {
    for (int i = index; i < N; i += lowbit(i))
        t[i] += delta;
}
```
T: $O(\log n)$
### max
原始数组单点修改操作可以是单纯地更新值。比如将$A_i$更新为$val$，需要更新$B_i$及以上的所有关联的节点。

这里和sum不一样的地方在于，在更新$B_{i} = \max_{j = i - 2^{k} + 1}^{i} A_{j}$时，需要考虑整个相关区间上的原始数组的值。

因此暴力的方式是将该点与区间内所有原始数组的值比较大小，取出最大值。
```cpp
void Update(int index, int val) {
    A[index - 1] = val;
    for (int i = index; i < N; i += lowbit(i)) {
        t[i] = A[i - 1];
        for (int j = i - lowbit(i) + 1; j <= i; j++)
            t[i] = max(t[i], A[j - 1]);
    }       
}
```
T: $O(n \log n)$

观察开头图片中树状数组的结构，可以发现使用树状数组的值，而无需枚举区间内所有原始数组的值。比如，在更新$A_4$后，我们更新$B_4$时，我们只需要比较$max(B_2,B_3,A_4)$; 更新$B_8$是，只需比较$B_4,B_6,B_7,A_8$。

归纳可得，比较的是$B_{i-2^k}, ..., B_{i-2^1}, B_{i-2^0}, A[i]$, 其中$2^k<lowbit(i)\leq 2^{k+1}$
```cpp
void update(int index, int val) {
    A[index - 1] = val;
    for (int i = index; i < N; i += lowbit(i)) {
        t[i] = A[i - 1];
        for (int k = 1; k < lowbit(i); k <<= 1)
            t[i] = max(t[i], t[i - k]);
    }
}

```
T: $O((\log n)^2)$

## 查询操作 Query
### sum
查询原始数组区间$[1,i]$的区间和。

$$\begin{aligned}
Query(i) &= A_{1} + A_{2} + ...... + A_{i} \\
&= A_{1} + A_{2} + ...... + A_{i-2^{k}} + A_{i-2^{k}+1} + ...... + A_{i} \\
&= A_{1} + A_{2} + A_{i-2^{k}} + B_{i} \\
&= Query(i-2^{k}) + B_{i} \\
&= Query(i-lowbit(i)) + B_{i} \\
\end{aligned}$$

$i - lowbit(i)$ 将 $i$ 的二进制中末尾的 1 去掉，最多有 $log(i)$ 个 1，所以查询操作最坏的时间复杂度是 $O(log n)$.
```cpp
int Query(int index) {
    int sum = 0;
    while (index >= 1) {
        sum += t[index];
        index -= lowbit(index);
    }
    return sum;
}
```
T: $O(\log n)$

### max
查询原始数组区间$[1,i]$的区间最大值。

$$\begin{aligned}
Query(i) &= max(A_{1}, A_{2}, ......, A_{i}) \\
&= max(A_{1}, A_{2}, ......, A_{i-2^{k}}, A_{i-2^{k}+1}, ......, A_{i}) \\
&= max(A_{1}, A_{2}, ......, A_{i-2^{k}}, B_{i}) \\
&= max(Query(i-2^{k}), B_{i}) \\
&= max(Query(i-lowbit(i)), B_{i}) \\
\end{aligned}$$

```cpp
int Query(int index) {
    int m = INT_MIN;
    while (index >= 1) {
        m = max(m, t[index]);
        index -= lowbit(index);
    }
    return m;
}
```
T: $O(\log n)$

## 后缀定义
以上都是树状数组节点的前缀定义，i.e., 树状数组中父子节点index关系是 $parent=son+2^k$。

在max含义中，常用一种后缀定义，i.e., 树状数组中父子节点index关系是$parent=son-2^k$, 当$parent=0$时忽略。
- 奇数节点都是叶子节点，其值就是原数组中相同下标存的值。
- 偶数节点除了最后一个都是父节点

不同于前缀定义，我们无法归纳出类似$B_{i} = \max_{j = i - 2^{k} + 1}^{i} A_{j}$这样树状数组和原始数组的关系式。

![[bit2.png]]

**单点修改操作 Update**：
根据当前节点，找到所有父节点
```cpp
void Update(int index, int val) {
	for (int i = index; i > 0; i -= lowbit(i))
		t[i] = max(t[i], val);
}
```
T: $O(\log n)$

**查询操作Query**：查询原始数组区间$[i,+\infty)$的区间最大值。
从图中可以看出，只需比较$B_i, B_{i+lowbit(i)}, ..., B_{N-lowbit(N)}$
==为什么会有这种巧合？==
```cpp
int Query(int index) {
	int m = INT_MIN;
	while (index < N) {
		m = max(m, t[index]);
		index += lowbit(index);
	}
	return m;
}
```
T: $O(\log n)$

```cpp
inline int lowbit(int x) {return x & (-x);}

class FenwickTree {
    vector<int> tree_;
    int capacity_;
public:
    FenwickTree(int n) {
        capacity_ = n;
        tree_.resize(n + 1);
    }

    void Update(int index, int val) {
        // propagate the information to the left
        for (; index > 0; index -= lowbit(index)) 
            tree_[index] = max(tree_[index], val);
    }

    // Compute suffix max (i.e. bit[i] == max(array[i:]))
    // NOTE: original array is virtual, but conceptually you can imagine it exists
    int Query(int index) {
        // get the information all the way to the right (suffix)
        int mx = 0; // sometimes we use 0 rather than INT_MIN
        for (; index <= capacity_; index += lowbit(index))
            mx = max(mx, tree_[index]);
        return mx;
    }
};
```
- [[218. The Skyline Problem]]
## 树状数组类的写法
sum
```cpp
#include <iostream>
#include <vector>
using namespace std;

inline int lowbit(int x) { return x & (-x); }

class BinaryIndexedTree {
    vector<int> *tree_ = nullptr;
    int capacity_ = 0;

public:
    BinaryIndexedTree(vector<int> nums) {
        capacity_ = nums.size() + 1;
        tree_ = new vector<int>(capacity_, 0);
        for (int i = 1; i < capacity_; i++) {
			(*tree_)[i] += nums[i-1];
			int j = i + lowbit(i);
			if (j < capacity_) (*tree_)[j] += (*tree_)[i];
            for (int j = i; j >= i - lowbit(i) + 1; j--) {
                (*tree_)[i] += nums[j-1];
            }
        }
    }

    bool Add(int index, int val) {
        if (index >= capacity_) return false;

        for (int i = index; i < capacity_; i += lowbit(i))
            (*tree_)[i] += val;

        return true;
    }

    int Query(int index) {
        int sum = 0;
        while (index >= 1) {
            sum += (*tree_)[index];
            index -= lowbit(index);
        }
        return sum;
    } 

    void getTree() {
        for (int i = 1; i < capacity_; i++)
            cout << (*tree_)[i] << ' ';
        cout << endl;
    }

};

int main () {
    BinaryIndexedTree t({1,2,3,4,5,6,7,8});
    t.getTree();
    t.Add(5,5);
    t.getTree();
    cout << t.Query(3) << endl; 
    return 0;
}
```

# 不同场景下树状数组的功能
根据节点维护的数据含义不同，树状数组可以提供不同的功能来满足各种各样的区间场景。
## 1. 单点增减 + 区间求和 
树状数组最经典的场景

单点增减：调用$Add(i,v)/Add(i,-v)$

求$[m,n]$区间和: $Query(n)-Query(m-1)$

Example:
- [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/)
- [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)
- [[2179. Count Good Triplets in an Array]]
## 2. 区间增减 + 区间求和
**区间增减**：原始数组在区间$[m,n]$内的每一个数都增加$v$。

这时需要引入一个中间辅助数组$C$，再对这个辅助数组求树状数组。*注意，这个辅助数组只是概念上的，无需物理存在*。
定义差分数组 $C_i:=A_i-A_{i-1},C_0=A_0$。显然，经过累加$$A_n=\sum_{j=1}^{n}C_j$$

经过区间增减后：
$$\begin{aligned}
C_{m} &= (A_{m} + v) - A_{m-1}\\
C_{m+1} &= (A_{m+1} + v) - (A_{m} + v)\\
C_{m+2} &= (A_{m+2} + v) - (A_{m+1} + v)\\
......\\
C_{n} &= (A_{n} + v) - (A_{n-1} + v)\\
C_{n+1} &= A_{n+1} - (A_{n} + v)\\
\end{aligned}$$

显然，$C_{m+1}, C_{m+2}, ......, C_{n}$的值都不变，变化只有$C_{m}, C_{n+1}$。因此，对于树状数组，仅需执行$Add(m,v),Add(n+1,-v)$。当$n+1$超出范围时，无需处理。

同理，对于下面引入的新辅助数组$iC_i$，也仅改变了$mC_m,(n+1)C_{n+1}$。因此，对于其对应的树状数组，仅需执行$Add(m,v), Add(n+1,-v)$。

----
**区间求和**：求$\sum_{i=m}^{n}A_i$

先考察区间$[1,n]$的区间和：$\sum_{i=1}^{n}A_i=A_{1} + A_{2} + A_{3} + ...... + A_{n}$
$$\begin{aligned}
 &= (C_{1}) + (C_{1} + C_{2}) + (C_{1} + C_{2} + C_{3}) + ...... + \sum_{1}^{n}C_{n}\\
&= n * C_{1} + (n-1) * C_{2} + ...... + C_{n}\\
&= n * (C_{1} + C_{2} + C_{3} + ...... + C_{n}) - (0 * C_{1} + 1 * C_{2} + 2 * C_{3} + ...... + (n - 1) * C_{n})\\
&= n \sum_{i=1}^{n}C_{i} - \sum_{i=1}^{n}(i-1)C_i\\
&= (n+1) \sum_{i=1}^{n}C_{i} - \sum_{i=1}^{n}iC_i
\end{aligned}$$

其中$\sum_{i=1}^{n}C_{i}$可以用之前的树状数组$Query$得到，而求$\sum_{i=1}^{n}iC_i$则需要再构建一个树状数组。
> 注意：在实现Add时，要考虑两个树状数组的更新。数组$iC_i$的更新要注意它的改变量也是定值。


对于一般情况区间$[m,n]$:
$$\begin{aligned}
\sum_{i=m}{n}A_i&=\sum_{i=1}^{n}A_i-\sum_{i=1}^{m-1}A_i\\
&=(n+1) \sum_{i=1}^{n}C_{i} - \sum_{i=1}^{n}iC_i - ( m\sum_{i=1}^{m-1}C_{i} - \sum_{i=1}^{m-1}iC_{i})
\end{aligned}$$

因此，为求区间$[m,n]$和，需要维护两个差分数组对应的树状数组，再调用$Query(n)-Query(m-1)$。

```cpp

int A[] = {1,2,3,4,5,6,7,8};
#define N sizeof(A) / sizeof(*A) + 1
int C[N];
int t1[N], t2[N];

void Init() {
    // initialize differential array
    C[1] = A[0];
    for (int i = 2; i < N; i++) {
        C[i] = A[i - 1] - A[i - 2];
    }
    // initialize two BITs
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += lowbit(j)) {
            t1[j] += C[i];
            t2[j] += i * C[i];
        }
    }
}

void Add(int index, int val) {
    if (index >= N) return;
    C[index] += val;
    int val2 = index * val; // const value!
    while (index < N) {
        // update two BITs
        t1[index] += val;
        t2[index] += val2; 
        index += lowbit(index);
    }
}

void Add_interval(int l, int r, int val) {
    Add(l, val), Add(r + 1, -val);
}

int Query(int *t, int index) {
    int sum = 0; 
    while (index >= 1) {
        sum += t[index];
        index -= lowbit(index);
    }
    return sum;
}

long long Query_interval(int l, int r) {
    return (r + 1ll) * Query(t1, r) - Query(t2, r) - 
            1ll * l * Query(t1, l - 1) + Query(t2, l - 1);
}
```

## 3. 单点更新 + 区间最值 
单点更新：调用$Update(i, v)$

==不太明白==
区间最值：求区间$[m,n]$的最大值。和区间求和不同，这并不能使用$Query(1,n)$。回顾节点定义$B_{i} = \max_{j = i - 2^{k} + 1}^{i} A_{j}$
- if $m \leq n-2^k$, then $query(m,n) = max(query(m, n - 2^k), B_n)$
- if $m > n-2^k$, then $query(m,n) = max(query(m, n-1), A_n)$

```cpp
nt Query(int m, int n) {
    int ans = INT_MIN;
    while (m <= n) {
        ans = max(ans, A[n-1]);
        n--;
        for (; m <= n - lowbit(n); n -= lowbit(n))
            ans = max(ans, t[n]);
    }
    return ans;
}
```
T：$O((\log n)^2)$

Example：
- [[I Hate It]]

## 4. 区间叠加 + 单点最值
[[218. The Skyline Problem]] 后缀定义的应用

# 常见应用
## 1. 求逆序对
给定$n$个数$A[i]\in [MIN, MAX]$的排列P，求满足$i<j,A[i]>A[j]$的数对$(i,j)$的个数。

1. 离散化。对数组排序，从小到大变为1到n的整数，相同的数仍然相同。这样将原数组A就映射到了数组B, $B[i]\in[1,n_{unique}]$。$n_{unique}$表示原数组A中有多少个不同的元素，所以$n_{unique}\leq n$
2. 创建树状数组。用来记录这样一个数组 C（下标从1算起）的前缀和
	1. 初始时数组 C 的值均为 0。
	2. 若 $[1, n]$ 这个排列中的数 $i$ 当前已经出现，则 $C[i]$ 的值为 1 ，否则为 0。
	3. 从数组 B 第一个元素开始遍历，对树状数组执行修改数组 C 的第 $B[j]$ 个数值加 1 的操作。再在树状数组中查询有多少个数小于等于当前的数 $B[j]$（即用树状数组查询数组 C 中的 $[1,B[j]]$ 区间前缀和），当前插入总数 i 减去小于等于 $B[j]$ 元素总数，差值即为大于 $B[j]$ 元素的个数，并加入计数器。
-[[剑指 Offer 51. 数组中的逆序对]]
- [315. Count of Smaller Numbers After Self](https://books.halfrost.com/leetcode/ChapterFour/0300~0399/0315.Count-of-Smaller-Numbers-After-Self/)
- [493. Reverse Pairs](https://books.halfrost.com/leetcode/ChapterFour/0400~0499/0493.Reverse-Pairs/)
- [1649. Create Sorted Array through Instructions](https://books.halfrost.com/leetcode/ChapterFour/1600~1699/1649.Create-Sorted-Array-through-Instructions/)

## 2. 求区间逆序对
1.  离散化数组 $A[i]$
2.  对所有区间按照右端点单调不减排序
3.  按照区间排序后的结果，从左往右依次遍历每个区间。依照从左往右的区间覆盖元素范围，从左往右将 $A[i]$ 插入至树状数组中，每个元素插入之前计算辅助数组 $C[i]$。
4.  依次遍历每个区间内的所有元素，对每个元素计算 $Query(A[i] - 1) - C[i]$，累加逆序对的结果即是这个区间所有逆序对的总数。


Reference:
- [blog 1](https://halfrost.com/binary_indexed_tree/)
- [OI wiki](https://oi-wiki.org/ds/fenwick/#__comments)
- [top coder](https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees)