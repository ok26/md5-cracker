#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "hash.h"

void find_with_table(char* hash, char* output) {
        FILE* file;
        char buffer[1024];

        file = fopen("data/crackstation-human-only.txt", "r");

        if (file == NULL) {
            printf("Could not open file.\n");
            return;
        }

        char* t_digest = malloc(sizeof(char) * 16);
        char* t_hash = malloc(sizeof(char) * 33);

        int found = 0;
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            buffer[strlen(buffer) - 1] = '\0';
            md5(buffer, t_digest);
            hexdigest(t_digest, 16, t_hash);
            if (strcmp(t_hash, hash) == 0) {
                strcpy(output, buffer);
                found = 1;
                break;
            }
        }

        if (!found) output = "";
        fclose(file);
        free(t_digest);
        free(t_hash);
}