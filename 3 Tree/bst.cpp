/**
 * @file bst.cpp
 * @author Xinyu Jian
 * @brief example code of the BST, mostly copied from the book
 * @version 0.1
 * @date 2022-06-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief   internal method to remove from a subtree,
 *          and set the new root of the subtree.
 * @tparam  Comparable 
 * @param x the item to remove
 * @param t the node that roots the subtree
 */
template <typename Comparable>
void remove(const Comparable & x, BinaryNode * & t) {
    if (t == nullptr) // item not found, do nothing
        return;
    if (x < t->val)
        remove(x, t->left);
    else if (x > t->val)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) // two children
    {
        // It is inefficient because it makes two passes down the tree 
        // to find and delete the smallest node in the right subtree.
        // Writing a special `removeMin` method is better.
        t->val = findMin(t->right)->val;
        remove(t->val, t->right);
    }
    else // one child or leaf
    {
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}