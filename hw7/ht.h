#pragma once

//#include "bst.h"

#include "node.h"
#include "bst.h"

#include <stdint.h>

//extern uint64_t lookups;

typedef struct HashTable HashTable;

struct HashTable{
    BSTnode *root;          //stores the root node of the BST associated with this HT
    uint64_t salt[2];       //salt for computing the hash key
    uint64_t size;          //stores the number of buckets associated with this tree
    uint64_t num_records;   //not implemented.  would be used to compute num_records/size of HT
    uint64_t long_link;     //not implemented.  would of computed the longest linked list in HT
    uint64_t num_entries;   //not implemented.  would of computed num_entries/size=%utilization of HT
    LLNode **llink;
};

HashTable *ht_create(uint32_t size);  //completed

void ht_delete(HashTable *ht);  //completed

void ht_delete_entry(HashTable *ht, LLNode *n);  //Deletes a node entry in the hash table

uint64_t ht_size(HashTable *ht);  //not implemented

LLNode *ht_lookup(HashTable *ht, char *email);  //completed

void ht_insert(HashTable *ht, LLNode *node);  //completed

uint32_t ht_count(HashTable *ht);  //not implemented

double ht_avg_bst_size(HashTable *ht);  //not implemented

double ht_avg_bst_height(HashTable *ht);  // not implemented

void ht_print(HashTable *ht);  //completed

void ht_save(HashTable *ht, char *outfile);  //implemented

