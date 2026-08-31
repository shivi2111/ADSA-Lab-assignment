#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void merge_sort_iterative(int *a, int n) {
    if (n < 2) return;
    int *b = (int *)malloc((size_t)n * sizeof(int));
    if (!b) return;

    for (int width = 1; width < n; width <<= 1) {
        for (int left = 0; left + width < n; left += width << 1) {
            int mid = left + width;
            int right = left + (width << 1);
            if (right > n) right = n;
            int i = left, j = mid, k = left;

            while (i < mid && j < right) b[k++] = a[i] <= a[j] ? a[i++] : a[j++];
            while (i < mid) b[k++] = a[i++];
            while (j < right) b[k++] = a[j++];

            for (i = left; i < right; ++i) a[i] = b[i];
        }
    }

    free(b);
}

static int read_int_value(int *value) {
    long long x;
    if (scanf("%lld", &x) != 1 || x < INT_MIN || x > INT_MAX) return 0;
    *value = (int)x;
    return 1;
}

int main(void) {
    long long temp;
    int n, *a, x;

    printf("Enter number of elements: ");
    if (scanf("%lld", &temp) != 1 || temp < 0 || temp > INT_MAX) {
        puts("Error: invalid size value.");
        return 1;
    }
    n = (int)temp;

    if (n == 0) {
        puts("Sorted array: []");
        return 0;
    }

    a = (int *)malloc((size_t)n * sizeof(int));
    if (!a) {
        puts("Error: memory allocation failed.");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        printf("Enter element %d: ", i + 1);
        if (!read_int_value(&x)) {
            free(a);
            puts("Error: invalid integer value.");
            return 1;
        }
        a[i] = x;
    }

    merge_sort_iterative(a, n);
    printf("Sorted array: [");
    for (int i = 0; i < n; ++i) printf(i ? ", %d" : "%d", a[i]);
    puts("]");

    free(a);
    return 0;
}
