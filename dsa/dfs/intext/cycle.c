#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct node {
  size_t to;
  struct node *next;
};

struct graph {
  struct node **adj;
  size_t n;
};

struct graph *new_graph(size_t n) {
  struct graph *g = malloc(sizeof(struct graph));
  g->n = n;
  g->adj = calloc(n, sizeof(struct node *));
  return g;
}

void add_edge(struct graph *g, size_t from, size_t to) {
  struct node *new_node = malloc(sizeof(struct node));
  new_node->to = to;
  new_node->next = g->adj[from];
  g->adj[from] = new_node;
}

void add_undirected_edge(struct graph *g, size_t a, size_t b) {
  add_edge(g, a, b);
  add_edge(g, b, a);
}

bool dfs_cycle(
  struct graph *g, size_t u, size_t parent,
  bool *visited, ssize_t *p,
  size_t *cycle_start, size_t *cycle_end
) {
  visited[u] = true;

  for (struct node *node = g->adj[u]; node; node = node->next) {
    size_t v = node->to;

    if (v == parent) continue;

    if (visited[v]) {
      *cycle_start = v;
      *cycle_end = u;
      return true;
    }

    p[v] = u;
    if (dfs_cycle(g, v, u, visited, p, cycle_start, cycle_end))
      return true;
  }

  return false;
}

bool find_cycle(struct graph *g, ssize_t *p, size_t *cycle_start, size_t *cycle_end) {
  bool *visited = calloc(g->n, sizeof(bool));

  for (size_t i = 0; i < g->n; i++) {
    if (!visited[i]) {
      p[i] = -1;
      if (dfs_cycle(g, i, SIZE_MAX, visited, p, cycle_start, cycle_end)) {
        free(visited);
        return true;
      }
    }
  }

  free(visited);
  return false;
}

void free_graph(struct graph *g) {
  for (size_t i = 0; i < g->n; i++) {
    struct node *node = g->adj[i];
    while (node) {
      struct node *tmp = node;
      node = node->next;
      free(tmp);
    }
  }
  free(g->adj);
  free(g);
}

int main() {
  size_t V, E;
  if (scanf("%zu %zu", &V, &E) != 2) return 1;

  struct graph *g = new_graph(V);

  for (size_t i = 0; i < E; i++) {
    size_t a, b;
    scanf("%zu %zu", &a, &b);
    add_undirected_edge(g, a, b);
  }

  ssize_t *p = malloc(V * sizeof(ssize_t));
  size_t cycle_start = SIZE_MAX, cycle_end = SIZE_MAX;

  for (size_t i = 0; i < V; i++) p[i] = -1;

  if (find_cycle(g, p, &cycle_start, &cycle_end)) {
    size_t *cycle = malloc(V * sizeof(size_t));
    size_t len = 0;

    cycle[len++] = cycle_start;
    for (size_t v = cycle_end; v != cycle_start; v = p[v])
      cycle[len++] = v;
    cycle[len++] = cycle_start;

    for (size_t i = len; i > 0; i--) {
      printf("%zu", cycle[i - 1]);
      if (i > 1) printf(" ");
    }
    printf("\n");

    free(cycle);
  } else {
    printf("N\n");
  }

  free(p);
  free_graph(g);

  return 0;
}
