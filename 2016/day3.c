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

void part2(FILE *f) {
    char line[100];
    int i, j, k = 0;
    int count = 0;
    int valid = 0;
    static int arr[1599][3] = {};

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d %d %d", &i, &j, &k) == 3) {
            arr[count][0] = i;
            arr[count][1] = j;
            arr[count][2] = k;
            count++;
        }
    }

    for (int row = 0; row < count; row += 3) {
        for (int col = 0; col < 3; col++) {
            int a = arr[row][col];
            int b = arr[row + 1][col];
            int c = arr[row + 2][col];

            if (a + b > c && b + c > a && c + a > b) {
                valid++;
            }
        }
    }
    printf("Valid vertical triangles: %d\n", valid);
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
