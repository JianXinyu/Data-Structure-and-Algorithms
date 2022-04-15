 Consider a sequence k where k is defined as follows:
1.  The number k(0) = 1 is the first one in k.
2.  For each x in k, then all of “a = 2 * x + 1” and “b = 3 * x + 1” and “c = 5 * x + 1” must be in k.
3.  There are no other numbers in k. 
Example:
-   k = [1, 3, 4, 6, 7, 9, 10, 13, 15, 16, 19, 21, 22, 27, …]

1 gives 3, 4 and 6, then 3 gives 7, 10 and 16, 4 gives 9, 13 and 21, then 6 gives 13 19 and 31 and so on…

**Question:**
Given parameter n the function find_in_seq returns the element k(n) of the ordered (with <) sequence k (so, there are no duplicates).

**Example:**
find_in_seq(10) should return 19

```cpp
int find_in_seq(int n) {
    priority_queue<int, vector<int>, greater<int>> pending;
    map<int, int> not_process; // 用map主要是为了去重，有序
    // initialize
    not_process.emplace(1, 0);
    pending.push(1);
    int count = 0;

    while (count < n+1) {
        // not_process 在这一步始终不会为空
        int x = not_process.begin()->first;
        not_process.erase(x);
        int a = 2 * x + 1;

        while (!pending.empty() && pending.top() <= a) {
            // 相等的时候只pop而不计数，是为了在最后一次出现时才计数
            if (pending.top() < a) count++;
            if (count == n+1) return pending.top();
            pending.pop();
        }
        pending.push(a);
        not_process.emplace(a, 0);
        int b = 3 * x + 1;
        pending.push(b);
        not_process.emplace(b, 0);
        int c = 5 * x + 1;
        pending.push(c);
        not_process.emplace(c, 0);
    }
    return 0;
}
```