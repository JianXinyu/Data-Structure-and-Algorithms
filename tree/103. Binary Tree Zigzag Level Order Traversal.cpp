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

// DFS
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* r, int d){
            if(!r) return;
            if(ans.size() <= d) ans.push_back({});
            ans[d].push_back(r->val);
            dfs( r->right, d+1 );
            dfs( r->left, d+1 );
        };
        dfs(root, 0);
        for(int i = 0; i < ans.size(); i+=2){
            reverse(begin(ans[i]), end(ans[i]));
        }
        return ans;
    }
};