#pragma once

typedef struct Node Node;

struct cus_rec {
    char *email;
    char *name;
    int *shoe_siz;
    char *food;
};

struct Node {
    struct cus_rec;
    char *oldspeak;
    char *newspeak;
    Node *left;
    Node *right;
};

Node *node_create(char *oldspeak, char *newspeak);

void node_delete(Node **n);

void node_print(Node *n);
