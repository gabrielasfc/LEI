/**
 * @file dataInterface.c
 * @brief Abstract functions to deal with abstract data structures 
 * @date 2021-11-09
 * 
 */

#include "dataInterface.h"

void* insert(void* old, int val){
    void *ret = (BTree* )bt_insert(*((BTree*)(old)), val);
    return ret;
}

int find(void* data, int val){
    int found = bTSearch(*((BTree*)(data)), val);
    return found;
}