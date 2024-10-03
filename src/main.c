#include <stdlib.h>
#include <stdio.h>

#include "hash.h"
#include "brute_force.h"
#include "table.h"
#include "rainbow_table.h"

void gen_md5(char* password, char* hash) {
    char* digest = malloc(sizeof(char) * 16);
    md5(password, digest);
    hexdigest(digest, 16, hash);
    printf("%s\n", hash);
    free(digest);
}

// Max length 4
void test_brute_force(char* hash) {
    char* password = brute_crack(hash);
    if (password == NULL) {
        printf("Could not find password\n");
    }
    else {
        printf("%s\n", password);
        free(password);
    }
}

void test_table(char* hash) {
    char* password = table_crack(hash);
    if (password == NULL) {
        printf("Could not find password\n");
    }
    else {
        printf("%s\n", password);
        free(password);
    }
}

void test_rainbow(HashTable* rainbow_table, char* hash) {
    char* password = rainbow_crack(rainbow_table, hash);
    if (password == NULL) {
        printf("Could not find password\n");
    }
    else {
        printf("%s\n", password);
        free(password);
    }
}

int main() {
    char* hash = malloc(sizeof(char) * 33);

    // Find password with brute-force
    gen_md5("0000", hash);
    test_brute_force(hash);

    gen_md5("aE9Z", hash);
    test_brute_force(hash);

    gen_md5("z2eK", hash);
    test_brute_force(hash);

    gen_md5("Kd7", hash);
    test_brute_force(hash);

    // Find password with word-list
    gen_md5("Hundar", hash);
    test_table(hash);

    gen_md5("password123", hash);
    test_table(hash);

    gen_md5("PASSW0RD!", hash);
    test_table(hash);

    gen_md5("Lukas123", hash);
    test_table(hash);

    gen_md5("00924", hash);
    test_table(hash);

    // Find password with rainbow-table
    HashTable* rainbow_table = get_rainbow_table();
    gen_md5("Hundar", hash);
    test_rainbow(rainbow_table, hash);

    gen_md5("password123", hash);
    test_rainbow(rainbow_table, hash);

    gen_md5("PASSW0RD!", hash);
    test_rainbow(rainbow_table, hash);

    gen_md5("Lukas123", hash);
    test_rainbow(rainbow_table, hash);

    // This takes forever, add memory-chunks to speed up the process
    free_table(rainbow_table);

    return 0;
}