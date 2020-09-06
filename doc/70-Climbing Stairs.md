Time: 15min, submit 4 times.

Dynamic programming

Runtime: 0 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.

Memory Usage: 6.2 MB, less than 23.16% of C++ online submissions for Climbing Stairs.

```c++
class Solution {
public:
    int climbStairs(int n) {
        // if(n == 1)
        //     return 1;
        // if(n == 2)
        //     return 2;
        // return climbStairs(n-1) + climbStairs(n-2);
        int last1 = 1;
        int last2 = 1;
        int sum = 1;
        for( int i = 1; i < n; i++)
        {
            sum = last1 + last2;
            last2 = last1;
            last1 = sum;
        }
        
        return sum;
    }
};
```

