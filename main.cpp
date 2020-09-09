#include <iostream>

#include "methods.h"

using namespace std;

int main()
{
    uniquePath2 p;
    vector<vector<int>> path {{0,0,0},{0,1,0},{0,0,0}};
    cout << p.uniquePathsWithObstacles(path);

    return 0;
}
