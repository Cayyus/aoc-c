#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Day 1: Secret Entrance ---

void part1(FILE *f) {
    int dial_pointer = 50;
    int zero_pointer = 0;
    char left[] = "L";
    char right[] = "R";

    char line[8];

    while (fgets(line, sizeof(line), f)) {
        char dir = line[0];
        char dial_str[5];
        snprintf(dial_str, sizeof(dial_str), "%s", line + 1);
        int dial = atoi(dial_str);
        
        if (dir == *left) {
            dial_pointer -= dial;
            if (dial_pointer < 0) {
                while (dial_pointer < 0) {
                    dial_pointer += 100; // add 100 to wrap it in rnage
                }
            }
            if (dial_pointer == 0) {
                zero_pointer++;
            }
        } 
        else if (dir == *right) {
            dial_pointer += dial;
            if (dial_pointer > 99) {
                while (dial_pointer > 99) {
                    dial_pointer -= 100; // subtract 100 from dial pointer until back in range
                }
            }
            if (dial_pointer == 0) {
                zero_pointer++;
            }
        }
    }
    printf("%i", zero_pointer);
}

void part2(FILE *f) {
    int dial_pointer = 50;
    int zero_pointer = 0;
    char left[] = "L";
    char right[] = "R";

    char line[16]; 

    while (fgets(line, sizeof(line), f)) {
        char dir = line[0];
        int dial = atoi(line + 1);

        if (dir == *left) {
            for (int i = 1; i <= dial; i++) {
                dial_pointer--;
                if (dial_pointer < 0) dial_pointer = 99;
                if (dial_pointer == 0) zero_pointer++;
            }
        }
        else if (dir == *right) {
            for (int i = 1; i <= dial; i++) {
                dial_pointer++;
                if (dial_pointer > 99) dial_pointer = 0;
                if (dial_pointer == 0) zero_pointer++;
            }
        }
    }

    printf("%i", zero_pointer);
}


int main() {
    FILE *f = fopen("aoc.txt", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }
    part2(f);
    fclose(f);
    return 0;
}
