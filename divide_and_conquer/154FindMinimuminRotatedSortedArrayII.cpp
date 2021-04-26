#include "divide_and_conquer.h"

// same with 153
// but the naive solution performs same with divide and conquer solution

// naive solution
int findMin2(vector<int>& nums) {
    auto last = nums.begin();
    int ret = *last;
    for ( auto i = nums.begin(); i != nums.end(); ++i){
        if ( *last > *i ){
            ret = *i;
            break;
        }
        last = i;
    }
    return ret;
}



