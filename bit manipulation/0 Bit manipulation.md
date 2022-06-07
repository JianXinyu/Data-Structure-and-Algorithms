- 原码
- 反码
- 补码

## AND
`&`

`a & (-a)`获得a的最低非0位: 比如a的二进制是 ??????10000，取反就是??????01111，加1就是??????10000。前面?的部分是和原来a相反的，相与必然都是0，所以最后整体相与的结果就是00000010000。
应用：$lowbit()$ 运算
注意C++会出错: runtime error: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself 

## XOR
`^`性质:
-   任何数和本身异或则为`0`
-   任何数和 0 异或是`本身`
-   异或运算满足交换律，即: a ^ b ^ c = a ^ c ^ b

在不借助第三个变量的情况下可以实现两数对调
```cpp
a = a^b
b = a^b
a = a^b
```

- [[136. Single Number]]
- [[260. Single Number III]]
- [[442. Find All Duplicates in an Array]] swap

## 常见用法

- 如果你想将某几个二进制位变成 1，其他二进制位不变，可以用或运算。 比如 a | 0xff，就是将 a 的低八位变为 1，其他位不变。
    
- 如果你想将某几个二进制位不变，其他二进制变成 0，可以用与运算。比如 a & 0xff，就是将 a 的低八位保持不变，其他位置为 0。

- 判断某一位是否为 1 : a & (1 << i)

- 更新某一位为 1 : a | (1 << i)
```cpp
#define getBit(x, n) ((x >> n) & 1)
#define setBit(x, n) (x | (1 >> n))
```
- 右移运算等价于乘以 2，但是要比乘法快得多。因此建议大家使用位移，而不是乘以 2（或者 2 的幂）

> 左移也是同理

-  当题目的数据范围有一项是 30 以内，可以考虑是否可以使用状态压缩。这样就可以使用位运算来优化性能。

### lowbit 
lowbit 低位运算：$lowbit(n)$定义为非负整数 $n$ 在二进制表示下**最低位的1及后面所有的0构成的数值**。
Example：$n=10=(1010)_2,lowbit(n)=(10)_2=2$

$$lowbit(n)=n\&(\thicksim n+1)=n\&(-n)$$

$(\thicksim n+1)$是求 补码非，见CSAPP_ch Page66.

```cpp
int lowbit(int x) {
 	return x&(-x);
}
```
便于记忆：$lowbit(n)=2^k, k:=n$的二进制表示中末尾0的个数。

应用：计算非负整数n的二进制表示下所有位是1的数值
Example：$n=10=(1010)_2$所有位是1的数值有$(10)_2=2,(1000)_2=8$

Naive做法是枚举每一bit，$T=O(len)，len:=n$的二进制表示的位数。
lowbit可以更高效地求所有位是1的数值，$T=O(len_1), len_1:=n$的二进制表示中1的位数。

Example：
$n=10=(1010)_2, lowbit(n)=(10)_2=2$
$n = n - lowbit(n)=10-2=8=(1000)_2,lowbit(n)=8$
$n = n - lowbit(n)=8-8=0,stop$

为了得到$n$的第几位为 1，可以对2和8分别取对数，即$\log_2 2 = 1, \log_2 8 = 3$。由于C++ math.h 库的$\log$函数是以e为底的实数运算，并且复杂度常数较大，所以可以通过预处理，利用哈希表来代替$\log$运算。

```cpp
const MAX_N = 1 << 20; // 最多有20 bits
int H[MAX_N + 1];
for (int i = 0; i <= 20; ++i) H[1 << i] = i;
while (cin >> n) {
    while (n > 0) {
        cout << H[n & -n] << ' ';
        n -= n & -n;
    }
    cout << endl;
}
```
## 位运算常见题型

### 直接考察位运算性质

-   [[231. Power of Two]]
    
