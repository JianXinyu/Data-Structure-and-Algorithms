给一个字符串，只包含'[',']','(',')'和'?',
求所有可能的分割方式，使得分割后的两个字符串都是均衡的。均衡的意思是字符串的左右方括号以及左右圆括号数量相等。'?'可以当成任意一个字符串。

Example:
输入：`[(?][?][`
输出：2
分割成`[(?]`和`[?][`或者分割成`[(?][?`和`][`

```cpp
int splitString(string &str) {
    std::map<char, int> pre, suf;
    for (char ch : str) suf[ch]++;
    function<bool(map<char, int>)> check = [](map<char, int> m) -> bool {
        int q = m['?'];
        int needed = abs(m['('] - m[')']) + abs(m['['] - m[']']);
        int remain = q - needed;
        if ((remain >= 0) && (remain % 2 == 0)) return true;
        return false;
    };
    const int n = str.length();
    int ans = 0;
    for (int idx = 2; idx < n - 1; idx += 2) {
        pre[str[idx - 2]]++, suf[str[idx - 2]]--;
        pre[str[idx - 1]]++, suf[str[idx - 1]]--;
        if (check(pre) && check(suf)) ans++;
    }
    return ans;
}
```