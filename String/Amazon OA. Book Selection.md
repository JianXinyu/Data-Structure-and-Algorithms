 A book is represented as a **binary string** having two types of pages:
- '0': an ordinary page  
- '1': a bookmarked page

Find the number of ways to select **3** pages in ascending index order such that no two adjacent selected pages are of the same type.

Constraints:
- $1 ≤ | book | ≤ 2 · 10^5$  
- Each character in book is either '0' or '1'.

Example:  book = '01001'
The following sequences of pages match the criterion:
[1, 2 ,3], that is, 01001 → 010.  
[1, 2 ,4], that is, 01001 → 010.  
[2, 3 ,5], that is, 01001 → 101.  
[2, 4 ,5], that is, 01001 → 101.
The answer is 4.

可以发现，答案只有两种："010", "101"
所以只需要对每一个 1 统计其左边有多少个0， 右边有多少个0。那么这一个 1 可以增加
对每一个0，统计左边有多少个1，右边有多少个1；
 
```cpp
long numberOfWays(string &book) {
    const int n = book.length();
    int zeros = 0, ones = 0;
    for (char ch : book)
        ones += ch - '0';
    zeros = n - ones;

    long ans = 0;
    int pre_zeros = 0, pre_ones = 0;
    for (int i = 0; i < n; i++) {
        if (book[i] == '0') {
            ans += (pre_ones * (ones - pre_ones));
            pre_zeros++;
        } else {
            ans += (pre_zeros * (zeros - pre_zeros));
            pre_ones++;
        }
    }

    return ans;
}
```