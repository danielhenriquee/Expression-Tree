#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

// Generic tree node
template <typename T>
struct TreeNode {
    T data;
    TreeNode<T> *right; // Points to right child node
    TreeNode<T> *left; // Points to left child node
};

// Generic linked tree
template <typename T>
struct Tree {
    TreeNode<T> *root;
};

// Boot generic binary tree
template <typename T>
void bootTree(Tree<T> &tree) {
    tree.root = nullptr;
};

#endif // BINARY_TREE_H_INCLUDED
