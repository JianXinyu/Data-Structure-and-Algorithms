我自己面试遇到的两道题
- [[Amazon Interview - Flip Equivalent]]
- [[Amazon Interview. Number Letter Length]]
---
以下是online assessment
## Sort Log Files
![[937. Reorder Data in Log Files]]

## The kth Factor of n
![[1492. The kth Factor of n]]

## Fresh Deliveries  
![[Amazon OA. Fresh Devlivery]]
    
## Demolition Robot  
![[Amazon OA. Demolition Robot]]

## Split string into balanced strings
![[Amazon OA.  Split String Into Balanced Strings]]

## Book Selection
![[Amazon OA. Book Selection]]

## Number Of Bricks
![[Amazon OA. Number of Bricks]]

## Maximum Pages
Given a singly linked list
- sum the first and last node, then remove them
- repeat. calculate the maximum sum

Note: space complexity should be O(1)

Constraints:
- $2\leq n\leq 10^5$, n is even
- $1\leq val\leq 10^9$

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr){}
    ListNode(int value) : val(value), next(nullptr) {}
    ListNode(int value, ListNode *node) : val(value), next(node) {}
};

int maximumPages(ListNode *head) {
    // find the first node of the second half of list
    ListNode *slow = head, *fast = head;
    while (fast) {
        fast = fast->next->next;
        slow = slow->next;
    }
    // now the slow is the first node of the second half list
    // reverse the second half list
    ListNode *prev = nullptr, *cur = slow, *nxt;
    while (cur) {
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    // now prev is the last node of the reversed second half
    int ans = 0;
    while (prev) {
        ans = max(ans, prev->val + head->val);
        prev = prev->next;
        head = head->next;
    }
    return ans;
}
```

## Password Strength
Given a string password, calculate the sum of the number of distinct characters present in all possible substrings of that password.

Note: A substring is a continuous sequence of characters within a string, taken in the same order.

Constraints:
- $1\leq password.length \leq 10^5$
- the string consists of lowercase English letter only

Example:
password = "good"
g 1, o 1, o 1, d 1
go 2, oo 1, od 2
goo 2, ood 2
good 3
ans = 1+1+1+1+ 2+1+2 +2+2 +3 = 16

DP：考虑每个字符在新增子串中的贡献度

状态定义：
$dp[i]:=$ 在所有以$s[i]$结尾的substrings中，number of distinct letters之和。比如"good", $dp[1]=2+1=3$
还需要一个辅助数组$last[j]:=s[i]$上次出现的索引， $j=s[i]-'a'$

考虑从$i-1$移动到$i$，以$s[i]$结尾的substrings有$i+1$个。这$i+1$个子串中，$s[i]$之前的字符的贡献都已经考虑了($dp[i-1]$)，而字符$s[i]$虽然出现在了这$i+1$个子串中，但在有的子串中已经出现过了，我们只记它第一次出现的贡献，因此需要排除这些子串。这时就需要用到$last[j]$。

转移方程：
$dp[i]=dp[i-1]+i-last[s[i]-'a']$

边界条件：
$dp[0] = 1$

答案：
$dp$数组的和

```cpp
int findPasswordStrength(string &password) {
    const int n = password.length();
    vector<int> dp(n, 1);
    vector<int> last(26, -1);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if (i > 0)
            dp[i] = dp[i - 1] + i - last[password[i] - 'a'];
        last[password[i] - 'a'] = i;
        ans += dp[i];

    }
    return ans;
}
```
T: O(n)
S: O(n)

```cpp
int findPasswordStrength(string &password) {
    const int n = password.length();
    int dp = 1;
    vector<int> last(26, -1);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if (i > 0)
            dp += i - last[password[i] - 'a'];
        last[password[i] - 'a'] = i;
        ans += dp;

    }
    return ans;
}
```
T: O(n)
S: O(1)

**Similar**: [[828. Count Unique Characters of All Substrings of a Given String]]

## Number Of Connections
[question link](https://www.1point3acres.com/bbs/thread-797169-1-1.html)
Given a `m x n` grid. two types of point in the grid:
- 1: node
- 0: blank

A node located in $i-th$ row is a level $i$ node.

Every node at a level connects to the next level that contains at least 1 node. (every node at level $i$ connects to all the nodes at level $k,k>i,k$ is the first level after level $i$ that contains at least 1 node.)

count the number of connections.

Example:
input: `gridOfNodes`= {{1,1,1},{0,1,0},{0,0,0},{1,1,0}};
output: 5

```cpp
int gridOfNodes(vector<vector<int>> &grid) {
    const int m = grid.size();
    int ans = 0;
    int cur_level = 0, prev_level = 0;
    for (int i = 0; i < m; i++) {
        cur_level = std::accumulate(grid[i].begin(), grid[i].end(), 0);
        if (cur_level == 0) continue;
        ans += prev_level * cur_level;
        prev_level = cur_level;
    }
    return ans;
}
```

## max Profit
Efficient Harvest: A farmer uses pivot irrigation to water a circular field of crops. Due to varying conditions, the field does not produce consistently. The farmer wants to achieve maximum profit using limited resources for harvest. The field is segmented into a number of equal segments, and a profit is calculated for each segment. This profit is the cost to harvest versus the sale price a the produce. The farmer will harvest a number of contiguous segments along with those opposite. 
（其实只有一个要求：连续的k块地+扇形对面）
Determine the maximum profit the farmer can achieve. For example, the field is divided into $n = 6$ sections and will select $k = 2$ contiguous sections and those opposite for harvest. The profit estimates are $profits = [1, 5, 1, 3, 7,-3]$ respectively. 

The diagrams below show the possible choices with $profits(0)$ at the 9 o'clock position and filling counterclockwise.The profit levels, from left to right, are $1 + 5+7 + 3 = 16, 5+1 +7 -3=10$, and $1 + 3-3+1 =2$. The maximum profit is 16. 
![[efficient_harvest1.png]]
![[efficient_harvest2.png]]
![[efficient_harvest3.png]]

Constraints:
- $1\leq k \leq n / 2$
- $2\leq n \leq 10^5$
- n is even
- $0\leq |profits[i]| \leq 10^9$

由于必须要求对面对称，那么可以限定开始计算的segment 索引在$[0,\frac{n}{2}-1]$。第一个segment起始索引$start$对面的索引$start+\frac{n}{2}$，就是一个边界，之后segment 终点索引不能超过这个边界。比如第二个segment，$start+k+k-1<start+\frac{n}{2}$

预先计算好以每一个索引开始的 k-segment 的区间和。
```cpp
int maxProfit(int k, vector<int> profits) {
	const int n = profits.size();
	vector<int> presum(n, 0);
	presum[0] = std::accumulate(profits.begin(), profits.begin() + k, 0);
	for (int i = 1; i < n; i++) {
		presum[i] = presum[i - 1] - profits[i - 1] + profits[(i + k - 1) % n];
	}
	
	int ans = INT_MIN;
	for (int i = 0; i < n / 2; i++) {
		int sum = 0;
		for (int cur = i; cur < i + n / 2; cur += 2 * k - 1) {
			sum += presum[cur] + presum[cur + n / 2];
		}
		ans = max(ans, sum);
	}
	return ans;
}
```
T: O(n)
S: O(n)

## count team
[[1395. Count Number of Teams]]

## combo popularity
[link](https://leetcode.com/discuss/interview-question/1625460/amazon-oa-find-k-maximum-priority)
k个最大的子集和
A combo is defined as a subset of the given $n$ terms. The total popularity is the sum of the individual items of the combo. design an algorithm that can find the 
$k$ combos with the highest popularity.  
two combos are considered different if they have different subset of items. return the array of $k$ integers where the $i-th$ term denotes the popularity of $i-th$ best combo. Combos should be returned arranged best to worst.

Example:
n = 3  array = [3,5,-2]  k = 3  
All possible populatrity of combos are 0,3,5,-2,8,3,1,6 .  
The best 3 are 8,6,5.  
hence , answer is [8,6,5].

Constraints:
- $1 <= n <= 10^5$ --> T $O(n\log n)$
- $-10^9 <= array[i] <= 10^9$
- $1 <= k <= min(2000,2^n)$--> can backtrack on k elements since $k< 2^{11}$

can combo be empty?

Algorithm:
1.sort the array  
2.Record the highest score combo which is the sum of all positive integers  
3.Find a window in the sorted array of math.min(11,n) elements -- this window consists of the lowest 11 absolute values in the sorted array. Several approaches to achieve that, since the candidates must be inside 22 elements window(11 smallest positive values + 11 biggest negative values), we can use PriorityQueue of size 11 scanning over these 22 elements. or we can use two pointers to find the sliding window of size 11.  
4.backtrack on this 11 absolute value elements window, find sum of each combo and put them into a size k/k-1 PriorityQueue. (size k is for the case that there's no positive elements)  
5.result is the sum of all positive integers plus (sum deducted by each of k-1 elements in PriorityQueue).

```cpp
vector<int> kcombo(vector<int> popularities, int k) {
    const int n = popularities.size();

    sort(popularities.begin(), popularities.end());
    // returns an iterator pointing to the first element which is bigger than 0
    vector<int>::iterator pivot = std::upper_bound(popularities.begin(), popularities.end(), 0);
    // 对于有没有正数需要分类讨论

    // if pivot == end(), then max_sum = 0
    int max_sum = std::accumulate(pivot, popularities.end(), 0);
    int subset_size = min(11, n); // smallest subset_size absolute values
    priority_queue<int> q;
    vector<int>::iterator left = pivot - min((int)(pivot - popularities.begin()), 11);
    vector<int>::iterator right = pivot + min((int)(popularities.end() - pivot), 11);
    for (auto i = left; i != right; i++) {
        if (q.size() >= subset_size) {
            if (abs(*i) >= q.top()) continue;
            q.pop();
        }
        q.push(abs(*i));
    }
    vector<int> subset;
    while (!q.empty()) {
        subset.push_back(q.top());
        q.pop();
    }
    // construct all subset sum for subset, find the smallest k / k-1
//    int q_size = pivot == popularities.end() ? k : k - 1;
    int q_size = k;
    for (int mask = 0; mask < (1 << subset_size); ++mask) {
        int sum = 0;
        for (int i = 0; i < subset_size; i++) {
            if (mask & (1 << i)) {
                sum += subset[i];
            }
        }
        if (q.size() >= q_size) {
            if (sum >= q.top())  continue;
            q.pop();
        }
        q.push(sum);
    }

    vector<int> ans;
//    if (pivot != popularities.end()) ans.push_back(max_sum);
    while (!q.empty()) {
        ans.push_back(max_sum - q.top());
        q.pop();
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}
```
T: $O(n\log n+11*2^{11})$

## Box delivery
You are an amazon delivery and you have some boxes that you have to deliver, but there are some conditions -

-   You can take 2 boxes of same weight in one round
-   you can take 3 boxes of same weight in one round

You have to find the minimum number of rounds to deliver the boxes or -1 if it is not possible to deliver them.

Example cases -  
**Input:** boxes - [2, 2, 3, 3, 2, 4, 4, 4, 4, 4]  
**Output:** 4  
**Explanation:** 3 boxes of weight 2 in 1st round, 2 boxes of weight 3 in 2nd round, 3 boxes of wt 4 in 3rd and 2 boxes of wt 4 in 4th round.

**Input:** boxes - [2, 3, 3]  
**Output:** -1  
**Explanation:** There is only one box with weight 2 and we can only take either 2 or 3 boxes in one round not lesser.

```cpp
int box_delivery(vector<int> boxes) {
    map<int, int> m;
    for (int b : boxes) m[b]++;
    int ans = 0;
    for (auto const& [w, n] : m) {
        if (n % 3 == 0) ans += n / 3;
        else if (n % 3 == 2) ans += n / 3 + 1;
        else
            return -1;
    }
    return ans;
}
```

## Items in container
![[Amazon_Items in container.png]]
```cpp
vector<int> item_in_container(string &s, vector<int> &startIndices, vector<int> &endIndices) {
    const int n = s.length();
    // prefix sum of stars, position of the left most pipe
    vector<int> stars(n + 1, 0);
    vector<int> leftPipeIdx(n + 1, -1), rightPipeIdx(n + 1, n + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '|') {
            stars[i] = stars[i - 1];
            leftPipeIdx[i] = i;
        }
        else {
            stars[i] = stars[i - 1] + 1;
            leftPipeIdx[i] = leftPipeIdx[i - 1];
        }
    }
    if (leftPipeIdx[n] == -1) return vector<int>(startIndices.size(), 0);
    
    // position of the right most pipe
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '|')
            rightPipeIdx[i + 1] = i + 1;
        else if (i < n - 1)
            rightPipeIdx[i + 1] = rightPipeIdx[i + 2];
    }

    // right pipe is the left-most pipe from the end index, left pipe is the right-most one from the start index
    vector<int> ans;
    for (int i = 0; i < startIndices.size(); i++) {
        int startIdx = startIndices[i], endIdx = endIndices[i];
        int leftPipe = rightPipeIdx[startIdx];
        int rightPipe = leftPipeIdx[endIdx];
        int num = leftPipe < rightPipe ? stars[rightPipe] - stars[leftPipe] : 0;
        ans.push_back(num);
    }
    return ans;
}
```
T: O(n)
S: O(n)

## Max deviation among all substrings
[link](https://leetcode.com/discuss/interview-question/1742621/Amazon-or-OA-or-Max-deviation-among-all-substrings)
Let's have a string: `abbbcacbcdce`

For substring `abbb`, you have most frequent letter b -> 3 and least frequent letter a -> 1.
So the deviation is = most frequent - least frequent = 3 - 1 = 2. You need to look at all the substrings and find the max deviation.

Here substring `cacbcdc` has the max deviation.
Frequency is like below:
c -> 4, a ->1, b->1, d->1.
So max freq - min freq = 4 - 1 = 3.
Among all substrings deviation, this is the max. So return it.

String length is 10^4. So you can't check each substring.

Max deviation 必然是从两个不同的char的频率求得的。
1.  We take all possible distinct as ( c1 & c2 pairs ) characters possible. eg. 'a' & 'b' , 'a' & 'c' ... 'y' & 'z'
2.  We consider **c1** as the character with **maximum Freq** and **c2** as the character with **minimum Freq**
3.  Then we construct array of only c1 and c2 from the string( coz we are only interested in max and min Freq characters).  
	- take **1** for c1 and **-1** for c2.  
    - if we have consecutive c1's we simply add their frequency.  
    - 这样可以保证转换为求array 的subarray最大和 的问题。
	eg. ababcccaac  
    c1 = 'c' and c2 = 'a'  
    the array formed is -1 -1 3 -1 -1 1
4.  Now the max deviation for pair(c1, c2) will be the maximum sum(at least 2 elements) of subarray in the generated array.  
    **Note** : that the size of subarray should be greater than 1.  
    **Why?** In above example max subarray sum is 3( of length 1 ) but this is not correct as all characters will be same( result should be 0)  
    So consider subarray of size>1.
```cpp

