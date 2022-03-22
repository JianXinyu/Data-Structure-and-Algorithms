
# Tree
Def: recursive definition. **directed edge**
root, edge, parent/child, leaves, siblings, path/length
**Depth**: length of the path from the tree's root to the node
**Height**: longest length of the path  from the node to a leaf.
The height of a tree, or the depth of the tree, is the height of its root.
 ancestor/descendant, proper ancestor/proper descendant

**Balanced**: if the heights of each node's subtrees are equal, or at least close, we call  the tree balanced.  A balanced tree has **logarithmic height**: the length of the path from the root to any node in the tree is $O(log n)$.

# Traversal
## 前序遍历 Preorder Traversal
work at a node is performed before (pre) its children are processed. e.g.:
	- list a directory
	- prefix notation
	
![[preorder-traversal.gif | +side -lg]]
针对二叉树, 前序遍历的顺序
1.  访问当前节点
2.  遍历左子树
3.  遍历右子树

```cpp
preorder(root) {  
	if not root: return  
	doSomething(root)  
	preorder(root.left)  
	preorder(root.right)  
}
```

```c++
function<void(TreeNode*, int)> dfs = [&](TreeNode* r, int d){
    if(!r) return;
    /* functional code according to question  */
    dfs(r->right, d+1);
    dfs(r->left, d+1);
};
dfs(root, 0);
```
## 中序遍历 Inorder Traversal 
first traverse its left subtree recursively, then visit the node in question, then traverse its right subtree recursively
	- infix notation 

![[inorder-traversal.gif | +side -lg]]
针对二叉树，中序遍历的顺序
1.  遍历左子树
2.  访问当前节点
3.  遍历右子树
```cpp
inorder(root) {  
	if not root: return  
	inorder(root.left)  
	doSomething(root)  
	inorder(root.right)  
}
```

## 后序遍历 Postorder Traversal
work at a node is performed after (post) its children are evaluated. e.g.:
	- calculate the size of a directory
	- postfix notation
![[postorder-traversal.gif | +side -lg]]
针对二叉树，后序遍历的顺序
1.  遍历左子树
2.  遍历右子树
3.  访问当前节点
```cpp
postorder(root) {  
	if not root: return  
	postorder(root.left)  
	postorder(root.right)  
	dosomething(root)
}
```

## 层次遍历 Level Order Traversal
![[level-order-traversal.gif | +side -lg]]
层次遍历是逐级遍历树，每一层从左往右依次遍历结点。广度优先搜索（Breadth-First Search）是一种遍历或搜索数据结构（如树或图）的算法。该算法从根节点开始，并首先访问该节点本身。然后遍历其邻居，遍历其第二级邻居，遍历其第三级邻居，依此类推。
具体算法上，可使用 DFS 并记录当前访问层级的方式实现，不过更多的时候还是使用借助队列的先进先出的特性来实现。
<br>
```cpp
bfs(root) {
	queue = []
	queue.push(root)
	while queue.length {
		curLevel = queue
		queue = []
		for i = 0 to curLevel.length {
			doSomething(curLevel[i])
			if (curLevel[i].left) {
				queue.push(curLevel[i].left)
			}
			if (curLevel[i].right) {
				queue.push(curLevel[i].right)
			}
		}
	}
}
```

```cpp
void bfs(TreeNode *root) {
	
}
```

## Zigzag
from left to right, then right to left for the next level and alternate between
也就是按层数的奇偶来决定每一层的输出顺序。规定二叉树的根节点为第 0 层，如果当前层数是偶数，从左至右输出当前层的节点值，否则，从右至左输出当前层的节点值。
[[103. Binary Tree Zigzag Level Order Traversal]]


Others: 
- Vertical Order Traversal [[987. Vertical Order Traversal of a Binary Tree]]


# 二叉树 Binary Trees
## Intro
Def
For a binary tree with $N$ nodes
- ==why?==Average depth $O(\sqrt N)$, worst depth $N-1$
- binary search tree, a special type of binary tree, has the average depth $O(logN)$

==why?==every binary tree with $N$ nodes would require $N+1$ `nullptr` links?

二叉树去掉一个子节点就是链表， 增加环就是图，熟悉二叉树是基础。

