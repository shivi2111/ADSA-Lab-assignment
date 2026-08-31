#include <stdio.h>
#include <stdlib.h>

typedef struct { size_t l, r, stage; } Node;

static void merge_ranges(int *a, int *b, size_t l, size_t m, size_t r) {
    size_t i = l, j = m, k = l;
    while (i < m && j < r)
        b[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i < m) b[k++] = a[i++];
    while (j < r) b[k++] = a[j++];
    for (i = l; i < r; ++i) a[i] = b[i];
}

static void merge_sort_iterative(int *a, size_t n) {
    int *b;
    Node st[64];
    int top = 0;

    if (n < 2) return;
    b = (int *)malloc(n * sizeof *b);
    if (!b) return;

    st[top++] = (Node){0, n, 0};
    while (top) {
        Node x = st[--top];
        size_t l = x.l, r = x.r, m;
        if (r - l < 2) continue;
        m = l + (r - l) / 2;
        if (!x.stage) {
            st[top++] = (Node){l, r, 1};
            st[top++] = (Node){m, r, 0};
            st[top++] = (Node){l, m, 0};
        } else {
            merge_ranges(a, b, l, m, r);
        }
    }
    free(b);
}

int main(void) {
    int n, *a, i, x;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        puts("Error: invalid size value.");
        return 1;
    }
    if (n == 0) {
        puts("Sorted array: []");
        return 0;
    }

    a = (int *)malloc((size_t)n * sizeof *a);
    if (!a) {
        puts("Error: memory allocation failed.");
        return 1;
    }

    for (i = 0; i < n; ++i) {
        if (scanf("%d", &x) != 1) {
            free(a);
            puts("Error: invalid integer value.");
            return 1;
        }
        a[i] = x;
    }

    merge_sort_iterative(a, (size_t)n);
    printf("Sorted array: [");
    for (i = 0; i < n; ++i) printf(i ? ", %d" : "%d", a[i]);
    puts("]");
    free(a);
    return 0;
}
