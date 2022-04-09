# 打印
1. vector
```cpp
template < typename T >
ostream& operator << ( ostream& o, const vector<T>& v ){
	o << '[';
	for( const auto& x : v){
		o << ' ' << x;
	}
	o << ']';

	return o;
}

int main (int argc, char *argv[]) {
    vector<vector<int>> vec = {{1,2}, {3,4}};
    cout << vec;
}
```

2. 类型
[link](https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c)
```cpp
#include <string_view>

template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}
```

使用
```cpp
const int ci = 0;
std::cout << "decltype(i) is " << type_name<decltype(ci)>() << '\n';
```

3. 二进制表示

```cpp
#include <bitset>
std::bitset<32>(var);

char a = -58;
std::bitset<8> x(a);
std::cout << x << '\n';
```

```cpp
#include <iostream>
#include <bitset>
using namespace std;
int main () {
    int mask = 79;
    cout << std::bitset<32>(mask) << endl;
    cout << std::bitset<32>(~mask) << endl;
    return 0;
}
```

# Builtin functions of GCC compiler
1. bit 1的个数
- `__builtin_popcount(x)`: count the number of ones(set bits) in an integer
- `__builtin_popcountl(x)`: long 
- `__builtin_popcountll(x)`: long long 
```cpp
include <stdio.h>
int main()
{
    int n = 5;
     
    printf("Count of 1s in binary of %d is %d ",
           n, __builtin_popcount(n));
	//output: Count of 1s in binary of 5 is 2
    return 0;
}
```

2. 奇偶性
- `__builtin_parity(x)`: returns true(1) if the number has odd parity else it returns false(0) for even parity.
- `__builtin_parityl(x)`: long
- `__builtin_parityll(x)`: long long
```cpp
#include <stdio.h>
int main()
{
    int n = 7;
     
    printf("Parity of %d is %d ",
           n, __builtin_parity(n));
	// output: Parity of 7 is 1
    return 0;
}
```

3. leading zeros 的个数

- `__builtin_clz(x)`: count the leading zeros of the integer (clz: count leading zeros). **only accept unsigned values**
- `__builtin_clzl(x)`: long
- `__builtin_clzll(x)`: long

```cpp
#include <stdio.h>
int main()
{
    int n = 16;
     
    printf("Count of leading zeros before 1 in %d is %d",
           n, __builtin_clz(n));
	//output: Count of leading zeros before 1 in 16 is 27
    return 0;
}
```

4. trailing zeros 的个数
- `__builtin_ctz(x)`: count the trailing zeros of the given integer. (ctz: count trailing zeros)
- `__builtin_ctzl(x)`: long
- `__builtin_ctzll(x)`: long long

```cpp
#include <stdio.h>
int main()
{
    int n = 16;
     
    printf("Count of zeros from last to first "
           "occurrence of one is %d",
           __builtin_ctz(n));
    return 0;
}
```

# sort
在`unordered_map<int, int> freq`中找出value最大的两个元素
```cpp
int fstkey = 0, fstval = 0, sndkey = 0, sndval = 0;
for (const auto& [key, val]: freq) {
	if (val > fstval) {
		tie(sndkey, sndval) = tuple{fstkey, fstval};
		tie(fstkey, fstval) = tuple{key, val};
	}
	else if (val > sndval) {
		tie(sndkey, sndval) = tuple{key, val};
	}
}

return {fstkey, fstval, sndkey, sndval};
```


# 离散化 
discretization/coordinate compression
- [ref1](https://oi-wiki.org/misc/discrete/)

离散化本质上可以看成是一种 [哈希](https://oi-wiki.org/string/hash/)，其保证数据在哈希以后仍然保持原来的全/偏序关系。
通俗地讲就是当有些数据因为本身很大或者类型不支持，自身无法作为数组的下标来方便地处理，而影响最终结果的只有元素之间的相对大小关系时，我们可以将原来的数据按照从大到小编号来处理问题，即离散化。
用来离散化的可以是大整数、浮点数、字符串等等。

如果我们要store $N (1 \leq N \leq 10^5)$ elements，而且element的范围也是$(1, 10^5)$，直接放到一个数组即可。但如果element的范围是$(1,10^{12})$，那不可能创建一个长度为$10^{12}$的数组。解决方法是：对N个元素排序，assign each of them a number based on increasing order. Because $N \leq 10^5$, the maximum number you assign is going to be $10^5$. Thus, by compressing the "coordinates", we maintain the relative order of points in a memory-efficient manner. 

**离散化数组**
```cpp
// a[i] 为初始数组,下标范围为 [1, n]
// len 为离散化后数组的有效长度
std::sort(a + 1, a + 1 + n);

len = std::unique(a + 1, a + n + 1) - a - 1;
// 离散化整个数组的同时求出离散化后本质不同数的个数。
```
完成上述离散化之后可以使用 `std::lower_bound` 函数查找离散化之后的排名（即新编号）：
```cpp
std::lower_bound(a + 1, a + len + 1, x) - a;  // 查询 x 离散化后对应的编号
```
**离散化vector**
```cpp
// std::vector<int> a, b; // b 是 a 的一个副本
std::sort(a.begin(), a.end());
a.erase(std::unique(a.begin(), a.end()), a.end());
for (int i = 0; i < n; ++i)
  b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin() + 1; // 下标从1开始，从0开始则不用+1
```
