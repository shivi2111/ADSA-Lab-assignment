#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNTING_RANGE_LIMIT UINT64_C(10000000)

static void insertion_sort(int *array, size_t count)
{
	size_t i;
	for (i = 1; i < count; ++i) {
		int value = array[i];
		size_t j = i;
		while (j > 0 && array[j - 1] > value) {
			array[j] = array[j - 1];
			--j;
		}
		array[j] = value;
	}
}

static void bubble_sort(int *array, size_t count)
{
	size_t end;
	for (end = count; end > 1; --end) {
		size_t i;
		int swapped = 0;
		for (i = 1; i < end; ++i) {
			if (array[i - 1] > array[i]) {
				int value = array[i - 1];
				array[i - 1] = array[i];
				array[i] = value;
				swapped = 1;
			}
		}
		if (!swapped)
			break;
	}
}

static void selection_sort(int *array, size_t count)
{
	size_t i;
	for (i = 0; i < count; ++i) {
		size_t smallest = i;
		size_t j;
		for (j = i + 1; j < count; ++j)
			if (array[j] < array[smallest])
				smallest = j;
		if (smallest != i) {
			int value = array[i];
			array[i] = array[smallest];
			array[smallest] = value;
		}
	}
}

static void shell_sort(int *array, size_t count)
{
	size_t gap = count / 2;
	while (gap > 0) {
		size_t i;
		for (i = gap; i < count; ++i) {
			int value = array[i];
			size_t j = i;
			while (j >= gap && array[j - gap] > value) {
				array[j] = array[j - gap];
				j -= gap;
			}
			array[j] = value;
		}
		gap /= 2;
	}
}

static size_t quick_partition(int *array, size_t low, size_t high)
{
	int pivot = array[high];
	size_t store = low;
	size_t i;
	for (i = low; i < high; ++i) {
		if (array[i] <= pivot) {
			int value = array[store];
			array[store++] = array[i];
			array[i] = value;
		}
	}
	array[high] = array[store];
	array[store] = pivot;
	return store;
}

static void quick_sort_range(int *array, size_t low, size_t high)
{
	while (low < high) {
		size_t pivot = quick_partition(array, low, high);
		if (pivot - low < high - pivot) {
			if (pivot > low)
				quick_sort_range(array, low, pivot - 1);
			low = pivot + 1;
		} else {
			if (pivot < high)
				quick_sort_range(array, pivot + 1, high);
			if (pivot == 0)
				break;
			high = pivot - 1;
		}
	}
}

static void quick_sort(int *array, size_t count)
{
	if (count > 1)
		quick_sort_range(array, 0, count - 1);
}

static int merge_sort_range(int *array, int *temporary, size_t low, size_t high)
{
	size_t middle;
	size_t left;
	size_t right;
	size_t output;
	if (high - low < 2)
		return 1;
	middle = low + (high - low) / 2;
	if (!merge_sort_range(array, temporary, low, middle) ||
		!merge_sort_range(array, temporary, middle, high))
		return 0;
	left = low;
	right = middle;
	output = low;
	while (left < middle && right < high)
		temporary[output++] = array[left] <= array[right] ? array[left++] : array[right++];
	while (left < middle)
		temporary[output++] = array[left++];
	while (right < high)
		temporary[output++] = array[right++];
	for (output = low; output < high; ++output)
		array[output] = temporary[output];
	return 1;
}

static void merge_sort(int *array, size_t count)
{
	int *temporary;
	if (count < 2)
		return;
	if (count > SIZE_MAX / sizeof(*temporary) ||
		(temporary = (int *)malloc(count * sizeof(*temporary))) == NULL) {
		insertion_sort(array, count);
		return;
	}
	merge_sort_range(array, temporary, 0, count);
	free(temporary);
}

static void heap_sort(int *array, size_t count)
{
	size_t start = count / 2;
	while (start > 0) {
		size_t root = --start;
		while (root <= (count - 2) / 2) {
			size_t child = root * 2 + 1;
			if (child + 1 < count && array[child] < array[child + 1])
				++child;
			if (array[root] >= array[child])
				break;
			{
				int value = array[root];
				array[root] = array[child];
				array[child] = value;
			}
			root = child;
		}
	}
	while (count > 1) {
		int value = array[0];
		size_t root = 0;
		array[0] = array[count - 1];
		array[count - 1] = value;
		--count;
		while (count > 1 && root <= (count - 2) / 2) {
			size_t child = root * 2 + 1;
			if (child + 1 < count && array[child] < array[child + 1])
				++child;
			if (array[root] >= array[child])
				break;
			value = array[root];
			array[root] = array[child];
			array[child] = value;
			root = child;
		}
	}
}