-   [268. 缺失数字](https://leetcode-cn.com/problems/missing-number/)
    

### 求某一个二进制位的值

比如我们要求 a 的第 n 位（从低到高）是多少。那么可以通过 (a >> n) & 1 的方式来获取。 实际上 (a >> n) & 1 就是一个左边全部是 0，最低位和 a 的第 n 位保持一致的数。

当然也可以用别的方式。比如 (a & (1 << n)) >> n。

> 当 n == 31 时，程序可能有问题。那么会有什么问题呢？

int的范围$[-2^{31},2^{31}-1]$

[[137. Single Number II]]
### 状态压缩

将状态进行压缩，可使用位来模拟。

```
Example：
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。说明：解集不能包含重复的子集。   
示例:   
输入: nums = [1,2,3]   
输出: [ [3], [1], [2], [1,2,3], [1,3], [2,3], [1,2], [] ]
```

例如我们现在有 3 个元素，那我们分别给这 3 个元素编号为 A B C

实际上这三个元素能取出的所有子集就是这 3 个元素的使用与不使用这两种状态的笛卡尔积。我们使用 0 与 1 分别表示这 3 个元素的使用与不使用的状态。那么这 3 个元素能构成的的所有情况其实就是：

```
000, 001, 010 ... 111
```

那么我们就依次遍历这些数，将为 1 的元素取出，即为子集. 时间和空间复杂度均为 O(n)，其中 n 为 nums 中数字总和。



更多参考：
-   [状压 DP 是什么？这篇题解带你入门](https://mp.weixin.qq.com/s?__biz=MzI4MzUxNjI3OA==&mid=2247486874&idx=1&sn=0f27ddd51ad5b92ef0ddcc4fb19a3f5e&chksm=eb88c183dcff4895209c4dc4d005e3bb143cc852805594b407dbf3f4718c60261f09c2849f70&token=513324802&lang=zh_CN#rd)
    

### 二进制的思维角度
有时从二进制角度思考问题可以实现降维打击的效果。不过这种思维方式不是很容易掌握，需要大家不断练习来掌握。

题目推荐：
-   [从老鼠试毒问题来看二分法](https://lucifer.ren/blog/2019/12/11/laoshushidu/)
    

## 更多

-   [力扣专题 - 位运算](https://github.com/azl397985856/leetcode/blob/master/thinkings/bit.md)
    

## 总结

位运算的题目，首先要知道的就是各种位运算有哪些，对应的功能以及性质。很多题目的考点基本都是围绕性质展开。另外一种题目的考点是状态压缩，大大减少时间和空间复杂度。使用位运算的状态压缩一点都不神秘，只是 api 不一样罢了。如果你不会，只能说明对位运算 api 不熟悉，多用几次其实就好了。


-   [190. 颠倒二进制位](https://leetcode-cn.com/problems/reverse-bits/)（简单）
-   [191. 位 1 的个数](https://leetcode-cn.com/problems/number-of-1-bits/)（简单）
-   [338. 比特位计数](https://leetcode-cn.com/problems/counting-bits/)（中等）
-   [1072. 按列翻转得到最大值等行数](https://leetcode-cn.com/problems/flip-columns-for-maximum-number-of-equal-rows/)（中等）
## 645. 错误的集合

和上面的`137. 只出现一次的数字2`思路一样。这题没有限制空间复杂度，因此直接 hashmap 存储一下没问题。 不多说了，我们来看一种空间复杂度$O(1)$的解法。

由于和`137. 只出现一次的数字2`思路基本一样，我直接复用了代码。具体思路是，将 nums 的所有索引提取出一个数组 idx，那么由 idx 和 nums 组成的数组构成 singleNumbers 的输入，其输出是唯二不同的两个数。

但是我们不知道哪个是缺失的，哪个是重复的，因此我们需要重新进行一次遍历，判断出哪个是缺失的，哪个是重复的。

```python
class Solution:
    def singleNumbers(self, nums: List[int]) -> List[int]:
        ret = 0  # 所有数字异或的结果
        a = 0
        b = 0
        for n in nums:
            ret ^= n
        # 找到第一位不是0的
        h = 1
        while(ret & h == 0):
            h <<= 1
        for n in nums:
            # 根据该位是否为0将其分为两组
            if (h & n == 0):
                a ^= n
            else:
                b ^= n

        return [a, b]

    def findErrorNums(self, nums: List[int]) -> List[int]:
        nums = [0] + nums
        idx = []
        for i in range(len(nums)):
            idx.append(i)
        a, b = self.singleNumbers(nums + idx)
        for num in nums:
            if a == num:
                return [a, b]
        return [b, a]

```

**_复杂度分析_**

- 时间复杂度：$O(N)$
- 空间复杂度：$O(1)$

## 260. 只出现一次的数字 3

题目大意是除了两个数字出现一次，其他都出现了两次，让我们找到这个两个数。

我们进行一次全员异或操作，得到的结果就是那两个只出现一次的不同的数字的异或结果。

我们刚才讲了异或的规律中有一个`任何数和本身异或则为0`， 因此我们的思路是能不能将这两个不同的数字分成两组 A 和 B。
分组需要满足两个条件.

1. 两个独特的的数字分成不同组

2. 相同的数字分成相同组

这样每一组的数据进行异或即可得到那两个数字。

问题的关键点是我们怎么进行分组呢？

由于异或的性质是，同一位相同则为 0，不同则为 1. 我们将所有数字异或的结果一定不是 0，也就是说至少有一位是 1.

我们随便取一个， 分组的依据就来了， 就是你取的那一位是 0 分成 1 组，那一位是 1 的分成一组。
这样肯定能保证`2. 相同的数字分成相同组`, 不同的数字会被分成不同组么。 很明显当然可以， 因此我们选择是 1，也就是
说`两个独特的的数字`在那一位一定是不同的，因此两个独特元素一定会被分成不同组。

```python
class Solution:
    def singleNumbers(self, nums: List[int]) -> List[int]:
        ret = 0  # 所有数字异或的结果
        a = 0
        b = 0
        for n in nums:
            ret ^= n
        # 找到第一位不是0的
        h = 1
        while(ret & h == 0):
            h <<= 1
        for n in nums:
            # 根据该位是否为0将其分为两组
            if (h & n == 0):
                a ^= n
            else:
                b ^= n

        return [a, b]
```

**_复杂度分析_**

- 时间复杂度：$O(N)$，其中 N 为数组长度。
- 空间复杂度：$O(1)$

## 相关题目

- [190. 颠倒二进制位](https://leetcode-cn.com/problems/reverse-bits/)（简单）
- [191. 位 1 的个数](https://leetcode-cn.com/problems/number-of-1-bits/)（简单）
- [338. 比特位计数](https://leetcode-cn.com/problems/counting-bits/)（中等）
- [1072. 按列翻转得到最大值等行数](https://leetcode-cn.com/problems/flip-columns-for-maximum-number-of-equal-rows/)（中等）