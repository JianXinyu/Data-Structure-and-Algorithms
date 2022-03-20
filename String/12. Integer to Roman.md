Time: 16min, submit once, test twice. Forget to set the change condition in while loop.

Runtime: 4 ms, faster than 98.11% of C++ online submissions for Integer to Roman.

Memory Usage: 6.1 MB, less than 65.59% of C++ online submissions for Integer to Roman.

Naive idea, transform the digit from the highest to smallest.

很直接的想法，没什么特别的。我一次就把逻辑写对了，说明我的逻辑还是很强的哈哈。

```C++
class Solution {
public:
    string intToRoman(int num) {
        vector<int> digits(4, 0);
        int digit = 0;
        string roman;
        
        digit = num / 1000;
        while(digit > 0)
        {
            roman.append("M");
            --digit;
        }
        num %= 1000;
        if(num >= 900)
        {
            roman.append("CM");
            num -= 900;
        }
        if(num >= 500)
        {
            roman.append("D");
            num -= 500;
        }
        if(num >= 400)
        {
            roman.append("CD");
            num -= 400;
        }
        
        digit = num / 100;
        while(digit > 0)
        {
            roman.append("C");
            --digit;
        }
        num %= 100;
        if(num >= 90)
        {
            roman.append("XC");
            num -= 90;
        }
        if(num >= 50)
        {
            roman.append("L");
            num -= 50;
        }
        if(num >= 40)
        {
            roman.append("XL");
            num -= 40;
        }
        
        digit = num / 10;
        while(digit > 0)
        {
            roman.append("X");
            --digit;
        }
        num %= 10;
        if(num == 9)
        {
            roman.append("IX");
            num -= 9;
        }
        if(num >= 5)
        {
            roman.append("V");
            num -= 5;
        }
        if(num == 4)
        {
            roman.append("IV");
            num -= 4;
        }
        while(num > 0)
        {
            roman.append("I");
            --num;
        }
        
        return roman;
    }
};
```

Better solution:

简化代码，把所有可能的组合用pair放到一个vector；另外直接减就好，不用取整或取模。

```C++
// Author: Huahua
class Solution {
public:
  string intToRoman(int num) {
    vector<pair<int,string>> v{{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
                               { 100, "C"}, { 90, "XC"}, { 50, "L"}, { 40, "XL"}, 
                               {  10, "X"}, {  9, "IX"}, {  5, "V"}, {  4, "IV"}, 
                               {   1, "I"}};
    string ans;
    auto it = cbegin(v);
    while (num) {
      if (num >= it->first) {
        num -= it->first;
        ans += it->second;
      } else {
        ++it;
      }
    }
    return ans;
  }
};
```

