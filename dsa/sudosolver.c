
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void printSudoku(int board[9*9]) {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            printf("%d", board[y*9 + x]);
            if (x != 8) printf(" ");
        }
        printf("\n");
    }
}

int sudoku_board[9*9] = {
   2, 0, 6, 0, 0, 0, 9, 0, 4,
   0, 0, 0, 0, 0, 7, 0, 3, 0,
   0, 4, 3, 2, 0, 0, 0, 0, 0,
   0, 0, 0, 9, 0, 5, 1, 4, 0,
   0, 5, 0, 0, 0, 2, 7, 0, 3,
   6, 0, 0, 4, 0, 0, 0, 0, 0,
   7, 6, 5, 8, 3, 0, 4, 2, 0,
   0, 1, 4, 5, 2, 0, 8, 9, 7,
   9, 0, 0, 7, 1, 0, 0, 0, 0,
};

struct node {
    int board[9*9];
    int fixed[9*9];
    int k;
    int last;
    int n;
};

void root(struct node *p, int board[9*9]) {
    p->k = 0;
    p->n = 9*9;
    p->last = 0;
    for (int i = 0; i < 9*9; ++i) {
        p->board[i] = board[i];
        p->fixed[i] = p->board[i];
    }
}

bool ok(struct node *p) {
    // column wise
    int col = ((p->k-1)%9);
    if (col == -1) return true; // no elements entered yet so its ok.
    
    int r = (p->k-1)/9;
    
    for (int i = 0; i < 9; ++i) {
        if (i == r) continue;
        if (p->board[i*9 + col] == p->board[p->k-1]) {
            return false;
        }
    }

    int base_row = (r/3)*3;
    int base_col = (col/3)*3;

    for (int i = base_row; i < base_row+3; ++i) {
        for (int j = base_col; j < base_col+3; ++j) {
            if (i == r && j == col) continue;
            if (p->board[i*9 + j] == p->board[r*9 + col])
                return false;
        }
    }

    return true;
}

bool down(struct node *p) {

    while ((p->fixed[p->k]) && (p->k < p->n)) 
        ++(p->k);
    if (p->k == p->n)
        return false;

    bool used[10];

    int rbase = (((p->k)/9))*9;

    for (int i = 0; i < 10; ++i)
        used[i] = false;
    
    for (int i = 0; i < 9; ++i) {
        used[p->board[rbase+i]] = true;
    }
    
    while (used[p->last+1] && (p->last < 9)) ++(p->last);
    if (p->last == 9) return false;
    p->board[p->k] = p->last+1;
    ++(p->k);
    p->last = 0;

    return true;
    
}

bool up(struct node *p) {

    if (p->k == -1) return false;
    do --(p->k);
    while (p->fixed[p->k] && p->k >= 0);
    p->last = p->board[p->k];
    p->board[p->k] = 0;

    return true;
}

bool leaf(struct node *p) {
    if (p->k == p->n) {
        return true;
    }
    return false;
}

bool solveSudoku(int tosolve[9*9]) {
    unsigned long long step = 0;
    struct node p;
    root(&p, tosolve); // initialize the node variable;
    while (true) {

        if (p.k == 9*9)
            break;

        if (!down(&p)) {
            if (p.k == 9*9) 
                break;
            if(!up(&p))
                break;
        }
        if (!ok(&p)) {
            if(!up(&p))
                break;
        }
        ++step;
    }

    if (leaf(&p) && ok(&p)) {
        printSudoku(p.board);
        return true;
    } else {
        printSudoku(p.board);
        return false;
    }
    return false;
}


int main() {
    
    for (int i = 0; i < 9*9; ++i) {
        scanf("%d", &sudoku_board[i]);
    }
    solveSudoku(sudoku_board);

    return 0;
}

