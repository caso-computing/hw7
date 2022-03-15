//
//  node.c
//  hw7
//
//  Created by Connor Lynch on 3/7/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "node.h"


LLNode *LLnode_create(void){
    return ((LLNode *)malloc(sizeof(LLNode)));
}

void LLnode_delete(LLNode *n){
    free(n->record.email);          //  Free up the dynamic strings from strdup
    n->record.email=NULL;
    free(n->record.name);
    n->record.name=NULL;
    free(n->record.fav_food);
    n->record.fav_food=NULL;
    free(n);
    n=NULL;
}

void LLnode_print_rec(LLNode *n){
    
    printf("\tEMAIL: %s\n",n->record.email);
    printf("\t\tNAME: %s\n",n->record.name);
    printf("\t\tSHOE SIZE: %d\n",n->record.shoe_size);
    printf("\t\tFAVORITE FOOD: %s\n\n",n->record.fav_food);
}
