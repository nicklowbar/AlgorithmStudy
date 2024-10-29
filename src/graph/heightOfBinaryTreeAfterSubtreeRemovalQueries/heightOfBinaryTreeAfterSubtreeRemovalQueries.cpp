#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <unordered_map>
#include <utils/printHelper.h>
#include <utils/treeNode.h>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

#ifndef NAIEVE
    #define NAIEVE 1
#endif
#ifndef MEMOIZED_MAP
    #define MEMOIZED_MAP 2
#endif
#ifndef DP_MEMOIZED_ARRAY
    #define DP_MEMOIZED_ARRAY 3
#endif

#define USE_SOLUTION DP_MEMOIZED_ARRAY

#if USE_SOLUTION==NAIEVE
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {

        // we want to find the tallest subtree possible if we remove a given node from the tree.
        // we do not rebalance the tree after this removal.
        //
        // we can do a DFS tree traversal, ignoring any subtree that has the given value we are querying for.
        // returning the maximum depth of the remaining tree.
        // This approach works, but is O(m * n) where we need to traverse the entire tree for each query.
        auto queryTreeMinus([](auto&& queryTreeMinus, TreeNode* node, int value){
            if (node == nullptr || node->val == value){
                return 0;
            }
            return 1 + max(queryTreeMinus(queryTreeMinus, node->left, value), queryTreeMinus(queryTreeMinus, node->right, value));
        });

        // preallocate result array
        vector<int> result;
        result.reserve(queries.size());

        // compute maximum tree size for every query.
        for (auto query : queries)
        {
            result.push_back(queryTreeMinus(queryTreeMinus, root, query) - 1);
        }
        return result;
    }
#endif

#if USE_SOLUTION==MEMOIZED_MAP
        vector<int> treeQueries(TreeNode* root, vector<int>& queries) {

        // we want to find the tallest subtree possible if we remove a given node from the tree.
        // we do not rebalance the tree after this removal.
        //
        // we can do a DFS tree traversal, ignoring any subtree that has the given value we are querying for.
        // returning the maximum depth of the remaining tree.
        //
        // since we already need to traverse the entire tree once, we should avoid having to do it multiple times, use some acceleration structure(s) to speed up a query of "how deep in the tree is element X" and a query of "are there any other elements at that depth?"
        // 
        // A data structure that comes to mind is a combination of hashmaps, where we can query if an element exists, and insert elements in (amortized)O(1)!
        // we can preprocess the tree, and store the depth of each element, and also store the maximum depth of its sibling node. 
        // we can then reduce our time complexity for all queries to ~O(n), worst case O(m*n) where we need to query our acceleration structure m times to find the next longest branch length.

        unordered_map<int, int> nodeMaxDepth;        

        auto computeMaxTreeDepth([&nodeMaxDepth](auto&& computeMaxTreeDepth, TreeNode* node, int depth){
            // Base case: an empty leaf node should not modify the current depth.
            if (node == nullptr){
                return depth - 1;
            }
            
            // Inductive step: a node's max depth is either its left or right leg's max depth.
            int maxLeftDepth = computeMaxTreeDepth(computeMaxTreeDepth, node->left, depth + 1);
            int maxRightDepth = computeMaxTreeDepth(computeMaxTreeDepth, node->right, depth + 1);
            
            depth = max(maxLeftDepth, maxRightDepth);
            nodeMaxDepth[node->val] = depth;
            return depth;
        });

        auto computeMaxSubtreeMinusDepth([&nodeMaxDepth](auto&& computeMaxSubtreeMinusDepth, TreeNode* node, int depth, int maxOtherDepth){
            // Base case: an empty leaf node should not modify the current depth.
            if (node == nullptr){
                return;
            }

            nodeMaxDepth[node->val] = maxOtherDepth;

            // inductive step: there are 3 places where the max depth of a tree minus a given node can be observed:
            //  1) its sibling node's max depth
            //  2) its parent's node's max depth
            //  2) recursively found elsewhere in the tree from its parent node.
            int maxLeftDepth = depth;
            int maxRightDepth = depth;
            if (node->left) {
                maxLeftDepth = nodeMaxDepth[node->left->val];
            }
            if (node->right){
                maxRightDepth = nodeMaxDepth[node->right->val];
            }

            computeMaxSubtreeMinusDepth(computeMaxSubtreeMinusDepth, node->left, depth + 1, max(maxRightDepth, maxOtherDepth));
            computeMaxSubtreeMinusDepth(computeMaxSubtreeMinusDepth, node->right, depth + 1,max(maxLeftDepth, maxOtherDepth));

        });

        // precompute tree information acceleration structures.
        computeMaxTreeDepth(computeMaxTreeDepth, root, 0);

        //cout << "Node max depth: " << endl;
        //for (auto p : nodeMaxDepth){
        //    cout << p.first << " -> " << p.second << endl;
        //}

        // compute the max tree depth excepting each node
        computeMaxSubtreeMinusDepth(computeMaxSubtreeMinusDepth, root, 0, 0);

        //cout << "Tree max depth excepting node: " << endl;
        //for (auto p : nodeMaxDepth){
        //    cout << p.first << " -> " << p.second << endl;
        //}
        // preallocate result array
        vector<int> result;
        result.reserve(queries.size());

        // compute maximum tree size for every query.
        for (auto query : queries)
        {
            int depth = nodeMaxDepth[query];
            result.push_back(depth);
        }
        return result;
    }
