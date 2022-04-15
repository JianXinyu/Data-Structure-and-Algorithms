# Question
Given a number `num < 10000`, return the sum of English words length for each number from 1 to `num`.
e.g., num = 3. one - 3, two - 3, three - 5
return 11

Note: space and hyphen are not included. `and` is included.

e.g. 351: three hundred and fifty-one, it's length is 5+7+3+5+3=23

# Analysis
先找规律：
先找出特殊的，放到map里，对于不特殊的就是排列组合。
特殊的：1-20, 30, 40, 50, 60, 70, 80, 90, 100, 1000
21 ~ 99 的格式要么是特殊的，要么是十位 + 个位
100 ～ 999 的格式要么是 `x hundred and 两位数`，要么是`x hundred`
1000 ～ 9999 的格式要么是`x thousand and 三位数`, 要么是`x thousand`

可以用递归实现

```cpp
// store length rather than string
std::unordered_map<int, int> m = {{1, 3}, {2, 3}, {3, 5}, {4, 4}, {5, 5}, {6, 3}, {7, 5}, {8, 5}, {9, 4},
                             {10, 3}, {20, 6}, {30, 6}, {40, 6}, {50, 5}, {60, 5}, {70, 7}, {80, 7}, {90, 6},};
int count_letters(int num) {
    auto itr = m.find(num);
    if (itr != m.end()) return itr->second;
    // two digits
    if (num < 100) {
        int ones = num % 10;
        int tens = num - ones;
        return m.find(tens)->second + m.find(ones)->second;
    }
    // three digits
    if (num < 1000) {
        int hundreds = num / 100;
        num %= 100; // num is now a two-digit number
        if (num == 0)
            return m.find(hundreds)->second + 7;
        return m.find(hundreds)->second + 7 + 3 + count_letters(num);
    }
    // four digits
    int thousands = num / 1000;
    num %= 1000; // num is now a three-digit number
    if (num == 0)
        return m.find(thousands)->second + 7;
    return m.find(thousands)->second + 7 + 3 + count_letters(num);
}

int count_all(int num) {
    int ans = 0;
    for (int i = 1; i <= num; i++)
        ans += count_letters(i);
    return ans;
}
```