---
cssclass: img-grid
---
# Def
数组和链表在物理存储上的不同：
- 数组：内存空间是连续的，通常每个元素的大小固定，可以按index随机访问
- 链表：物理存储单元上非连续、非顺序。数组元素的逻辑顺序由链表的指针链接次序实现。

链表由一系列结点（链表中每一个元素称为结点）组成，结点可以在运行时动态生成。**链表适合在数据需要有一定顺序，但是又需要进行频繁增删除的场景**。常用逻辑结构来表示。
```cpp
Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

> 链表是一种递归的数据结构，因此采用递归的思想去考虑往往事半功倍，
# 分类
1. 按照指针个数分：
- 单链表 singly linked list
- 双向链表 doubly linked list
STL list就是一个双向链表。双向链表的好处在于删除和插入的时候，可以更快地找到前驱指针。如果用单链表的话， 那么时间复杂度最坏的情况是 `O(N)`。双向链表的本质就是**空间换时间**，因此如果题目对时间有要求，可以考虑使用双向链表，如146. LRU Cache

2. 按是否循环分：
- 循环链表
- 非循环链表
当我们需要在遍历到尾部之后重新开始遍历的时候，可以考虑使用循环链表。 需要注意的是，如果链表长度始终不变，那么使用循环链表很容易造成死循环，因此循环链表经常会伴随着节点的删除操作，比如[约瑟夫环问题](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/tong-su-yi-dong-mo-yun-suan-mo-ni-python3-by-azl39/)。

# 基本概念
## 虚拟节点
定义：数据结构中，在链表的第一个结点之前附设一个结点，它没有直接前驱，称之为虚拟结点。虚拟结点的数据域可以不存储任何信息，虚拟结点的指针域存储指向第一个结点的指针。
```cpp
ListNode dummy(0);
dummy.next = head;
ListNode *prev = &dummy;
```
作用：对链表进行增删时统一算法逻辑，减少边界处理（避免了判断是否是空表或者是增删的节点是否为第一个节点)。在head node可能发生变化的时候很有用

## 尾节点
定义：数据结构中，尾结点是指链表中最后一个节点，即存储最后一个元素的节点。

作用：由于移动到链表末尾需要线性的时间，因此在链表末尾插入元素会很耗时， 增加尾节点便于在链表末尾以 `O(1)` 的时间插入元素。

### 静态链表
定义：用数组描述的链表，它的内存空间是连续的，称为静态链表。相对地，动态链表因为是动态申请内存的，所以每个节点的物理地址可以不连续，要通过指针来顺序访问。

作用：既可以像数组一样在 O(1）的时间对访问任意元素，又可以像链表一样在 O(1)的时间对节点进行增删

> 静态链表和动态链表这个知识点对刷题帮助不大， 作为了解即可。

# 基本操作
插入
删除
遍历

# 解题套路
## 一个原则 
画图
## 两个考点
### 指针的修改
指针修改最典型的就是链表反转。
反转任意一段链表， 其中 head 指的是需要反转的头节点，tail 是需要反转的尾节点， terminal是tail后面的节点
```cpp
class Solution:  
 # 翻转一个子链表，并且返回新的头与尾  
 def reverse(self, head: ListNode, tail: ListNode, terminal:ListNode):  
	 cur = head  
	 pre = None  
	 while cur != terminal:  
		 next = cur.next   
		 cur.next = pre  
		 pre = cur  
		 cur = next  
     # 返回反转后的新的头尾节点  
	 return tail, head
```
### 链表的拼接
链表的价值就在于其不必要求物理内存的连续性，以及对插入和删除的友好。因此链表的题目很多拼接的操作。

## 三个注意
链表最容易出的错:
-   出现了环，造成死循环。
-   分不清边界，导致边界条件出错。
-   搞不懂递归怎么做
### 环
先画图，然后对指针的操作都反应在图中。仅仅画出一个子结构就可以。
### 边界
一个考虑边界的技巧就是看题目信息。
- 如果题目的头节点可能被移除，那么考虑使用虚拟节点，这样「头节点就变成了中间节点」，就不需要为头节点做特殊判断了。
- 题目让你返回的不是原本的头节点，而是尾部节点或者其他中间节点，这个时候要注意指针的变化。

见[[#虚拟头]]
### 前后序 - 递归
链表结构天生具有递归性，那么使用递归的解法或者递归的思维都会对我们解题有帮助。绝大多数的题目都是单链表，而单链表只有一个后继指针。因此只有前序和后序，没有中序遍历。
- 如果是前序遍历，那么你可以想象前面的链表都处理好了，怎么处理的不用管
- 如果是后续遍历，那么你可以想象后面的链表都处理好了，怎么处理的不用管

考虑反转链表的问题：
#### 前序遍历
前序遍历的时候，我们应该画这个图。只看中间的框（子结构）就行了，同时注意两点。
1.  前面的已经处理好了
2.  后面的还没处理好
![[list-preorder.jpg]]

```python
def dfs(head, pre):  
	if not head: return pre  
	# 留下联系方式（由于后面的都没处理，因此可以通过 head.next 定位到下一个）  
	next = head.next  
	# 主逻辑（改变指针）在进入后面节点的前面（由于前面的都已经处理好了，因此不会有环）  
	head.next = pre  
	dfs(next, head)  
  
