#ifndef ARV_
#define ARV_

typedef struct node *BTree;


/**
 * @brief Inserts a new element and balances the tree if necessary
 * 
 * @param t Tree
 * @return New root
 */
BTree bt_insert(BTree t, int val);


/**
 * @brief Searchs an element in the tree
 * 
 * @param t Tree
 * @param x Element value
 * @return 1 the element is found, 0 otherwise
 */
int bTSearch(BTree t, int x);


/**
 * @brief Free a whole tree
 * 
 * @param t Tree
 * @return void
 */
void freeBT(BTree t);


/**
 * @brief Put the field of a file in a Binary Tree
 * 
 * @param f File to write
 * @param count Position of the field
 * @return New root
 */
BTree fieldToBT(FILE *f, int count);


#endif