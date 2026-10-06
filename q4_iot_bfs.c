#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define V 7

int node_index(char c) {
  c = (char)toupper((unsigned char)c);
  return (c >= 'A' && c < 'A' + V) ? c - 'A' : -1;
}

int main(void) {
  int g[V][V] = {0};
  int links[][3] = {{0, 1, 6},  {0, 3, 12}, {1, 3, 5},  {1, 2, 11}, {2, 3, 17},
                    {2, 6, 25}, {3, 4, 22}, {3, 5, 15}, {4, 5, 10}, {5, 6, 22}};
  for (size_t i = 0; i < sizeof(links) / sizeof(links[0]); i++) {
    g[links[i][0]][links[i][1]] = links[i][2];
    g[links[i][1]][links[i][0]] = links[i][2]; /* undirected */
  }

  /* 1. Read and validate the starting gateway */
  char buf[64];
  int s = -1;
  while (s == -1) {
    printf("Enter starting gateway (A-G): ");
    if (!fgets(buf, sizeof buf, stdin)) {
      printf("\nNo input.\n");
      return 1;
    }
    buf[strcspn(buf, "\r\n")] = '\0';
    if (strlen(buf) == 1)
      s = node_index(buf[0]);
    if (s == -1)
      printf("Invalid gateway '%s'. Valid gateways are A to G.\n", buf);
  }

  /* 2. BFS with a real queue */
  int visited[V] = {0}, hop[V] = {0};
  int queue[V], front = 0, rear = 0;
  int order[V], ocount = 0; /* one-hop gateways in discovery order */

  visited[s] = 1;
  queue[rear++] = s;
  while (front < rear) {
    int u = queue[front++]; /* dequeue */
    for (int v = 0; v < V; v++) {
      if (g[u][v] > 0 && !visited[v]) {
        visited[v] = 1;
        hop[v] = hop[u] + 1;
        queue[rear++] = v; /* enqueue */
        if (hop[v] == 1)
          order[ocount++] = v;
      }
    }
  }

  printf("\nDirectly connected gateways to %c (BFS discovery order): ",
         'A' + s);
  if (ocount == 0) {
    printf("none\n");
    return 0;
  }
  for (int i = 0; i < ocount; i++)
    printf("%c ", 'A' + order[i]);
  printf("\n");

  /* 3. Highest transfer time among the one-hop neighbours */
  int best = order[0];
  printf("\n");
  for (int i = 0; i < ocount; i++) {
    printf("%c -- %c : %d ms\n", 'A' + s, 'A' + order[i], g[s][order[i]]);
    if (g[s][order[i]] > g[s][best])
      best = order[i];
  }
  printf("\nHighest data-transfer time: Gateway %c (%d ms)\n", 'A' + best,
         g[s][best]);
  return 0;
}
