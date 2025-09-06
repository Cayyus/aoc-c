#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverseString(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    char temp;

    while (left < right) {
        temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--; 
    }
}

void replaceDigit(char *str) {
    int i = 0;
    while (i < strlen(str)) {
        if (str[i] == '1') {
            str[i] = '0';
        } 
        else if (str[i] == '0') {
            str[i] = '1';
        }
        i++;
    }
}

char *generate_data(const char *a, size_t target_length) {
    char *result = malloc(target_length + 1);
    if (!result) {
        perror("Failed to allocate memory");
        return NULL;
    }
    size_t result_len = 0;
    char *current = strdup(a);
    
    while (result_len < target_length) {
        char *b = malloc(strlen(a) + 1);
        strcpy(b, current);
        reverseString(b);
        replaceDigit(b);
        
        snprintf(result, target_length + 1, "%s0%s", current, b);;
        result_len = strlen(result);
        free(b);
        free(current);
        current = strdup(result);
    }
    free(current);
    result[target_length] = '\0';
    return result;
}

char *compute_checksum(char *data) {
    size_t len = strlen(data);
    char *checksum = NULL;

    do {
        size_t new_len = len / 2;
        checksum = malloc(new_len + 1);
        if (!checksum) {
            perror("Failed to allocate memory for checksum");
            return NULL;
        }

        for (size_t i = 0; i < len - 1; i+=2) {
            if (data[i] == data[i + 1]) {
                checksum[i / 2] = '1';
            } else {
                checksum[i / 2] = '0';
            }
        }
        checksum[new_len] = '\0';
        data = checksum;
        len = new_len;
    } while (len % 2 == 0);

    return checksum;
}

int main() {
    char input[] = "10111100110001111";
    int target_length = 272;
    char *data = generate_data(input, target_length);
    char *checksum = compute_checksum(data);
    printf("Checksum: %s\n", checksum);
    free(data);
    free(checksum);
    return 0;
}