#endif
#if USE_SOLUTION==DP_MEMOIZED_ARRAY

    int maxDepth[100001]; // we have max 10^5 values we can encounter, use a flat array to store their max depth.
    int maxCurrentDepth = 0; // use a global variable to store the max depth as we traverse without needing closures.

    void traverseLeftToRight(TreeNode* node, int depth)
    {
        if (node == nullptr) return;

        // store this value in our cache.
        maxDepth[node->val] = maxCurrentDepth;

        // update our global maximum depth encountered so far.
        maxCurrentDepth = max<int>(depth, maxCurrentDepth);
        
        // continue traversing the tree, in left to right order.
        traverseLeftToRight(node->left, depth + 1);
        traverseLeftToRight(node->right, depth + 1);
    }

    void traverseRightToLeft(TreeNode* node, int depth)
    {
        if (node == nullptr) return;

        // store this value in our cache.
        maxDepth[node->val] = max(maxCurrentDepth, maxDepth[node->val]);

        // update our global maximum depth encountered so far.
        maxCurrentDepth = max(depth, maxCurrentDepth);
        
        // continue traversing the tree, in right to left order.
        traverseRightToLeft(node->right, depth + 1);
        traverseRightToLeft(node->left, depth + 1);
    }

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        // This is a two pass approach, similar to our previous attempts, but unique.

        // using a dynamic variable, we can keep track of the concept of "what is the maximum depth of all nodes evaluated before this node?"

        // doing a left to right and right to left prefix traversals, and keeping track of the maximum between both passes allow us to combine both concepts to represent "what is the maximum depth of all other nodes in the tree except my subtree?" without requiring n passes to do so, or an expensive map to maintain and do 2*n hashes and dereferences to access.
        
        traverseLeftToRight(root, 0);
        maxCurrentDepth = 0;
        traverseRightToLeft(root, 0);

        vector<int> result(queries.size());
        for (int i = 0; i < queries.size(); ++i)
        {
            result[i] = maxDepth[queries[i]];
        }

        return result;
    }

#endif
};

int main()
{
    /* TODO: these are actually tests for TreeNode and constructors, move them to a separate file.
    {
        TreeNode* root = new TreeNode(1);
        cout << printTree(root) << endl;
        vector<int> arr = {1};
        TreeNode* rootArray = new TreeNode(arr);
        cout << printTree(rootArray) << endl;
    }

    {
        TreeNode* root = new TreeNode(1, new TreeNode(2), new TreeNode(3));
        cout << printTree(root) << endl;
        vector<int> arr = {1, 2, 3};
        TreeNode* rootArray = new TreeNode(arr);
        cout << printTree(rootArray) << endl;
    }
    
    {
        TreeNode* root = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3, new TreeNode(6), new TreeNode(7)));
        cout << printTree(root) << endl;
        vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
        TreeNode* rootArray = new TreeNode(arr);
        cout << printTree(rootArray) << endl;
    }
    
    return 0;
    */
    { //TODO: refactor these as test cases.
        
        Solution s;
        vector<int> input = {1, 3, 4, 2, INT_MIN, 6, 5, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 7};
        TreeNode* root = new TreeNode( input );
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "\t as Tree: " << printTree(root) << endl;
        
        
        vector<int> queries = {4};
        cout << "Queries: " << utils::printVector(queries) << endl;
        auto result = s.treeQueries(root, queries);

        vector<int> expected = {2};
        cout << "Output: " << utils::printVector(result) << "\nExpected: " << utils::printVector(expected) << endl;
        delete(root);
    }
    {
        Solution s;
        vector<int> input = {5, 8, 9, 2, 1, 3, 7, 4, 6};
        TreeNode* root = new TreeNode( input );
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "\t as Tree: " << printTree(root) << endl;

        vector<int> queries = {3, 2, 4, 8};
        cout << "Queries: " << utils::printVector(queries) << endl;
        auto result = s.treeQueries(root, queries);

        vector<int> expected = {3, 2, 3, 2};
        cout << "Output: " << utils::printVector(result) << "\nExpected: " << utils::printVector(expected) << endl;
    }
    {
        Solution s;
        vector<int> input = {1, INT_MIN, 5, 3, INT_MIN, 2, 4};
        TreeNode* root = new TreeNode( input );
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "\t as Tree: " << printTree(root) << endl;

        vector<int> queries = {3, 5, 4, 2, 4};
        cout << "Queries: " << utils::printVector(queries) << endl;
        auto result = s.treeQueries(root, queries);

        vector<int> expected = {1, 0, 3, 3, 3};
        cout << "Output: " << utils::printVector(result) << "\nExpected: " << utils::printVector(expected) << endl;
    }
}