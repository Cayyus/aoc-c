#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Day 2: Rock Paper Scissors ---

void part1(FILE *f) {
    char opp_rock[] = "A";
    char opp_paper[] = "B";
    char opp_scissor[] = "C";

    char my_rock[] = "X";
    char my_paper[] = "Y";
    char my_scissor[] = "Z";

    // Set the score rules
    int rock_score = 1;
    int paper_score = 2;
    int scissor_score = 3;

    int win_score = 6;
    int draw_score = 3;

    int total_score = 0;

    char line[32];

    while (fgets(line, sizeof(line), f)) {
        char *t1 = strtok(line, " ");
        char *t2 = strtok(NULL, " ");

        if (!t1 || !t2) {
            continue;
        }

        char opp_move = t1[0];
        char my_move = t2[0];

        if (my_move == *my_rock) {
            total_score += rock_score;
        } else if (my_move == *my_paper) {
            total_score += paper_score;
        } else if (my_move == *my_scissor) {
            total_score += scissor_score;
        }

        // draw condition
        if ((opp_move == *opp_rock && my_move == *my_rock) || (opp_move == *opp_paper && my_move == *my_paper) || (opp_move == *opp_scissor && my_move == *my_scissor)) {
            total_score += draw_score;
        }

        // win condition
        if ((opp_move == *opp_rock && my_move == *my_paper) || (opp_move == *opp_paper && my_move == *my_scissor) || (opp_move == *opp_scissor && my_move == *my_rock)) {
            total_score += win_score;
        }
    }
    printf("The score is: %d (Part 1)", total_score);      
}

void part2(FILE *f) {
    char opp_rock[] = "A";
    char opp_paper[] = "B";
    char opp_scissor[] = "C";

    char lose_outcome[] = "X";
    char draw_outcome []= "Y";
    char win_outcome[] = "Z";

    // Set the score rules
    int rock_score = 1;
    int paper_score = 2;
    int scissor_score = 3;

    int win_score = 6;
    int draw_score = 3;

    int total_score = 0;

    char line[32];

    while (fgets(line, sizeof(line), f)) {
        char *t1 = strtok(line, " ");
        char *t2 = strtok(NULL, " ");

        if (!t1 || !t2) {
            continue;
        }

        char opp_move = t1[0];
        char outcome_needed = t2[0];

        if (outcome_needed == *draw_outcome) {
            if (opp_move == *opp_rock) {
                total_score += draw_score + rock_score;
            } 
            else if (opp_move == *opp_paper) {
                total_score += draw_score + paper_score;
            } 
            else if (opp_move == *opp_scissor) {
                total_score += draw_score + scissor_score;
            }
        } 
        else if (outcome_needed == *win_outcome) {
            if (opp_move == *opp_rock) {
                total_score += win_score + paper_score;
            }
            else if (opp_move == *opp_paper) {
                total_score += win_score + scissor_score;
            }
            else if (opp_move == *opp_scissor) {
                total_score += win_score + rock_score;
            }
        }
        else if (outcome_needed == *lose_outcome) {
            if (opp_move == *opp_rock) {
                total_score += scissor_score;
            } 
            else if (opp_move == *opp_paper) {
                total_score += rock_score;
            }
            else if (opp_move == *opp_scissor) {
                total_score += paper_score;
            }
        }
    }
    printf("%i (Part 2)", total_score);
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
