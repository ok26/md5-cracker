#include <stdlib.h>
#include <stdio.h>

#include "hash.h"
#include "brute_force.h"
#include "table.h"

void gen_md5(char* password, char* hash) {
    char* digest = malloc(sizeof(char) * 16);
    md5(password, digest);
    hexdigest(digest, 16, hash);
    printf("%s\n", hash);
    free(digest);
}

// Max length 4
void find_brute_force(char* hash) {
    char* password = malloc(sizeof(char) * 5);
    brute_force(hash, password);
    printf("%s\n", password);
}

void test_table(char* hash) {
    char password[1024];
    find_with_table(hash, password);
    printf("%s\n", password);
}

int main() {
    char* hash = malloc(sizeof(char) * 33);

    /*
    gen_md5("0000", hash);
    find_brute_force(hash);

    gen_md5("aE9Z", hash);
    find_brute_force(hash);

    gen_md5("z2eK", hash);
    find_brute_force(hash);

    gen_md5("Kd7", hash);
    find_brute_force(hash);
    */
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

    return 0;
}