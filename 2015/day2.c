#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Day 2: I Was Told There Would Be No Math

int main() {
    // File Handling

    FILE *file = fopen("Day-2.txt", "rb");
    if (file == NULL) {
        printf("File not found\n");
        return 1;
    }

    // Move the file pointer to the end
    fseek(file, 0, SEEK_END);
    // Get the file size
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); // Move file pointer back to the beginning

    // Allocate memory for the file content
    char *fileContent = (char *)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Read the file content into the allocated memory
    fread(fileContent, fileSize, 1, file);
    // Null-terminate the string
    fileContent[fileSize] = '\0';
    fclose(file);

    // Surface area calculation: 2*l*w + 2*w*h + 2*h*l
    int total_sqft  = 0;

    char *line = strtok(fileContent, "\n");
    while (line != NULL) {
        int length, width, height;
        sscanf(line, "%dx%dx%d", &length, &width, &height);
        
        int lw = length * width;
        int wh = width * height;
        int hl = height * length;

        // Surface area calcuation
        int surface_area = 2 * lw + 2 * wh + 2 * hl;

        // Find the smallest side
        int smallest_side = 0;

        if (lw <= wh && lw <= hl) { 
            smallest_side = lw; //If lw is smaller than both wh and hl
        } else if (wh <= lw && wh <= hl) { //
            smallest_side = wh; // If wh is smaller than both lw and hl
        } else {
            smallest_side = hl; // If all other conditions fail, hl is the smallest side
        }

        // Add the gift surface area and the smallest side to the total sqft 
        total_sqft += surface_area + smallest_side;
        line = strtok(NULL, "\n");
    }

    printf("Part 1 Solution: %d", total_sqft);
    
    free(fileContent);
    return 0;
}
