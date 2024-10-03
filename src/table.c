#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "consts.h"
#include "hash.h"

char* table_crack(char* hash) {
    FILE* file;
    char buffer[1024];
    char* output = NULL;

    file = fopen(WORD_LIST, "r");
    if (file == NULL) {
        printf("Could not open file: %s\n", WORD_LIST);
        return NULL;
    }

    char* t_digest = malloc(sizeof(char) * 16);
    char* t_hash = malloc(sizeof(char) * 33);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        md5(buffer, t_digest);
        hexdigest(t_digest, 16, t_hash);
        if (strcmp(t_hash, hash) == 0) {
            output = malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(output, buffer);
            break;
        }
    }

    fclose(file);
    free(t_digest);
    free(t_hash);
    return output;
}