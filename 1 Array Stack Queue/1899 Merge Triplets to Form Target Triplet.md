# Question
[link](https://leetcode-cn.com/problems/merge-triplets-to-form-target-triplet/)
Given an array of triplet, can this array give the target triplet using the piece-wise max operation?
# Analysis
找出所有可以合并成target的triplets
> Crux: triplet要含有target中的值，且另外两个值不能大于target中的另外两个值
```cpp
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        unordered_map<int, vector<int>> m {{0, {}}, {1, {}}, {2, {}}};
        const int n = triplets.size();
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < 3; ++j){
                if(triplets[i][j] == target[j]){
                    int idx1 = (j+1)%3, idx2 = (j+2)%3;
                    if(triplets[i][idx1] <= target[idx1] && triplets[i][idx2] <= target[idx2])
                        m[j].push_back(i);
                }
                    
            }
        }
        for(auto const & x : m){
            if(x.second.size() == 0)
                return false;
        }
        return true;
    }
};
```
T: O(n)，其中 n 是数组triplets 的长度。
S: O(1)

![[Merge Triplets to Form Target Triplet.png]]
```cpp
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int x = target[0], y = target[1], z = target[2];
        int a = 0, b = 0, c = 0;

        for (const auto& triplet: triplets) {
            int ai = triplet[0], bi = triplet[1], ci = triplet[2];
            if (ai <= x && bi <= y && ci <= z) {
                tie(a, b, c) = tuple{max(a, ai), max(b, bi), max(c, ci)};
            }
        }

        return tie(a, b, c) == tie(x, y, z);
    }
};
```