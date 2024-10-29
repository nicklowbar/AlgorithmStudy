#pragma once
#include <vector>
#include <string>

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode();
    TreeNode(int x);
    TreeNode(int x, TreeNode* left, TreeNode* right);
    TreeNode(std::vector<int>& input);
    ~TreeNode();
};

std::string printTree(TreeNode* root);