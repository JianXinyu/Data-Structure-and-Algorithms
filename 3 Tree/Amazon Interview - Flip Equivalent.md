check if two binary trees are equivalent after some flip operations.
Flip operation: switch left and right child
e.g.,
```text
   Tree X
     1
   /   \
  3     2
 / \   /
4   5 6
   / \
  7   8

   Tree Y
     1
   /   \
  2     3
   \   / \
    6 5   4
     / \
    7   8
```
Tree X and Tree Y are equal after flipping node 1 and 3

```cpp
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool check_flip_equal(TreeNode *rootX, TreeNode *rootY) {
    if (!rootX && !rootY) return true;
    if (!rootX || !rootY) return false;
    if (rootX->val != rootY->val) return false;
    bool ret1 = check_flip_equal(rootX->left, rootY->left);
    bool ret2 = check_flip_equal(rootX->right, rootY->right);
    bool ret3 = check_flip_equal(rootX->left, rootY->right);
    bool ret4 = check_flip_equal(rootX->right, rootY->left);
    return (ret1 && ret2) || (ret3 && ret4);
}

```