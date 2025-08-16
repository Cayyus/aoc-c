#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Day 2: Bathroom Security ---
 
char *read_file(const char *filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        perror("Error opening file");
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    long filesize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(fptr);
        return NULL;
    }

    fread(buffer, 1, filesize, fptr);
    buffer[filesize] = '\0';
    fclose(fptr);
    return buffer;
}

void part1(char *filecontent) {
    int keypad[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
    };
    
    int code = 0;
    int button = 0;

    // Start at 5
    int i = 1;
    int j = 1;

    char *line = strtok(filecontent, "\n");
    while (line != NULL) {
        for (int l = 0; l < strlen(line); l++) {
            if (line[l] == 'L') {
                j--;
            }
            if (line[l] == 'R') {
                j++;
            }
            if (line[l] == 'U') {
                i--;
            }
            if (line[l] == 'D') {
                i++;
            }

            // Keep within bounds
            if (i < 0) i = 0;
            if (i > 2) i = 2;
            if (j < 0) j = 0;
            if (j > 2) j = 2;
        }
        button = keypad[i][j];
        code = code * 10 + button;
        line = strtok(NULL, "\n");
    }
    printf("The code is: %d", code);
}

int main() {
    char *file_content = read_file("aoc.txt");
    if (file_content == NULL) {
        return 1;
    }

    part1(file_content);
    free(file_content);
    return 0;
}
