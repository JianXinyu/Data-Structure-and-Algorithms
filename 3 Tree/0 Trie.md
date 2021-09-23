---
cssclass: img-grid
---
https://leetcode-solution.cn/solutionDetail?type=2&id=4001&max_id=4007

## Intro
Trie/字典树/前缀树: 是一棵N叉树，常用于存储、查找字符串，删除用得比较少

前缀树的每一个结点代表一个字符串的前缀。根节点表示 空字符串。每一个结点会有多个子结点，通往不同子结点的路径上有着不同的字符。子结点代表的字符串是由结点本身的原始字符串 ，以及通往该子结点路径上所有的字符组成的。
![[trie.png | +side -med -left]]

前缀树的一个重要的特性是，结点所有的后代都与该结点相关的字符串有着共同的前缀，这是前缀树名称的由来。

## 结构
### Node
节点可能包括两部分：
- 数据域，存储字符
- 控制域，根据实际问题来定义，如isWord(是否是单词), count(前缀出现的次数)

子节点可以用Array存储，也可以用Hash表存储。如存储含有字母 `a` 到 `z` 的字符串，可以在每个节点中声明一个大小为 26 的数组来存储其子节点。对于特定字符 `c` ，使用 `c - 'a'` 作为索引来查找数组中相应的子节点。
```cpp
// change this value to adapt to different cases
#define N 26

struct TrieNode {
    TrieNode* children[N]; // Array
	// unordered_map<char, TrieNode*> children; // Hash
    
    bool isWord; // self-define
};

/** Usage:
 *  Initialization: TrieNode* root = new TrieNode();
 *  Return a specific child node with char c: (root->children)[c - 'a']
 */
```
### Insert
在前缀树中插入一个字符串 S，
- 从根节点开始， 根据 $S[0]$（S中的第一个字符），选择一个子节点或添加一个新的子节点。
- 到达第二个节点，根据 $S[1]$ 做出选择。 
- 再到第三个节点，以此类推。
- 最后，依次遍历 S 中的所有字符并到达末尾。 
- 末端节点将是表示字符串 S 的节点。
```text
1. Initialize: cur = root
2. for each char c in target string S:
3. 		if cur does not have a child c:
4.			cur.children[c] = new Trie node
5.		cur = cur.children[c]
6. cur is the node which represents the string S
```
**Note!** 首先初始化根节点

构建前缀树实际上就是多次调用插入函数。

### Find
```text
1. Initialize: cur = root
2. for each char c in target string S:
3. 		if cur does not have a child c:
4.			search fails
5.		cur = cur.children[c]
6. search successes
```

如何搜索特定的单词，而不是前缀?
- 首先将这个词作为前缀，按上述方法搜索
- 如果搜索失败，那么意味着没有单词以目标单词开头，那么目标单词绝对不会存在于前缀树中
- 如果搜索成功，需要检查目标单词是否是前缀树中单词的前缀，或者它本身就是一个单词。因此在前缀树定义时，控制域设为isWord

### Implementation
[208. Implement Trie (Prefix Tree)](https://leetcode-cn.com/problems/implement-trie-prefix-tree/)
```cpp
class Trie {
private:
    struct TrieNode{
        TrieNode* children[26];
        bool isWord;
    };

    TrieNode *root_;
public:
    /** Initialize your data structure here. */
    Trie() {
        root_ = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* cur = root_;
        for(char &ch : word){
            if( !cur->children[ch - 'a'] )
                cur->children[ch - 'a'] = new TrieNode();
            cur = cur->children[ch - 'a'];
        }
        cur->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* cur = root_;
        for(char &ch : word){
            if( !cur->children[ch - 'a'] )
                return false;
            cur = cur->children[ch - 'a'];
        }
        if( !cur->isWord )
            return false;
        return true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* cur = root_;
        for(char &ch : prefix){
            if( !cur->children[ch - 'a'] )
                return false;
            cur = cur->children[ch - 'a'];
        }
        return true;       
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
 ```

其实不需要单独为节点定义一个结构体。
```cpp
class Trie {
private:
    bool isEnd;
    Trie* next[26];
public:
    Trie() {
        isEnd = false;
        memset(next, 0, sizeof(next));
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            if (node->next[c-'a'] == NULL) {
                node->next[c-'a'] = new Trie();
            }
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            node = node->next[c - 'a'];
            if (node == NULL) {
                return false;
            }
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            node = node->next[c-'a'];
            if (node == NULL) {
                return false;
            }
        }
        return true;
    }
};
```

**Caution!** 这里并没有进行内存释放。算法题一般不需要考虑内存问题，但工程上必须考虑！

Complexity Analysis:
Time: 插入和查找 O(len), len为字符串长度
Space: 最坏情况$O(m^n)$. Trie 的每个结点中都保留着一个字母表，很耗费空间。如果 Trie 的高度为 n，字母表的大小为 m，最坏的情况是 Trie 中不存在前缀相同的单词。

## 总结
**前缀树的核心思想就是空间换时间**。将一系列的单词记录到树上， 如果这些单词没有公共前缀，则和直接用数组存没有任何区别。而如果有公共前缀， 则公共前缀仅会被存储一次。可以想象，如果一系列单词的公共前缀很多， 则会有效减少查询的时间消耗。

换句话说，如果一组单词没有公共前缀，使用前缀树没有任何意义。

查询可以完整查询，也可以前缀查询，其中基于前缀查询才是前缀树的灵魂，也是其名字的来源。
## 应用
什么时候用前缀树? 算法的复杂度瓶颈在字符串查找，并且字符串有很多公共前缀，就可以用前缀树优化。

实际应用:
1.  [自动补全](https://en.wikipedia.org/wiki/Autocomplete)
2.  [拼写检查](https://en.wikipedia.org/wiki/Spell_checker)（[添加与搜索单词 - 数据结构设计](https://leetcode-cn.com/leetbook/read/trie/x0jtri/)）

-   [0211.添加与搜索单词 - 数据结构设计](https://github.com/azl397985856/leetcode/blob/b0b69f8f11dace3a9040b54532105d42e88e6599/problems/211.add-and-search-word-data-structure-design.md)
    
-   [0212.单词搜索 II](https://github.com/azl397985856/leetcode/blob/b0b69f8f11dace3a9040b54532105d42e88e6599/problems/212.word-search-ii.md)
    
-   [0472.连接词](https://github.com/azl397985856/leetcode/blob/master/problems/472.concatenated-words.md)
    
-   [648. 单词替换](https://leetcode-cn.com/problems/replace-words/)
    
-   [0820.单词的压缩编码](https://github.com/azl397985856/leetcode/blob/master/problems/820.short-encoding-of-words.md)
    
-   [1032.字符流](https://github.com/azl397985856/leetcode/blob/master/problems/1032.stream-of-characters.md)


给你若干单词 words 和一系列关键字 keywords，让你判断 keywords 是否在 words 中存在，或者判断 keywords 中的单词是否有 words 中的单词的前缀。比 pre 就是 pres 的前缀**之一**。

如果使用 Trie 来解，会怎么样呢？首先我们需要建立 Trie，这部分的时间复杂度是 O(t)，其中 t 为 words 的总字符。**预处理**完毕之后就是查询了。对于查询，由于树的高度是 O(m)，其中 m 为 words 的平均长度，因此查询基本操作的次数不会大于 m。当然查询的基本操作次数也不会大于 k，其中 k 为被查询单词 keyword 的长度，因此对于查询来说，时间复杂度为 O(min(m, k))。时间上优化的代价是空间上的消耗，对于空间来说则是预处理的消耗，空间复杂度为 O(t)。