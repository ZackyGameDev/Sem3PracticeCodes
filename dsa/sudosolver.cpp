#include <bits/stdc++.h>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void printSudokuFancy(int board[81]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }

            int val = board[i * 9 + j];
            if (val == 0) {
                cout << "." << " ";  // empty cell
            } else {
                // color code based on number
                string color;
                switch(val) {
                    case 1: color = RED; break;
                    case 2: color = GREEN; break;
                    case 3: color = YELLOW; break;
                    case 4: color = BLUE; break;
                    case 5: color = CYAN; break;
                    default: color = BOLD; break; // bold for 6-9
                }
                cout << color << val << RESET << " ";
            }
        }
        cout << endl;
    }
}

void printSudoku(int board[81], int fixed[81]) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }

            int val = board[i * 9 + j];
            if (val == 0) {
                cout << ". ";
            } else {
                if (fixed[i * 9 + j]) {
                    cout << BOLD << val << RESET << " ";
                } else
                cout << BLUE << val << RESET << " ";
            }
        }
        cout << endl;
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

    // printf("DOWN vvvvvvvvvvvvvvvvv\n");
    // printSudoku(p->board, p->fixed);
    // // printSudokuFancy(p->board);
    // cout << "Above is OK? " << ok(p) << endl;

    // if (p->board[1] == 7 && p->board[3] == 3 && p->board[4] == 5 && p->board[5] == 8 && p->board[7] == 1
    //     && p->board[9] == 1 && p->board[10] == 9 && p->board[11] == 8 && p->board[12] == 6 && p->board[13] == 4 && p->board[15] == 2
    //     && p->board[18] == 5 && p->board[24] == 6 && p->board[27] == 8 && p->board[29] == 7 && p->board[31] == 6 && p->board[36] == 4 && p->board[36] == 4
    //     && p->board[39] == 1 && p->board[40] == 8)
    //     printf("break\n");

    return true;
    
}

bool up(struct node *p) {

    if (p->k == -1) return false;
    do --(p->k);
    while (p->fixed[p->k] && p->k >= 0);
    p->last = p->board[p->k];
    p->board[p->k] = 0;

    // printf("UP ^^^^^^^^^^^^^^^^^^^^^\n");
    // printSudoku(p->board, p->fixed);
    // cout << "Above is OK? " << ok(p) << endl;

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
        printf("Solved.\n");
        printSudoku(p.board, p.fixed);
        return true;
    } else {
        printf("Unsolved.\n");
        printSudoku(p.board, p.fixed);
        return false;
    }
    return false;
}


int main() {
    solveSudoku(sudoku_board);
    //struct node p;
    //root(&p, sudoku_board);
    //for (int i = 0; i < 16; ++i)  {
    //    down(&p);
    //    printf("DOWN vvvvvvvvvvvvvvvvv\n");
    //    printSudoku(p.board, p.fixed);
    //    cout << "Above is OK? " << ok(&p) << endl;
    //}

    //for (int i = 0; i < 3; ++i)  {
    //    up(&p);
    //    printf("UP ^^^^^^^^^^^^^^^^^^\n");
    //    printSudoku(p.board, p.fixed);
    //    cout << "Above is OK? " << ok(&p) << endl;
    //}

    //for (int i = 0; i < 2; ++i)  {
    //    down(&p);
    //    printf("DOWN vvvvvvvvvvvvvvvv\n");
    //    printSudoku(p.board, p.fixed);
    //    cout << "Above is OK? " << ok(&p) << endl;
    //}

    return 0;
}

