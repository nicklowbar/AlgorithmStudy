#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int maxArea(vector<int>& height) {
    // this appears to be a sliding window problem:
    // we need to find the largest "area" enclosed by two indices i and j such that:
    // i < j, and area = min(height[i], height[j]) * j - i;
    // a naieve approach would require ~O(n^2) iterations, checking area for each combination of indices i and j
    // however, since we are optimizing for area, we can eliminate many redundant computations by greedily only retaining a reference to the larger of the two walls currently referenced, starting with two opposing pointers that start at either end, maximizing our starting width.
    
    auto left = height.begin();
    auto right = --height.end();
    
    int result = 0;
    while (left != right)
    {
        //cout << "left: " << *left << " right: " << *right << endl;
        result = max<int>(result, min(*left, *right) * (right - left));
        if (*left < *right)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return result;
}

int main()
{
    {
        vector<int> height = {1,8,6,2,5,4,8,3,7};
        int expected = 49;
        cout << "Input: " << endl;
        cout << "Output: " << maxArea(height) << " Expected: " << expected << endl;
    }
    {
        vector<int> height = {1,1};
        int expected = 1;
        cout << "Input: " << endl;
        cout << "Output: " << maxArea(height) << " Expected: " << expected << endl;
    }
    {
        vector<int> height = {4,3,2,1,4};
        int expected = 16;
        cout << "Input: " << endl;
        cout << "Output: " << maxArea(height) << " Expected: " << expected << endl;
    }
    {
        vector<int> height = {1,2,1};
        int expected = 2;
        cout << "Input: " << endl;
        cout << "Output: " << maxArea(height) << " Expected: " << expected << endl;
    }
    return 0;

}