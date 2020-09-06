#pragma once

#include <vector>

using std::vector;

/// Binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/// N-ary tree node.
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {
        val = 0;
        children = std::vector<Node*>();
    }

    explicit Node(int val_) {
        val = val_;
    }

    explicit Node(int val_, const std::vector<Node*>& children_) {
        val = val_;
        children = children_;
    }
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class RandomNode {
public:
    int val;
    Node* next;
    Node* random;

    explicit RandomNode(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

struct DoublyListNode {
    int val;
    ListNode *next;
    ListNode *prev;
    DoublyListNode() : val(0), next(nullptr), prev(nullptr) {}
    explicit DoublyListNode(int x) : val(x), next(nullptr), prev(nullptr) {}
    DoublyListNode(int x, ListNode *next, ListNode *prev) : val(x), next(next), prev(prev) {}
};

class MultilevelDoublyListNode {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};