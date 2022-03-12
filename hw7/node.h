#pragma once

typedef struct LLNode LLNode;
typedef struct cus_rec cus_rec;

struct cus_rec {
    char *email;
    char *name;
    int shoe_size;
    char *fav_food;
    LLNode *left;
    LLNode *right;
};

struct LLNode {
    cus_rec record;
    LLNode *next;
};

LLNode *LLnode_create(void);

void LLnode_delete(LLNode *n);

void LLnode_print_rec(LLNode *n);
