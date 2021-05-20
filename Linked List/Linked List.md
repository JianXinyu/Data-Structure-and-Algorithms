
# 链表 Linked List
## Def
数组和链表在物理存储上的不同：
- 数组：内存空间是连续的，通常每个元素的大小固定，可以按index随机访问
- 链表：物理存储单元上非连续、非顺序。数组元素的逻辑顺序由链表的指针链接次序实现。

链表由一系列结点（链表中每一个元素称为结点）组成，结点可以在运行时动态生成。链表适合在数据需要有一定顺序，但是又需要进行频繁增删除的场景。常用逻辑结构来表示。
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
## 分类
1. 按照指针个数分：
- 单链表 singly linked list
- 双向链表 doubly linked list
STL list就是一个双向链表。双向链表的好处在于删除和插入的时候，可以更快地找到前驱指针。如果用单链表的话， 那么时间复杂度最坏的情况是 `O(N)`。双向链表的本质就是**空间换时间**，因此如果题目对时间有要求，可以考虑使用双向链表，如146. LRU Cache

2. 按是否循环分：
- 循环链表
- 非循环链表
当我们需要在遍历到尾部之后重新开始遍历的时候，可以考虑使用循环链表。 需要注意的是，如果链表长度始终不变，那么使用循环链表很容易造成死循环，因此循环链表经常会伴随着节点的删除操作，比如[约瑟夫环问题](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/tong-su-yi-dong-mo-yun-suan-mo-ni-python3-by-azl39/)。

## 基本概念
### 虚拟节点
定义：数据结构中，在链表的第一个结点之前附设一个结点，它没有直接前驱，称之为虚拟结点。虚拟结点的数据域可以不存储任何信息，虚拟结点的指针域存储指向第一个结点的指针。
```cpp
ListNode dummy(0);
dummy.next = head;
ListNode *prev = &dummy;
```
作用：对链表进行增删时统一算法逻辑，减少边界处理（避免了判断是否是空表或者是增删的节点是否为第一个节点)。在head node可能发生变化的时候很有用

### 尾节点
定义：数据结构中，尾结点是指链表中最后一个节点，即存储最后一个元素的节点。

作用：由于移动到链表末尾需要线性的时间，因此在链表末尾插入元素会很耗时， 增加尾节点便于在链表末尾以 `O(1)` 的时间插入元素。

### 静态链表
定义：用数组描述的链表，它的内存空间是连续的，称为静态链表。相对地，动态链表因为是动态申请内存的，所以每个节点的物理地址可以不连续，要通过指针来顺序访问。

作用：既可以像数组一样在 O(1）的时间对访问任意元素，又可以像链表一样在 O(1)的时间对节点进行增删

> 静态链表和动态链表这个知识点对刷题帮助不大， 作为了解即可。

## 基本操作
插入
删除
遍历

## 常见题型
### 题型一：反转链表
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

### 题型二：合并链表
1.  将两条有序或无序的链表合并成一条有序链表
2.  将 k 条有序链表合并成一条有序链表

### 题型三：相交或环形链表
#### 1.  判断某条链表是否存在环
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
#### 2.  获取某条链表环的大小
#### 3.  获取某两条链表的相交节点
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
### 题型四：设计题
要求设计一种数据结构，可以在指定的时间或空间复杂度下完成 XX 操作，这种题目的套路就是**牢记所有基本数据结构的基本操作以及其复杂度**。分析算法的瓶颈，并辅以恰当的数据结构进行优化。
