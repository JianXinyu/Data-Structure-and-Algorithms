Disjoint-set / union-find forest

an efficient data structure to solve the **equivalence problem**.
 - simple to implement
 - difficult to analyze

首先定义什么是 Relation
>  A **relation** $R$ is defined on a set $S$ if for every pair of elements $(a,b)$, $a,b \in S$, $a R b$ is either true or false. If $aRb$ is true, then we say that $a$ is related to $b$.

其次定义什么是 Equivalence Relation
- 自反性 Reflexive
- 对称性 Symmetric
- 传递性 Transitive

> An **equivalence relation** is a relation $R$ that satisfies three properties:
> 1. (Reflexive) $aRa$, for all $a \in S$.  
> 2. (Symmetric) $aRb$ if and only if $bRa$.  
> 3. (Transitive) $aRb$ and $bRc$ implies that $aRc$.

pseudo code 
```pseudo
class DisjointSet:
	func DisjointSet(n):
		parents = [1...n]
		ranks = [0...0] (n zeros)
		
	func Find(x):
		// path compression
		if x != parents[x]:
			parents[x] = Find(parents[x])
		return parents[x]
	
	func Union(x, y):
		px, py = Find(x), Find(y)
		// union by rank
		if ranks[px] > ranks[py]: parents[py] = px
		if ranks[px] < ranks[py]: parents[px] = py
		if ranks[px] == ranks[py]:
			parents[py] = px
			ranks[px]++
		
```

```cpp
#include <vector>

using namespace std;

class DisjSets 
{
    public:
        explicit DisjSets( int numElements );

        int find( int x ) const;
        int find( int x );
        void unionSets( int root1, int root2 );
    
    private:
        vector<int> s;
};

/**
 * @brief Construct the disjoint sets object
 * @param numElements the initial number of disjoint sets  
 */
DisjSets::DisjSets( int numElements ) : s{ numElements, -1 }
{
}

/**
 * @brief Perform a find.
 * Error checks omitted again for simplicity. 
 * 
 * @param x 
 * @return int the set containing x.
 */

int DisjSets::find ( int x ) const
{
    if ( s[ x ] < 0 ) 
        return x;
    else
        return find( s[ x ] );
}

/**
 * @brief Union two disjoint sets. 
 * For simplicity, we assume root1 and root2 are distinct and represent set names. 
 * 
 * @param root1 the root of set 1
 * @param root2 the root of set 2
 */
void DisjSets::unionSets( int root1, int root2 ) 
{
    // simple
    // s[ root2 ] = root1;
    
    // union-by-height
    if ( s[ root2 ] < s[ root1 ] )  // root2 is deeper
        s[ root1 ] = root2;         // make root2 new root
    else
    {
        if ( s[ root1 ] == s[ root2 ] )
            --s[ root1 ];           // update height if same
        s[ root2 ] = root1;         // make root1 new root
    }
}

#include <iostream>
#include <bitset>

int main () {
    int mask = 79;
    cout << std::bitset<32>(mask) << endl;
    cout << std::bitset<32>(~mask) << endl;
    return 0;
}
```
# Intro
并查集(Union find algorithm)用于处理不相交集(Disjoint sets)的查询find和合并merge的问题。
并查集只能回答**是否联通**的问题，无法回答具体的联通路径是什么。要想找到具体的联通路径，需要借助其他算法，如BFS。

并查集定义了两种操作：
- find 确定元素属于哪一个子集
- union将两个子集合并成一个集合

如何表示集合？一种常用的策略是为每个集合选定一个固定的元素，称为代表，以表示整个集合。所以：
- Find(x) 返回 x 所属集合的代表，
- Union 使用两个集合的代表作为参数进行合并。
- 初始时，每个元素的代表都是自己本身。

## find
```python
# iterative
def find(self, x):
    while x != self.parent[x]:
        x = self.parent[x]
    return x

#recursive
def find(self, x):
    if x != self.parent[x]:
        self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    return x
```

递归实现的 find 过程进行了路径的压缩，每次往上查找之后都会将树的高度降低到 2。
路径压缩的用处：每次 find 都会从当前节点往上不断搜索，直到到达根节点，因此 find 的时间复杂度大致相等于节点的深度，树的高度如果不加控制则可能为节点数，因此 find 的时间复杂度可能会退化到 $O(n)$。而如果进行路径压缩，那么树的平均高度不会超过 $logn$，如果使用了路径压缩和下面要讲的**按秩合并**，那么时间复杂度可以趋近 $O(1)$。极限情况下，每一个路径都会被压缩，这种情况下**继续**查找的时间复杂度就是 $O(1)$。
![[disjoint_sets_find.jpeg]]


## connected
如果两个节点的祖先相同，那么其就联通。
```python
def connected(self, p, q):
    return self.find(p) == self.find(q)
```

## union
![[disjoint_sets_union.gif]]
如果我们将 0 和 7 进行一次合并。即 `union(0, 7)` ，则会发生如下过程。
-   找到 0 的根节点 3, 在find的过程中发生路径压缩
-   找到 7 的根节点 6
-   将 6 指向 3。（为了使得合并之后的树尽可能平衡，一般选择将小树挂载到大树上面，下面的代码模板会体现这一点。3 的秩比 6 的秩大，这样更利于树的平衡，避免出现极端的情况）

这里的“小树挂大树”就是**按秩合并**。

```python
def union(self, p, q):
    if self.connected(p, q): return
    self.parent[self.find(p)] = self.find(q)
```
这里我并没有判断秩的大小关系，目的是方便理清主脉络。完整代码见下。

