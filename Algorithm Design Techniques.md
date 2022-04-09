# Divide and Conquer
Divide-and-conquer algorithms consist of two parts:
- Divide: Smaller problems are solved recursively (except, of course, base cases).
- Conquer: The solution to the original problem is then formed from the solutions to the subproblems.
	- the subproblems be **disjoint** (that is, essentially non-overlapping).


## Running Time
![[divide-conquer time1.png]]
mergesort has $a = b = 2$ and $k = 1$. Thus $O(N log N)$

## Closest Point Problem
Given N points in a plane, the closest pair of points can be found in $O(N log N)$ time.
exhaustive search: $N(N-1)$->$O(N^2)$
It has a close relationship with [[0 Sort#Merge Sort]]
![[pointset.png | +side -sm -border1]]
Assume a small point set $P$.
```c++
std::default_random_engine re(std::chrono::system_clock::to_time_t(
		std::chrono::system_clock::now() ) );
std::uniform_real_distribution<double> urd(-100.0, 100.0);

std::vector<point_T> P(100);
std::generate(P.begin(), P.end(), [&urd, &re]() {
	return point_T { urd(re), urd(re)};
});
```

1. <ins>Assume that the points have been sorted by x coordinate.</ins> e.g., using merge sort will add $O(N log N)$ to the final time bound.
```c++
std::sort( P.begin(), P.end(), [](const point_T& a, const point_T& b) {
	return a.first < b.first;
});
```

![[pointset_lr.png| +side -sm -border1]]

2. Since the points are sorted by x coordinate, we can draw an imaginary vertical line that partitions the point set into two halves, $P_L$ and $P_R$. Then the closest points are:
	- both in $P_L$ -> distances is $d_L$
	- both in $P_R$->$d_R$
	- one is in $P_L$, the other is in $P_R$->$d_C$
```c++
    auto N = P.size();
    auto PL = std::vector<point_T>();
    auto PR = std::vector<point_T>();
    std::copy(P.begin(), P.begin() + N/2, std::back_inserter(PL));
    std::copy(P.begin() + N/2, P.end(), std::back_inserter(PR));

    double xM = P[(N-1)/2].first; // the middle point x coordinate
```
3. compute $d_L$ and $d_R$ recursively. ==how?== The problem, then, is to compute $d_C$. Since we would like an $O(N log N)$ solution, we must be able to compute $d_C$ with only $O(N)$ additional work. ==why can't $O(NlogN)$?==
```c++
// compute left and right side recursively
std::pair<double, pointPair_T> ret1 = optimizedSearch(PL, QL);
std::pair<double, pointPair_T> ret2 = optimizedSearch(PR, QR);
```
there are $logN$ recursions, so for each recursion, computing $d_C$ can't exceed $O(N)$
![[pointset_strip.png| +side -sm -border1]]

4. Let $\delta = min(d_L, d_R)$. The *first observation* is that we only need to compute $d_C$ if $d_C$ improves on $\delta$. If $d_C$ is such a distance, then the two points that define $d_C$ must be within $\delta$ of the dividing line; we will refer to this area as a **strip**.

5. Two strategies to compute $d_C$:
	- For large point sets that are uniformly distributed, the number of points that are expected to be in the strip is very small. Indeed, it is easy to argue that only $O(\sqrt{N})$ ==why?==points are in the strip on average. Then perform a brute-force calculation on these points in $O(N)$ time. Pseudocode of Brute-force calculation of $min(δ, d_C)$:
	```c++
	// Points are all in the strip
	for( i = 0; i < numPointsInStrip; i++ )
		for( j = i + 1; j < numPointsInStrip; j++ )
			if( dist(pi, pj) < δ )
				δ = dist(pi, pj);
	```
	However, in the worst case, all the points could be in the strip, so this strategy does not always work in linear time. 
	- *Second observation*: The y coordinates of the two points that define $d_C$ can differ by at most δ. <ins>Suppose that the points in the strip are sorted by their y coordinates.</ins> Therefore, if $p_i$ and $p_j$’s y coordinates differ by more than δ, then we can proceed to $p_{i+1}$. Pseudocode: 
	```c++
	// Points are all in the strip and sorted by y-coordinate
	for( i = 0; i < numPointsInStrip; i++ )
		for( j = i + 1; j < numPointsInStrip; j++ )
			if( pi and pj’s y-coordinates differ by more than δ )
				break;
			// Go to next pi.
			else
				if( dist(pi, pj) < δ )
					δ = dist(pi, pj);
	```
	
	![[pointset_strip2.png| +side -sm -border1]]
	
	This extra test has a significant effect on the running time, because for each $p_i$ only a few points $p_j$ are examined before $p_i$’s and $p_j$’s y coordinates differ by more than δ and force an exit from the inner for loop. e.g., point $p_3$, only need to check $p_4, p_5$, then exit
	<br>
	<br>
```c++
for ( auto i = strip.begin(); i != strip.end(); i++ ){
	for ( auto k = i + 1; k != strip.end(); k++) {
		// since strip is sorted by y coordinate, std::abs isn't needed.
		if((k->second - i->second) >= delta) break;

		auto new_dist = std::abs(dist(*k, *i));
		if ( new_dist < result.first ) {
			result = { new_dist, { *i, *k } };
		}
	}
}
```

6. The worst case: all points in the strip lie in one of the δ-by-δ squares. Hence,  for any point $p_i$, at most 7 points $p_j$ are considered. (note, we're not talking about the above point example)
![[pointset_worst.png| +side -md -border1]]
	On the other hand, by the definition of $\delta$, all the points in each δ-by-δ square are separated by at least δ. In the worst case, each square contains four points, one at each corner. Notice that even though $p_{L2}$ and $p_{R1}$ have the same coordinates, they could be different points. For the actual analysis, it is only important that the number of points in the δ-by-2δ  rectangle be $O(1)$, and this much is certainly clear.
	Because at most 7 points are considered for each $p_i$, the time to compute a $d_C$ that is better than δ is $O(N)$.(must $\leq 7N$)
	
7. We recursively split according to x coordinate. So each recursion, we have to sort y coordinate, which causes $O(n log n)$ extra work($n=N/2^i, i=0,1,..,logN$). There are $logN$ recursion, so the total time complexity is $O(N log^2 N)$
8. Solution: maintain two lists:
	- the point list sorted by x coordinate $P$
	- the point list sorted by y coordinate $Q$
	- Both can be obtained by a pre-processing sorting step at cost $O(N log N)$  and thus *does not affect the time bound*.
```c++
std::sort( P.begin(), P.end(), [](const point_T& a, const point_T& b) {
	return a.first < b.first;
});
auto Q = P;
std::sort( Q.begin(), Q.end(), [](const point_T& a, const point_T& b) {
	return a.second < b.second;
});
```
Then we can split them:
- $P_L$ and $Q_L$ are the lists passed to the left-half recursive call.
- $P_R$ and $Q_R$ are the lists passed to the right-half recursive call.
- How to get them? As before, $P$ is easily split in the middle, we get the dividing line. we step through $Q$ sequentially, placing each element in $Q_L$ or $Q_R$ as appropriate. It is easy to see that $Q_L$ and $Q_R$ will be automatically sorted by y coordinate.
```c++
// divide the point set into left and right parts.
auto N = P.size();
auto PL = std::vector<point_T>();
auto PR = std::vector<point_T>();
std::copy(P.begin(), P.begin() + N/2, std::back_inserter(PL));
std::copy(P.begin() + N/2, P.end(), std::back_inserter(PR));

double xM = P[(N-1)/2].first; // the middle point x coordinate

auto QL = std::vector<point_T>();
auto QR = std::vector<point_T>();
std::copy_if(Q.begin(), Q.end(), std::back_inserter(QL), [&xM](const point_T& point){
	return point.first <= xM;
});
std::copy_if(Q.begin(), Q.end(), std::back_inserter(QR), [&xM](const point_T& point){
	return point.first > xM;
});
```
When the recursive calls return, we scan through the Q list and discard all the points whose x coordinates are not within the strip. Then a new list contains only points in the strip, and these points are guaranteed to be sorted by their y coordinates.
In this case, for each recursion, only $O(n)$ extra work happens ($n=N/2^i, i=0,1,..,logN$).  
```c++
// compute left and right side recursively
std::pair<double, pointPair_T> ret1 = optimizedSearch(PL, QL);
std::pair<double, pointPair_T> ret2 = optimizedSearch(PR, QR);
// pick up the better one
std::pair<double, pointPair_T> result = ( ret1.first <= ret2.first )? ret1 : ret2;

double delta = result.first;
auto strip = std::vector<point_T>();
std::copy_if(Q.begin(), Q.end(), std::back_inserter(strip), [&delta, &xM](const point_T& point){
	return std::abs(xM - point.first) < delta;
});
```
So the total time complexity consists:
- pre-processing sort x, y: $O(N log N)$. happens only once
- traverse $Q$ after each dividing of $P$: $O(N)$. happens every recursion
- compute $d_C$: $O(N)$. happens every recursion
- total recursion times: $O(logN)$

Complete code: [GitHub](https://github.com/JianXinyu/LeetCode/blob/master/divide_and_conquer/closest_points.cpp)
## The Selection Problem
find the $k_{th}$ smallest element in a collection $S$ of $N$ elements. Of particular interest is the special case of finding the median. This occurs when $k = [N/2]$.

It has a close relationship with [[0 Sort#Quick Sort]]

# Dynamic Programming
recursive algorithm may not be recognized by the compiler. ==why?==
Solution: rewrite the recursive algorithm as a nonrecursive algorithm that *systematically records the answers to the sub- problems in a table* ->DP

