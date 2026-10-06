#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct {
  char id[4];
  char name[20];
  int priority;
} Patient;

void swap_patient(Patient *a, Patient *b) {
  Patient t = *a;
  *a = *b;
  *b = t; /* ID, name and score move together */
}

void max_heapify(Patient h[], int n, int i) {
  for (;;) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && h[l].priority > h[largest].priority)
      largest = l;
    if (r < n && h[r].priority > h[largest].priority)
      largest = r;
    if (largest == i)
      return;
    swap_patient(&h[i], &h[largest]);
    i = largest;
  }
}

void heapify_up(Patient h[], int i) {
  while (i > 0 && h[(i - 1) / 2].priority < h[i].priority) {
    swap_patient(&h[i], &h[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void build_max_heap(Patient h[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    max_heapify(h, n, i);
}

int extract_max(Patient h[], int *n, Patient *out) {
  if (*n <= 0)
    return 0; /* empty-heap guard */
  *out = h[0];
  h[0] = h[*n - 1];
  (*n)--;
  max_heapify(h, *n, 0);
  return 1;
}

int insert_patient(Patient h[], int *n, Patient p) {
  if (*n >= MAX_SIZE)
    return 0;
  h[*n] = p;
  heapify_up(h, *n);
  (*n)++;
  return 1;
}

int delete_patient(Patient h[], int *n, const char *id) {
  int idx = -1;
  for (int i = 0; i < *n; i++)
    if (strcmp(h[i].id, id) == 0) {
      idx = i;
      break;
    }
  if (idx == -1)
    return 0;
  (*n)--;
  if (idx == *n)
    return 1;
  h[idx] = h[*n];
  if (idx > 0 && h[idx].priority > h[(idx - 1) / 2].priority)
    heapify_up(h, idx);
  else
    max_heapify(h, *n, idx);
  return 1;
}

void print_heap(const Patient h[], int n) {
  printf("Array:\n");
  for (int i = 0; i < n; i++)
    printf("  [%d] %s  %-7s  %d\n", i, h[i].id, h[i].name, h[i].priority);
  printf("Tree (parent -> children):\n");
  for (int i = 0; 2 * i + 1 < n; i++) {
    printf("  %s:%d -> %s:%d", h[i].id, h[i].priority, h[2 * i + 1].id,
           h[2 * i + 1].priority);
    if (2 * i + 2 < n)
      printf(", %s:%d", h[2 * i + 2].id, h[2 * i + 2].priority);
    printf("\n");
  }
}

int main(void) {
  Patient heap[MAX_SIZE] = {{"P01", "Amina", 72},  {"P02", "Daniel", 45},
                            {"P03", "Eric", 91},   {"P04", "Grace", 63},
                            {"P05", "Hassan", 88}, {"P06", "Irene", 54},
                            {"P07", "Jean", 76}};
  int n = 7;

  build_max_heap(heap, n);
  printf(" 1. Initial Max-Heap\n");
  print_heap(heap, n);

  /* Extraction empties the heap, so run it on copy and keep the original */
  printf("\n 2. Treatment order\n");
  Patient copy[MAX_SIZE];
  memcpy(copy, heap, sizeof(Patient) * n);
  int cn = n;
  Patient p;
  while (extract_max(copy, &cn, &p))
    printf("Patient %s (%s) -- Priority %d\n", p.id, p.name, p.priority);

  printf("\n3. After inserting Kofi (P08, 98)\n");
  Patient kofi = {"P08", "Kofi", 98};
  insert_patient(heap, &n, kofi);
  print_heap(heap, n);

  printf("\n4. After clearing P08\n");
  if (!delete_patient(heap, &n, "P08"))
    printf("P08 not found\n");
  print_heap(heap, n);
  return 0;
}
