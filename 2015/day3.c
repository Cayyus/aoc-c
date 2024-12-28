#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 200

// Day 3: Perfectly Spherical Houses in a Vacuum

int main() {
    // File handling
    FILE *file = fopen("Day-3.txt", "rb");

    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *fileContent = (char *)malloc(filesize + 1);
    if (fileContent == NULL) {
        printf("Memory allocation failed (fileContent)\n");
        return 1;
    }

    fread(fileContent, 1, filesize, file);
    fileContent[filesize] = '\0';
    fclose(file);

    char *fileContentCopy = strdup(fileContent);
    if (fileContentCopy == NULL) {
        printf("Memory allocation failed (fileContentCopy)\n");
        free(fileContent);
        return 1;
    }

    
    // Part 1
    // Grid to track visited houses
    // (0, 0) is the origin; let's use an offset to avoid negative indices
    int grid[MAX_SIZE][MAX_SIZE] = {0};
    int x = MAX_SIZE / 2;  // Starting at the center of the grid (0, 0)
    int y = MAX_SIZE / 2;  // (0, 0) position in the grid
    grid[x][y] = 1;  // Start position is visited

    // Traverse through the directions in the fileContent string
    for (int i = 0; i < filesize; i++) {
        if (fileContent[i] == '^') {
            y--; // Move up (y decreases)
        } else if (fileContent[i] == 'v') {
            y++; // Move down (y increases)
        } else if (fileContent[i] == '>') {
            x++; // Move right (x increases)
        } else if (fileContent[i] == '<') {
            x--; // Move left (x decreases)
        }

        // Mark new position as visited
        grid[x][y] = 1;
    }

    // Count the number of visited houses
    int visitedHouses = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (grid[i][j] == 1) {
                visitedHouses++;
            }
        }
    }

    printf("Part 1: %d\n", visitedHouses);
    free(fileContent);
    return 0;
}
