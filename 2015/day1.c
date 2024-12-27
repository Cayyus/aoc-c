#include <stdio.h>
#include <string.h>

// Day 1: Not Quite Lisp
int main() {
    // Opening the input file
    FILE *input_file = fopen("Day-1.txt", "r");
    // Storing the contents of the file
    char content[7002];
    fgets(content, 7002, input_file);
    // Closing the file
    fclose(input_file);

    // Part 1
    
    // Variable to store the current floor
    int floor = 0;
    // Looping through the file contents
    for (int i = 0; i < strlen(content); i++) {

        // Checks if the current character is an opening parenthesis
        if (content[i] == '(') {
            floor++; // If it is, increments the floor by 1
            } 
        // If not, checks if the current character is a closing parenthesis
        else if (content[i] == ')') {
            floor--; // If it is, decrements the floor by 1
            }
        // If the current character is neither an opening nor a closing parenthesis, breaks the loop
        else {
            break;
        }
    };

    // Output the solution
    printf("Part 1 Solution: %d", floor);

    // Part 2
    // Same as Part 1, but with an additional check to see if the floor is -1

    int pos = 0; // Initialize the position variable to keep track of the position of the character
    floor = 0;
    for (int i = 0; i < strlen(content); i++) {

        if (content[i] == '(') {
            floor++;
            pos++; // Increment the position variable
            } 
        else if (content[i] == ')') {
            floor--;
            pos++; 
            }
        else {
            break;
        }

        // Checks if floor is -1
        if (floor == -1) {
            printf("\nPart 2 Solution: %d", pos); // Outputs the position of the character that causes the floor to be -1 (solution)
            break;
        }
    };
    return 0;
}
