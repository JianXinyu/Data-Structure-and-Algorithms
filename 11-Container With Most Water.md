TIme: 30 mins, submit 3 times.

Runtime: 32 ms, faster than 79.46% of C++ online submissions for Container With Most Water.

Memory Usage: 14.2 MB, less than 76.09% of C++ online submissions for Container With Most Water.

At first, I tried the naive, brute force solution:

time complexity is $O(n^2)$

space complexity is $O(1)$

```C++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int max_area = 0;
        for(auto i = height.begin(); i != height.end() - 1; i++)
        {
            for(auto j = i + 1; j != height.end(); j++)
            {
                area = (j - i) * min(*i, *j);
                max_area = area > max_area ? area : max_area;
            }
        }
        return max_area;
    }
};
```

Of course, the auto-grader shows "Time Limited Exceeded".

Then I was inspired by the idea of merge sort. 

	- begin from two sides of the array, move towards the middle.
	- compare the area and move one side per step.

Time complexity is $O(n)$,

Space complexity is O(1).

```
class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        int max_area = 0;
		auto i = height.begin();
        auto j = height.end() - 1;
        
        while(i!=j)
        {
            area = (j - i) * min(*i, *j);
            max_area = area > max_area ? area : max_area;
            if(*i > *j) 
                j--;
            else
                i++;
        }
        
        return max_area;
    }
```

