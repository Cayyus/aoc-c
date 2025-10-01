#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

# Day 14: One Time Pad

char *md5_hash(char *input) {
    unsigned char digest[MD5_DIGEST_LENGTH];

    MD5((unsigned char*)input, strlen(input), digest);
    static char md5_string[33];
    for (int i = 0; i < 16; i++)
        sprintf(&md5_string[i*2], "%02x", (unsigned int)digest[i]);
    return md5_string;
} 

struct Triplet {
    char sequence; 
    int found; // 0 for not found, 1 for found
};

struct Quintuple {
    char sequence;
    int found; // 0 for not found, 1 for found
};

struct TripletEntry {
    int index;
    char sequence;
};

#define MAX_TRIPLETS 1000
struct TripletEntry triplets[MAX_TRIPLETS];
int triplet_count = 0;

struct Triplet has_triplet(char *hash) {
    struct Triplet result = {0, 0};
    int len = strlen(hash);
    for (int i = 0; i < len - 2; i++) {
        if (hash[i] == hash[i + 1] && hash[i] == hash[i + 2]) {
            result.sequence = hash[i];
            result.found = 1;
            return result;
        }
    }
    return result;
}

struct Quintuple has_quintuple(char *hash) {
    struct Quintuple result = {0, 0};
    int len = strlen(hash);
    for (int i = 0; i < len - 4; i++) {
        if (hash[i] == hash[i + 1] && hash[i] == hash[i + 2] && hash[i] == hash[i + 3] && hash[i] == hash[i + 4]) {
            result.sequence = hash[i];
            result.found = 1;
            return result;
        }
    }
    return result;
}

int key_indices[64];

void part1(char *input) {
    int i = 0;
    int k_count = 0;
    while (1) {
        char to_hash[100];
        sprintf(to_hash, "%s%d", input, i);
        char *hash = md5_hash(to_hash);
        printf("Index: %d, Hash: %s\n", i, hash);

        struct Triplet result = has_triplet(hash);
        struct Quintuple qresult = has_quintuple(hash);
        
        if (result.found) {
            printf("Triplet found at input index %d (hash = %s, char = %c)\n",
                   i, hash, result.sequence);
            triplets[triplet_count].sequence = result.sequence;
            triplets[triplet_count].index = i;
            triplet_count++;
        } else {
            printf("No triplet found at input index %d\n", i);
        }
        if (qresult.found) {
            printf("Quintuple found at input index %d (hash = %s, char = %c)\n",
                   i, hash, qresult.sequence);
            
            for (int j = 0; j < triplet_count; j++) {
                if (triplets[j].sequence == qresult.sequence && 
                    i - triplets[j].index <= 1000 && i > triplets[j].index) {
                        key_indices[k_count++] = triplets[j].index;
                        printf("Key found at triplet index %d (validated by quintuple at %d)\n",
                        triplets[j].index, i);
                    } 
            }
        } else {
            printf("No quintuple found at input index %d\n", i);
        }
        printf("Total keys found so far: %d\n", k_count);
        if (k_count >= 64) {
            printf("64 keys found. Stopping.\n");
            printf("64th key index: %d\n", key_indices[63]);
            break;
        }
        for (int j = 0; j < triplet_count; j++) {
            if (i - triplets[j].index > 1000) {
                // Remove triplet from list
                for (int k = j; k < triplet_count - 1; k++) {
                    triplets[k] = triplets[k + 1];
                }
                triplet_count--;
            } else {
                j++;
            }
        }
        i++;
    }
}

int main() {
    char input[25] = "zpqevtbw";
    part1(input);

}