// calculate the maximum subarray sum with at least k elements. T: O(n), S: O(n)
int calSum(const vector<int> &nums, int k) {
    const int n = nums.size();
    assert(n > 1 && k <= n);
    // calculate the maximum subarray sum end with index i
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    for (int i = 1; i < n; i++) {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
    }
    int ksum = std::accumulate(nums.begin(), nums.begin() + k, 0);
    int kdp = ksum;
    int ans = kdp;
    for (int i = k; i < n; i++) {
        ksum += nums[i] - nums[i - k];
        kdp = max(dp[i - k] + ksum, ksum);
        ans = max(ans, kdp);
    }
    return ans;
}

int maxDeviation(const string && str) {
    int ans = 0;
    vector<int> cnt(26, 0);
    for (auto c : str)
        cnt[c - 'a']++;

    // treat c1 as maxFreq char, c2 as minFreq char
    for (char c1 = 'a'; c1 <= 'z'; c1++) {
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            // no need to check one char
            if (c1 == c2 || !cnt[c1 - 'a'] || !cnt[c2 - 'a'])
                continue;

            vector<int> arr;
            for (auto c : str) {
                if (c == c1) {
                    if (arr.size() && arr.back() != -1) arr.back() += 1;
                    else
                        arr.push_back(1);
                }
                else if (c == c2)
                    arr.push_back(-1);
            }
//            printf("c1 = %c, c2 = %c, arr_size = %lu\n", c1, c2, arr.size());
            ans = max(ans, calSum(arr, 2));
        }
    }
    return ans;
}
```
T: $O(26*26*n)$
S: O(n)

## max greyness
[link](https://leetcode.com/discuss/interview-question/1753436/Amazon-OA)
grid[i][j] = 0 or 1
greyness[i][j] = the number of 1's  in i-th row + the number of 1's in j-th column - the number of 0's  in i-th row - the number of 0's in j-th column
no need to consider repeat counting.

## sum of scores
[link](https://leetcode.com/discuss/interview-question/1736639/solution-to-amazon-oa-2022-problem-sum-of-scores-of-subarray/1255065)
[link_cn](https://leetcode-cn.com/circle/discuss/YStFp6/)
Given an array "points" of numbers, a score can be calculated for a subarray [i....j] by $score = min(points[i...j])*sum(points[i...j[)$.

Return the sum of all scores of all possible subarrays. (mod 1e9+7)

constraint
1 <= len(A) <= 500000
1 <= A[i] <= 1e5;


Example 1
points = [2,1,3]  
in the form index pair = score  
0,0 = 4  
0,1 = 3  
0,2 = 6  
1,1 = 1  
1,2 = 4  
2,2 = 9
total = 27

Example 2
power = [2, 3, 2, 1]
There are n= 4 servers. The powers of contiguous groups of servers are:
Power[0,0] = min([2]) * sum([2]) = 4
Power [0,1]= min([2, 3]) * sum([2, 3]) = 10
Power [0, 2]= min([2, 3, 2]) * sum([2, 3, 2]) = 14
Power [0,3] = min([2, 3, 2, 1]) * sum([2, 3, 2, 1]) = 8
Power [1,1] = min([3]) * sum([3]) = 9
Power [1,2]= min([3, 2]) * sum([3, 2]) = 10
Power [1, 3] = min([3, 2, 1])* sum ([3, 2, 1]) = 6
Power [2, 2] = min([2]) * sum ([2]) = 4
Power[2,3] = min([2, 1]) * sum([2, 1]) = 3
Power [3,3] = min([1]) * sum([1]) = 1
Total Power = 69

著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
- 遍历数组
- 把当前元素cur作为区间最小值，那么就维护左右两个数组，一个是左边第一个大于cur的index数组left，另一个是右边第一个大于cur的index数组right
	- 所以需要预先求出两个数组
	- 通过单调栈（入栈顺序）来求。right数组，从左到右遍历，维护单调递增栈。遇到比栈顶元素小的，就pop，并将当前元素记录为栈顶元素右边的第一个小的；否则就push。left数组，从右到左遍历，维护单调递增栈。
- 当前元素cur索引为$i$，则$$ans += cur *(sum of all subarrays that include cur in [left[i]+1, right[i]-1])$$
- 统计这个区间中每个元素出现的次数，找到规律
```cpp
int sumScores(vector<int> &nums) {
    const int n = nums.size();
    std::stack<int>stk;
    vector<int> left(n, -1), right(n, n); // 注意初始化值
	
    // calculate right, using monotonically increasing stack
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && nums[stk.top()] > nums[i]) {
            int idx = stk.top();
            stk.pop();
            right[idx] = i;
        }
        stk.push(i);
    }
	
    while (!stk.empty()) stk.pop();

    // calculate left, using monotonically increasing stack
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && nums[stk.top()] > nums[i]) {
            int idx = stk.top();
            stk.pop();
            left[idx] = i;
        }
        stk.push(i);
    }
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int preSmall = left[i];
        int nextSmall = right[i];
        int acc = 0;

        for (int j = preSmall + 1; j < i; j++)
            acc += nums[j] * (j - preSmall) * (nextSmall - i);
        for (int j = i; j < nextSmall; j++)
            acc += nums[j] * (nextSmall - j) * (i - preSmall);
        ans += nums[i] * acc;
