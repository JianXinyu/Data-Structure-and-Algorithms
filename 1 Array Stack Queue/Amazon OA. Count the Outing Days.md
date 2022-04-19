# Question
[link](https://leetcode.com/discuss/interview-question/algorithms/1520406/Amazon-OA-count-the-outing-days)
Amazon Alexa AI team is working to add feature that suggest days for camping based on the weather forecast. According to survey, a day is ideal for camping if the amount of rainfall has been non-increasing for the prior k days from the considered day and will be non-decreasing for the following k days from the considered day. Given the predicted rainfall for the next n days, find all ideal days. 

Formally a day is ideal if the following is true: $day[i-k]\geq \cdots \geq day[i-1]\geq day[i]\leq day[i+1]\leq \cdots \leq day[i+k]$

Return the ideal days in ascending order. The $i-th$ element of the array represents the data for the day $i+1$. 

Example, given input day =[3,2,2,2,3,4], k = 2  
here day1>=day2>=day3<=day4<=day5, so day3 is ideal  
also day2>=day3>=day4<=day5<=day6, so day4 is ideal  
The answer is [3,4]  

Ex:- Given/Input day=[1,0,1,0,1], k=1  
So, day1>=day2<=day3  
day3>=day4<=day5  
Output: [2,4]

Ex:- Given/input day=[1,0,0,0,1], k=2  
So, day1>=day2>=day3 <=day4<=day5  
Output: [3]

Ex:- Given day=[1,1,1,1,1,1,1,1,1,1], k=3
So, day1>=day2>=day3>=day4<=day5<=day6<=day7  
day2>=day3>=day4>=day5<=day6<=day7<=day8  
day3>=day4>=day5>=day6<=day7<=day8<=day9  
day4>=day5>=day6>=day7<=day8<=day9<=day10  
Output: [4,5,6,7]

Input method takes 2 arguments day[n] and k(an integer)  
returns int[], the ideal days in sorted ascending

```cpp
vector<int> idealDays(vector<int> &days, int k) {
    const int n = days.size();
    assert(k < 2 * n);
    vector<int> ans;
    vector<int> leftDecr(n ,0), rightAsce(n, 0);
    for (int i = 1; i < n; i++) {
        if (days[i - 1] >= days[i]) leftDecr[i] = leftDecr[i - 1] + 1;
        if (days[n - i - 1] <= days[n - i]) rightAsce[n - i - 1] = rightAsce[n - i] + 1;
    }
    cout << leftDecr << "\n" << rightAsce << endl;
    for (int i = 1; i < n; i++) {
        if (leftDecr[i] >= k && rightAsce[i] >= k)
            ans.push_back(i + 1);
    }
    return ans;
}
```

similar: [[821. Shortest Distance to a Character]]