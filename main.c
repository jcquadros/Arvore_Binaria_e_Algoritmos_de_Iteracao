#include <stdio.h>
#include <stdlib.h>
#include "src/binary_tree.h"
#include "vector.h"
#include <string.h>

int cmp_fn(key_type a, key_type b){
    return strcmp(a, b);
}

void destroy_key_fn(key_type key){
    //free(key);
}

void destroy_value_fn(value_type value){
    //free(value);
}

int main(){
    // Create a new tree
    BinaryTree *tree = binary_tree_construct(cmp_fn, destroy_key_fn, destroy_value_fn);

    // Add some ps
    binary_tree_add(tree, "Murilo", "Schirmer (Mu)");
    binary_tree_add(tree, "Rogerio", "Schirmer (Rog)");
    binary_tree_add(tree, "Rafaela", "Schirmer (Rafa)");
    binary_tree_add(tree, "Jullie", "Quadros");
    binary_tree_add(tree, "Bernardo", "Schirmer (Be)");
    binary_tree_add(tree, "Soraia", "Schirmer (So)");
    
    // Get some ps
    // printf("Murilo: %s\n", (char*)binary_tree_get(tree, "Murilo")->value);
    // printf("Rogerio: %s\n", (char*)binary_tree_get(tree, "Rogerio")->value);
    // printf("Rafaela: %s\n", (char*)binary_tree_get(tree, "Rafaela")->value);
    // printf("Jullie: %s\n", (char*)binary_tree_get(tree, "Jullie")->value);
    // printf("Bernardo: %s\n", (char*)binary_tree_get(tree, "Bernardo")->value);
    // printf("Soraia: %s\n", (char*)binary_tree_get(tree, "Soraia")->value);

    // Inorder traversal
    Vector *inorder = inorder_traversal_recursive(tree);
    printf("Inorder: ");
    for(int i = 0; i < vector_size(inorder); i++){
        Pair *p = vector_get(inorder, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(inorder) > 0){
        Pair *p = vector_pop_back(inorder);
        free(p);
    }
    vector_destroy(inorder);

    // inorder traversal iterative
    Vector *inorder_iterative = inorder_traversal_iterative(tree);
    printf("Inorder iterative: ");
    for(int i = 0; i < vector_size(inorder_iterative); i++){
        Pair *p = vector_get(inorder_iterative, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(inorder_iterative) > 0){
        Pair *p = vector_pop_back(inorder_iterative);
        free(p);
    }
    vector_destroy(inorder_iterative);

    // preorder traversal
    Vector *preorder = preorder_traversal_recursive(tree);
    printf("Preorder: ");
    for(int i = 0; i < vector_size(preorder); i++){
        Pair *p = vector_get(preorder, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(preorder) > 0){
        Pair *p = vector_pop_back(preorder);
        free(p);
    }
    vector_destroy(preorder);

    // preorder traversal iterative
    Vector *preorder_iterative = preorder_traversal_iterative(tree);
    printf("Preorder iterative: ");
    for(int i = 0; i < vector_size(preorder_iterative); i++){
        Pair *p = vector_get(preorder_iterative, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(preorder_iterative) > 0){
        Pair *p = vector_pop_back(preorder_iterative);
        free(p);
    }
    vector_destroy(preorder_iterative);

    // postorder traversal
    Vector *postorder = postorder_traversal_recursive(tree);
    printf("Postorder: ");
    for(int i = 0; i < vector_size(postorder); i++){
        Pair *p = vector_get(postorder, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(postorder) > 0){
        Pair *p = vector_pop_back(postorder);
        free(p);
    }
    vector_destroy(postorder);

    // postorder traversal iterative
    Vector *postorder_iterative = postorder_traversal_iterative(tree);
    printf("Postorder iterative: ");
    for(int i = 0; i < vector_size(postorder_iterative); i++){
        Pair *p = vector_get(postorder_iterative, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(postorder_iterative) > 0){
        Pair *p = vector_pop_back(postorder_iterative);
        free(p);
    }
    vector_destroy(postorder_iterative);

    // Level order traversal
    Vector *level_order = levelorder_traversal(tree);
    printf("Level order: ");
    for(int i = 0; i < vector_size(level_order); i++){
        Pair *p = vector_get(level_order, i);
        printf("%s ", (char*)p->key);
    }
    printf("\n");
    while(vector_size(level_order) > 0){
        Pair *p = vector_pop_back(level_order);
        free(p);
    }
    vector_destroy(level_order);

    // Minimum
    Pair *min = binary_tree_min(tree);
    if(min){
        printf("Min: %s\n", (char*)min->key);
        free(min);
    }
    else{
        printf("Min: NULL\n");
    }
    // Maximum
    Pair *max = binary_tree_max(tree);
    if(max){
        printf("Max: %s\n", (char*)max->key);
        free(max);
    }
    else{
        printf("Max: NULL\n");
    }

    // Remove pairs
    Pair *p = binary_tree_remove(tree, "Murilo");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover rogerio
    p = binary_tree_remove(tree, "Rogerio");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover rafaela
    p = binary_tree_remove(tree, "Rafaela");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover jullie
    p = binary_tree_remove(tree, "Jullie");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover bernardo
    p = binary_tree_remove(tree, "Bernardo");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }

    // remover soraia
    p = binary_tree_remove(tree, "Soraia");
    if(p){
        printf("Removido: %s\n", (char*)p->key);
        free(p);
    }
    else{
        printf("Removido: NULL\n");
    }
    
    // Destroy the tree
    binary_tree_destroy(tree);
    
    return 0;
}