//        printf("left = %d, right = %d, acc = %d\n", preSmall, nextSmall, acc);
    }
    return ans;
}
```
T: $O(n^2)$ 当所有数相等时
S: O(n)

Improve:
left表示的是以某个元素结尾的所有subarray的sum of minimum(SOM)，
right表示的是以某个元素开始的所有subarray的sum of minimum(SOM)，
求出left和right的前缀和，利用前缀和则可以求出某个元素左边的所有subarray的SOM和右边所有subarray的SOM，则可得包含某个元素的的所有subarray的SOM。
```python
N = len(arr)
stack = []
left = [0] * len(arr)
for i in range(len(arr)):
    while stack and arr[stack[-1]] > arr[i]:
        stack.pop()

    left[i] = left[stack[-1]]+(i-stack[-1])*arr[i] if stack else (i+1)*arr[i]
    stack.append(i)

stack = []
right = [0] * len(arr)
for i in range(len(arr)-1,-1,-1):
    while stack and arr[stack[-1]] > arr[i]:
        stack.pop()

    right[i] = right[stack[-1]]+(stack[-1]-i)*arr[i] if stack else (N-i)*arr[i]
    stack.append(i)

leftAcc = [0]
rightAcc = [0]
for i in range(N):
    leftAcc.append(leftAcc[-1] + left[i])
    rightAcc.append(rightAcc[-1] + right[N-i-1])