# 代码模板
## 不带权并查集
```python
class UF:
    def __init__(self, M):
        self.parent = {}
        self.size = {}
        self.cnt = 0
        # 初始化 parent，size 和 cnt
        # size 是一个哈希表，记录每一个联通域的大小，其中 key 是联通域的根，value 是联通域的大小
        # cnt 是整数，表示一共有多少个联通域
        for i in range(M):
            self.parent[i] = i
            self.cnt += 1
            self.size[i] = 1

    def find(self, x):
        if x != self.parent[x]:
            self.parent[x] = self.find(self.parent[x])
            return self.parent[x]
        return x
    def union(self, p, q):
        if self.connected(p, q): return
        # 小的树挂到大的树上， 使树尽量平衡
        leader_p = self.find(p)
        leader_q = self.find(q)
        if self.size[leader_p] < self.size[leader_q]:
            self.parent[leader_p] = leader_q
            self.size[leader_q] += self.size[leader_p]
        else:
            self.parent[leader_q] = leader_p
            self.size[leader_p] += self.size[leader_q]
        self.cnt -= 1
    def connected(self, p, q):
        return self.find(p) == self.find(q)
```
-   [547. 朋友圈](https://github.com/azl397985856/leetcode/blob/master/problems/547.friend-circles.md)
-   [721. 账户合并](https://leetcode-cn.com/problems/accounts-merge/solution/mo-ban-ti-bing-cha-ji-python3-by-fe-lucifer-3/)
-   [990. 等式方程的可满足性](https://github.com/azl397985856/leetcode/issues/304)
-   [1202. 交换字符串中的元素](https://leetcode-cn.com/problems/smallest-string-with-swaps/)
## 带权并查集
上面讲到的其实都是有向无权图，因此仅仅使用 parent 表示节点关系就可以了。而如果使用的是有向带权图呢？实际上除了维护 parent 这样的节点指向关系，我们还需要维护节点的权重，一个简单的想法是使用另外一个哈希表 weight 存储节点的权重关系。比如 `weight[a] = 1 表示 a 到其父节点的权重是 1`。

如果是带权的并查集，其查询过程的路径压缩以及合并过程会略有不同，因为我们不仅关心节点指向的变更，也关心权重如何更新。比如：
```
a    b
^    ^
|    |
|    |
x    y
```
如上表示的是 x 的父节点是 a，y 的父节点是 b，现在我需要将 x 和 y 进行合并。

```
a    b
^    ^
|    |
|    |
x -> y
```

假设 x 到 a 的权重是 w(xa)，y 到 b 的权重为 w(yb)，x 到 y 的权重是 w(xy)。合并之后会变成如图的样子：

```
a -> b
^    ^
|    |
|    |
x    y
```

那么 a 到 b 的权重应该被更新为什么呢？我们知道 w(xa) + w(ab) = w(xy) + w(yb)，也就是说 a 到 b 的权重 w(ab) = w(xy) + w(yb) - w(xa)。

当然上面关系式是加法，减法，取模还是乘法，除法等完全由题目决定，我这里只是举了一个例子。不管怎么样，这种运算一定需要满足**可传导性**。

以加法型带权并查集为例：
```python
class UF:
    def __init__(self, M):
        # 初始化 parent，weight
        self.parent = {}
        self.weight = {}
        for i in range(M):
            self.parent[i] = i
            self.weight[i] = 0

   def find(self, x):
        if self.parent[x] != x:
            ancestor, w = self.find(self.parent[x])
            self.parent[x] = ancestor
            self.weight[x] += w
        return self.parent[x], self.weight[x]
    def union(self, p, q, dist):
        if self.connected(p, q): return
        leader_p, w_p = self.find(p)
        leader_q, w_q = self.find(q)
        self.parent[leader_p] = leader_q
        self.weight[leader_p] = dist + w_q - w_p
    def connected(self, p, q):
        return self.find(p)[0] == self.find(q)[0]
```

-   [399. 除法求值](https://leetcode-cn.com/problems/evaluate-division/)
-   [1697. 检查边长度限制的路径是否存在](https://leetcode-cn.com/problems/checking-existence-of-edge-length-limited-paths/)
# complexity analysis
令 n 为图中点的个数。

首先分析空间复杂度。空间上，由于我们需要存储 parent （带权并查集还有 weight） ，因此空间复杂度取决于于图中的点的个数， 空间复杂度不难得出为 $O(n)$。

并查集的时间消耗主要是 union 和 find 操作，路径压缩和按秩合并优化后的时间复杂度接近于 O(1)。更加严谨的表达是 O(log(m×Alpha(n)))，n 为合并的次数， m 为查找的次数，这里 Alpha 是 Ackerman 函数的某个反函数。但如果只有路径压缩或者只有按秩合并，两者时间复杂度为 O(logx)和 O(logy)，x 和 y 分别为合并与查找的次数。

# Application
-   检测图是否有环

思路： 只需要将边进行合并，并在合并之前判断是否已经联通即可，如果合并之前已经联通说明存在环。

代码：
```python
uf = UF()
for a, b in edges:
    if uf.connected(a, b): return False
    uf.union(a, b)
return True
```
题目推荐：

-   [684. 冗余连接](https://leetcode-cn.com/problems/redundant-connection/solution/bing-cha-ji-mo-ban-ben-zhi-jiu-shi-jian-0wz2m/)
-   [Forest Detection](https://binarysearch.com/problems/Forest-Detection)
-   最小生成树经典算法 Kruskal