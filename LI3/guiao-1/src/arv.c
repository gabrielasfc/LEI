/**
 * @file arv.c
 * @brief Functions related to AVL trees data structure
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,l) (((a)>(l))?(a):(l))


typedef struct node{
    int ht;
    int val;
    struct node *left, *right;
} *BTree;


/**
 * @brief Gives the height of the tree
 * 
 * @param t Tree
 * @return Height
 */
int height(BTree t){
    if (t == NULL) return 0;
    return t->ht;
}


/**
 * @brief Rotates the tree to the right
 * 
 * @param t Tree
 * @return New root
 */
BTree rightRotate(BTree t){
    BTree l = t->left;
    BTree lr = l->right;

    l->right = t;
    t->left = lr;

    //changing heights in struct
    t->ht = MAX(height(t->left), height(t->right)) + 1;
    l->ht = MAX(height(l->left), height(l->right)) + 1;
    
    return l;
}


/**
 * @brief Rotates the tree to the left
 * 
 * @param t Tree
 * @return New root
 */
BTree leftRotate(BTree t){
    BTree r = t->right;
    BTree rl = r->left;

    r->left = t;
    t->right = rl;

    t->ht = MAX(height(t->left), height(t->right)) + 1;
    r->ht = MAX(height(r->left), height(r->right)) + 1;
    
    return r;
}


/**
 * @brief Allocates a new node with the given value
 * 
 * @param val Value
 * @return New node
 */
BTree newNode(int val){
    BTree new = malloc(sizeof(struct node));
    new->val = val;
    new->left = new->right = NULL;
    new->ht = 1;
    return new;
}


/**
 * @brief Gets the balance factor
 * 
 * @param t Tree
 * @return Factor
 */
int getBalance(BTree t){
    int h=0;
    if (t != NULL) 
        h = (height(t->left) - height(t->right));
    return h;
}


/**
 * @brief Inserts a new element and balances the tree if necessary
 * 
 * @param t Tree
 * @return New root
 */
BTree bt_insert(BTree t, int val){

    if (t == NULL) return (newNode(val));
    if (val < t->val) t->left = bt_insert(t->left, val);
    else if (val > t->val) t->right = bt_insert(t->right, val);
    else return t;

    t->ht = 1 + MAX(height(t->left), height(t->right));
    
    int balance = getBalance(t);
    
    if (balance > 1 && val < t->left->val) return rightRotate(t);
    if (balance < -1 && val > t->right->val) return leftRotate(t);

    if (balance > 1 && val > t->left->val){
        t->left = leftRotate(t->left);   
        return rightRotate(t);
    }
    if (balance < -1 && val < t->right->val){
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }
    
    return t;
}


/**
 * @brief Searchs an element in the tree
 * 
 * @param t Tree
 * @param x Element value
 * @return 1 the element is found, 0 otherwise
 */
int bTSearch(BTree t, int x){
    int r=0;

    while(t != NULL && t->val != x){
        if (x > t->val) t = t->right;
        else t = t->left;
    }

    if (t!=NULL) r=1;
    return r;
}


/**
 * @brief Free a whole tree
 * 
 * @param t Tree
 * @return void
 */
void freeBT(BTree t){
    if(t==NULL) return;

    freeBT(t->left);
    freeBT(t->right);
    free(t);
}


/**
 * @brief Put the field of a file in a Binary Tree
 * 
 * @param f File to write
 * @param count Position of the field
 * @return New root
 */
BTree fieldToBT(FILE *f, int count){
    char *buffer = malloc(100000), *found;
    BTree ret = NULL;

    while(fgets(buffer, 100000, f)!=NULL){
        char *dup = strdup(buffer), *backup = dup;
        int i;

        for(i = 0; i<count; i++) found = strsep(&dup, ";");

        ret = bt_insert(ret, atoi(found));

        free(backup);
    }
    free(buffer);
    return ret;
}
