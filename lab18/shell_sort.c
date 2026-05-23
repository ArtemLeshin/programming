#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ELEMENT_NR 20000
#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))
const char *notation =
    "Shell Sort Big O Notation:\
						\n--> Best Case: O(n log(n)) \
						\n--> Average Case: depends on gap sequence \
						\n--> Worst Case: O(n)";

void show_data(int arr[], int len)
{
    int i;

    for (i = 0; i < len; i++) printf("%3d ", arr[i]);
    printf("\n");
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void shellSort(int array[], int len)
{
    int i, j, gap;

    for (gap = len / 2; gap > 0; gap = gap / 2)
        for (i = gap; i < len; i++)
            for (j = i - gap; j >= 0 && array[j] > array[j + gap]; j = j - gap)
                swap(&array[j], &array[j + gap]);
}
