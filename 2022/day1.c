// --- Day 1: Calorie Counting ---

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void part1(FILE *f) {
    char line[256];
    int total = 0;
    int highest = 0;

    while (fgets(line, sizeof(line), f)) {
        // If an empty line is detected, we sum up the numbers before this empty line
        // Then we go the next cluter of lines and sum those up until another empty line
        if (line[0] == '\n' || line[0] == '\r') {
            total = 0;
            continue;
        }
        int num = atoi(line);
        total = total + num;
        if (total > highest) {
            highest = total;
        }
    }
    printf("The highest caloric count is: %i", highest);
}

int compare_desc(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);

    if(int_a < int_b) return 1;
    else if (int_a > int_b) return -1;
    else return 0;
}

void part2(FILE *f) {
    char line[256];
    int *totals_arr;
    int total = 0;
    int size = 256;
    int count = 0;

    totals_arr = (int*)calloc(size, sizeof(int));

    if (totals_arr == NULL) {
        fprintf(stderr, "Memory allocation failed");
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '\n') {
            if (count == size) {
                size *= 2;  // double the array size
                int *tmp = realloc(totals_arr, size * sizeof(int));
                if (!tmp) {
                    fprintf(stderr, "Memory reallocation failed.\n");
                    free(totals_arr);
                    return;
                }
                totals_arr = tmp;
            }

            totals_arr[count] = total;
            count++;            
            total = 0;
            continue;
        }
        int num = atoi(line);
        total = total + num;
    }
    qsort(totals_arr, count, sizeof(int), compare_desc);
    int sum = totals_arr[0] + totals_arr[1] + totals_arr[2];
    printf("%i", sum);
    free(totals_arr);
}

int main() {
    FILE *f = fopen("aoc.txt", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }
    part1(f);
    part2(f);
    fclose(f);
    return 0;
}
