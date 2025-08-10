// file created for sake of analysis. code not original.

#include <bits/stdc++.h>

using namespace std;

bool next(int n, char *arr) {
    int i = n-2; 

    while (i >= 0 && arr[i] > arr[i+1])
        --i;
    
    if (i < 0) 
        return false;
    
    int j = n-1;
    while (arr[j] < arr[i]) 
        --j;

    swap(arr[i], arr[j]);

    reverse(&arr[i+1], &arr[n]);

    return true;
}

bool ok( size_t n, size_t * queens )
{
for ( size_t i = 0; i < n; ++i)
for ( size_t j = i+1; j < n; ++j) {
size_t d;
if ( queens [i] < queens [j])
d = queens [j]- queens [i];
else
d = queens [i]- queens [j];
 if (d == j-i)
 return false ;
 }
 return true ;
 }

int main() {

    char test[] = "0123";
    int n = 4;
    for (int i = 0; i < 100; ++i) {
        cout << test << endl;
        next(n, test);
    }
    cout << test << endl;
    return 1;
}