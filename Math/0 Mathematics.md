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