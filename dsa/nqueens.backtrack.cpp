// file created for sake of analysis. code not original.

#include <bits/stdc++.h>

using namespace std;

struct node {
    size_t n;
    size_t *queens;
    size_t k;
    size_t last;
};

void root(size_t n, struct node *p) {
    p->n = n;
    p->queens = (size_t*)malloc(n * sizeof(size_t));
    assert(p->queens);
    p->k = 0;
    p->last = (size_t)-1; // Start before 0 so down() begins from index 0
}

bool up(struct node *p) {
    if (p->k == 0) 
        return false;
    p->last = p->queens[p->k-1];
    --(p->k);
    return true;
}

bool down(struct node *p) {
    bool *used = (bool *)malloc(p->n * sizeof(bool));
    assert(used);

    for (size_t i = 0; i < p->n; ++i)
        used[i] = false;

    for (size_t i = 0; i < p->k; ++i)
        used[p->queens[i]] = true;

    for (size_t i = p->last + 1; i < p->n; ++i) {
        if (!used[i]) {
            p->queens[p->k] = i;
            ++(p->k);
            p->last = -1;
            free(used);
            return true;
        }
    }

    free(used);
    return false;
}

bool leaf(struct node *p) {
    return p->k == p->n;
}

bool ok(struct node *p) {
    for (size_t i = 0; i < p->k; ++i) {
        for (size_t j = i + 1; j < p->k; ++j) {
            // Same column
            if (p->queens[i] == p->queens[j])
                return false;

            // Same diagonal
            if ((p->queens[i] > p->queens[j] ? 
                 p->queens[i] - p->queens[j] : 
                 p->queens[j] - p->queens[i]) == (j - i))
                return false;
        }
    }
    return true;
}


size_t nqueens(size_t n) {
    struct node p;
    root(n, &p);

    size_t c = 0;

    while (true) {
        if (leaf(&p)) {
            if (ok(&p))
                ++c;

            if (!up(&p))
                break;

        } else {
            if (!ok(&p)) {
                if (!up(&p))
                    break;

            } else {
                if (!down(&p))
                    if (!up(&p))
                        break;
            }
        }
    }

    return c;
}

int main() {
    cout << nqueens(5);  
}
