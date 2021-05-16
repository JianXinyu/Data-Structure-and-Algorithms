//1. We want to keep track of last time it rained for each city in fullLakes,
//      a Map<Integer, Integer>.
//2. One idea is that each time it rains to a city where it rained before,
//      we want to find a dry day in between the 2 rain days so that we can dry the lake.
//3. The optimal way to do it is to choose the smallest such available dry day.
//4. To do that we store all available dry day in a TreeSet<Integer> noRain.
//5. Once we find the dry day we update the int[] res.
//6. At the end we fill the remaining dry days with 1s.

vector<int> avoidFlood(vector<int>& rains) {
    // Keep track of full lakes and the last rain date for them.
    unordered_map<int, int> fullLakes;
    // Keep track of days with no rain that we didn't use yet.
    set<int> noRain;
    // Hold result to return.
    vector<int> res(rains.size(), INT_MIN);

    for(int i = 0; i < rains.size(); i ++){
        if(rains[i] > 0){
            int index = rains[i]; // lake index
            // if lake is already full
            if(fullLakes.count(index)){
                // if there is no dry day left to use, we can never dry the lake
                if(noRain.empty()) return {};
                // otherwise, we choose a dry day to use
                // note, this dry day must be after the rain day
                set<int>::iterator iter = noRain.lower_bound(fullLakes[index]);
                if(iter == noRain.end()) return {};
                res[*iter] = index;
                noRain.erase(iter);
            }
            res[i] = -1;
            fullLakes[index] = i;
        }
        else noRain.insert(i);
    }

    for(int& e: res) if(e == INT_MIN) e = 1;
    return res;
}