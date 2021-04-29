#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm> // std::count
using namespace std;

// Time limit exceeded
//     int countPairs(vector<int>& deliciousness) {
//         constexpr int kMod = 1e9 + 7;
//         int ret = 0;
//         int n = deliciousness.size();
//         vector<int> evens;
//         vector<int> odds;
//         for(int i = 0; i < n; ++i){
//             int tmp = deliciousness[i];
//             if(tmp % 2 == 0){
//                 evens.push_back(tmp);
                    // 1+0 is also power of 2
//                 if(tmp == 0) ret += count(deliciousness.begin(), deliciousness.end(), 1);
//             }

//             else
//                 odds.push_back(tmp);
//         }

//         ret += (countpairs(evens)+countpairs(odds));
//         return ret % kMod;
//     }
//     int countpairs(vector<int>& deli) {
//         if(deli.size() < 2)
//             return 0;
//         int ret = 0;
//         for(auto i = deli.begin(); i != deli.end(); ++i){
//             for(auto j = i + 1; j != deli.end(); ++j){
//                 int sum = *i+*j;
//                 if(IsPowerOfTwo(sum)){
//                     ret++;
//                 }
//             }
//         }
//         return ret;
//     }

//     bool IsPowerOfTwo(ulong x)
//     {
//         return (x != 0) && ((x & (x - 1)) == 0);
//     }

// 妙啊
int countPairs(vector<int>& A) {
    constexpr int kMod = 1e9 + 7;
    unordered_map<int, int> m;
    long ans = 0;
    for (int x : A) {
        for (int t = 1; t <= 1 << 21; t *= 2) {
            auto it = m.find(t - x);
            if (it != end(m)) ans += it->second;
        }
        ++m[x];
    }
    return ans % kMod;
}