#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>

#include <utils/printHelper.h>

using namespace std;
using namespace utils;

class SolutionNLogN {
public:
    int longestSquareStreak(vector<int>& nums) {
        // we represent this array in an alternate way to speed up how we check for a sequence.
        const long int nums_max = 100000; // max of 10^5
        int sequenceLengths[nums_max + 1]; // initialize all possible numbers in sequence to 0;
        fill_n(sequenceLengths, nums_max + 1, 0); // for some reason some garbage can get set in sequence_lengths. set to 0.

        sort(nums.begin(), nums.end()); // O(nlog(n)) sort array smallest to largest. 

        // for each element in the array, compute the max square sequence length.
        int maxSequenceLength = 0;
        for (int i = nums.size()-1; i >= 0; --i) // O(n) iterations.
        {
            int value = nums[i];
            //cout << "Processing: " << value;
            long int square = static_cast<long int>(value);
            square = square * square;
            //cout << " Value is: " << value;

            //cout << " Square is: " << square; 
            int sequenceLength = 0;
            if (square <= nums_max)
            {
                sequenceLength = sequenceLengths[square];
                //cout << " Square has sequence length: " << sequenceLength;
            }
            
            //cout << " Sequence Length: " << sequenceLength;
            sequenceLengths[value] = sequenceLength + 1;
            maxSequenceLength = max(sequenceLength, maxSequenceLength);
            //cout << " maxSequenceLength: " << maxSequenceLength << endl;
        }

        if (maxSequenceLength < 1)
        {
            return -1; // we did not find a sequence longer than 1.
        }
        return maxSequenceLength + 1;
    }
};

class SolutionLinear
{
public:
    int longestSquareStreak(vector<int>& nums) {
        // we represent this array in an alternate way to speed up how we check for a sequence.
        const long int nums_max = 100000; // max of 10^5

        bitset<nums_max+1> hasNumber; // use a 10^5 long bitset to store the presence of a number in our input array
        int maxNum = 0; // keep track of largest number in input array, it controls the maximum number of iterations we need to do.
        
        for (auto num : nums) // O(n) iteration through input array
        {
            hasNumber[num] = 1;
            maxNum = max(maxNum, num); 
        }

        int maxSequence = 0;
        int currentSequence = 0;
        int maxNumToTest = sqrt(maxNum); // we only need to check all the numbers that can have our maximum number next in its sequence.
        for (int i = 0; i <= maxNumToTest; ++i) // ~O(sqrt(n)) iteration through
        {
            if (!hasNumber[i]) continue;

            //cout << "Checking: " << i;
            currentSequence = 1;
            for (long int j = i*i; j <= maxNum; j *= j) // iterate through the sequence, checking if the next number is in our input array.
            {
                if (!hasNumber[j])
                {
                    break;
                }
                //cout << " Next: " << j;
                currentSequence++;
            }
            maxSequence = max(currentSequence, maxSequence); // keep track of the longest sequence seen so far.
            //cout << " Max Sequence: " << maxSequence << endl;
        }

        if (maxSequence <= 1)
        {
            return -1;
        }

        return maxSequence;
    }
};

class Solution : public SolutionLinear {};

int main()
{
    {
        vector<int> input = {4,3,6,16,8,2};
        Solution s;
        auto result = s.longestSquareStreak(input);
        cout << "Input: " << printVector(input) << endl;
        int expected = 3;
        cout << "Output: " << result << " Expected: " << expected << endl;
    }
    {
        vector<int> input = {2,3,5,6,7};
        Solution s;
        auto result = s.longestSquareStreak(input);
        cout << "Input: " << printVector(input) << endl;
        int expected = -1;
        cout << "Output: " << result << " Expected: " << expected << endl;
    }
    {
        vector<int> input = {4,16,256,65536};
        Solution s;
        auto result = s.longestSquareStreak(input);
        cout << "Input: " << printVector(input) << endl;
        int expected = 4;
        cout << "Output: " << result << " Expected: " << expected << endl;
    }
}