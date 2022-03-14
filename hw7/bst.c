//
//  bst.c
//  hw7
//
//  Created by Connor Lynch on 3/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ht.h"
#include "node.h"
#include "bst.h"

BSTnode *bst_create(void){
    return ((BSTnode *)malloc(sizeof(BSTnode)));
}

void bst_destroy(BSTnode *root){

  if (root != NULL){
      bst_destroy(root->left);
      bst_destroy(root->right);
      free(root);                   // if we get to here, this has to be a end node to be taken out.
      root=NULL;
      return;
  }
}

BSTnode *bst_insert(HashTable *ht, BSTnode *node, BSTnode *n_insert){
    
    if (node==NULL){
        return (n_insert);
    }
    if (strcmp(n_insert->cusPtr->email, node->cusPtr->email)<0){
        node->left=bst_insert(ht,node->left, n_insert);
    }
    else if (strcmp(n_insert->cusPtr->email, node->cusPtr->email)>0){
        node->right=bst_insert(ht,node->right,n_insert);
    }
    else{                             //  email key already exits, so just copy updated name,
                                      //  fav_food, and shoe size
        free(node->cusPtr->name);
        node->cusPtr->name=strdup(n_insert->cusPtr->name);
        free(node->cusPtr->fav_food);
        node->cusPtr->fav_food=strdup(n_insert->cusPtr->fav_food);
        node->cusPtr->shoe_size=n_insert->cusPtr->shoe_size;
        return NULL;
    }
    return node;
}

// Find the inorder successor
BSTnode *minValueNode(BSTnode *node) {
    BSTnode *current = node;
    
    // Find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;
    
    return current;
}

// Deleting a node
BSTnode *bst_delete(BSTnode *root, char *key) {
    // Return if the tree is empty
    if (root == NULL) return root;
    
    // Find the node to be deleted
    if (strcmp(key,root->cusPtr->email)<0){
        root->left = bst_delete(root->left, key);
    }
    else if (strcmp(key, root->cusPtr->email)>0)
        root->right = bst_delete(root->right, key);
    
    else {
        // If the node is with only one child or no child
        if (root->left == NULL) {
            BSTnode *temp = root->right;
            return temp;
        } else if (root->right == NULL) {
            BSTnode *temp = root->left;
            return temp;
        }
        
        // If the node has two children
        BSTnode *temp = minValueNode(root->right);
        
        // Place the inorder successor in position of the node to be deleted
//        free(root);                 //  Delete the memory pointed to by root, ie node being deleted
        root->cusPtr=temp->cusPtr;      // Replace root customer ptr w successors customer ptr
        root->right=temp->right;        // Then make sure the root now points to the successor R leaf
        free(temp);                     //Don't need the successors container anymore
        temp=NULL;
        
    }
    return root;
}


void bst_print(BSTnode *node){
    if (node != NULL){
        bst_print(node->left);
        printf("[key]: %s\n",node->cusPtr->email);
        if (node->left){
            printf("Left = %s",node->left->cusPtr->email);
        }
        else {
            printf("Left = NULL");
        }
        if (node->right){
            printf(", Right = %s\n",node->right->cusPtr->email);
        }
        else{
            printf(", Right = NULL\n");
        }
        bst_print(node->right);
    }
    
}

