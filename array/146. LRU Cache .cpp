/**
 * 根据需求来设计data structure
 * Access to a random key in O(1) -> hashtable
 * Remove the last entry in LRU cache in O(1) -> list
 * Add/move an entry to the front of LRU cache in O(1) -> list
 * 有时候我们需要两个基本data structures to implement required functions.
 */
class LRUCache {

public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }

    int get(int key) {
        const auto itr = m_.find(key);

        // key doesn't exist
        if(itr == m_.end()) return -1;

        // Move the key to the front of the cache
        cache_.splice(cache_.begin(), cache_, itr->second);
        return itr->second->second;

    }

    void put(int key, int value) {
        const auto itr = m_.find(key);
        // if key exists
        if( itr != m_.end()){
            // update value
            itr->second->second = value;
            // move the key to the front of the cache
            cache_.splice(cache_.begin(), cache_, itr->second);
            return;
        }

        // check capacity, remove the LRU entry
        if(cache_.size() == capacity_){
            const auto& node = cache_.back();
            m_.erase(node.first);
            cache_.pop_back();
        }

        // insert the entry to the front of the cache
        cache_.emplace_front(key, value);
        m_[key] = cache_.begin();
    }

private:
    int capacity_;
    list<pair<int, int>> cache_;
    unordered_map<int, list<pair<int, int>>::iterator> m_;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */