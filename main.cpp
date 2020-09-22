#include <iostream>

#include "methods.h"

using namespace std;

int main()
{
    Robber r;
    vector<int> vec = {2,1,1,2};
    cout << r.rob(vec);

    return 0;
}
