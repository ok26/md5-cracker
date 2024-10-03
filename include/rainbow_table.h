#pragma once

typedef struct Entry {
    char* key;
    char* value;
    struct Entry* next;
} Entry;

typedef struct HashTable {
    Entry** table;
} HashTable;

void gen_rainbow_file();
HashTable* get_rainbow_table();
void free_table(HashTable* hash_table);
char* rainbow_crack(HashTable* rainbow_table, char* hash);