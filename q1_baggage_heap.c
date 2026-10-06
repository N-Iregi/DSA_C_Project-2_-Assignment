#include <stdio.h>

#define MAX_SIZE 50

typedef struct {
  char id;
  int priority;
} Container;

void swap(Container *a, Container *b) {
  Container t = *a;
  *a = *b;
  *b = t; /* ID and priority move together */
}

/* Heapifying down: used in build and after deletion */
void heapify_down(Container h[], int n, int i) {
  for (;;) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l].priority > h[largest].priority)
      largest = l;
    if (r < n && h[r].priority > h[largest].priority)
      largest = r;
    if (largest == i)
      return;
    swap(&h[i], &h[largest]);
    printf("   heapify-down: swapped %c:%d with %c:%d\n", h[largest].id,
           h[largest].priority, h[i].id, h[i].priority);
    i = largest;
  }
}

/* Heapify up: used after insertion */
void heapify_up(Container h[], int i) {
  while (i > 0 && h[(i - 1) / 2].priority < h[i].priority) {
    int p = (i - 1) / 2;
    swap(&h[i], &h[p]);
    printf("   heapify-up: swapped %c:%d with parent %c:%d\n", h[p].id,
           h[p].priority, h[i].id, h[i].priority);
    i = p;
  }
}

void build_max_heap(Container h[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify_down(h, n, i);
}

int insert(Container h[], int *n, Container c) {
  if (*n >= MAX_SIZE) {
    printf("Heap full\n");
    return 0;
  }
  h[*n] = c;
  heapify_up(h, *n);
  (*n)++;
  return 1;
}

/* Remove a specific container by ID (not only the root) */
int delete_by_id(Container h[], int *n, char id) {
  int idx = -1;
  for (int i = 0; i < *n; i++)
    if (h[i].id == id) {
      idx = i;
      break;
    }
  if (idx == -1) {
    printf("Container %c not found\n", id);
    return 0;
  }

  (*n)--;
  if (idx == *n)
    return 1;     /* it was the last element */
  h[idx] = h[*n]; /* move last element into the hole */
  if (idx > 0 && h[idx].priority > h[(idx - 1) / 2].priority)
    heapify_up(h, idx);
  else
    heapify_down(h, *n, idx);
  return 1;
}

void print_array(const Container h[], int n) {
  printf("Array: [");
  for (int i = 0; i < n; i++)
    printf("%s%c:%d", i ? ", " : "", h[i].id, h[i].priority);
  printf("]\n");
}

void print_tree(const Container h[], int n) {
  printf("Tree (parent -> children):\n");
  for (int i = 0; i < n; i++) {
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l >= n)
      break;
    printf("   %c:%d -> %c:%d", h[i].id, h[i].priority, h[l].id, h[l].priority);
    if (r < n)
      printf(", %c:%d", h[r].id, h[r].priority);
    printf("\n");
  }
}

int is_max_heap(const Container h[], int n) {
  for (int i = 1; i < n; i++)
    if (h[(i - 1) / 2].priority < h[i].priority)
      return 0;
  return 1;
}

void show(const char *title, const Container h[], int n) {
  printf("\n=== %s ===\n", title);
  print_array(h, n);
  print_tree(h, n);
  printf("Valid Max-Heap: %s\n", is_max_heap(h, n) ? "YES" : "NO");
}

int main(void) {
  int P[] = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
  int n = sizeof(P) / sizeof(P[0]);
  Container heap[MAX_SIZE];

  for (int i = 0; i < n; i++) {
    heap[i].id = 'A' + i;
    heap[i].priority = P[i];
  }
  show("Initial binary tree (unheapified)", heap, n);

  printf("\nBuilding Max-Heap...\n");
  build_max_heap(heap, n);
  show("1. After Max-Heap construction", heap, n);

  printf("\nInserting X:100...\n");
  Container x = {'X', 100};
  insert(heap, &n, x);
  show("2. After inserting X:100", heap, n);

  printf("\nRemoving X...\n");
  delete_by_id(heap, &n, 'X');
  show("3. After removing X", heap, n);
  return 0;
}
