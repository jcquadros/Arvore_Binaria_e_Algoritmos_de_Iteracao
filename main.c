#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Celula{
    int lin;
    int col;
}Celula;


int cmp_fn(key_type a, key_type b)
{
    if(((Celula *)a)->lin == ((Celula *)b)->lin){
        return ((Celula *)a)->col - ((Celula *)b)->col;
    }
    return ((Celula *)a)->lin - ((Celula *)b)->lin;
}

void destroy_key_fn(key_type key)
{
    free(key);
}

void destroy_value_fn(value_type value)
{
    free(value);
}


int main(){

    int n;
    scanf("%d%*c", &n);

    BinaryTree *tree = binary_tree_construct(cmp_fn, destroy_key_fn, destroy_value_fn);
    for(int i = 0; i < n; i++){
        char fn[10];
        scanf("%s%*c", fn);
        if(strcmp(fn, "SET") == 0){
            Celula *cel = (Celula *)malloc(sizeof(Celula));
            int *val = (int *)malloc(sizeof(int));
            scanf("%d%*c%d%*c%d%*c", &cel->lin, &cel->col, val);
            binary_tree_add(tree, cel, val);
        }else if(strcmp(fn, "GET") == 0){
            Celula cel;
            scanf("%d%*c%d%*c", &cel.lin, &cel.col);
            Pair *p = binary_tree_get(tree, &cel);
            
            if(p!=NULL){
                printf("%d\n", *(int *)p->value);
                free(p);
            }
        }
    }

    binary_tree_destroy(tree);

    return 0;
}