total = leftAcc[-1]
ans = 0
for i in range(N):
    ans += (total - leftAcc[i] - rightAcc[N-(i+1)])*arr[i]
```
## longest difference subarray
[[1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit]]
## largest rectangle
[[84. Largest Rectangle in Histogram]]
## Count Binary Substrings
[[696. Count Binary Substrings]]

## count the outing days
![[Amazon OA. Count the Outing Days]]
## two sum
[link](https://leetcode.com/discuss/interview-question/356960/amazon-oa-2019-find-pair-with-given-sum)
注意corner case
- Return `null` or `empty list`
- `[0, 0]` and `target = 30`， return `[0, 0]`
```cpp
vector<int> twoSum(vector<int> nums, int target) {
    unordered_map<int, int> m;
    const int t = target - 30;
    int ans = INT_MIN;
    int icnt = 0;
    for (auto num : nums) {
        if (num * 2 == t) icnt++;
        if (t - num != num && m.find(num) != m.end())
            ans = max({ans, num, m[num]});
        m[t - num] = num;
    }
    if (icnt > 1 && t / 2 > ans) ans = t / 2;
    if (ans != INT_MIN) return {ans, m[ans]};
    return {};
}
```

## count the number of retailers
[link](https://leetcode.com/discuss/interview-question/1692516/Amazon-OA1-full-time-question-Jan-2022)
```cpp
vector<int> countNumberOfRetailers(vector<vector<int>> &retailers, vector<vector<int>> &requests) {
    vector<int> ans;
    std::sort(retailers.begin(), retailers.end()); // sort by [x, y]
    std::sort(retailers.begin(), retailers.end(), [](const vector<int> &r1, const vector<int> &r2){
        return r1[1] < r2[1];
    }); // sort by y
    for (const auto &request : requests) {
        const auto &itr = std::upper_bound(retailers.begin(), retailers.end(), request,
                                           [](const vector<int> &request, const vector<int> &retailer){
            return (request[0] <= retailer[0]) && (request[1] <= retailer[1]);
        });
        ans.push_back(retailers.end() - itr);
    }
    return ans;
}
```
## Similarity of String
Determine the length of the common prefix between each suffix and the original string
[hackerrank link](https://www.hackerrank.com/challenges/string-similarity/problem)
[geekforgeeks link](https://www.geeksforgeeks.org/sum-of-similarities-of-string-with-all-of-its-suffixes/)
Given a string **str**, the task is to find the sum of the similarities of **str** with each of its suffixes.   
The similarity of strings **A** and **B** is the length of the longest prefix common to both the strings i.e. the similarity of “aabc” and “aab” is **3** and that of “qwer” and “abc” is **0**.  

**Examples:**   
**Input:** str = “ababa”   
**Output:** 9   
The suffixes of str are “ababa”, “baba”, “aba”, “ba” and “a”. The similarities of these strings with the original string “ababa” are 5, 0, 3, 0 & 1 respectively.   
Thus, the answer is 5 + 0 + 3 + 0 + 1 = 9.  
**Input:** str = “aaabaab”   
**Output:** 13   

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
// Function to calculate the Z-array for the given string
void getZarr(string str, int n, int Z[])
{
    int L, R, k;
 
    // [L, R] make a window which matches with prefix of s
    L = R = 0;
    for (int i = 1; i < n; ++i) {
 
        // if i>R nothing matches so we will calculate.
        // Z[i] using naive way.
        if (i > R) {
            L = R = i;
 
            // R-L = 0 in starting, so it will start
            // checking from 0'th index. For example,
            // for "ababab" and i = 1, the value of R
            // remains 0 and Z[i] becomes 0. For string
            // "aaaaaa" and i = 1, Z[i] and R become 5
            while (R < n && str[R - L] == str[R])
                R++;
            Z[i] = R - L;
            R--;
        }
        else {
 
            // k = i-L so k corresponds to number which
            // matches in [L, R] interval.
            k = i - L;
 
            // if Z[k] is less than remaining interval
            // then Z[i] will be equal to Z[k].
            // For example, str = "ababab", i = 3, R = 5
            // and L = 2
            if (Z[k] < R - i + 1)
                Z[i] = Z[k];
 
            // For example str = "aaaaaa" and i = 2, R is 5,
            // L is 0
            else {
                // else start from R and check manually
                L = i;
                while (R < n && str[R - L] == str[R])
                    R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
}
 
// Function to return the similarity sum
int sumSimilarities(string s, int n)
{
    int Z[n] = { 0 };
 
    // Compute the Z-array for the given string
    getZarr(s, n, Z);
 
    int total = n;
 
    // Summation of the Z-values
    for (int i = 1; i < n; i++)
        total += Z[i];
 
    return total;
}
 
// Driver code
int main()
{
    string s = "ababa";
    int n = s.length();
 
    cout << sumSimilarities(s, n);
    return 0;
}
```

T: O(n)
S: O(n)

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <bitset>
#include <cmath>
#include <complex>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <utility>
#include <ctime>
using namespace std;

#define MOD 1000000007
#define BIT(x) __builtin_popcount(x)
#define MAX 100005
string C;
int P[MAX];
void Compute()
{
    int g = 0,f = 0;;
    int n = C.size();
    P[g = 0] = n;
    for(int i = 1 ; i < n ; i++)
    {
        if(i < g && P[i-f]!=(g-i))
            P[i] = min(P[i-f],g-i);
        else{
            g = max(g,f=i);
        while(g<n && C[g] == C[g-f])++g;
           P[i] = g-f;
        }
    }

}

int main()
{
	int t;cin >> t;
	while(t--){
	  cin >> C;
	  Compute();
	  long long s = 0;
	  for(int i = 0 ; i < C.size();i++)
		 {
		   s =s + (long long)P[i];
		   P[i] = 0;
		 }
	  cout << s << endl;
	}
	return 0;
}
```