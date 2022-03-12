#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "node.h"


//extern uint64_t branches;

LLNode *bst_create(void);

uint32_t bst_height(LLNode *root);

uint32_t bst_size(LLNode *root);

LLNode *bst_find(LLNode *root, LLNode *n);

LLNode *bst_insert(HashTable *ht, LLNode *node, LLNode *n_insert);

void bst_print(LLNode *root);

LLNode *bst_delete(LLNode *root, char *key);