static void radix_sort(int *array, size_t count)
{
	int *output;
	size_t pass;
	if (count < 2)
		return;
	if (count > SIZE_MAX / sizeof(*output) ||
		(output = (int *)malloc(count * sizeof(*output))) == NULL) {
		insertion_sort(array, count);
		return;
	}
	for (pass = 0; pass < sizeof(unsigned int); ++pass) {
		size_t frequency[256] = {0};
		size_t i;
		size_t position[256];
		for (i = 0; i < count; ++i) {
			unsigned int key = ((unsigned int)array[i] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1)));
			++frequency[(key >> (pass * CHAR_BIT)) & 255u];
		}
		position[0] = 0;
		for (i = 1; i < 256; ++i)
			position[i] = position[i - 1] + frequency[i - 1];
		for (i = 0; i < count; ++i) {
			unsigned int key = ((unsigned int)array[i] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1)));
			unsigned int digit = (key >> (pass * CHAR_BIT)) & 255u;
			output[position[digit]++] = array[i];
		}
		memcpy(array, output, count * sizeof(*array));
	}
	free(output);
}

static void counting_sort(int *array, size_t count)
{
	int minimum;
	int maximum;
	uint64_t range;
	size_t *frequency;
	size_t i;
	if (count < 2)
		return;
	minimum = maximum = array[0];
	for (i = 1; i < count; ++i) {
		if (array[i] < minimum) minimum = array[i];
		if (array[i] > maximum) maximum = array[i];
	}
	range = (uint64_t)(int64_t)maximum - (uint64_t)(int64_t)minimum + 1;
	if (range > COUNTING_RANGE_LIMIT || range > SIZE_MAX / sizeof(*frequency) ||
		(frequency = (size_t *)calloc((size_t)range, sizeof(*frequency))) == NULL) {
		insertion_sort(array, count);
		return;
	}
	for (i = 0; i < count; ++i)
		++frequency[(size_t)((int64_t)array[i] - (int64_t)minimum)];
	i = 0;
	for (size_t value = 0; value < (size_t)range; ++value)
		while (frequency[value] != 0) {
			array[i++] = (int)((int64_t)minimum + (int64_t)value);
			--frequency[value];
		}
	free(frequency);
}

typedef struct {
	int *values;
	size_t size;
	size_t capacity;
} Bucket;

static void bucket_insert(Bucket *bucket, int value)
{
	size_t i = bucket->size;
	while (i > 0 && bucket->values[i - 1] > value) {
		bucket->values[i] = bucket->values[i - 1];
		--i;
	}
	bucket->values[i] = value;
	++bucket->size;
}

static void bucket_based_sort(int *array, size_t count, int address_mode)
{
	Bucket *buckets;
	int minimum;
	int maximum;
	uint64_t span;
	size_t i;
	if (count < 2)
		return;
	if (count > SIZE_MAX / sizeof(*buckets) ||
		(buckets = (Bucket *)calloc(count, sizeof(*buckets))) == NULL) {
		insertion_sort(array, count);
		return;
	}
	minimum = maximum = array[0];
	for (i = 1; i < count; ++i) {
		if (array[i] < minimum) minimum = array[i];
		if (array[i] > maximum) maximum = array[i];
	}
	span = (uint64_t)(int64_t)maximum - (uint64_t)(int64_t)minimum + 1;
	for (i = 0; i < count; ++i) {
		uint64_t offset = (uint64_t)((int64_t)array[i] - (int64_t)minimum);
		size_t index = (size_t)((offset * (uint64_t)count) / span);
		if (index >= count) index = count - 1;
		if (buckets[index].size == buckets[index].capacity) {
			size_t capacity = buckets[index].capacity == 0 ? 4 : buckets[index].capacity * 2;
			int *values;
			if (capacity < buckets[index].capacity || capacity > SIZE_MAX / sizeof(*values)) {
				free(buckets);
				insertion_sort(array, count);
				return;
			}
			values = (int *)realloc(buckets[index].values, capacity * sizeof(*values));
			if (values == NULL) {
				for (size_t j = 0; j < count; ++j) free(buckets[j].values);
				free(buckets);
				insertion_sort(array, count);
				return;
			}
			buckets[index].values = values;
			buckets[index].capacity = capacity;
		}
		bucket_insert(&buckets[index], array[i]);
	}
	i = 0;
	for (size_t bucket = 0; bucket < count; ++bucket) {
		for (size_t value = 0; value < buckets[bucket].size; ++value)
			array[i++] = buckets[bucket].values[value];
		free(buckets[bucket].values);
	}
	free(buckets);
	(void)address_mode;
}

static void bucket_sort(int *array, size_t count)
{
	bucket_based_sort(array, count, 0);
}

