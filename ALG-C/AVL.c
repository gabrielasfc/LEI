#include <stdio.h>


typedef enum balancefactor{
    LH, //left sub-tree has more height 
    EH,
    RH //right sub-tree has more height
} BalanceFactor;

typedef struct node{
    BalanceFactor bf;
    int value;
    struct node *left;
    struct node *right;
} *AVLTree;


#define MAX(x, y) (x>y ? x : y)



//Worst case = Best case: N
int non_avl_height(AVLTree t) {
    if (t==NULL) return 0;
    int left = non_avl_height(t->left);
    int right = non_avl_height(t->right);
    if (left>right) return left+1;
    else return right+1;
}


//Worst case = Best case: log N
int height(AVLTree t){
	int r = 0;
	while(t != NULL){
		r++;
		if(t->bf == RH) t = t->right;
        else t = t->left;
	}
	return r;
}



//Checks if it is a AVL Tree and puts tree height on h
//Worst case: N
int is_avl_aux(AVLTree t, int *height){
    if(t==NULL){
        *height = 0;
        return 1;
    }
    int left_height, right_height;
    int is_avl_left = is_avl_aux(t->left, &left_height);
    int is_avl_right = is_avl_aux(t->right, &right_height);
    if(abs(right_height - left_height) > 1 || is_avl_left==0 || is_avl_right==0) return 0;
    *height = 1 + MAX(left_height, right_height);
    return 1;
}

int is_avl(AVLTree t){
    int h;
    return (is_avl_aux(t, &h));
}



// requires: t != NULL && t->right != NULL
AVLTree rotate_left(AVLTree t){
    AVLTree aux = t->right;
    t->right = aux->left;
    aux->left = t;
    t = aux;
    return t;
}


// requires : t != NULL && t->left != NULL
AVLTree rotate_right(AVLTree t){
    AVLTree aux = t->left;
    t->left = aux->right;
    aux->right = t;
    t = aux;
    return t;
}


// requires: t != NULL && t->left != NULL
AVLTree balance_left(AVLTree t){
    if(t->left->bf == LH){
        t = rotate_right(t);
        t->bf = EH;
        t->right->bf = EH;
    }
    else{
        t->left = rotate_left(t->left);
        t = rotate_right(t);
        switch(t->bf){
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = RH;
                t->right->bf = EH;
                break;
            case RH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
        }
        t->bf = EH;
    }
    return t;
}


// requires: t != NULL && t->right != NULL
AVLTree balance_right(AVLTree t){
    if(t->right->bf == RH){
        t = rotate_left(t);
        t->bf = EH;
        t->left->bf = EH;
    }
    else{
        t->right = rotate_right(t->right);
        t = rotate_left(t);
        switch(t->bf){
            case EH:
                t->left->bf = EH;
                t->right->bf = EH;
                break;
            case LH:
                t->left->bf = EH;
                t->right->bf = RH;
                break;
            case RH:
                t->left->bf = LH;
                t->right->bf = EH;
        }
        t->bf = EH;
    }
    return t;
}


AVLTree insert(AVLTree t, int value, int *grow){ //grow is to check if the height grew with the insertion
    if(t==NULL){
        t = malloc(sizeof(struct node));
        t->value = value;
        t->right = t->left = NULL;
        t->bf = EH;
        *grow = 1;
    }
    else{
        if(value > t->value){
            t->right = insert(t->right, value, grow);
            if(*grow == 1){
                switch(t->bf){
                    case LH:
                        t->bf = EH;
                        *grow = 0;
                        break;
                    case EH:
                        t->bf = RH;
                        *grow = 1;
                        break;
                    case RH:
                        t = balance_right(t);
                        *grow = 0;
                        break;
                }
            }
        }
        else{
            t->left = insert(t->left, value, grow);
            if(*grow == 1){
                switch(t->bf){
                    case LH:
                        t = balance_left(t);
                        *grow = 0;
                        break;
                    case EH:
                        t->bf = LH;
                        *grow = 1;
                        break;
                    case RH:
                        t->bf = EH;
                        *grow = 0;
                        break;
                }
            }
        }
    return t;
}