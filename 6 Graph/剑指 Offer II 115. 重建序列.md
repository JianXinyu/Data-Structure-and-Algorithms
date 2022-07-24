# Question
[link](https://leetcode.cn/problems/ur2n8P/)

# Analysis
判断 nums 是不是序列的唯一最短超序列，只需要判断根据 sequences 中的每个序列构造超序列的结果是否唯一。

把 sequences 中的所有序列看成有向图，数字 1 到 n 分别表示图中的 n 个结点，每个序列中的相邻数字表示的结点之间存在一条有向边。根据给定的序列构造超序列等价于有向图的拓扑排序。

首先根据有向边计算每个结点的入度，然后将所有入度为 0 的结点添加到队列中，进行拓扑排序。每一轮拓扑排序时，队列中的元素个数表示可以作为超序列下一个数字的元素个数，根据队列中的元素个数，执行如下操作。

如果队列中的元素个数大于 1，则超序列的下一个数字不唯一，因此 nums 不是唯一的最短超序列，返回 false。

如果队列中的元素个数等于 1，则超序列的下一个数字是队列中唯一的数字。将该数字从队列中取出，将该数字指向的每个数字的入度减 1，并将入度变成 0 的数字添加到队列中。

重复上述过程，直到出现队列中的元素个数不等于 1 的情况。

- 如果队列中的元素个数大于 1，则 nums 不是唯一的最短超序列，返回 false。
- 如果队列为空，则完整的拓扑排序结束，nums 是唯一的最短超序列，返回 true。


```python
class Solution:
    def sequenceReconstruction(self, nums: List[int], sequences: List[List[int]]) -> bool:
        n = len(nums)
        in_degrees = [0] * (n + 1)
        graph = [[] for _ in range(n + 1)]
        for seq in sequences:
            for pre, nxt in pairwise(seq):
                graph[pre].append(nxt)
                in_degrees[nxt] += 1
                
        q = deque([i + 1 for i, x in enumerate(in_degrees[1:]) if x == 0])
        while q:
            if len(q) > 1:
                return False
            node = q.popleft()
            for nxt in graph[node]:
                in_degrees[nxt] -= 1
                if in_degrees[nxt] == 0:
                    q.append(nxt)
        return True
```


```cpp
class Solution {
public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        const int n = nums.size();
        vector<int> indegrees(n + 1);
        vector<unordered_set<int>> graph(n + 1);
        for (const auto &seq : sequences) {
            for (int i = 1; i < seq.size(); i++) {
                int pre = seq[i - 1], nxt = seq[i];
                if (!graph[pre].count(nxt)) {
                    graph[pre].emplace(nxt);
                    indegrees[nxt]++;
                }
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indegrees[i] == 0) {
                q.emplace(i); 
            }
        }

        while (!q.empty()) {
            if (q.size() > 1)
                return false;
            int idx = q.front();
            q.pop();
            for (auto next : graph[idx]) {
                indegrees[next]--;
                if (indegrees[next] == 0) {
                    q.emplace(next);
                }
            }
        }
        return true;
    }
};
```