static void radix_exchange_sort_range(int *array, size_t low, size_t high, unsigned int bit)
{
	size_t left = low;
	size_t right = high;
	unsigned int mask = 1u << bit;
	while (left <= right) {
		unsigned int left_key = (unsigned int)array[left] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1));
		unsigned int right_key = (unsigned int)array[right] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1));
		while (left <= right && (left_key & mask) == 0) {
			++left;
			if (left <= right) left_key = (unsigned int)array[left] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1));
		}
		while (left <= right && (right_key & mask) != 0) {
			if (right == 0) break;
			--right;
			right_key = (unsigned int)array[right] ^ (1u << (sizeof(unsigned int) * CHAR_BIT - 1));
		}
		if (left < right) {
			int value = array[left]; array[left] = array[right]; array[right] = value;
			++left;
			if (right > 0) --right;
		} else break;
	}
	if (bit > 0) {
		if (low < right) radix_exchange_sort_range(array, low, right, bit - 1);
		if (left < high) radix_exchange_sort_range(array, left, high, bit - 1);
	}
}

static void radix_exchange_sort(int *array, size_t count)
{
	if (count > 1)
		radix_exchange_sort_range(array, 0, count - 1, sizeof(unsigned int) * CHAR_BIT - 1);
}

static void address_calculation_sort(int *array, size_t count)
{
	bucket_based_sort(array, count, 1);
}

static int parse_integer(const char *text, int *result)
{
	char *end;
	long value;
	errno = 0;
	end = NULL;
	value = strtol(text, &end, 10);
	while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')
		++end;
	if (errno == ERANGE || end == text || *end != '\0' || value < INT_MIN || value > INT_MAX)
		return 0;
	*result = (int)value;
	return 1;
}

static int read_size(const char *prompt, size_t *result)
{
	char input[64];
	char *end;
	uintmax_t value;

	printf("%s", prompt);
	if (fgets(input, sizeof(input), stdin) == NULL)
		return 0;
	errno = 0;
	end = NULL;
	value = strtoumax(input, &end, 10);
	while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')
		++end;
	if (errno == ERANGE || end == input || *end != '\0' || value > SIZE_MAX)
		return 0;
	*result = (size_t)value;
	return 1;
}

int main(int argc, char **argv)
{
	int *array;
	size_t count;
	char input[64];
	char *end;
	long choice;
	static const char *names[] = {
		"Insertion sort", "Bubble sort", "Selection sort", "Shell sort",
		"Quick sort", "Merge sort", "Heap sort", "Radix sort",
		"Counting sort", "Bucket sort", "Radix exchange sort", "Address calculation sort"
	};
	if (argc < 2) {
		if (!read_size("Enter number of elements: ", &count)) {
			fprintf(stderr, "Invalid array size.\n");
			return EXIT_FAILURE;
		}
	} else {
		count = (size_t)argc - 1;
	}
	if (count > SIZE_MAX / sizeof(*array)) {
		fprintf(stderr, "Input array is too large.\n");
		return EXIT_FAILURE;
	}
	array = count == 0 ? NULL : (int *)malloc(count * sizeof(*array));
	if (count > 0 && array == NULL) {
		fprintf(stderr, "Not enough memory for the input array.\n");
		return EXIT_FAILURE;
	}
	if (argc < 2) {
		for (size_t i = 0; i < count; ++i) {
			char value[64];
			printf("Enter element %zu: ", i + 1);
			if (fgets(value, sizeof(value), stdin) == NULL || !parse_integer(value, &array[i])) {
				fprintf(stderr, "Invalid integer.\n");
				free(array);
				return EXIT_FAILURE;
			}
		}
	} else {
		for (size_t i = 0; i < count; ++i) {
			if (!parse_integer(argv[i + 1], &array[i])) {
				fprintf(stderr, "Invalid integer: %s\n", argv[i + 1]);
				free(array);
				return EXIT_FAILURE;
			}
		}
	}
	printf("Choose a sorting algorithm:\n");
	for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); ++i)
		printf("%zu. %s\n", i + 1, names[i]);
	printf("Enter choice (1-12): ");
	if (fgets(input, sizeof(input), stdin) == NULL) {
		fprintf(stderr, "Invalid choice.\n");
		free(array);
		return EXIT_FAILURE;
	}
	errno = 0;
	choice = strtol(input, &end, 10);
	while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') ++end;
	if (errno == ERANGE || end == input || *end != '\0' || choice < 1 || choice > 12) {
		fprintf(stderr, "Invalid choice. Enter a number from 1 to 12.\n");
		free(array);
		return EXIT_FAILURE;
	}
	switch (choice) {
	case 1: insertion_sort(array, count); break;
	case 2: bubble_sort(array, count); break;
	case 3: selection_sort(array, count); break;
	case 4: shell_sort(array, count); break;
	case 5: quick_sort(array, count); break;
	case 6: merge_sort(array, count); break;
	case 7: heap_sort(array, count); break;
	case 8: radix_sort(array, count); break;
	case 9: counting_sort(array, count); break;
	case 10: bucket_sort(array, count); break;
	case 11: radix_exchange_sort(array, count); break;
	case 12: address_calculation_sort(array, count); break;
	}
	printf("Sorted array: ");
	for (size_t i = 0; i < count; ++i)
		printf("%d%s", array[i], i + 1 == count ? "\n" : " ");
	free(array);
	return EXIT_SUCCESS;
}
