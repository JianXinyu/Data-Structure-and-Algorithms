1h, submit twice

Runtime: 12 ms, faster than 99.79% of C++ online submissions for ZigZag Conversion.

Memory Usage: 7.8 MB, less than 93.41% of C++ online submissions for ZigZag Conversion.

Logic:

​	calculate each ZigZag character's index in the original string.

​	we see each Z in ZigZag as a cycle.

​	append the new string in the sequence of each row.

```c++
class Solution {
public:
    string convert(string s, int numRows) {
        int len = s.size();
        if(len < 2 || numRows == 1) return s; //special case
        int n = numRows * 2 - 2; // how many characters in a cycle
        int k = len / n; // how many cycles
		// index for two characters in a row within the same cycle
        int idx1; 
        int idx2;
        
        string result;
        
        for(int row = 0; row < numRows; row++)
        {
            for(int i = 0; i <= k; i++)
            {
                idx1 = i*n+row;
                idx2 = (i+1)*n-row;
                if(idx1 < len) result.append(s, idx1, 1);
                // in the middles rows, there are two characters within the same cycle
                if(row!=0 && row!=numRows-1 && idx2 < len) result.append(s, idx2, 1);
            }
        }

        return result;
    }
};
```

