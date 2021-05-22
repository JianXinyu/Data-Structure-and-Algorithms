# Tree
Def: **directed edge**
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
具体算法上，我们可是使用 DFS 并记录当前访问层级的方式实现， 不过更多的时候还是使用借助队列的先进先出的特性来实现。
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
- zigzag
==implement 3 expression notations==

# 二叉树 Binary Trees
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
二叉树有一个经典的题型就是构造二叉树。注意单前/中/后序遍历是无法确定一棵树。但是中序序列和前、后，层次序列任意组合唯一确定一颗二叉树（前提是遍历是**基于引用**的或者二叉树的**值都不相同**）。前、后、层次序列都是提供根结点的信息，中序序列用来区分左右子树。

实际上构造一棵树的本质是：
1.  确定根节点
2.  确定其左子树
3.  确定其右子树

比如拿到前序遍历结果 preorder 和中序遍历 inorder，在 preorder 我们可以能确定树根 root，拿到 root 可以将中序遍历切割中左右子树。这样就可以确定并构造一棵树，整个过程我们可以用递归完成。详情见 [构建二叉树专题](https://github.com/azl397985856/leetcode/blob/master/selected/construct-binary-tree.md)
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

![image-20200704163048782](figures\image-20200704163048782.png)

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

     ​			Each node's balance factor: the difference between the heights of the node's two subtrees

     ![image-20200711091052011](.\figures\avl)

#### Single Rotation

​	--- newly-inserted nodes are ***outer*** nodes, since they appear on the outside edge of a subtree.

		- add a node to the left of the left subtree of a node
		- add a node to the right of the right subtree of a node

**Without child**

![image-20200711091430456](.\figures\image-20200711091430456.png)

1. decide which of 17's subtrees has the greater value. In this case, the left subtrees

2. take the left subtree and make it the root of the subtree that used to be rooted at 17

3. make the old root of the subtree, i.e., 17, the right child of the new subtree root, i.e., 8

   ![image-20200711092231893](.\figures\image-20200711092231893.png)

**With child**

Insert 2 to the tree

![image-20200711093804127](.\figures\image-20200711093804127.png)

the new subtree root (4) *already has* a child node on its right: the 5 node.

![image-20200711095833215](.\figures\image-20200711095833215.png)

the right child(5) of the new subtree root(4) becomes the left subchild of the old subtree root(6)



#### Double rotation

Insert an ***inner*** node, that is, the right child of a left node or the left child of a right node

![image-20200711110113460](.\figures\image-20200711110113460.png)

If we follow the single rotation rules, we will end up grafting the new node onto a node (which used to be the pre-rotation subtree root) at the same depth in the subtree. A left-right node becomes a right-left node, but it remains an inner node at the same depth!

![drsr](A:\MUN\Course\2020Spring\Data Structures\ENGI-4892-Data-Structure-and-Algorithms\Notes\figures\class.md)

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

递归中可能存在这么多的重复计算，为了消除这种重复计算，一种简单的方式就是记忆化递归。即一边递归一边使用“记录表”（比如哈希表或者数组）记录我们已经计算过的情况，当下次再次碰到的时候，如果之前已经计算了，那么直接返回即可，这样就避免了重复计算。而**动态规划中 DP 数组其实和这里“记录表”的作用是一样的**。

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





