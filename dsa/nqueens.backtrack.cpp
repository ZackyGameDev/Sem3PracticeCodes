// technically not original code but i did type this out myself.


#include <bits/stdc++.h>

using namespace std;


struct node {
    size_t n;
    size_t k;
    size_t *queens;
    size_t last;
};


void root(int n, node *p) {
    p->n = n;
    p->k = 0;
    p->queens = (size_t *)malloc(n * sizeof(size_t));
    p->last = -1;
    assert(p->queens);
}

bool ok(node *p) {
    for (size_t i = 0; i < p->k; i++) {
        for (size_t j = i+1; j < p->k; ++j) {
            size_t d;
            if (p->queens[i] > p->queens[j]) {
                d = p->queens[i] - p->queens[j];
            } else {
                d = p->queens[j] - p->queens[i];
            }
            if (d == j-i) { 
                return false;
            }
        }
    }
    return true;

}

bool up(node *p) {
    if (p->k <= 0) 
        return false;
    p->last = p->queens[p->k-1];
    --(p->k);

    // for (int i = 0; i < p->k; ++i) 
    //     cout << p->queens[i];
    // cout << endl;

    return true;

}

bool down(node *p) {
    if (p->k >= p->n)
        return false;
    
    size_t *used = (size_t *)malloc(p->n * sizeof(size_t));
    for (size_t i = 0; i < p->n; ++i) {
        used[i]= false;
    }
    for (size_t i = 0; i < p->k; ++i) {
        used[p->queens[i]]= true;
    }
    
    for (size_t i = p->last+1; i < p->n; ++i) {
        if (!used[i]) {
            ++(p->k);
            p->queens[p->k-1] = i;
            p->last = -1;

            // for (int i = 0; i < p->k; ++i) 
            //     cout << p->queens[i];
            // cout << endl;
            
            free(used);
            return true;
        }
    }
    free(used);
    return false;
}

bool leaf(struct node *p) {
    return (p->k==p->n);
}

int nqueens(int n) {
    struct node obj;
    struct node *p = &obj; 
    assert(p);
    root(n, p);
    
    size_t c = 0;

    while (true) {

        if (leaf(p)) {
            if (ok(p))
                ++c;
            if(!up(p))
                break;
        } else {
            if (!ok(p)) {
                if(!up(p))
                    break;
            } else {
                if (!down(p))
                    if (!up(p))
                        break;
            }
        }
    }
    return c;

}


int main() {
    for (int i = 0; i < 9; ++i)
        cout << nqueens(i) << endl;
    return 0;
}
