// Given an n-element array A of integers that is obtained by rotating
// an array sorted in increasing order and an element v as input, output the index
// of v in A if it exists or −1.
// To illustrate the property of the input array, note that the input array {4, 5, 6, 1, 2, 3}
// is obtained by rotating {1, 2, 3, 4, 5, 6} three places to the right.


#include <iostream>

int main() {
    // the algorithm is trivial so im not typing it out. 
    // use one binary search to find where the point is where the order breaks, then
    // using the bounds of the two partition by the pivot, determine which partition 
    // likely has the needle. and then run regular binary search on that sorted partition.
}