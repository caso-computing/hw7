//
//  ht.c
//  hw7
//
//  Created by Connor Lynch on 3/7/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ht.h"
#include "input.h"
#include "salts.h"
#include "node.h"
#include "speck.h"



//  ht_create is a routine that creates a dynamically allocated hash table.  The hash table contains
//  the 128bit salt to be used in the speck sipher, the size of the hash table itself, and an array of
//  pointers to the customer node records stored in the hash table.  Only if a hash table index has a null
//  pointer does it indicate nothing has been hashed to that address.
//
//  Also, not that collisions in the hash table are singulary linked to the next entry for that hash
//  table index.
//
//  Function returns a pointer to the hash table created.
HashTable *ht_create(uint32_t size){

    HashTable *out = (HashTable *) calloc(1, sizeof(HashTable));
    out->size= size;
    out->salt[0]=SALT_HASHTABLE_LO;
    out->salt[1]=SALT_HASHTABLE_HI;
    out->long_link=0;
    out->num_entries=0;
    out->num_records=0;
    out->llink=(LLNode **)calloc(size, sizeof(LLNode));
    
    return out;
}

// Free up everything in the hash table.  Start by locating all the record nodes and freeing up all
// the strings stored in record.  Then free up the node the stored is stored in  Next make sure you get
// rid of all nodes at a hash table entry.  Finally, free up the hash table set the pointer to null.
//
void ht_delete(HashTable *ht){
    LLNode *lnode, *ltemp;
    for (uint64_t i=0; i<ht->size;i++){
        lnode=ht->llink[i];
        if (lnode){
            do {
                ltemp=lnode;
                lnode=lnode->next;
                free(ltemp->record.name);
                free(ltemp->record.email);
                free(ltemp->record.fav_food);
                free(ltemp);
                ltemp=NULL;
            } while (lnode);
        }
        ht->llink[i]=NULL;
    }
    free(ht->llink);
    ht->llink=NULL;
    free(ht);
    ht=NULL;
}

//  This routine will delete an single entry from the hassh table.
//  It assumes that the node passed to it exists somewhere in the hashtable.  ie, it was run through
//  the function lookup_entry before trying to delete it.

void ht_delete_entry(HashTable *ht, LLNode *n){
    LLNode *node = n;
    LLNode *cur_ptr, *prev_ptr;
    uint32_t i=hash(ht->salt, n->record.email);
    i = i % ht->size;
    cur_ptr=ht->llink[i];
    prev_ptr=ht->llink[i];
    
    while (cur_ptr!=node){         // look for where the node to be deleted is on a llink list
        prev_ptr=cur_ptr;
        cur_ptr=cur_ptr->next;
    }
    if (cur_ptr==ht->llink[i]){    // if first node in link, make sure to set hashtable entry to NULL
        ht->llink[i]=NULL;
    }
    else {
        prev_ptr->next=cur_ptr->next;    // Remove node from link
    }
        
    LLnode_delete(n);         // Free up unused memory.
    n=NULL;
}

LLNode *ht_lookup(HashTable *ht, char *email){
    LLNode *node = NULL;
//    void *ptr = NULL;
    uint32_t i=hash(ht->salt, email);
    i = i % ht->size;
    node = ht->llink[i];
    while (node){
        if (!(strcmp(node->record.email,email))){       // strcmp returns 0 if the two strings are equal
            return node;
        }
        node = node->next;
    }
    return node;
}

void ht_insert(HashTable *ht, LLNode *node){
    
    uint32_t i=hash(ht->salt, node->record.email);
    i = i % ht->size;
    
    LLNode *temp = ht->llink[i];
        ht->llink[i] = node;  //Insert the new node at the beginning of the ll
        node->next=temp;        // make sure the new node points to the old head of the ll.
}

uint64_t ht_size(HashTable *ht){
    return ((uint64_t) ht->size);
}

void ht_print(HashTable *ht){
    LLNode *lnode;
    for (uint64_t i=0; i<ht->size; i++ ){
        lnode = ht->llink[i];
        while(lnode){                   //check to make sure there is an entry at this index
            printf("Hash index = %llu\n",i);
            do {
                printf ("    email: %s\n",lnode->record.email);
                printf("    name: %s\n",lnode->record.name);
                printf("    shoe size = %d\n",lnode->record.shoe_size);
                printf("    favorite food = %s\n\n",lnode->record.fav_food);
                lnode = lnode->next;
                
            } while (lnode);
        }
    }
}

void ht_save(HashTable *ht, char *outfile){
    LLNode *link;
    FILE *fout;
    fout=fopen(outfile, "w");
    // scan down hash list for entries
    for (uint64_t i=0; i<ht->size; i++){
        if (ht->llink[i]){              // if there is an entry at this index then grab the node to print
            link=ht->llink[i];
            do{
                fprintf(fout, "%s\t%s\t",link->record.email,link->record.name);
                fprintf(fout, "%d\t%s\n",link->record.shoe_size,link->record.fav_food);
                link=link->next;
            
            } while (link);
        }
    }
    fclose(fout);
}
