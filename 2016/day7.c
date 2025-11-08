#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Day 7: Internet Protocol Version 7 ---

int part1(char* line) {
    // Plan: check if ABBA exists in brackets, if so, disregard that input immediately
    // Use ABBA rules to check if are TLS complied

    int in_brackets = 0; // flag to see if we are inside brackets
    int discard = 0;
    int found_abba = 0;

    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '[') {
            in_brackets = 1; // we've entered bracketed section
            continue;
        } else if (line[i] == ']') {
            in_brackets = 0; // exited bracketed section
            continue;
        }
        
        // only check ABBA for 4 or more than 4 chars
        if (line[i+3] == '\0') break;

        if (in_brackets) { 
            // abba a:0 b:1 b:2 a:3
            if (line[i] == line[i+3] &&
                line[i+1] == line[i+2] &&
                line[i] != line[i+1]) {
                    discard = 1;
                    break;
                }
        } else if (line[i] == line[i+3] &&
                  line[i+1] == line[i+2] &&
                  line[i] != line[i+1]) {
            found_abba = 1;
        }
    }

    return !discard && found_abba;
}


int main() {
    FILE *f = fopen("aoc.txt", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }

    char line[1024]; // buffer to store each line
    int valid_lines = 0;
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = 0;  // remove newline
        if (part1(line)) valid_lines++;
    }
    printf("%d\n", valid_lines);

    fclose(f);
    return 0;
}
