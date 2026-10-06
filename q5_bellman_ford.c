#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define V 10 /* A to J */
#define E_COUNT 15
#define INF INT_MAX

typedef struct {
  int u, v, w;
} Edge;

int node_index(char c) {
  c = (char)toupper((unsigned char)c);
  return (c >= 'A' && c < 'A' + V) ? c - 'A' : -1;
}

void print_path(const int parent[], int j) {
  if (parent[j] == -1) {
    printf("%c", 'A' + j);
    return;
  }
  print_path(parent, parent[j]);
  printf(" \xe2\x86\x92 %c", 'A' + j);
}

int read_node(const char *prompt, char *buf, size_t sz) {
  printf("%s", prompt);
  if (!fgets(buf, (int)sz, stdin))
    return -2; /* EOF */
  buf[strcspn(buf, "\r\n")] = '\0';
  return strlen(buf) == 1 ? node_index(buf[0]) : -1;
}

int main(void) {
  Edge edges[E_COUNT] = {{0, 1, 6},  {0, 3, 16}, {1, 2, 6}, {1, 3, 6},
                         {1, 9, 7},  {2, 6, -9}, {3, 4, 7}, {3, 9, 8},
                         {4, 5, 10}, {4, 8, -2}, {5, 6, 4}, {5, 8, 2},
                         {6, 7, 13}, {8, 5, 2},  {9, 4, 3}};

  printf("Directed edges:\n");
  for (int i = 0; i < E_COUNT; i++)
    printf("  %c -> %c : %d\n", 'A' + edges[i].u, 'A' + edges[i].v, edges[i].w);

  char buf[64];
  int src = -1;
  while (src < 0) {
    src = read_node("\nEnter source data center (A-J): ", buf, sizeof buf);
    if (src == -2) {
      printf("\nNo input.\n");
      return 1;
    }
    if (src == -1)
      printf("Invalid data center '%s'. Valid names are A to J.\n", buf);
  }

  int dist[V], parent[V];
  for (int i = 0; i < V; i++) {
    dist[i] = INF;
    parent[i] = -1;
  }
  dist[src] = 0;

  /* V-1 relaxation passes, with early exit if nothing changes */
  for (int pass = 1; pass <= V - 1; pass++) {
    int changed = 0;
    for (int j = 0; j < E_COUNT; j++) {
      int u = edges[j].u, v = edges[j].v, w = edges[j].w;
      if (dist[u] != INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;
        changed = 1;
      }
    }
    if (!changed)
      break;
  }

  /* One more pass means any further relaxation means a reachable negative cycle
   */
  for (int j = 0; j < E_COUNT; j++) {
    if (dist[edges[j].u] != INF &&
        dist[edges[j].u] + edges[j].w < dist[edges[j].v]) {
      printf("\nNegative-weight cycle detected.\n");
      printf("Shortest-path results may be undefined.\n");
      return 0;
    }
  }
  printf("\nNo negative-weight cycle detected.\n");

  printf("\nSource: %c\n\n%-12s %-14s %s\n", 'A' + src, "Destination",
         "Shortest Cost", "Path");
  for (int i = 0; i < V; i++) {
    if (i == src)
      continue;
    if (dist[i] == INF) {
      printf("%-12c %-14s %s\n", 'A' + i, "Unreachable", "-");
      continue;
    }
    printf("%-12c %-14d ", 'A' + i, dist[i]);
    print_path(parent, i);
    printf("\n");
  }

  /* Optional lookup which shows invalid names are handled without crashing */
  for (;;) {
    int d = read_node("\nQuery a destination (or press Enter to quit): ", buf,
                      sizeof buf);
    if (d == -2 || buf[0] == '\0')
      break;
    if (d == -1) {
      printf("Invalid data center '%s'.\n", buf);
      continue;
    }
    if (dist[d] == INF) {
      printf("%c is unreachable from %c.\n", 'A' + d, 'A' + src);
      continue;
    }
    printf("Destination: %c\nPath: ", 'A' + d);
    print_path(parent, d);
    printf("\nCost: %d\n", dist[d]);
  }
  return 0;
}
