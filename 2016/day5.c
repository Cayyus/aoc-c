#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *md5(const char *input) {
    static char hash[33]; // Fixed size for MD5 Hash
    char cmd[512];
    if (!hash) return NULL;

    snprintf(cmd, sizeof(cmd),
             "python -c \"import hashlib; print(hashlib.md5(b'%s').hexdigest())\"",
             input);
    
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        return NULL;
    }

    if (fgets(hash, sizeof(hash), fp) == NULL) {
        pclose(fp);
        return NULL;
    }

    pclose(fp);
    return hash;
}

int main() {
   char base[] = "ffykfhsq";
   char passw[10] = {0};
   int i = 0;

    char *hash = md5(base);
    while (strlen(passw) < 8) {
        char input[64];
        if (!input) return 1;
        sprintf(input, "%s%d", base, i);

        char *hash = md5(input);
        if (hash) {
            printf("MD5 of '%s': %s\n", input, hash);
            if (strncmp(hash, "00000", 5) == 0) {
                strncat(passw, &hash[5], 1);
            }
        } else {
            fprintf(stderr, "Failed to compute MD5\n");
        }

        i++;
    }
    printf("%s", passw);
    return 0;

}
