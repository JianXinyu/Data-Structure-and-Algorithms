$\lfloor a \rfloor$ 向下取整
$\lceil a \rceil$ 向上取整
# Merge Sort
- $O(N log N)$ worst-case running time, and the number of comparisons used is **nearly optimal**. 
-  a classic **divide-and-conquer recursive** algorithm.
	- The problem is divided into smaller problems and solved recursively. 
	- The conquering phase consists of patching together the answers. 

# Quick Sort
- average running time is $O(N log N)$.
- $O(N^2)$ worst-case performance, but this can be made exponentially unlikely with a little effort
- By combining quicksort with heapsort, we can achieve quicksort’s fast running time on almost all inputs, with heapsort’s O(N log N) worst-case running time. ==Ex. 7.27==
- **a divide-and-conquer recursive algorithm.**

## Algorithm
### picking the pivot
- 1st element: if input is random, fine. if input is presorted, horrible!
- choose the pivot randomly: safe, but random number generation is expensive,
- Median-of-Three Partitioning: left, right, and center (in position $\lfloor(left + right)/2\rfloor$) elements. no need random.

### Partitioning Strategy
Assume that all the elements are distinct.
![[quicksort.png | +side -med]]
1. Calculate the pivot.
2. Get the pivot element out of the way by swapping it with the last element. $i$ starts at the first element and $j$ starts at the next-to-last element.
3. While $i$ is to the left of $j$:
	- move $i$ right, skipping over elements that are smaller than the pivot.
	- move $j$ left, skipping over elements that are larger than the pivot.
	- when $i$ and $j$ have stopped, $i$ is pointing at a large element and $j$ is pointing at a small element. **Swap** the elements pointed to by $i$ and $j$.
4. Swap the pivot element with the element pointed to by $i$.
	- every element in a position $p < i$ must be small
	- every element in a position $p > i$ must be large

What to do in the presence of duplicates? As a limiting case, our algorithm must do the proper thing if all of the elements are identical.
- if the duplicate elements are different from the pivot, that's fine.
- if elements are equal to the pivot, how to deal with it? The crux is how to do with $i,j$.
	- Intuitively, $i, j$ ought to do the same thing, since otherwise the partitioning step is biased. For instance, if $i$ stops and $j$ does not, then all elements that are equal to the pivot will wind up in $S_2$.
	- consider the case where all the elements in the array are identical.
		- both $i, j$ stop: many useless swaps between identical elements. But the positive effect is that $i, j$ will cross in the middle, so when the pivot is replaced, the partition creates two nearly equal subarrays. -> $O(N log N)$.
		![[quicksort2.png | +side -med]]
		- neither $i$ nor $j$ stops: no swaps. But $i$ stops at the next-to-last position. This would create very uneven subarrays. -> $O(N)$ ==why?== once $i,j$ cross, they should stop. Even if they stop when cross, check the example at the right side, which also gives very uneven subarrays.
➡ both $i, j$ should stop

### Small Arrays
For very small arrays (N ≤ 20), quicksort does not perform as well as insertion sort.
Solution: use a cutoff range N = 10

## Code
**Very easy to do it wrong!**
### pivot selection
sort $a[left], a[right]$, and $a[center]$ in place.
- save a little bit of work. simply place the pivot in $a[right - 1]$, initialize $i$ and $j$ to $left + 1$ and $right - 2$ in the partition phase.
- $a[left]$ acts like a sentinel for $j$. storing the pivot in $a[right-1]$ provides a sentinel for $i$

What if not sort in place?  ==Exercise 7.51==

```cpp
template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right)
{
    int center = (left + right) / 2;

    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ]);
    if( a[ right ] < a[ left ])
        std::swap(a[ left ], a[ right ]);
    if( a[ right ] < a[ center ])
        std::swap( a[ center ], a[ right ]);

    //Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1] );
    return a[right - 1];
}
```
### heart of the quicksort routine
```cpp
template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right)
{
	if (left + 10 <= right) {
		const Comparable &pivot = median3(a, left, right);

		int i = left, j = right - 1;
		for (;;) {
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j)
				std::swap(a[i], a[j]);
			else
				break;
		}
		std::swap(a[i], a[right - 1]); 

		quicksort(a, left, i - 1);
		quicksort(a, i + 1, right); 
	} else 
		insertionSort(a, left, right);
}
```

1. ==Why== initialize $i$ and $j$ to 1 past their correct values and increment when compare? To avoid special cases. Since we increment $i,j$ first, it has the same effect with initializing $i$ and $j$ to $left + 1$ and $right - 2$.
For example, if we write code like this:
```cpp
	int i = left + 1, j = right - 2;
	for( ; ; )
	{
		while( a[ i ] < pivot ) i++;
		while( pivot < a[ j ] ) j--;
		if( i < j )
			std::swap( a[ i ], a[ j ] );
		else
			break;
	}
```
This does not work, because there would be an infinite loop if $a[i] = a[j] = pivot$.
Hence, we must increment $i,j$ before comparing.

2. **I don't quite understand**
> The swapping action at line 22 is sometimes written explicitly, for speed purposes. For the algorithm to be fast, it is necessary to force the compiler to compile this code inline. Many compilers will do this automatically if swap is declared using inline, but for those that do not, the difference can be significant.

3. why quicksort is so fast? the inner loop (for loop) consists of:
	- an increment/decrement (by 1, which is fast)
	- a test, 
	- a jump
There is no extra juggling as there is in mergesort.==is quicksort really better than mergesort?==
[code](./quick_sort.cpp)

## Analysis
Assume a random pivot (no median-of-three partitioning) and no cutoff for small arrays, $T(0) = T(1) = 1$
$$T(N) = T(i) + T(N − i − 1) + cN$$
where $i = |S_1|$ is the number of elements in $S_1$. 
### Worst Case
The pivot is the smallest element, all the time. $i=0$
$T(N)=O(N^2)$

### Best Case
The pivot is in the middle。
$T(N)=O(NlogN)$

### Average-Case
TBD


![[quicksort_time.png]]

## Reflect
以上是升序，那么降序该怎么写呢？
median3和quicksort都要修改
```c++
    int median3(vector<int>& nums, int l, int r){
        int mid = (l+r) / 2;
        if(nums[l] < nums[mid])
            swap(nums[l], nums[mid]);
        if(nums[l] < nums[r])
            swap(nums[l], nums[r]);
        if(nums[mid] < nums[r])
            swap(nums[mid], nums[r]);
        swap(nums[mid], nums[l+1]);
        return nums[l+1];
    }
    
    
    void quicksort(vector<int>& nums, int l, int r){
        if(l+1 >= r){
          if(nums[l] < nums[r])
              swap(nums[l], nums[r]);
          return;
        } 
        int pivot = median3(nums, l, r);
        int i = l + 1, j = r;
        for(;;){
            while(nums[++i] > pivot){}
            while(nums[--j] < pivot){}
            if(i < j)
                swap(nums[i], nums[j]);
            else
                break;
        }
        swap(nums[j], nums[l+1]);
        quicksort(nums, l, j-1);
        quicksort(nums, j+1, r);
    }
```
Question: 
`swap(nums[j], nums[l+1]);`这里选$j- or- i$有区别吗? 应该是没有区别的
