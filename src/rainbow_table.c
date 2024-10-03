#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rainbow_table.h"
#include "consts.h"
#include "hash.h"

#define TABLE_SIZE 100003
#define BASE 31

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    for (int i = 0; i < (int)strlen(key); i++) {
        hash = (hash * BASE) % TABLE_SIZE;
        hash = (hash + (unsigned int)key[i]) % TABLE_SIZE;
    }
    return hash;
}

HashTable* create_table() {
    HashTable* hash_table = malloc(sizeof(HashTable));
    hash_table->table = malloc(sizeof(Entry*) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;   
    }
    return hash_table;
}

void insert(HashTable* hash_table, const char* key, const char* value) {
    unsigned int index = hash(key);
    Entry* entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = hash_table->table[index];
    hash_table->table[index] = entry;
}

char* find(HashTable* hash_table, const char* key) {
    unsigned int index = hash(key);
    Entry* entry = hash_table->table[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void free_table(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = hash_table->table[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}

HashTable* get_rainbow_table() {
    HashTable* hash_table = create_table();

    FILE* rainbow;
    rainbow = fopen(RAINBOW_TABLE, "r");
    char buffer[1024];
    char rainbow_hash[33];
    char password[1024];
    while (fgets(buffer, sizeof(buffer), rainbow) != NULL) {
        strncpy(rainbow_hash, buffer, 32);
        rainbow_hash[32] = '\0';
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(password, buffer + 32);
        
        insert(hash_table, rainbow_hash, password);
    }

    return hash_table;
}

char* rainbow_crack(HashTable* rainbow_table, char* hash) {
    return find(rainbow_table, hash);
}

void gen_rainbow_file() {
    FILE* word_list;
    FILE* rainbow;

    word_list = fopen(WORD_LIST, "r");
    if (word_list == NULL) {
        printf("Could not open file: %s\n", WORD_LIST);
        return;
    }

    rainbow = fopen(RAINBOW_TABLE, "w");
    if (rainbow == NULL) {
        printf("Could not open file: %s\n", RAINBOW_TABLE);
        return;
    }

    char buffer[1024];
    char* t_digest = malloc(sizeof(char) * 16);
    char* t_hash = malloc(sizeof(char) * 33);

    while (fgets(buffer, sizeof(buffer), word_list) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        md5(buffer, t_digest);
        hexdigest(t_digest, 16, t_hash);
        fprintf(rainbow, "%s%s\n", t_hash, buffer);
    }

    fclose(word_list);
    fclose(rainbow);
    free(t_digest);
    free(t_hash);
}