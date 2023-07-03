#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include "vector.h"
typedef void* key_type;
typedef void* value_type;
typedef int (*cmp_func)(key_type, key_type);

typedef struct Node{
    key_type key;
    value_type value;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct BinaryTree BinaryTree;


BinaryTree* binary_tree_construct(cmp_func cmp_fn);
void binary_tree_add(BinaryTree* tree, key_type key, value_type value);
value_type binary_tree_get(BinaryTree* tree, key_type key);
Node *binary_tree_pop(BinaryTree* tree, key_type key);
Node *binary_tree_min(BinaryTree* tree);
Node *binary_tree_max(BinaryTree* tree);
Node *binary_tree_remove_min(BinaryTree* tree);
Node *binary_tree_remove_max(BinaryTree* tree);
void binary_tree_destroy(BinaryTree* tree);


// Iterator
typedef struct Iterator Iterator;

void iterator_inorder_traversal_recursive(BinaryTree* tree, Vector *vector);
void iterator_inorder_traversal_iterative(BinaryTree* tree, Vector *vector);
void iterator_preorder_traversal_recursive(BinaryTree* tree, Vector *vector);
void iterator_preorder_traversal_iterative(BinaryTree* tree, Vector *vector);
void iterator_postorder_traversal_recursive(BinaryTree* tree, Vector *vector);
void iterator_postorder_traversal_iterative(BinaryTree* tree, Vector *vector);
void iterator_levelorder_traversal(BinaryTree* tree, Vector *vector);

void iterator_destroy(Iterator* iterator);
#endif