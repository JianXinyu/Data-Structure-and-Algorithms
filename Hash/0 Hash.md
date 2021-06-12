# Intro
Hash Table一种在**平均时间复杂度** O(1) 内可实现**任何操作**的数据结构
- 查询
- 插入
- 删除
- 修改
需要注意的是这里描述的是平均时间复杂度，最坏的情况仍然有可能是线性的。

Hash的基本思想是**建立恰当大小值域的数组进行某种映射**。
```python
size = 10
hash_number = 0

for c in s:
	hash_number += ord(c)
	hash_number %= size
```
如上建立了一个大小为 10 的值域，值域的值分别是 0，1，2，3，4，5，6，7，8，9。接下来，我们对字符串逐个字符取 ASCII 码并相加模 10，模 10 可以确保值不会越界。**这就是一个最简单的 hash 思想**

散列表/哈希表（Hash table），是根据关键码值(Key)而直接进行访问的数据结构。散列表可以使用**数组 + 链表**的方式来实现，也可以用别的方式，比如**数组 + 红黑树**。

哈希表查询的精髓就在于**数组**，哈希表查找的平均时间复杂度 O(1) 就是因为这个。但是数组元素的删除和新增操作的平均时间复杂度是O(N)。哈希表删除和新增的精髓就在于**链表或者树**，哈希表修改和删除的平均时间复杂度 O(1)就是因为这个。

# 冲突
哈希查询的精髓在于数组，而数组的索引就是哈希表的 key。但哈希表可以存任意 string，而数组索引只能是数字，且数组的索引范围是 \[0, n)，其中 n 为数组长度。这怎么办呢？上哈希函数！输入是 key，返回值是索引，并且相同的 key 计算出的索引是确定不变的，也就是说哈希函数需要是数学中的函数。

而理论上两个不同的 key 是可以算出同样的 hashcode 的。这个就叫做哈希冲突。

哈希函数不是万能的，根据**抽屉原理**，除非你给一个容器足够大的抽屉（工程中不现实），否则不可避免的可能会造成两个不同的 Key 算出来的 hash 值相同，比如 hash 函数是 x % 3，这样 key=2 和 key=5 算出的 hash 值都为 2。一般有两种方法来处理，开放地址法和拉链法：
![[hash_conflict.jpg]]
另一个思路是避免冲突。


 [705\. 设计哈希集合](https://leetcode-cn.com/problems/design-hashset/solution/li-kou-jia-jia-zhe-jian-dan-ti-ting-fei-760d2/) 
 [706\. 设计哈希映射](https://leetcode-cn.com/problems/design-hashmap/solution/li-kou-jia-jia-zhe-ti-ye-ting-fei-mo-shu-s54w/)
 
 # 题目类型
 哈希表的一个重要作用就是空间换时间，当你想出暴力算法，可以考虑是否可用哈希表来优化。哈希表优化时间复杂度算是最最简单的一种优化手段了。相比单调栈，二分等简单很多。
 ## 统计
 统计 xx 出现次数/频率
 若已知数据范围较小且比较连续，也可以用数组来实现
 -   [811.子域名访问计数](https://leetcode-cn.com/problems/subdomain-visit-count/description/)

## 设计题
需要查找/增加/删除操作为 O(1)时间复杂度。
见到这种要求的题可以考虑一下是否需要 hash 表来做，比如 LRU，LFU 之类的题，题目中要求了时间复杂度，就是用 hash 表+双向链表解决的。
[[146. LRU Cache]]
## 图相关（比如并查集）
这样可能需要构建有向图/无向图，这时可以用 hash 表来表示图并进行后续操作。

## 空间换时间
需要存储之前的状态以减少计算开销
[[1. Two Sum]]

记忆化搜索，该方法就利用 hash 表来存储历史状态，这样可以大大减少重复计算。
-   状态压缩（本质就是 bit 上的哈希结构）。参考 [状压 DP 是什么？这篇题解带你入门](https://mp.weixin.qq.com/s/ecxTTrRvUJbdWwSFbKgDiw)
-   记录第一次出现的位置，以便求最远或者最近。比如题目 [697\. 数组的度](https://leetcode-cn.com/problems/degree-of-an-array/solution/li-kou-jia-jia-ha-xi-biao-chang-jian-yin-7jez/)

题目推荐
-   [218.天际线](https://leetcode-cn.com/problems/the-skyline-problem/) （使用哈希统计可能会 OOM，但是思路上可行）
-   [面试题 01.04. 回文排列](https://leetcode-cn.com/problems/palindrome-permutation-lcci/)
-   [500\. 键盘行](https://leetcode-cn.com/problems/keyboard-row/description/)
-   [36\. 有效的数独](https://leetcode-cn.com/problems/valid-sudoku/description/)
-   [37\. 解数独](https://leetcode-cn.com/problems/sudoku-solver/description/) 与 36 类似，还需要点回溯的思想


-------------
# Definition

Sacrifice: no ordering

The **hash table** is a data structure that provides **constant-time insertion, lookup and removal** of elements that have two properties: 

- **Equality test**:  a test of whether or not two values (or two keys) are the same

  ```c++
  bool operator == (const T &other)
  {	return /* whether or not these are the same */	}
  ```

- **Hash function**: elements can be processed with a *hash function* to produce an integer *hash code*.

  A hash table stores values in an array with index derived from elements' values, *i.e.*, hash code derived from hash function.

  ```c++
  index = hash(value)
  table[index] = value
  ```

  a good hash function is expected to provide a different code to every value.

  A simple example: mod % 

Problem: ***hash collision***: two different values hash to the same index

Solution:

 1. **chaining**: keep a list of all elements that hash to the same code

    the table’s *load factor* $\lambda=\frac{N}{M}$, $N$: number of elements in the hash table, $M$: size of the table

    - choose a table size that is a prime number
    - keep $\lambda\approx1$ 
      - Higher than that and we need to do more iteration to find the right elements; 
      - lower than that and we’re wasting space that probably isn’t required.

 2. **probing**

## Perfect Hash

Prerequist: **we know all possible keys in advance**

