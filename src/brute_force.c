#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"


void search(char* hash, int length, char* output) {
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
            strcpy(output, t_password);
            break;
        }
    }

    free(t_password);
    free(t_digest);
    free(t_hash);
}

void brute_force(char* hash, char* output) {
    for (int i = 0; i <= 4; i++) output[i] = '0';
    for (int length = 1; length <= 4; length++) {
        search(hash, length, output);
        if (output[length] == '\0') return;
    }
    printf("Cannot brute force password longer than 4 bytes or with special charachters\n");
}