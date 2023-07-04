#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "vector.h"

typedef void *key_type;
typedef void *value_type;
typedef int (*cmp_func)(key_type, key_type);
typedef void (*destroy_key_func)(key_type);
typedef void (*destroy_value_func)(value_type);

typedef struct Pair
{
    key_type key;
    value_type value;
} Pair;

typedef struct Node Node;
typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_construct(cmp_func cmp_fn, destroy_key_func destroy_key_fn, destroy_value_func destroy_value_fn);
void binary_tree_add(BinaryTree *tree, key_type key, value_type value);
Pair *binary_tree_get(BinaryTree *tree, key_type key);
Pair *binary_tree_remove(BinaryTree *tree, key_type key);
Pair *binary_tree_min(BinaryTree *tree);
Pair *binary_tree_max(BinaryTree *tree);
Pair *binary_tree_pop_min(BinaryTree *tree);
Pair *binary_tree_pop_max(BinaryTree *tree);
void binary_tree_destroy(BinaryTree *tree);

Vector *inorder_traversal_recursive(BinaryTree *tree);
Vector *inorder_traversal_iterative(BinaryTree *tree);
Vector *preorder_traversal_recursive(BinaryTree *tree);
Vector *preorder_traversal_iterative(BinaryTree *tree);
Vector *postorder_traversal_recursive(BinaryTree *tree);
Vector *postorder_traversal_iterative(BinaryTree *tree);
Vector *levelorder_traversal(BinaryTree *tree);

#endif