#include <string>
#include <unordered_set>
#include <algorithm>
#include <iostream>

using namespace std;
    
int lengthOfLongestSubstring(string s) {
    // this appears to be a sliding window problem:
    // we want to evaluate the longest sequence consisting of solely unique characters in this string.
    // This requres us to:
    // 1 evaluate every character in the string
    // 2 evaluate the longest span of characters possible starting at that character
    // 3 maintain a sequence of unique characters
    // 4 update that sequence and span as we encounter new characters.
    
    // a naieve approach requires O(N^2) evaluations, as we start at each character in the string and add characters to our evaluated substring until we encounter a duplicate.
    // an informed approach using a sliding window technique reduces this to ~O(n), where we need to do an O(1) set insertion and an O(1) set removal for every element in the collection, if it is all duplicates.
    // we can also maintain the maximum length of all subsequences evaluated so far.
    //
    //
    // We can break this down into a few important parts:
    //
    // windowStart = s.begin()
    // windowEnd = s.begin()
    // maxLength = 0
    // unique_elements_in_sequence = set()
    // for each element in array
    //  current = *windowEnd
    //  while (current in uniqueElementsInSequence ): // while we still are seeing duplicates, shrink the window from the left
    //      elementToRemove = *windowStart
    //      uniqueElementsInSequence.remove(element)
    //      windowStart++
    //  uniqueElementsInSequence.insert(current) // after we can insert a valid character, grow the window to the right.
    //  windowEnd++
    //  maxLength = max(maxLength, windowEnd - windowStart) // persist the longest of all evaluated subsequences.
    // return maxLength
    
    // lets implement this in modern c++, though our pseudo is already quite close to our implementation.
    auto windowStart = s.begin();
    auto windowEnd = s.begin();
    int maxLength = 0;
    unordered_set<int> uniqueChars;
    
    for(auto ch : s) // iterate through string front to back
    {
        while(uniqueChars.contains(ch))
        {
            auto to_remove = *windowStart;
            uniqueChars.erase(to_remove);
            windowStart++;
        }
        uniqueChars.insert(ch);
        windowEnd++;
        maxLength = max<int>(maxLength, windowEnd - windowStart);
    }
    return maxLength;
}

int main()
{
    string s = "abcabcbb";
    int expected = 3;
    cout << "Input: " << s << endl;
    cout << "Output: " << lengthOfLongestSubstring(s) << " Expected:" << expected << endl; // Output: 3
    return 0;
}