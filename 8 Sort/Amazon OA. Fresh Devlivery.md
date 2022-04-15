This question was basically K closest points to the origin (0,0) with added tie condition.

Given a list of N possible delivery destinations, implement an algorithm to create the delivery plan for the closest X destinations.

**Input:** 
- `alLocations`, a list where each element consists of a pair of integers representing the x and y coordinates of the delivery locations;
- `numDeliveries`, an integer representing the number of deliveries that will be delivered in the plan (X).

**Output:** 
Return a list of elements where each element of the list represents the X closest x and y integer coordinates of the delivery destinations,
where X represents the `numDeliveries` input. If there is one tie, use the location with the closest X coordinate. If no location is possible,
return a list with an empty location - not just an empty list.

**Constraints:**
numDeliveries ≤ size(allLocations)

**Note:**
- The plan starts with the trucks location $[0, 0]$.
- The distance of the truck from a delivery destination (x, y) is the square root of $x^2 + y^2$
- If there are multiple ties, then return the locations starting with the closest x-coordinate as long as you satisfy returning exactly X delivery locations.
- The returned output can be in any order.

**Example:**
Input: allLocations = $[[1,2],[3,4],[1,-1]]$, numDeliveries=2
Output: $[[1,-1], [1,2]]$

```cpp
vector<vector<int>> findpath(vector<vector<int>>& allLocations, int numDeliveries) {  
	sort(allLocations.begin(), allLocations.end(), [](const vector<int> &a, const vector<int> &b){  
        int d1 = a[0] * a[0] + a[1] * a[1];  
		int d2 = b[0] * b[0] + b[1] * b[1];  
 		return d1 < d2;  
	});  
	return vector<vector<int>>(allLocations.begin(), allLocations.begin() + numDeliveries);  
}
```