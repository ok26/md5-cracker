#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

char* search(char* hash, int length) {
    char* output = NULL;

    char* t_password = malloc(sizeof(char) * (length + 1));
    char* t_digest = malloc(sizeof(char) * 16);
    char* t_hash = malloc(sizeof(char) * 33);

    t_password[length] = '\0';
    const char *chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int chars_len = strlen(chars);
    for (int i = 0; i < length; i++) t_password[i] = chars[0];

    int total_perms = 1;
    for (int i = 0; i < length; i++) total_perms *= chars_len;

    for (int perm = 0; perm < total_perms; perm++) {
        int mask = perm;
        for (int i = 0; i < length; i++) {
            t_password[i] = chars[mask % chars_len];
            mask /= chars_len;
        }
        md5(t_password, t_digest);
        hexdigest(t_digest, 16, t_hash);
        if (strcmp(t_hash, hash) == 0) {
            output = malloc(sizeof(char) * 5);
            strcpy(output, t_password);
            break;
        }
    }

    free(t_password);
    free(t_digest);
    free(t_hash);
    return output;
}

char* brute_crack(char* hash) {
    for (int length = 1; length <= 4; length++) {
        char* output = search(hash, length);
        if (output != NULL) return output;
    }
    return NULL;
}