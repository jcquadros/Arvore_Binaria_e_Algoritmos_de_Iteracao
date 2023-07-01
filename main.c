#include <stdio.h>
#include <stdlib.h>
#include "src/binary_tree.h"
#include <string.h>

int cmp_fn(key_type a, key_type b){
    return strcmp(a, b);
}

int main(){
    // Create a new tree
    BinaryTree *tree = binary_tree_construct(cmp_fn);

    // Add some nodes
    binary_tree_add(tree, "Murilo", "Schirmer (Mu)");
    binary_tree_add(tree, "Rogerio", "Schirmer (Rog)");
    binary_tree_add(tree, "Rafaela", "Schirmer (Rafa)");
    binary_tree_add(tree, "Jullie", "Quadros");
    binary_tree_add(tree, "Bernardo", "Schirmer (Be)");
    binary_tree_add(tree, "Soraia", "Schirmer (So)");
    
    // Get some nodes
    printf("Murilo: %s\n", (char*)binary_tree_get(tree, "Murilo"));
    printf("Rogerio: %s\n", (char*)binary_tree_get(tree, "Rogerio"));
    printf("Rafaela: %s\n", (char*)binary_tree_get(tree, "Rafaela"));
    printf("Jullie: %s\n", (char*)binary_tree_get(tree, "Jullie"));
    printf("Bernardo: %s\n", (char*)binary_tree_get(tree, "Bernardo"));
    printf("Soraia: %s\n", (char*)binary_tree_get(tree, "Soraia"));
    printf("Valor nulo: %s\n", (char*)binary_tree_get(tree, "Valor nulo"));

    // Minimum
    Node *min = binary_tree_min(tree);
    if(min){
        printf("Min: %s\n", (char*)min->key);
    }
    else{
        printf("Min: NULL\n");
    }
    // Maximum
    Node *max = binary_tree_max(tree);
    if(max){
        printf("Max: %s\n", (char*)max->key);
    }
    else{
        printf("Max: NULL\n");
    }

    // Remove node
    Node *node = binary_tree_pop(tree, "Murilo");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover rogerio
    node = binary_tree_pop(tree, "Rogerio");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover rafaela
    node = binary_tree_pop(tree, "Rafaela");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover jullie
    node = binary_tree_pop(tree, "Jullie");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover bernardo
    node = binary_tree_pop(tree, "Bernardo");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover soraia
    node = binary_tree_pop(tree, "Soraia");
    if(node){
        printf("Removido: %s\n", (char*)node->key);
        free(node);
    }
    else{
        printf("Removido: NULL\n");
    }
    
    // Destroy the tree
    binary_tree_destroy(tree);
    
    return 0;
}
