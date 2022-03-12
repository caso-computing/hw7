//
//  bst.c
//  hw7
//
//  Created by Connor Lynch on 3/10/22.
//

#include <stdio.h>
#include <string.h>

#include "ht.h"
#include "node.h"

LLNode *bst_insert(HashTable *ht, LLNode *node,LLNode *n_insert){
    
    if (node==NULL){
        return (node=n_insert);
    }
    if (strcmp(n_insert->record.email, node->record.email)<0){
        node->record.left=bst_insert(ht,node->record.left, n_insert);
    }
    else if (strcmp(n_insert->record.email, node->record.email)>0){
        node->record.right=bst_insert(ht,node->record.right,n_insert);
    }
    else{
        node->record.name=n_insert->record.name;
        node->record.shoe_size=n_insert->record.shoe_size;
        node->record.fav_food=n_insert->record.fav_food;
        return NULL;
    }
    return node;
}

// Find the inorder successor
LLNode *minValueNode(LLNode *node) {
    LLNode *current = node;
    
    // Find the leftmost leaf
    while (current && current->record.left != NULL)
        current = current->record.left;
    
    return current;
}

// Deleting a node
LLNode *bst_delete(LLNode *root, char *key) {
    // Return if the tree is empty
    if (root == NULL) return root;
    
    // Find the node to be deleted
    if (strcmp(key,root->record.email)<0){
        root->record.left = bst_delete(root->record.left, key);
    }
    else if (strcmp(key, root->record.email)>0)
        root->record.right = bst_delete(root->record.right, key);
    
    else {
        // If the node is with only one child or no child
        if (root->record.left == NULL) {
            LLNode *temp = root->record.right;
            return temp;
        } else if (root->record.right == NULL) {
            LLNode *temp = root->record.left;
            return temp;
        }
        
        // If the node has two children
        LLNode *temp = minValueNode(root->record.right);
        
        // Place the inorder successor in position of the node to be deleted
        root->record.email = temp->record.email;
        
        // Delete the inorder successor
        root->record.right = bst_delete(root->record.right, temp->record.email);
    }
    return root;
}


void bst_print(LLNode *node){
    if (node != NULL){
        bst_print(node->record.left);
        printf("[key]: %s\n",node->record.email);
        bst_print(node->record.right);
    }
    
}

