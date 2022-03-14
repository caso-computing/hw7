#pragma once

//#include "bst.h"

#include "node.h"
#include "bst.h"

#include <stdint.h>

//extern uint64_t lookups;

typedef struct HashTable HashTable;

struct HashTable{
    BSTnode *root;
    uint64_t salt[2];
    uint64_t size;
    uint64_t num_records;
    uint64_t long_link;
    uint64_t num_entries;
    LLNode **llink;
};

HashTable *ht_create(uint32_t size);  //completed

void ht_delete(HashTable *ht);  //completed

void ht_delete_entry(HashTable *ht, LLNode *n);  //Deletes a node entry in the hash table

uint64_t ht_size(HashTable *ht);

LLNode *ht_lookup(HashTable *ht, char *email);  //completed

void ht_insert(HashTable *ht, LLNode *node);  //completed

uint32_t ht_count(HashTable *ht);

double ht_avg_bst_size(HashTable *ht);

double ht_avg_bst_height(HashTable *ht);

void ht_print(HashTable *ht);  //completed

void ht_save(HashTable *ht, char *outfile);

