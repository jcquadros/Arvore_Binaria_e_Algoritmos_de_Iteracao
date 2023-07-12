#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
    char nome[100];
    int idade;
    float altura;
}Pessoa;


int cmp_fn(key_type a, key_type b)
{
    return strcmp((char *)a, (char *)b);
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
            Pessoa *p = (Pessoa *)malloc(sizeof(Pessoa));
            scanf("%s%*c%d%*c%f%*c", p->nome, &p->idade, &p->altura);
            binary_tree_add(tree, strdup(p->nome), p);
        }else if(strcmp(fn, "GET") == 0){
            char key[12];
            scanf("%s%*c", key);
            Pair *p = binary_tree_get(tree, key);
            if(p != NULL){
                Pessoa *pessoa = (Pessoa *)p->value;
                printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
                free(p);
            }
        }else if(strcmp(fn, "POP") == 0){
            char key[12];
            scanf("%s%*c", key);
            Pair * p = binary_tree_remove(tree, key);
            if(p != NULL){
                destroy_key_fn(p->key);
                destroy_value_fn(p->value);
                free(p);
            }else{
                printf("CHAVE INEXISTENTE\n");
            }

        }else if(strcmp(fn, "MAX") == 0){
            Pair * p = binary_tree_max(tree);
            if(p != NULL){
                Pessoa *pessoa = (Pessoa *)p->value;
                printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
                free(p);
            }
        }else if(strcmp(fn, "MIN") == 0){
            Pair * p = binary_tree_min(tree);
            if(p != NULL){
                Pessoa *pessoa = (Pessoa*)p->value;
                printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
                free(p);
            }
        }else if(strcmp(fn, "POP_MAX") == 0){
            Pair *p = binary_tree_pop_max(tree);
            if(p != NULL){
                Pessoa *pessoa = (Pessoa*)p->value;
                printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
                destroy_key_fn(p->key);
                destroy_value_fn(p->value);
                free(p);
            }else{
                printf("ARVORE VAZIA\n");
            }
        }else if(strcmp(fn, "POP_MIN") == 0){
            Pair *p = binary_tree_pop_min(tree);
            if(p != NULL){
                Pessoa *pessoa = (Pessoa*)p->value;
                printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
                destroy_key_fn(p->key);
                destroy_value_fn(p->value);
                free(p);
            }else{
                printf("ARVORE VAZIA\n");
            }
        }
    }

    Vector *v = postorder_traversal_recursive(tree);

    for(int i = 0; i < vector_size(v) ;i++){
        Pair *p = (Pair *)vector_get(v, i);
        if(p != NULL){
            Pessoa *pessoa = (Pessoa*)p->value;
            printf("%s %d %.2f\n", pessoa->nome, pessoa->idade, pessoa->altura);
            free(p);
        }
    }    
    vector_destroy(v);
    binary_tree_destroy(tree);

    return 0;
}