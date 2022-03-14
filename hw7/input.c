//
//  input.c
//  hw7
//
//

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>


#include "parser.h"
#include "input.h"
#include "node.h"
#include "ht.h"
#include "bst.h"
#include "speck.h"

#define BLOCK 1024

char buffer[BLOCK] = {0};



void add_cust_re(HashTable *ht){
/*
    regex_t db_parse;
    if (regcomp(&db_parse, "\\w+@[a-z]+\\.?[a-z]+", REG_EXTENDED)){
        fprintf(stderr, "Failed to compile regex.\n)");
        return;;
    }
 */
    //    customer_rec record;
    LLNode *node=LLnode_create();
    BSTnode *bstnode = bst_create();
    bstnode->cusPtr=&node->record;           // Set pointers to customer rec so you can modify
                                            //from either the HT or BST


    printf("Input email address: ");
    if (!fgets(buffer, BLOCK, stdin)) {
        free(node);
        node = NULL;
        return ;
    }
    buffer[strlen(buffer)-1]='\0';      //strip trailing newline from buffer
    node->record.email=strdup(buffer);
    
    printf("Input customer name: ");
    if (!fgets(buffer, BLOCK, stdin)) {
        free(node);
        node = NULL;
        return ;
    }
    buffer[strlen(buffer)-1]='\0';      //strip trailing newline from buffer
    node->record.name=strdup(buffer);
    
    printf("Input customer shoe size: ");
    if (!fgets(buffer, BLOCK, stdin)) {
        free(node);
        node = NULL;
        return ;
    }
    node->record.shoe_size=atoi(buffer);
    
    printf("Input customer favorite food: ");
    if (!fgets(buffer, BLOCK, stdin)) {
        free(node);
        node = NULL;
        return ;
    }
    buffer[strlen(buffer)-1]='\0';      //strip trailing newline from buffer
    node->record.fav_food=strdup(buffer);
    node->record.left=NULL;
    node->record.right=NULL;
    
    ht_insert(ht, node);
    if (ht->root){
        bst_insert(ht, ht->root, bstnode);
    }
    else{
        ht->root=bstnode;
    }
    return;
}

LLNode  *lookup_cus_by_email(HashTable *ht, char *email){
    LLNode *node=NULL;
    
    printf("Input email address: ");
    if (!fgets(buffer, BLOCK, stdin)) {
        email=strdup("no email entered.\n");
        return NULL;
    }
    buffer[strlen(buffer)-1]='\0';      //strip trailing newline from buffer
    strcpy(email,buffer);
    if ((node=ht_lookup(ht, email))){
//        LLnode_print_rec(node);
        return node;
    }
    return NULL;
}

bool delete_cus_by_email(HashTable *ht, char *email){
    LLNode *node;
    if (!(node=lookup_cus_by_email(ht, email))){
        printf("Couldn't find email address: %s\n\n",email);
        return false;
    }
    printf("Deleting record with key = %s\n",node->record.email);
    bst_delete(ht->root, node->record.email);
    ht_delete_entry(ht, node);
    return true;
}



//
// main input data for terminal routine.  It understands five commands typed into stdin:
//  add, lookup, delete, list, save, quit
//
//  Takes a link to a hash table for input and return true if the command complete successfully, false
//  otherwise.
//
bool input(HashTable *ht, char *output_file){
    enum commands {
        add=1,
        lookup,
        delete,
        list,
        list_ordered,
        save,
        quit,
        hash_key
    };
    char s[20];
//    char *email="";
    char email[100];
    int sw_val;
    bool more_input=true;
    LLNode *node;
    uint32_t key=0;
    
    while (more_input){
    printf("\n*** Input a valid command: ");
        if (!fgets(s, 20, stdin)) {
            return false;
        };
    s[strlen(s)-1]='\0';            // strip the lf from end of string
    sw_val=0;
    if (strcmp(s,"add")==0) sw_val=add;
    if (strcmp(s,"lookup")==0) sw_val=lookup;
    if (strcmp(s,"delete")==0) sw_val=delete;
    if (strcmp(s,"list")==0) sw_val=list;
    if (strcmp(s,"list_ordered")==00) sw_val=list_ordered;
    if (strcmp(s,"save")==0) sw_val=save;
    if (strcmp(s,"quit")==0) sw_val=quit;
    if (strcmp(s,"hash_key")==0) sw_val=hash_key;
    
    
    switch (sw_val){
        case add:
            add_cust_re(ht);        // add customer record will now promt for 5 fields
            break;
        case lookup:
            if (!(node=lookup_cus_by_email(ht, email))){
                printf("Couldn't find customer email %s\nPlease enter a new command.\n",email);
            }
            else{
                LLnode_print_rec(node);
            }
            break;
        case delete:
            if (!delete_cus_by_email(ht, email)){
                printf("Couldn't find customer email %s\nPlease enter a new command.\n",email);
            }
            else{
                printf("Deleted record key %s\n",email);
                email[0]='\0';                  // reset string
            }
            break;
        case list:
            ht_print(ht);
            break;
        case list_ordered:
            bst_print(ht->root);
            break;
        case save:
            ht_save(ht,output_file);
            break;
        case quit:
            printf("quiting program.\n");
            //  clean up memory
            more_input=false;
            break;
        case hash_key:
            lookup_cus_by_email(ht, email);
            key= hash(ht->salt, email);
            printf("32bit hash key = %u, modulo key = %llu\n",key,key%ht->size);
            break;
        default:
            printf("Not a valid program command. \n");
            printf("Valid commands are:  add, lookup, delete, list, list_ordered, save, or quit.\n");
    }
        
    }
    return true;
}
