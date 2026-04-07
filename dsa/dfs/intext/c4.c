// ROLL NUMBER: 25120002
// NAME: AAYAN GOHAR

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH  (5)
#define HEIGHT (4)
#define CELLS  (WIDTH * HEIGHT)

enum { LOSS = 1, DRAW = 2, WIN = 4 };

size_t power(size_t a, size_t n) {
  size_t p = 1;
  while (n-- > 0)
    p *= a;
  return p;
}

int mark(uint64_t board, size_t r, size_t c) {
  size_t n = r * WIDTH + c;
  return (board / power(3, n)) % 3;
}

uint64_t place(uint64_t board, size_t c, int p) {
  for (size_t r = 0; r < HEIGHT; ++r) {
    if (mark(board, r, c) == 0) {
      if (r == 0 || mark(board, r - 1, c) != 0) {
        size_t n = r * WIDTH + c;
        return board + p * power(3, n);
      }
    }
  }
  return UINT64_MAX; // invalid move
}

bool is_full(uint64_t board) {
  for (size_t c = 0; c < WIDTH; ++c)
    if (mark(board, HEIGHT - 1, c) == 0)
      return false;
  return true;
}

bool has_won(uint64_t board, int m) {
  // horizontal
  for (size_t r = 0; r < HEIGHT; ++r)
    for (size_t c = 0; c + 3 < WIDTH; ++c) {
      bool ok = true;
      for (size_t k = 0; k < 4; ++k)
        if (mark(board, r, c + k) != m) { ok = false; break; }
      if (ok) return true;
    }
  // vertical
  for (size_t c = 0; c < WIDTH; ++c)
    for (size_t r = 0; r + 3 < HEIGHT; ++r) {
      bool ok = true;
      for (size_t k = 0; k < 4; ++k)
        if (mark(board, r + k, c) != m) { ok = false; break; }
      if (ok) return true;
    }
  // diagonal down-right
  for (size_t r = 0; r + 3 < HEIGHT; ++r)
    for (size_t c = 0; c + 3 < WIDTH; ++c) {
      bool ok = true;
      for (size_t k = 0; k < 4; ++k)
        if (mark(board, r + k, c + k) != m) { ok = false; break; }
      if (ok) return true;
    }
  // diagonal up-right
  for (size_t r = 3; r < HEIGHT; ++r)
    for (size_t c = 0; c + 3 < WIDTH; ++c) {
      bool ok = true;
      for (size_t k = 0; k < 4; ++k)
        if (mark(board, r - k, c + k) != m) { ok = false; break; }
      if (ok) return true;
    }
  return false;
}

bool is_done(uint64_t board) {
  return (
    is_full(board) ||
    has_won(board, 1) ||
    has_won(board, 2)
  );
}

uint8_t move(uint8_t result, size_t c) {
  return (result << 4) | (c & 0xF);
}

bool is_loss(uint8_t mv) { return mv & 0x10; }
bool is_draw(uint8_t mv) { return mv & 0x20; }
bool is_win(uint8_t mv)  { return mv & 0x40; }

int player(uint64_t board) {
  size_t marks[3] = {0};
  for (size_t r = 0; r < HEIGHT; ++r)
    for (size_t c = 0; c < WIDTH; ++c)
      marks[mark(board, r, c)]++;
  return (marks[1] <= marks[2]) ? 1 : 2;
}

/* --- memoization table --- */
#define TABLE_SIZE (1ULL << 22)
static uint64_t *keys;
static uint8_t  *vals;

size_t hash(uint64_t k) {
  k ^= k >> 33;
  k *= 0xff51afd7ed558ccdULL;
  k ^= k >> 33;
  return (size_t)k & (TABLE_SIZE - 1);
}

uint8_t lookup(uint64_t key) {
  size_t i = hash(key);
  for (;;) {
    if (keys[i] == UINT64_MAX) return 0;
    if (keys[i] == key) return vals[i];
    i = (i + 1) & (TABLE_SIZE - 1);
  }
}

void store(uint64_t key, uint8_t val) {
  size_t i = hash(key);
  for (;;) {
    if (keys[i] == UINT64_MAX) {
      keys[i] = key;
      vals[i] = val;
      return;
    }
    if (keys[i] == key) {
      vals[i] = val;
      return;
    }
    i = (i + 1) & (TABLE_SIZE - 1);
  }
}

uint8_t c4(uint64_t board) {
  assert(!is_done(board));

  uint8_t cached = lookup(board);
  if (cached) return cached;

  int p = player(board);
  uint8_t b = 0;

  for (size_t c = 0; c < WIDTH; ++c) {
    if (mark(board, HEIGHT - 1, c) != 0) continue;
    uint64_t new_board = place(board, c, p);
    if (new_board == UINT64_MAX) continue;
    if (has_won(new_board, p))
      return store(board, move(WIN, c)), move(WIN, c);
    if (is_done(new_board))
      return store(board, move(DRAW, c)), move(DRAW, c);
    uint8_t f = c4(new_board);
    if (is_loss(f))
      return store(board, move(WIN, c)), move(WIN, c);
    if (is_draw(f))
      b = move(DRAW, c);
    else if (!b)
      b = move(LOSS, c);
  }

  assert(b);
  store(board, b);
  return b;
}

int main() {
  keys = malloc(TABLE_SIZE * sizeof(uint64_t));
  vals = malloc(TABLE_SIZE * sizeof(uint8_t));
  for (size_t i = 0; i < TABLE_SIZE; ++i) keys[i] = UINT64_MAX;

  char myc;
  scanf(" %c", &myc);
  int myPlayer = (myc == 'Y') ? 1 : 2;
  uint64_t board = 0;
  bool myTurn = (myPlayer == 1);

  while (!is_done(board)) {
    if (myTurn) {
      uint8_t mv = c4(board);
      size_t c = mv & 0xF;
      printf("%c %zu\n", (myPlayer == 1) ? 'Y' : 'R', c + 1);
      board = place(board, c, myPlayer);
    } else {
      char oc;
      size_t col;
      scanf(" %c %zu", &oc, &col);
      int op = (oc == 'Y') ? 1 : 2;
      board = place(board, col - 1, op);
    }
    myTurn = !myTurn;
  }

  if (has_won(board, 1)) printf("Y won\n");
  else if (has_won(board, 2)) printf("R won\n");
  else printf("draw\n");

  free(keys);
  free(vals);
  return 0;
}
