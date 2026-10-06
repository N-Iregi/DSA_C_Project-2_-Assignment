#include <stdio.h>
#include <stdlib.h>

#define V 7
#define E 10

typedef struct {
  int u, v, w;
} Edge;

int find(int parent[], int i) {
  while (parent[i] != i) {
    parent[i] = parent[parent[i]];
    i = parent[i];
  }
  return i;
}

int cmp(const void *a, const void *b) {
  return ((const Edge *)a)->w - ((const Edge *)b)->w;
}

int main(void) {
  /* A=0 B=1 C=2 D=3 E=4 F=5 G=6 */
  Edge edges[E] = {{0, 1, 6},  {0, 3, 12}, {1, 3, 5},  {1, 2, 11}, {2, 3, 17},
                   {2, 6, 25}, {3, 4, 22}, {3, 5, 15}, {4, 5, 10}, {5, 6, 22}};

  /* 1. Adjacency matrix (undirected -> symmetric) */
  int m[V][V] = {0};
  for (int i = 0; i < E; i++) {
    m[edges[i].u][edges[i].v] = edges[i].w;
    m[edges[i].v][edges[i].u] = edges[i].w;
  }
  printf("Adjacency matrix:\n     ");
  for (int j = 0; j < V; j++)
    printf("%4c", 'A' + j);
  printf("\n");
  for (int i = 0; i < V; i++) {
    printf("%4c ", 'A' + i);
    for (int j = 0; j < V; j++)
      printf("%4d", m[i][j]);
    printf("\n");
  }

  /* 2. Kruskal */
  qsort(edges, E, sizeof(Edge), cmp);
  int parent[V];
  for (int i = 0; i < V; i++)
    parent[i] = i;

  printf("\nProcessing edges in increasing cost:\n");
  Edge chosen[V - 1];
  int count = 0, total = 0;
  for (int i = 0; i < E; i++) {
    int ru = find(parent, edges[i].u), rv = find(parent, edges[i].v);
    printf("  %c - %c : %2d  -> ", 'A' + edges[i].u, 'A' + edges[i].v,
           edges[i].w);
    if (ru != rv) {
      parent[ru] = rv;
      chosen[count++] = edges[i];
      total += edges[i].w;
      printf("SELECTED\n");
      if (count == V - 1) {
        printf("  (V-1 edges reached, stop)\n");
        break;
      }
    } else {
      printf("rejected (cycle)\n");
    }
  }

  /* Result */
  printf("\nSelected Connections:\n");
  for (int i = 0; i < count; i++)
    printf("Station %c \xe2\x80\x94 Station %c : %d\n", 'A' + chosen[i].u,
           'A' + chosen[i].v, chosen[i].w);
  printf("\nTotal Installation Cost: %d thousand dollars\n", total);
  return 0;
}
