#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

char findKthBit(int n, int k) {
    // a naieve solution would be for us to generate the S(n) string, and index into it to find the kth bit. 
    // in order to do so we need to allocate enough space to store S(n), 
    // S(n) = 2*S(n-1) + 1
    // sizeof(S(n)) = 2^n - 1
    // therefore its _possible_ but untenable to solve this problem naively.
    // instead, since this string is a recursive pattern, we can recursively solve this using a divide and conquer strategy(?).
    // we know that our base case is that S(1) = 0, and for S(n) | n > 1, S(n)[middle] == 1;
    // if neither are true, then from there we can recurse, into an index of the substring of the current string depending on whether we need to recurse into the left substring or the right substring, based on the index.
    // for the left substring, our indices should propagate as expected, however if we are in the right substring, then we need to compute the "mirror" index and invert the value we retrieve as we propagate back up the recursive stack.
    std::function<char(int, int)> computeKthBit;
    computeKthBit = [&](int n, int k) -> char {
        //cout << "n = " << n << " k = " << k << endl;
        // Base case 0: S(1) = '0'
        if (n == 1)
        {
            return '0';
        }
        int sLength = pow(2, n) - 1; // compute the length of this substring.
        int middle = sLength/2; // compute the middle index of this substring.
        // base case 1: S(middle) = '1'
        if (k == middle){
            return '1';
        }

        if (k < middle)
        {
            return computeKthBit(n-1, k);
        }
        else
        {
            // compute the mirror index reflected through the middle index by computing the difference from the given index to the middle, and take that difference from the middle.
            //cout << "inverting..." << endl;
            return computeKthBit(n-1, middle - (k - middle)) == '0' ? '1' : '0'; // invert the right side bit.
        }

    };

    return computeKthBit(n, k-1);
}

int main(){
    auto runTestCase([](int n, int k, char expected) {
        auto result = findKthBit(n, k);
        cout << "Input: n = " << n << " k = " << k << endl;
        cout << "Output: " << result << " Expected: " << expected << endl;
        cout << (result == expected ? "PASS": "FAIL") << endl;
    });

    runTestCase(3, 1, '0'); // Output: 0 Expected: 0
    runTestCase(4, 11, '1'); // Output: 1 Expected: 1
    runTestCase(1, 1, '0'); // Output: 0 Expected: 0
    runTestCase(2, 3, '1'); // Output: 1 Expected: 1
    runTestCase(8, 158, '0'); // Output: 1 Expected: 1
    runTestCase(8, 200, '1'); // Output: 1 Expected: 1
    runTestCase(20, 1000000, '1'); // Output: 1 Expected: 1
    
}