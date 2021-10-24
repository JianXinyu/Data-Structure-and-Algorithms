https://binarysearch.com/problems/Top-View-of-a-Tree

## 思路
- 从上往下看，注意被遮挡的节点: 给每个节点设置二维坐标，根节点纵坐标为0，向下增长， 横坐标为0， 向右增长. 横坐标相等时纵坐标小的覆盖纵坐标大的。
- 从左向右读: 按照横坐标从小到大的顺序输出。
- 纵坐标不是必要的，因为纵坐标小的先遍历到，直接覆盖以后的就好了。

- BFS遍历，记录坐标
- map记录，省得再排序
- queue来覆盖
The queue declaration

```cpp
queue<tuple<Tree*, int>> q;
```

`make_tuple` methods

```cpp
q.push(make_tuple(root, 0));  // tuple<Tree*, int>
```

`tie` to unpack a tuple variable.

```cpp
Tree* node = nullptr;
int x = 0;
tie(node, x) = q.front();
```
## Code
```cpp
/**
 * class Tree {
 *     public:
 *         int val;
 *         Tree *left;
 *         Tree *right;
 * };
 */

void bfs(Tree* root, map<int, int>& um) {
    queue<tuple<Tree*, int>> q;
    q.push(make_tuple(root, 0));  // tuple<Tree*, int>
    while (q.empty() == false) {
        Tree* node = nullptr;
        int x = 0;
        tie(node, x) = q.front();
        // cout << node->val << " ";
        if (um.find(x) == um.end()) {  // new visible node
            um[x] = node->val;
        }
        q.pop();

        /* Enqueue left child */
        if (node->left != nullptr) q.push(make_tuple(node->left, x - 1));

        /*Enqueue right child */
        if (node->right != nullptr) q.push(make_tuple(node->right, x + 1));
    }
}

vector<int> solve(Tree* root) {
    // hash map to record the x-coordinate of node
    map<int, int> um;  // (x, val)
    // traverse the Tree
    bfs(root, um);  // O(n)
    vector<int> ans;
    for (auto [key, val] : um) {
        // cout << key << "\t" << val << endl;
        ans.push_back(val);
    }

    return ans;
}
```

T: O(nlogn) traverse O(n), insert node to map O(logn)
S: O(n)