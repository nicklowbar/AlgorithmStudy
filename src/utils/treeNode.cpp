#include "utils/treeNode.h"
#include <climits>
#include <queue>

//TODO: add test for this function
TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

//TODO: add test for this function
TreeNode::TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

//TODO: add test for this function
TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr) {}

//TODO: add test for this function
TreeNode::TreeNode(std::vector<int>& input) {
    if (input.size() == 0) {
        return;
    }
    val = input[0];
    std::queue<TreeNode*> q;
    TreeNode* current = this;
    for (int i = 1; i < input.size(); i++) {
        if (input[i] > INT_MIN) {
            current->left = new TreeNode(input[i]);
            q.push(current->left);
        } else {
            current->left = nullptr;
        }
        i++;
        if (i < input.size() && input[i] > INT_MIN) {
            current->right = new TreeNode(input[i]);
            q.push(current->right);
        } else {
            current->right = nullptr;
        }
        current = q.front();
        q.pop();
    }
}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

//TODO: add test for this function
std::string printTree(TreeNode* root) {
    std::string result = "[";
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        if (current == nullptr) {
            result += "null";
        } else {
            result += std::to_string(current->val);
            q.push(current->left);
            q.push(current->right);
        }
        if (!q.empty()) {
            result += ", ";
        }
    }
    result += "]";
    return result;
}

