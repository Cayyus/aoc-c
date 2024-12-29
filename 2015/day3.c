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

    // Part 2
    // Reset the grid for Part 2 by setting all positions to 0
    memset(grid, 0, sizeof(grid));

    // Starting positions for both Santa and Robo-Santa
    // They both start at the center of the grid
    int santa_x = MAX_SIZE / 2;
    int santa_y = MAX_SIZE / 2;
    int robo_x = MAX_SIZE / 2;
    int robo_y = MAX_SIZE / 2;

    // Mark the starting house as visited
    grid[santa_x][santa_y] = 1;

    // Process each move from the input
    for (int i = 0; i < filesize; i++) {
        // Decide whether it's Santa's turn or Robo-Santa's turn
        // Santa moves on even numbers (0, 2, 4, ...), Robo-Santa on odd (1, 3, 5, ...)
        if (i % 2 == 0) {
            // It's Santa's turn
            if (fileContentCopy[i] == '^') {
                santa_y--; // Move Santa up
            } else if (fileContentCopy[i] == 'v') {
                santa_y++; // Move Santa down
            } else if (fileContentCopy[i] == '>') {
                santa_x++; // Move Santa right
            } else if (fileContentCopy[i] == '<') {
                santa_x--; // Move Santa left
            }
            // Mark the house Santa visited
            grid[santa_x][santa_y] = 1;
        } else {
            // It's Robo-Santa's turn
            if (fileContentCopy[i] == '^') {
                robo_y--; // Move Robo-Santa up
            } else if (fileContentCopy[i] == 'v') {
                robo_y++; // Move Robo-Santa down
            } else if (fileContentCopy[i] == '>') {
                robo_x++; // Move Robo-Santa right
            } else if (fileContentCopy[i] == '<') {
                robo_x--; // Move Robo-Santa left
            }
            // Mark the house Robo-Santa visited
            grid[robo_x][robo_y] = 1;
        }
    }

    // Count how many houses were visited by either Santa or Robo-Santa
    visitedHouses = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (grid[i][j] == 1) {
                visitedHouses++;
            }
        }
    }

    printf("Part 2: %d\n", visitedHouses);
    free(fileContentCopy);

    return 0;
}