分类:
-   完全二叉树
-   满二叉树
-   二叉搜索树
-   [平衡二叉树](https://github.com/azl397985856/leetcode/blob/master/thinkings/balanced-tree.md)
-   红黑树
- etc

## 二叉树构建 TBD
二叉树有一个经典的题型就是构造二叉树。**注意单是前/中/后序遍历无法确定一棵树**。但是中序序列和前、后，层次序列任意组合可以唯一确定一颗二叉树（前提是遍历是**基于引用**的或者二叉树的**值都不相同**）。前、后、层次序列都是提供根结点的信息，中序序列用来区分左右子树。

实际上构造一棵树的本质是(递归定义)：
1.  确定根节点
2.  确定其左子树
3.  确定其右子树

- preorder+inorder [[105. Construct Binary Tree from Preorder and Inorder Traversal]] 用preorder得到结果， 我们可以能确定树根 root，拿到 root 可以将中序遍历切割中左右子树。这样就可以递归构造一棵树。


## 二叉树遍历
[二叉树的遍历](https://leetcode-solution-leetcode-pp.gitbook.io/leetcode-solution/thinkings/binary-tree-traversal)
## 二叉搜索树 Binary Search Tree
Visualization: https://visualgo.net/en/bst
二叉搜索树是二叉树的一种，具有以下性质
1.  左子树的所有节点值小于根的节点值（注意不含等号）
2.  右子树的所有节点值大于根的节点值（注意不含等号）

另外二叉搜索树的中序遍历结果是一个有序列表，这个性质很有用。比如 1008. 前序遍历构造二叉搜索树。根据先序遍历构建对应的二叉搜索树，由于二叉树的中序遍历是一个有序列表，我们可以有以下思路：1.  对先序遍历结果排序，排序结果是中序遍历结果；2.  根据先序遍历和中序遍历确定一棵树。原问题就又转换为了二叉树构建
1. **search**: since sorted, search faster than linearly. there are no false starts and the maximum number of recursions is equal to the height of the tree, which in a balanced tree is $O(logn)$.

![[bst.png]]

   Find 24: 

```C++
if this == null
   return null
else if this key == search value
   return this
else if this key < search value
   search right
else search left
```

2. **Finding** the minimum or maximum value: straight forward, just keep following left or right

3. **insertion**:  
   1. start from root, compare the new value to the current node's value 
   2. if less than the node value, insert on the left
   3. if bigger than the node value, insert on the right
   4. if equal, increment a counter in the node, add the new value to a linked list hung off the node or (in some cases) simply ignore the new value
      
  - adding to an empty tree is a matter of creating a new node and setting the subtree’s "root" to point at it.
  - in a balanced tree, insertion takes logarithmic time. However, insertion may cause the tree to become less balanced.

![[avl_insertion.png]]

```c++
if insertion point is found
	creat new vertex
if value to be inserted < this key
	go left
else go right
```

4. **Removal**
   1. find the node by recursive descent



### Adelson–Velsky–Landis (AVL) tree

a binary search tree that keeps itself balanced when you add or remove nodes. **Self-balanced**

Problem: BST works well when it is balanced, $O(log_2 n)$. adding or removing nodes will cause BST loses its balance. Worst case: degenerate into a linked list, $O(n)$.

Solution:  add one more constraint to keep the tree self-balanced.

- binary

   - each node's left subtree and right subtree are partitioned by the node's value

   - **New**: every node's height can differ in height by no more than one

     
Each node's balance factor: the difference between the heights of the node's two subtrees

 ![[avl.jpg]]

#### Single Rotation

- newly-inserted nodes are ***outer*** nodes, since they appear on the outside edge of a subtree.

	- add a node to the left of the left subtree of a node
	- add a node to the right of the right subtree of a node

**Without child**

![[avl_single_rot.png]]

1. decide which of 17's subtrees has the greater value. In this case, the left subtrees

2. take the left subtree and make it the root of the subtree that used to be rooted at 17

3. make the old root of the subtree, i.e., 17, the right child of the new subtree root, i.e., 8

   ![[avl_single_rot2.png]]

**With child**

Insert 2 to the tree

![[avl_single_rot3.png]]

the new subtree root (4) *already has* a child node on its right: the 5 node.

![[avl_single_rot4.png]]

the right child(5) of the new subtree root(4) becomes the left subchild of the old subtree root(6)



#### Double rotation

Insert an ***inner*** node, that is, the right child of a left node or the left child of a right node

![[avl_double_rot.png]]

If we follow the single rotation rules, we will end up grafting the new node onto a node (which used to be the pre-rotation subtree root) at the same depth in the subtree. A left-right node becomes a right-left node, but it remains an inner node at the same depth!


1. arrange for the subtree to be too deep in an outer node rather than an inner one through rotation.

   in this case, left rotation

   

2. rotate. in this case, right rotation


the **complexity** of performing this double-rebalancing in terms of the number of nodes in the tree:

## 堆 Heap TBD
在这里讲堆是因为堆可以被看作近似的完全二叉树。堆通常以数组形式的存储，而非上述的链式存储。

表示堆的数组 A 中，如果 A\[1\]为根节点，那么给定任意节点 i，其父子节点分别为
- 父亲节点：Math.floor(i / 2)
- 左子节点：2 * i
- 右子节点: 2 * i + 1
如果 A\[parent(i)\] ≥ A\[i\]，则称该堆为最大堆，如果 A\[parent(i)\] ≤ A\[i\]，称该堆为最小堆。

堆这个数据结构有很多应用，比如堆排序，TopK 问题，共享计算机系统的作业调度(优先队列)等。下面看下给定一个数据如何构建一个最大堆。

伪代码：
```cpp
// 自底向上建堆  
BUILD-MAX-HEAP(A)  
 A.heap-size = A.length  
 for i = Math.floor(A.length / 2) downto 1  
 MAX-HEAPIFY(A, i)  
  
// 维护最大堆的性质  
MAX-HEAPIFY(A, i)  
 l = LEFT(i)  
 r = RIGHT(i)  
 // 找到当前节点和左右儿子节点中最大的一个，并交换  
 if l <= A.heap-size and A\[l\] > A\[i\]  
 largest = l  
 else largest = i  
 if r <= A.heap-size and A\[r\] > A\[largest\]  
 largest = r  
 if largest != i  
 exchange A\[i\] with A\[largest\]  
 // 递归维护交换后的节点堆性质  
 MAX-HEAPIFY(A, largest)
```

关于堆的更多内容，请参考：

-   [几乎刷完了力扣所有的堆题，我发现了这些东西。。。 （上）](https://mp.weixin.qq.com/s?__biz=MzI4MzUxNjI3OA==&mid=2247486985&idx=1&sn=4c0275e5ef02e0b9b8e4e99ba57b58dc&chksm=eb88c210dcff4b062cf5d72d86733e7b0ec087adbc714e112db083c683161320e3dcbf1d87f7&token=450700782&lang=zh_CN#rd)
    
-   [几乎刷完了力扣所有的堆题，我发现了这些东西。。。（下）](https://mp.weixin.qq.com/s?__biz=MzI4MzUxNjI3OA==&mid=2247487374&idx=1&sn=821382621edcb1c8bdd7abbd50058ed7&chksm=eb88c397dcff4a8127fbeaca2d7aaea76d86910f411bce1a4a0d44f871f2be20237aef81a1f8&token=450700782&lang=zh_CN#rd)

## 递归 Recursion
二叉树是一种递归的数据结构， 是最能体现递归美感的结构之一，看到二叉树的题第一反应就应该是用递归去写。二叉树特别适合练习递归。

递归就是**方法或者函数调用自身的方式成为递归调用**。在这个过程中，调用称之为**递**，返回成为**归**。

算法中使用递归可以很简单地完成一些用循环实现的功能，比如二叉树的左中右序遍历。递归在算法中有非常广泛的使用，包括现在日趋流行的函数式编程。

有意义的递归算法会把问题分解成规模缩小的同类子问题，当子问题缩减到寻常的时候，就可以知道它的解。然后建立递归函数之间的联系即可解决原问题，这也是我们使用递归的意义。准确来说， 递归并不是算法，它是和迭代对应的一种编程方法。只不过，由于隐式地借助了函数调用栈，因此递归写起来更简单。

一个问题要使用递归来解决必须有递归终止条件（算法的有穷性）。

**递归三要素**
-   递归出口，问题最简单的情况
-   递归调用总是去尝试解决更小的问题，这样问题才会被收敛到最简单的情况
-   递归调用的父问题和子问题没有交集

递归中可能存在这么多的重复计算，为了消除这种重复计算，一种简单的方式就是记忆化递归。即一边递归一边使用“记录表”（比如哈希表或者数组）记录我们已经计算过的情况，当下次再次碰到的时候，如果之前已经计算了，那么直接返回即可，这样就避免了重复计算。而**动态规划中 DP 数组其实和这里“记录表”的作用是一样的**。

如何理解树的递归? 画图 + 手动代入
![[tree_recursion.jpg]]
练习递归:
平时试着把迭代改成递归
汉诺塔问题
fibonacci 数列
二叉树的前中后序遍历
归并排序
求阶乘
递归求和

## More
 相关专题
二叉树的最大路径和
给出所有路径和等于给定值的路径
最近公共祖先
各种遍历。前中后，层次，拉链式等。
-   [专题篇 - 搜索](https://algo91.herokuapp.com/topic-search.md)
-   [二叉树的遍历](https://github.com/azl397985856/leetcode/blob/master/thinkings/binary-tree-traversal.md)
-   [前缀树专题](https://github.com/azl397985856/leetcode/blob/master/thinkings/trie.md)

题目: 
-   [589\. N 叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)（熟悉 N 叉树）
-   [662\. 二叉树最大宽度](https://leetcode-cn.com/problems/maximum-width-of-binary-tree/) (请分别使用 BFS 和 DFS 解决，空间复杂度尽可能低)
-   [834\. 树中距离之和](https://leetcode-cn.com/problems/sum-of-distances-in-tree/description/)（谷歌面试题）
-   [967\. 连续差相同的数字](https://leetcode-cn.com/problems/numbers-with-same-consecutive-differences/description/) (隐形树的遍历)
-   [1145\. 二叉树着色游戏](https://leetcode-cn.com/problems/binary-tree-coloring-game/)（树上进行决策）
# 解题技巧 TBD
 [几乎刷完了力扣所有的树题，我发现了这些东西。。。](https://mp.weixin.qq.com/s?__biz=MzI4MzUxNjI3OA==&mid=2247485899&idx=1&sn=27d1c7b8ff88cbe235b7fca63227d356&chksm=eb88c5d2dcff4cc4102a036bc558b9c598fbf1c69f6ee9dc2822b0784975f8b2df8b8a7609dd&token=450700782&lang=zh_CN#rd) 。
 ## 一个中心 REVIEW
 不管是什么题目，核心就是树的遍历，这是一切的基础。
 树的遍历方法有很多[[#Traversal]]
 树的遍历可分为两个基本类型：深度优先遍历和广度优先遍历
 
**树的遍历的迭代写法**
使用双色标记法来统一前中后三种遍历，灵感来源于垃圾回收算法中的三色标记法。
-   使用颜色标记节点的状态，新节点为白色，已访问的节点为灰色。
-   如果遇到的节点为白色，则将其标记为灰色，然后将其右子节点、自身、左子节点依次入栈。
-   如果遇到的节点为灰色，则将节点的值输出。
```python
def inorderTraversal(self, root: TreeNode) -> List[int]:
	WHITE, GRAY = 0, 1
	res = []
	stack = [(WHITE, root)]
	while stack:
		color, node = stack.pop()
		if node is None: continue
		if color == WHITE:
			stack.append((WHITE, node.right))
			stack.append((GRAY, node))
			stack.append((WHITE, node.left))
		else:
			res.append(node.val)
	return res

#preorder
stack.append((GRAY, node))
stack.append((WHITE, node.right))
stack.append((WHITE, node.left))

#postorder
stack.append((WHITE, node.right))
stack.append((WHITE, node.left))
stack.append((GRAY, node))
```
实际上WHITE 就表示的是递归中的第一次进入过程，Gray 则表示递归中的从叶子节点返回的过程。 因此这种迭代的写法更接近递归写法的本质。

## 两个基本点
- 深度优先搜索 Depth First Search DFS 适合暴力枚举，借助函数调用栈，可用递归轻松实现DFS
	- Preorder
	- Inorder
	- Postorder
- 广度优先搜索 Breadth First Search BFS 适合求最短距离
	- 带层的
	- 不带层的
### 深度优先遍历
DFS算法是一种用于遍历树或图的算法。沿着树的深度遍历树的节点，尽可能深的搜索树的分支。当节点 v 的所在边都己被探寻过，搜索将回溯到发现节点 v 的那条边的起始节点。这一过程一直进行到已发现从源节点可达的所有节点为止。如果还存在未被发现的节点，则选择其中一个作为源节点并重复以上过程，整个进程反复进行直到所有节点都被访问为止，属于**盲目搜索**。DFS是图论中的经典算法，利用深度优先搜索算法可以产生目标图的相应拓扑排序表，利用拓扑排序表可以方便的解决很多相关的图论问题，如最大路径问题等等。因发明「深度优先搜索算法」，约翰 · 霍普克洛夫特与罗伯特 · 塔扬在 1986 年共同获得计算机领域的最高奖：图灵奖。

截止2020-02-21，深度优先遍历在 LeetCode 中的题目是 129 道。在 LeetCode 中的题型绝对是超级大户了。而对于树的题目，我们基本上都可以使用 DFS 来解决，甚至我们可以基于 DFS 来做层次遍历，而且由于 DFS 可以基于递归去做，因此算法会更简洁。 在对性能有很高要求的场合，我建议你使用迭代，否则尽量使用递归，不仅写起来简单快速，还不容易出错。

**算法流程**：
![[depth-first-search.gif | +side -med]]
1.  首先将根节点放入stack。
2.  从stack中取出第一个节点，并检验它是否为目标。如果找到所找的节点，则结束搜寻并回传结果。否则将它某一个尚未检验过的直接子节点加入stack中。
3.  重复步骤 2。
4.  如果不存在未检测过的直接子节点。将上一级节点加入stack中。
    重复步骤 2。
5.  重复步骤 4。
6.  若stack为空，表示整张图都检查过了——亦即图中没有欲搜寻的目标。结束搜寻并回传“找不到目标”。
这里的 stack 可以理解为自己实现的栈，也可以理解为调用栈。如果是调用栈的时候就是递归，如果是自己实现的栈的话就是迭代。

**算法模板**:
```javascript
const visited = {}
function dfs(i) {
    if (满足特定条件）{
        // 返回结果 or 退出搜索空间
    }

    visited[i] = true // 将当前状态标为已搜索
    for (根据i能到达的下个状态j) {
        if (!visited[j]) { // 如果状态j没有被搜索过
            dfs(j)
        }
    }
}
```
visited 是为了防止由于环的存在而导致死循环的。 而我们知道树是不存在环的，因此树的题目大多数不需要 visited，除非你对树的结构做了修改，比如就左子树的 left 指针指向自身，此时会有环。再比如 [138\. 复制带随机指针的链表](https://leetcode-cn.com/problems/copy-list-with-random-pointer/) 这道题需要记录已经复制的节点，这些需要记录 visited 信息的树的题目**少之又少**。

因此树当中的DFS更多是:
```javascript
function dfs(root) {
    if (满足特定条件）{
        // 返回结果 or 退出搜索空间
    }
    for (const child of root.children) {
        dfs(child)
    }
}
```
而几乎所有的题目几乎都是二叉树，因此下面这个模板更常见。
```javascript
function dfs(root) {
    if (满足特定条件）{
        // 返回结果 or 退出搜索空间
    }
    dfs(root.left)
    dfs(root.right)
}
```
不同的题目除了 if (满足特定条件)部分不同之外，还会写一些特有的逻辑，这些逻辑写的位置不同，效果也截然不同。

前序遍历和后序遍历是最常见的两种 DFS 方式。中序遍历一般用于平衡二叉树。
```javascript
// preorder
function dfs(root) {
    if (满足特定条件）{
        // 返回结果 or 退出搜索空间
    }
    // 主要逻辑
    dfs(root.left)
    dfs(root.right)
}
// postorder
function dfs(root) {
    if (满足特定条件）{
        // 返回结果 or 退出搜索空间
    }
    dfs(root.left)
    dfs(root.right)
    // 主要逻辑
}
```
有时候前后都有，关注主逻辑即可。
### 广度优先遍历
![[breadth-first-search.gif | +side -med]]
BFS 也是图论中算法的一种，不同于 DFS， BFS 采用横向搜索的方式，在数据结构上通常采用队列结构。 注意，DFS 我们借助的是栈来完成，而这里借助的是队列。BFS 比较适合找**最短距离/路径**和**某一个距离的目标**。比如"给定一个二叉树，在树的最后一行找到最左边的值。"，此题是力扣 513 的原题。这不就是求距离根节点**最远距离**的目标么？ 一个 BFS 模板就解决了。

**算法流程**
1.  首先将根节点放入队列中。
2.  从队列中取出第一个节点，并检验它是否为目标。
    -   如果找到目标，则结束搜索并回传结果。
    -   否则将它所有尚未检验过的直接子节点加入队列中。
3.  若队列为空，表示整张图都检查过了——亦即图中没有欲搜索的目标。结束搜索并回传“找不到目标”。
4.  重复步骤 2。
```javascript
const visited = {}
function bfs() {
    let q = new Queue()
    q.push(初始状态)
    while(q.length) {
        let i = q.pop()
        if (visited[i]) continue
        if (i 是我们要找的目标) return 结果
        for (i的可抵达状态j) {
            if (j 合法) {
                q.push(j)
            }
        }
    }
    return 没找到
}
```

BFS 比较适合找**最短距离/路径**和**某一个距离的目标**。根据题目，BFS主要有两类:
- 如果要求的是最短距离/路径，走到第几步的信息可以忽略。此时无需，这个时候可是用不标记层的目标
- 如果要求和某个节点的距离等于 k 的所有节点，需要记录第几步的信息

```python
// 标记层
def bfs(k):
	# 使用双端队列，而不是数组。因为数组从头部删除元素的时间复杂度为 N，双端队列的底层实现其实是链表。
	queue = collections.deque([root])
	# 记录层数
	steps = 0
	# 需要返回的节点
	ans = []
	# 队列不空，生命不止！
	while queue:
		size = len(queue)
		# 遍历当前层的所有节点
		for _ in range(size):
			node = queue.popleft()
			if (step == k) ans.append(node)
			if node.right:
				queue.append(node.right)
			if node.left:
				queue.append(node.left)
		# 遍历完当前层所有的节点后 steps + 1
		steps += 1
	return ans		
	
// 不标记层
def bfs(k):
	# 使用双端队列，而不是数组。因为数组从头部删除元素的时间复杂度为 N，双端队列的底层实现其实是链表。
	queue = collections.deque([root])
	# 队列不空，生命不止！
	while queue:
		node = queue.popleft()
		# 由于没有记录 steps，因此我们肯定是不需要根据层的信息去判断的。否则就用带层的模板了。
		if (node 是我们要找到的) return node
		if node.right:
			queue.append(node.right)
		if node.left:
			queue.append(node.left)
	return -1
```



层次遍历和 BFS 是**完全不一样**的东西。

层次遍历就是一层层遍历树，按照树的层次顺序进行访问。**BFS 的核心在于求最短问题时候可以提前终止，这才是它的核心价值，层次遍历是一种不需要提前终止的 BFS 的副产物**。这个提前终止不同于 DFS 的剪枝的提前终止，而是找到最近目标的提前终止。比如我要找距离最近的目标节点，BFS 找到目标节点就可以直接返回。而 DFS 要穷举所有可能才能找到最近的，这才是 BFS 的核心价值。实际上，我们也可以使用 DFS 实现层次遍历的效果，借助于递归，代码甚至会更简单。

> 如果找到任意一个满足条件的节点就好了，不必最近的，那么 DFS 和 BFS 没有太大差别。同时为了书写简单，我通常会选择 DFS

## 三种题型
搜索类的题目最多，其次是构建类，最后是修改类。
### 搜索类
搜索类只有两种解法: DFS, BFS。所有搜索类的题目只要把握三个核心点：**开始点**，**结束点** 和 **目标**。
#### DFS搜索
基本套路: 从入口开始做 dfs，然后在 dfs 内部判断是否是结束点，这个结束点通常是**叶子节点**或**空节点**[[#边界]]。返回值有两种情况：
- 基本值（比如数字）, 直接返回或者使用一个全局变量记录即可
- 数组, [[#参数扩展]]
```python
# 其中 path 是树的路径， 如果需要就带上，不需要就不带
def dfs(root, path):
    # 空节点
    if not root: return
    # 叶子节点
    if not root.left and not root.right: return
    path.append(root)
    # 逻辑可以写这里，此时是前序遍历
    dfs(root.left)
    dfs(root.right)
    # 需要弹出，不然会错误计算。
    # 比如对于如下树：
    """
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
    """
    # 如果不 pop，那么 5 -> 4 -> 11 -> 2 这条路径会变成 5 -> 4 -> 11 -> 7 -> 2，其 7 被错误地添加到了 path

    path.pop()
    # 逻辑也可以写这里，此时是后序遍历

    return 你想返回的数据
```

## 七个技巧
### 边界
### 参数扩展


# 8. Sets and Maps in the Standard Library

The STL containers vector and list are inefficient for searching.

Set and map, two other STL containers, guarantee logarithmic cost for insertion, deletion and searching. 

## Sets

A **set** is an ordered container that doesn't allow duplicates

### Maps

```c++
#include <memory>
template <typename K, typename V>
class Map
{
private:
	struct Entry
	{
		K key;
		V value;
	};
	BinarySearchTree<Entry, ComparatorBasedOnKey> map;
}
```





