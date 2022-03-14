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

void bst_destroy(BSTnode *root);

BSTnode *bst_insert(HashTable *ht, BSTnode *node, BSTnode *n_insert);

void bst_print(BSTnode *root);

BSTnode *bst_delete(BSTnode *root, char *key);

