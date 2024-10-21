#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <numeric>

#include "utils/printHelper.h"

using namespace std;

int oddEvenJumps(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 1;


    /**
     * @brief Generates jump indices for a given order of elements.
     *
     * This lambda function takes a vector of integers representing an order and 
     * generates a vector of jump indices. For each element in the order, it finds 
     * the next greater element and records its index. If no greater element exists, 
     * the index remains -1.
     *
     * @param order A vector of integers representing the order of elements.
     * @return A vector of integers where each element is the index of the next 
     *         greater element in the order. If no greater element exists, the 
     *         index is -1.
     */
    auto make_jump_indices = [&](vector<int>& order) {
        vector<int> result(n, -1); // Initialize result vector with -1
        stack<int> stk; // Stack to keep track of indices
        for (int i : order) { // Iterate over each index in the order
            while (!stk.empty() && stk.top() < i) { // Find the next greater element
                result[stk.top()] = i; // Record the index of the next greater element
                stk.pop(); // Remove the index from the stack
            }
            stk.push(i); // Push the current index onto the stack
        }
        return result; // Return the result vector
    };

    // Initialize sorted_indices with values from 0 to n-1
    vector<int> sorted_indices(n);
    iota(sorted_indices.begin(), sorted_indices.end(), 0);

    // Sort indices based on the values in arr for odd jumps
    sort(sorted_indices.begin(), sorted_indices.end(), [&](int i, int j) {
        return arr[i] < arr[j] || (arr[i] == arr[j] && i < j);
    });

    // Generate jump indices for odd jumps
    vector<int> odd_jump_indices = make_jump_indices(sorted_indices);

    // Sort indices based on the values in arr for even jumps
    sort(sorted_indices.begin(), sorted_indices.end(), [&](int i, int j) {
        return arr[i] > arr[j] || (arr[i] == arr[j] && i < j);
    });

    // Generate jump indices for even jumps
    vector<int> even_jump_indices = make_jump_indices(sorted_indices);

    // Initialize vectors to track good indices for odd and even jumps
    vector<bool> odd_good(n, false), even_good(n, false);
    odd_good[n - 1] = even_good[n - 1] = true; // Last index is always good

    // Traverse the array from second last to the first element
    for (int i = n - 2; i >= 0; --i) {
        // If there's a valid odd jump, mark current index based on even jump result
        if (odd_jump_indices[i] != -1) {
            odd_good[i] = even_good[odd_jump_indices[i]];
        }
        // If there's a valid even jump, mark current index based on odd jump result
        if (even_jump_indices[i] != -1) {
            even_good[i] = odd_good[even_jump_indices[i]];
        }
    }

    return count(odd_good.begin(), odd_good.end(), true);
}

// Example usage:
int main() {
    vector<int> arr = {10, 13, 12, 14, 15};
    
    cout << oddEvenJumps(arr) << endl;  // Output: 2
    return 0;
}