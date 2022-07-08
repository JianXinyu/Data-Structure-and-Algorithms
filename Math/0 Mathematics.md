辗转相除法：
- [[780. Reaching Points]]

数位相关：
- [[357. Count Numbers with Unique Digits]]

数论：
- 连续整数求和 [[829. Consecutive Numbers Sum]]
- 平方数
	- [[279. Perfect Squares]]
- 回文数 [[479. Largest Palindrome Product]]

序列：
- [[AMD Interview. Find In Sequence]]


# prime
```cpp
bool isPrime(int x) {
	if (x < 2)
		return false;
	for (int i = 2; i * i <= x; ++i)
		if (x % i == 0) return false;
	return true;
}
```
# gcd
[wiki](https://zh.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E5%85%AC%E5%9B%A0%E6%95%B8)
**最大公因数**（英语：highest common factor，hcf）也称**最大公约数**（英语：greatest common divisor，gcd）

辗转相除法：
```cpp
template < typename T >
T GCD(T a, T b) {
	if(b) while((a %= b) && (b %= a));
	return a + b;
}
```

a⋅b是k的倍数的充分必要条件是$\gcd(a, k) \cdot \gcd(b, k)$是k的倍数 [proof](https://leetcode-cn.com/problems/count-array-pairs-divisible-by-k/solution/an-zui-da-gong-yue-shu-fen-lei-fu-za-du-8pq92/)

- [[2183. Count Array Pairs Divisible by K]]


# 组合数
- [[62. Unique Paths]]

# Permutations / Combinations / Subsets
[link](https://leetcode.com/problems/subsets/solution/)
their solution space is often quite large:
-   [Permutations]: N!
-   [Combinations]: $C_N^k = \frac{N!}{(N - k)! k!}$
-   Subsets: $2^N$2N, since each element could be absent or present.

Given their exponential solution space, it is tricky to ensure that the generated solutions are _**complete**_ and _**non-redundant**_.

There are generally three strategies to do it:
-   Recursion
-   Backtracking
-   Lexicographic generation based on the mapping between binary bitmasks and the corresponding permutations / combinations / subsets.**Recommend!**

> The idea is that we map each subset to a bitmask of length n, where `1` on the i_th_ position in bitmask means the presence of `nums[i]` in the subset, and `0` means its absence.

For instance, the bitmask `0..00` (all zeros) corresponds to an empty subset, and the bitmask `1..11` (all ones) corresponds to the entire input array `nums`.

```cpp
// generate bitmask, from 0...00 to 1...11
for (int mask = 0; mask < (1 << n); mask++) {
	for (int i = 0; i < n; i++) {
		if (mask & (1 << i)) {
			// do something
		}
	}
}
```
Time complexity: $\mathcal{O}(N \times 2^N)$ 

- [[31. Next Permutation]]
- [[556. Next Greater Element III]]