dfs(head, None)
````
值得注意的是，**前序遍历很容易改造成迭代，因此推荐大家使用前序遍历**。准确地说应该是**前序遍历容易改成不需要栈的递归，而后续遍历需要借助栈来完成**。因为后续遍历的主逻辑在函数调用栈的弹出过程，而前序遍历则不需要。
![[list-pre-iter-compare.jpg]]
#### 后续遍历
![[list-postorder.jpg]]
通过 head.next 拿到下一个元素，然后将下一个元素的 next 指向自身来完成反转。
![[list-postorder2.jpg]]
画出图之后，是不是很容易看出图中有一个环？ 现在知道画图的好处了吧？就是这么直观，当你很熟练了，就不需要画了，但是在此之前，请不要偷懒。
因此我们需要将 head.next 改为不会造成环的一个值，比如置空。
![[list-postorder3.jpg]]
```python
def dfs(head):
    if not head or not head.next: return head
    # 不需要留联系方式了，因为我们后面已经走过了，不需走了，现在我们要回去了。
    res = dfs(head.next)
    # 主逻辑（改变指针）在进入后面的节点的后面，也就是递归返回的过程会执行到
    head.next.next = head
    # 置空，防止环的产生
    head.next = None

    return res
```
## 四个技巧
### 虚拟头
-   将头节点变成中间节点，简化判断。
	-   头节点是最常见的边界，那如果**用一个虚拟头指向头节点，虚拟头就是新的头节点了，而虚拟头不是题目给的节点，不参与运算，因此不需要特殊判断**。
-   通过在合适的时候断开链接，返回链表的中间节点。
	-   题目需要返回链表中间的某个节点时：新建一个虚拟头，然后让虚拟头在恰当的时候（刚好指向需要返回的节点）断开连接，返回虚拟头的 next. [[25. Reverse Nodes in k-Group]]
二叉树等也经常用到这个技巧。 比如题目要求返回二叉树的最左下方的节点。新建一个虚拟节点，虚拟节点 next 指向当前节点，并跟着一起走，在递归到最左下的时候断开链接，最后返回虚拟节点的 next 指针即可。
### 快慢指针
应用:
- 判断链表是否有环
- 求环的入口
- 求链表的交点

