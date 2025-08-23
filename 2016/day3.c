#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Day 3: Squares With Three Sides ---

void part1(FILE *f) {
    char line[100];
    int i, j, k = 0;
    int valid = 0;
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d %d %d", &i, &j, &k) == 3) {
            if (i + j > k && j + k > i && k + i > j) {
                valid++;
                i = j = k = 0;
            }
        }
    }
    printf("Valid triangles: %d\n", valid);
}

int main() {
    FILE *f = fopen("aoc.txt", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }
    part1(f);
    fclose(f);
    return 0;
}
