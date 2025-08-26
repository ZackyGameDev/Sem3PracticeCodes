#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int DX[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int DY[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

struct node {
    int board[8*8];
    int pos[8*8 + 1];
    int last[8*8 + 1];
    int n, m;
    int total;
    int k;
};

void printBoard(struct node *p) {
    for (int r = 0; r < p->n; ++r) {
        for (int c = 0; c < p->m; ++c) {
            int val = p->board[r * p->m + c];
            printf("%d", val);
            if (c != p->m - 1) printf(" ");
        }
        printf("\n");
    }
}

void root(struct node *p, int n, int m, int sr, int sc) {
    p->n = n; p->m = m;
    p->total = n * m;
    for (int i = 0; i < n*m; ++i) {
        p->board[i] = 0;
    }
    for (int i = 0; i <= n*m; ++i) {
        p->pos[i] = -1;
        p->last[i] = -1;
    }
    int sidx = sr * m + sc;
    p->pos[1] = sidx;
    p->board[sidx] = 1;
    p->k = 1;
    p->last[1] = -1;
}

bool ok(struct node *p, int nr, int nc) {
    if (nr < 0 || nc < 0 || nr >= p->n || nc >= p->m) return false;
    if (p->board[nr * p->m + nc] != 0) return false;
    return true;
}

bool leaf(struct node *p) {
    if (p->k != p->total) return false;
    int last_idx = p->pos[p->k];
    int sr_idx = p->pos[1];
    int lr = last_idx / p->m;
    int lc = last_idx % p->m;
    int sr = sr_idx / p->m;
    int sc = sr_idx % p->m;
    for (int d = 0; d < 8; ++d) {
        int nr = lr + DY[d];
        int nc = lc + DX[d];
        if (nr == sr && nc == sc) return true;
    }
    return false;
}

bool down(struct node *p) {
    if (p->k >= p->total) return false; 

    int cur_idx = p->pos[p->k];
    int cr = cur_idx / p->m;
    int cc = cur_idx % p->m;

    int start_dir = p->last[p->k + 1] + 1;
    for (int d = start_dir; d < 8; ++d) {
        int nr = cr + DY[d];
        int nc = cc + DX[d];
        if (!ok(p, nr, nc)) continue;
        int nidx = nr * p->m + nc;
        p->board[nidx] = p->k + 1;
        p->pos[p->k + 1] = nidx;
        p->last[p->k + 1] = d;
        ++(p->k);
        if (p->k + 1 <= p->total) p->last[p->k + 1] = -1;
        return true;
    }
    p->last[p->k + 1] = 7;
    return false;
}

bool up(struct node *p) {
    if (p->k == 1) return false;
    int cur_idx = p->pos[p->k];
    p->board[cur_idx] = 0;
    p->pos[p->k] = -1;
    --(p->k);
    return true;
}


bool solve(struct node *p) {
    unsigned long long steps = 0;
    while (1) {
        if (leaf(p)) break;
        if (!down(p)) {
            if (!up(p)) break;
        }
        ++steps;
    }
    if (leaf(p)) return true;
    return false;
}

int main(void) {
    int n, m, r, c;
    if (scanf("%d %d %d %d", &n, &m, &r, &c) != 4) return 0;
    struct node p;
    root(&p, n, m, r, c);
    if (solve(&p)) {
        printBoard(&p);
    } else {
        printf("-1\n");
    }
    return 0;
}