本质是因为链表不支持随机访问， 因此如果想要获取中间、倒数第几项等特定元素就需要一些特殊的手段->快慢指针
- 找链表中间项: 两个指针，一个大步走（一次走两步），一个小步走（一次走一步），这样快指针走到头，慢指针刚好在中间
- 求链表倒数第 2 个: 让快指针先走一步，慢指针再走，这样快指针走到头，慢指针刚好在倒数第二个
[[141. Linked List Cycle]]
[[142. Linked List Cycle II]]
### 穿针引线
这个方法通常不是最优解，但是好理解，方便书写，不易出错，推荐新手用。
继续反转链表， 假设链表已经反转好[[#指针的修改]]，如何拼回去？
![[list-reverse.jpg]]![[list-reverse2.jpg]]
从左到右给断点编号，2个断点，共有4个节点a，b，c，d。
先找到它们，然后连接`a.next = c`, `b.next = d`

### 先穿再排后判空

# 常见题型
## 题型一：反转链表
1.  反转链表
2.  在 O(n) 时间, O(1) 空间复杂度下逆序读取链表的某个值
3.  将链表按 K 个一组进行反转 [[24. Swap Nodes in Pairs]]
```cpp
ListNode *prev = nullptr, *curr = head, *next;
while(curr){
	next = curr->next;
	curr->next = prev;
	prev = curr;
	curr = next;
}
```
T: $O(N)$
S: $O(1)$
## 题型二：合并链表
1.  将两条有序或无序的链表合并成一条有序链表
2.  将 k 条有序链表合并成一条有序链表

## 题型三：相交或环形链表
### 1.  判断某条链表是否存在环
环形链表求环的起点.
**Solution 1 Hash**
-   遍历整个链表,同时将每个节点都插入哈希表,
-   如果当前节点在哈希表中不存在,继续遍历,
-   如果存在,那么当前节点就是环的入口节点
```cpp
ListNode *detectCycle(ListNode *head){
	unordered_map<ListNode*, int> m;
	while(head){
		if(m.count(head))
			return head;
		m[head] = head->val;
		head = head->next;
	}
	return nullptr;
}
```
T: $O(N)$
S: $O(N)$
**Solution 2 Fast and Slow Pointers**
- 定义一个 fast 指针,每次前进两步,一个 slow 指针,每次前进一步
- 当两个指针相遇时:
	- 将 fast 指针指向链表头部,同时 fast 指针每次只前进一步
	- slow 指针继续前进,每次前进一步
- 当两个指针再次相遇时,当前节点就是环的入口

为什么第二次相遇的点为环的入口?
![[linked_list_ring.png | +side -lg]]
E点为环的入口，P点为两指针第一次相遇点。从head到E的距离为a，从E到P的距离为b，环的周长为L。
第一次相遇时：
- 快指针移动的距离为：$s_1 = a+b+n_1*L$. $n_1$为快指针绕环圈数
- 慢指针移动的距离为：$s_2 = a+b+n_2*L$. $n_2$为慢指针绕环圈数
- 快指针是慢指针速度的两倍: $s_1 = 2s_2$
- 解得$a+b=(n_1-2n_2)L$
- 注意此时慢指针在环上的位置是$b$, i.e., P点
第一次相遇后，快指针重置到head，当快指针到达E点时，
- 快指针移动的距离为 $a$
- 由于两指针速度相同，慢指针也移动了$a$，所以在环上的位置是$b+a=(n_1-2n_2)L$，即在环的起点E
- 两指针又相遇了
```cpp
ListNode *detectCycle(ListNode *head) {
	if(!head || !head->next) return nullptr;
	ListNode *fast = head, *slow = head;
	do{
		if(fast && fast->next)
			fast = fast->next->next;
		else
			fast = nullptr;
		slow = slow->next;
	} while(fast != slow);
	// if fast and slow are null
	if(!fast) return nullptr;
	fast = head;
	while(fast != slow){
		fast = fast->next;
		slow = slow->next;     
	}
	return fast;
}
```
T: $O(N)$
S: $O(1)$
[[142. Linked List Cycle II]]
### 2.  获取某条链表环的大小
### 3.  获取某两条链表的相交节点
两个单链表A, B，找出它们相交的起始节点。
**Solution 1 Hash**
-   先遍历 A 链表, 并将 A 中的所有节点存入哈希表。
-   再遍历 B 链表,检查节点是否在哈希表中, 第一个存在的就是相交节点
```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	unordered_map<ListNode *, int> m;
	while(headA){
		m[headA] = headA->val;
		headA = headA->next;
	}

	while(headB){
		if(m.count(headB))
			return headB;
		headB = headB->next;
	}
	return nullptr;
}
```
T: $O(N)$
S: $O(N)$
**Solution 2 Two pointers**

例如使用 a, b 两个指针分别指向 A, B 这两条链表, 两个指针以相同的速度向后移动
![[list_intersect.png | +side -lg]]
-   当 a 到达链表的尾部时,重定位到链表 B 的头结点
-   当 b 到达链表的尾部时,重定位到链表 A 的头结点。
-   a, b 指针相遇的点为相交的起始节点，否则没有相交点 

为什么两个指针必然相交于p点？因为当两个指针第二次移动到交点p时，它们都走了A+B+C的距离。
```cpp
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if(!headA || !headB) return nullptr;
	ListNode *curA = headA, *curB = headB;
	while(curA != curB){
		curA = curA ? curA->next : headB;
		curB = curB ? curB->next : headA;
	}
	return curA;
}
```

为啥不是`curA = curA->next ? curA->next : headB;`?
![[list_parallel.png | +side -med]]
如果这样的话，那curA和curB就不会是nullptr。如此一来，如果两个链表不相交，那么就会`curA!=curB`永远成立，陷入死循环。实际上，使用nullptr相当于让两个链表必然相交，i.e., 相交的长度至少是1。这样就避免了讨论特殊情况。

T: $O(N)$
S: $O(1)$
[[160\. Intersection of Two Linked Lists]]
## 题型四：设计题
要求设计一种数据结构，可以在指定的时间或空间复杂度下完成 XX 操作，这种题目的套路就是**牢记所有基本数据结构的基本操作以及其复杂度**。分析算法的瓶颈，并辅以恰当的数据结构进行优化。

如[[146. LRU Cache]]

# 题目推荐
21. 合并两个有序链表
[[82. Remove Duplicates from Sorted List II]]
[[83. Remove Duplicates from Sorted List]]
86. 分隔链表
92. 反转链表 II
138. 复制带随机指针的链表
[[141. Linked List Cycle]]
[[142. Linked List Cycle II]]
143. 重排链表
148. 排序链表
206. 反转链表
234. 回文链表

反转列表:
[206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)  
[92. 反转链表 II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)  
[25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)
[206. 反转链表](https://leetcode-cn.com/problems/reverse-linked-list/)  
[92. 反转链表 II](https://leetcode-cn.com/problems/reverse-linked-list-ii/)  
[25. K 个一组翻转链表](https://leetcode-cn.com/problems/reverse-nodes-in-k-group/)

---
[^1]: https://mp.weixin.qq.com/s?__biz=MzI4MzUxNjI3OA==&mid=2247485582&idx=1&sn=eff845460e91be97026c937b229c2989&chksm=eb88c497dcff4d81e08ac30951b160f0083bc9fe5a2b64b8e1ea9e0988e14a9df2b56515f508&token=450700782&lang=zh_CN#rd