#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

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

Iterator* iterator_inorder_traversal_recursive_construct(BinaryTree* tree);
Node* iterator_inorder_traversal_recursive_next(Iterator* iterator);
int iterator_is_over(Iterator* iterator);
void iterator_destroy(Iterator* iterator);
#endif