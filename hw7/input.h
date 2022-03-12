//
//  input.h
//  hw7
//
//

#ifndef input_h
#define input_h

#include <stdio.h>
#include <stdbool.h>

#include "ht.h"
#include "node.h"

typedef struct customer_rec customer_rec;
typedef struct LLNode LLNode;

bool input(HashTable *ht, char *outfile);

#endif /* input_h */
