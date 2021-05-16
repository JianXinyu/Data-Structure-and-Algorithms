class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;
        // for(int i = 0; i < nums.size(); i++){
        //     indices[nums[i]] = i;
        // }
        // for(int i = 0; i < nums.size(); i++){
        //     int b = target - nums[i];
        //     if(indices.count(b) && indices[b] != i)
        //         return {i, indices[b]};
        // }

        // improve
        for(int i = 0; i < nums.size(); i++){
            if(indices.find(target - nums[i]) != indices.end())
                return {i, indices[target - nums[i]]};
            indices.insert({nums[i], i});
        }
        return {};
    }
};