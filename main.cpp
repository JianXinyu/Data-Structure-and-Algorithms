#include <iostream>

#include "methods.h"

using namespace std;

int main()
{
//    vector<vector<int>> vec = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
    vector<vector<int>> vec = {{-3,-2}, {-2,-1}};
    cout << calculateMinimumHP(vec);

    return 0;
}
