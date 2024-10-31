#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <sstream>

#include "utils/printHelper.h"

using namespace std;


class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        // we want to create an array that strictly ascends, then descends.
        // we can do this by removing descending indices from the left, and ascending indices from the right
        // we should have a mountain if the next descending index occurs after the next ascending index.
        // we can use two stacks to store the next index to be removed on both sides.
        // 
        // iterate over the array front to back, an ascending index i is an index such that arr[i + 1] >= arr[i]
        /*
        stack<int> ascending;
        int numNums = nums.size();
        
        for(int i = 0; i < numNums - 2; ++i)
        {
            if (nums[i + 1] >= nums[i] )
            {
                ascending.push(i);
            }
        }
        
        // iterate over the array back to front, an descending index i is an index such that arr[i] >= arr[i+1]
        stack<int> descending;
        for(int i = numNums - 2; i >= 0; --i)
        {
            if (nums[i] >= nums[i+1])
            {
                descending.push(i);
            }
        }

        {
            stack<int> tmp = ascending;
            cout << "ascending index stack: ";
            while(!tmp.empty())
            {
                cout << tmp.top() << " ";
                tmp.pop();
            }
            cout << endl;
        }

        {
            stack<int> tmp = descending;
            cout << "descending index stack: ";
            while(!tmp.empty())
            {
                cout << tmp.top() << " ";
                tmp.pop();
            }
            cout << endl;
        }
        


        int removals = 0;

        // Now, remove ascending indices from the descening end, or remove descending indices from the ascending end until we reach equilibrium.
        while( descending.top() < ascending.top() )
        {
            if (descending.top() < ascending.top())
            {
                cout << "Removing index: " << descending.top() << endl;
                removals++;
                descending.pop();
            }
            if (ascending.top() > descending.top())
            {
                cout << "Removing index: " << ascending.top() << endl;
                removals++;
                ascending.pop();
            }
        }

        return removals;
        */

        // The previous approach doesn't work, due to 1: we are assuming that the mountain peak will be some index > 0 and < size - 1, which isn't necessarily the case. we need a more informed approach that will also inform as to which side of the mountain to remove items from, oppsed to always removing from both, and making sure we optimize our answer for all possible locations of our mountain peak.
        // We can keep track of the concept of "how long would this side of the mountain be (including the peak) if our peak was at this index?"
        // This is doable using a dynamic programming technique, storing this as a static array, and finding the peak index which yields the fewest removals to generate these longest increasing subsequences.
        //
        // This is a two step process:
        // 1) generate the longest increasing subsequence of numbers at each index encountered from front to back. (ascending)
        //      a) for an input array [2,3,1,2,3,5,6,2,3,1] the longest increasing subsequence is: [1,2,3,5,5,6]
        //      b) this will be generated as [1,2,2,2,3,4,5,5,5,5] in our algorithm
        // 2) generate the longest increasing subsequence of numbers at each index encountered from the back to front. (descending)
        //      a) for an input array [2,3,1,2,3,5,6,2,3,1] the longest decreasing subsequence is: [6,3,1] or [5,2,1] or some other 3 length permutation.
        //      b) this will be generated as [3,3,3,3,3,3,3,2,2,1] in our algorithm.
        // 3) evaluate the sum of the length of the forward and backwards subsequences at each index.
        //      a) this is represented as [4,5,5,5,6,7,8,7,7,6]
        //          i) notice how this sum naturally creates a mountain array, with the future peak indices overlapping.
        // 4) return the minimum difference between the sum of these subsequences and the original list. 
        //      a) this is stored in memory as the minimum input.size() - 3a[i] for 0 <= i <= input.size()
        // This difference represents the minimum amount of numbers to be removed from the sequence to create our mountain array.

        // First, how do we generate the length of these longest increasing subsequences?
        // use a helper function to return, for every index of the input array, the longest increasing subsequence length at each index, evaluated from start to end.
        int numSize = nums.size(); 
        auto getLisLengths = [](vector<int>& vec){
            int size = vec.size();
            // Base case: an element is a length 1 subsequence
            vector<int> lisLengths(size, 1); // initialize all possible subsequences as length 1

            vector<int> lis({vec[0]}); // initialize longest subsequence with the first element in the vector.
            for (int index = 1; index < size; ++index) // for every element in the array, 
            {
                int current = vec[index];
                // if our current is greater than the end of the current longest sequence, append it to the sequence
                if (current > lis.back())
                {
                    lis.push_back(current);
                }
                // otherwise replace the next largest element in the sequence with our element
                // in memory, this may represent an impossible sequence, however, this dynamically stores a future possible sequence,
                // updating lis.back() as we encounter possible sequence values.
                else 
                {
                    int index = lower_bound(lis.begin(), lis.end(), current) - lis.begin(); // find the index of the lowest value greater than current
                    lis[index] = current;
                }
                lisLengths[index] = lis.size();
            }
            return lisLengths;
        };
        #define PRINT 0
        #if PRINT
        auto vector_to_string = [](vector<int> input){
            stringstream result;
            result << "[ ";
            for (int i = 0; i < input.size(); ++i){
                result << input[i];
                if (i < input.size() - 1)
                {
                    result << ", ";
                }
            }
            result << " ]";
            return result.str();
        };

        cout << "Input: " << vector_to_string(nums) << endl;
        #endif

        // now, we can compute the forward and backwards traversing longest increasing series lengths.
        vector<int> lisForward = getLisLengths(nums);

        reverse(nums.begin(), nums.end()); // reverse the array to compute back to front
        vector<int> lisBackward = getLisLengths(nums);
        reverse(lisBackward.begin(), lisBackward.end()); // reverse the result so its back in the original array order.
        
        #if PRINT
        cout << "Longest Increasing Set: " << vector_to_string(lisForward) << endl;
        cout << "Longest Decreasing Set: " << vector_to_string(lisBackward) << endl;
        #endif

        // finally, compute the maximum mountain size, 
        int maxMountain = 0;
        for (int i = 0; i < numSize; ++i)
        {
            int lisForwardVal = lisForward[i];
            int lisBackwardVal = lisBackward[i];
            if (lisForwardVal > 1 && lisBackwardVal > 1) // remember, a mountain has to have atleast one element on either side of its peak.
            {
                maxMountain = max(lisForward[i] + lisBackward[i] - 1, maxMountain);
            }
        }

        return numSize - maxMountain;
    }
};

int main(){
    {
        Solution s;
        int expected = 0;
        vector<int> input({1,3,1});
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "Output: " << s.minimumMountainRemovals(input) << " Expected: " << expected << endl;
    }
    {
        Solution s;
        int expected = 3;
        vector<int> input({2,1,1,5,6,2,3,1});
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "Output: " << s.minimumMountainRemovals(input) << " Expected: " << expected << endl;
    }
    {
        Solution s;
        int expected = 3;
        vector<int> input({2,3,1,2,3,5,6,2,3,1});
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "Output: " << s.minimumMountainRemovals(input) << " Expected: " << expected << endl;
    }
    {
        Solution s;
        int expected = 2;
        vector<int> input({9,8,1,7,6,5,4,3,2,1});
        cout << "Input: " << utils::printVector(input) << endl;
        cout << "Output: " << s.minimumMountainRemovals(input) << " Expected: " << expected << endl;
    }
    
    return 0;
}