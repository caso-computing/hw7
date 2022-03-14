#pragma once



typedef struct BSTnode BSTnode;
typedef struct HashTable HashTable;


struct BSTnode {
    cus_rec *cusPtr;
    BSTnode *left;
    BSTnode *right;
};


//extern uint64_t branches;

BSTnode *bst_create(void);

uint32_t bst_height(LLNode *root);

uint32_t bst_size(LLNode *root);

BSTnode *bst_find(LLNode *root, LLNode *n);

BSTnode *bst_insert(HashTable *ht, BSTnode *node, BSTnode *n_insert);

void bst_print(BSTnode *root);

BSTnode *bst_delete(BSTnode *root, char *key);

