// Let i be the index of a needle in the haystack or N if it is absent
// from the haystack. Design an algorithm that runs in time proportional to log (i)
// to search for the needle in the haystack if the elements are arranged in order

#include <iostream>

// assuming haystack is already sorted.
template <typename T>
size_t search(T *haystack, size_t n, const T& needle) {
    size_t end;
    for (end = 1; end < n; end *= 2) {
        if (haystack[end] > needle)
            break;
    }

    size_t start = 0;
    if (end > n) end = n;
    // now run binary search
    while (start < end) {
        size_t mid = start + (end - start) / 2;
        if (haystack[mid] > needle) {
            end = mid;
        } else if (haystack[mid] < needle) {
            start = mid + 1;
        } else {
            return mid;
        }
    }

    return n;
}


int main() {

    int a[] = {1, 2, 3, 4, 5, 6, 7};
    std::cout << search<int>(a, 7, 9) << std::endl;

}