#include <iostream>

#include "methods.h"

using namespace std;

int main()
{
    uniquePath3 p;
    vector<vector<int>> path {{1,3,1},{1,5,1},{4,2,1}};
    cout << p.minPathSum(path);

    return 0;
}
