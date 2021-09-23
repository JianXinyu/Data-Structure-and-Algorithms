/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        int max_depth = -1;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* r, int d){
            if(!r) return;
            if( d > max_depth ){
                ans.push_back(r->val);
                max_depth++;
            }
            dfs(r->right, d+1);
            dfs(r->left, d+1);
        };
        dfs(root, 0);

        return ans;
    }
};

/*
 * 另一个想法是先遍历tree，保存到一个vector数组。e.g.[1,2,3,null,5,null,4]
 * 第0层, i.e., root的index是0
 * 第1层的index是1 to 2
 * 第2层的index是3 to 6
 * 第k层的index是2^k-1 to 2^{k+1}-2
 * 只需在vector中找出每一层对应index区间中最后一个不为null的元素,
 * e.g., 第2层index区间是[null, 5, null, 4]， 那么第二层最右元素就是4
 */