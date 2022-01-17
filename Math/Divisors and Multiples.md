Given an array _arr_ of length _n,_ for each index _i_ from 1 to _n,_ count the number of indices _j (j != i),_ such that either _arr[j]_ _is a divisor of_ _arr[i]_ _or_ _arr[j]_ _is a multiple of_ _arr[i]__._

Note:

-   _x_ is called a divisor of _y_ if _y_ is divisible by _x._
-   _x_ is called a multiple of _y_ if _x_ is divisible by _y._

**Example**

_arr = [1, 3, 4, 2, 6]_

-   For i = 1, Number of divisors of 1 = 0. Number of multiples of 1 = 4.
-   For i = 2, Number of divisors of 3 = 1. Number of multiples of 3 = 1.
-   For i = 3, Number of divisors of 4 = 2. Number of multiples of 4 = 0.
-   For i = 4, Number of divisors of 2 = 1. Number of multiples of 2 = 2.
-   For i = 5, Number of divisors of 6 = 3. Number of multiples of 6 = 0.

Hence, the answer for the above example is _[4, 2, 2, 3, 3]._

**Function Description**

Complete the function _getCount_ in the editor below.

_getCount_ has the following parameter(s):

    _int arr[n]:_ an array of integers

**Returns**

 _int[n]:_ an array of integers, the answers at each index

**Constraints**

-   1 _≤ n ≤_ 105
-   1 _≤ arr[i] ≤_ 105




## Solution
**Concepts Covered:** The problem tests the candidate on Arrays, Loops, counters, and Maths.
**Optimal Solution:** This problem can be solved by a sieve-like implementation ([Refer here](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)).

-   First of all, create a frequency array from the given array, _freq[i]_ stores the number of times _i_ is present in the given array, _arr_.
-   Now, to calculate the number of multiples of any number _i_ in the given array, iterate over each multiple of _i_ and add its frequency to _multiples[i]._ 
-   You can do this for each _i_ between _1_ to _M,_ where _M_ is the maximum element in the given array.

The number of divisors of each _i_ can also be found in a similar way. 

Code:
```python
def getCount(arr):
    mx = max(arr)+1
    cnt = [0 for _ in range(mx)]
    ans = [0 for _ in range(mx)]
    for item in arr:
        cnt[item] += 1

    for i in range(1,mx):
        for j in range(i+i, mx,i):
            ans[i] += cnt[j]
            ans[j] += cnt[i]

    return [cnt[item]-1+ans[item] for item in arr]
```

```cpp
vector<int> getCount(vector<int> arr) {
    int maximum = *max_element(arr.begin(), arr.end());
    vector<int> ans(maximum+1), cnt(maximum+1);
    for (const auto & i : arr) {
        cnt[i]++;
    }
    
    for (int i = 1; i <= maximum; i++) {
        for (int j = i; j <= maximum; j += i) {
            if (i == j) ans[i] += cnt[j] - 1;
            else {
                ans[i] += cnt[j];
                ans[j] += cnt[i];              
            }
        }
    }
    
    vector<int> ret(arr.size());
    for (int i = 0; i <= arr.size(); i++) {
        ret[i] = ans[arr[i]];
    }
    
    return ret;
}
```

**Time Complexity** - The time complexity of the solution will be _O(M*Log(M)+n)_. 

**Space Complexity** - O(M + n)

Where _M_ is the maximum element in the given array and _n_ is the size of the given array.