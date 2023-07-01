#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct BinaryTree{
    Node *root;
    cmp_func cmp_fn;
};

// Create a new node
Node *node_construct(Node *parent, Node *left, Node *right, key_type key, value_type value) {
    Node *node = malloc(sizeof(Node));
    node->left = left;
    node->right = right;
    node->value = value;
    node->key = key;
    node->parent = parent;
    return node;
}

// Destroy a node
void node_destroy(Node *node) {
    if (node == NULL) {
        return;
    }
    node_destroy(node->left);
    node_destroy(node->right);
    free(node);
}

// Create a new tree
BinaryTree *binary_tree_construct(cmp_func cmp_fn) {
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->cmp_fn = cmp_fn;
    return tree;
}

Node *_add_recursive(Node *node, Node *parent, key_type key, value_type value, cmp_func cmp_fn){
    if(node == NULL){
        //printf("Construindo um novo nó para a chave %s\n", (char*)key);
        return node_construct(parent, NULL, NULL, key, value);
    }
    if(cmp_fn(key, node->key) < 0){
        //printf("Inserindo %s na esquerda de %s\n", (char*)key, (char*)node->key);
        node->left = _add_recursive(node->left, node, key, value, cmp_fn);
    }
    else{
        //printf("Inserindo %s na direita de %s\n", (char*)key, (char*)node->key);
        node->right = _add_recursive(node->right, node, key, value, cmp_fn);
    }
    return node;
}

// Add a new node to the tree
void binary_tree_add(BinaryTree* tree, key_type key, value_type value){
    tree->root = _add_recursive(tree->root, NULL, key, value, tree->cmp_fn);
}

Node *_get_recursive(Node *node, key_type key, cmp_func cmp_fn){
    if(node == NULL){
        return NULL;
    }
    if(cmp_fn(key, node->key) == 0){
        return node;
    }
    if(cmp_fn(key, node->key) < 0){
        return _get_recursive(node->left, key, cmp_fn);
    }
    else{
        return _get_recursive(node->right, key, cmp_fn);
    }
}

value_type binary_tree_get(BinaryTree* tree, key_type key){
    // recursive
    Node *node = _get_recursive(tree->root, key, tree->cmp_fn);
    if(node == NULL){
        return NULL;
    }
    return node->value;
}


Node *_get_min(Node *node){
    if(node->left == NULL){
        return node;
    }
    return _get_min(node->left);
}

Node *binary_tree_min(BinaryTree* tree){
    if(tree->root == NULL){
        return NULL;
    }
    return _get_min(tree->root);
}

Node *_get_max(Node *node){
    if(node->right == NULL){
        return node;
    }
    return _get_max(node->right);
}

Node *binary_tree_max(BinaryTree* tree){
    if(tree->root == NULL){
        return NULL;
    }
    return _get_max(tree->root);
}

void _transplant(BinaryTree* tree, Node *u, Node *v){
    if(u->parent == NULL){
        tree->root = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    if(v != NULL){
        v->parent = u->parent;
    }
}

Node *_delete_recursive(BinaryTree *tree, Node *node){
    // caso 1 : nao tem o filho da esquerda ou nenhum filho
    if(node->left == NULL){
        _transplant(tree, node, node->right);
    // caso 2 : nao tem o filho da direita
    }else if (node->right == NULL){
        _transplant(tree, node, node->left);
    // caso 3 : tem os dois filhos
    }else{
        Node *successor = _get_min(node->right);
        // caso 3.1 : sucessor nao eh filho direito de node entao eu faco a substicuicao para que seja o filho direito
        if(successor->parent != node){
            _transplant(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        // caso 3.2 : sucessor eh filho direito de node entao faco a substituicao com o node e atualiza a arvore da esquerda
        _transplant(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }
    return node;
}

Node *binary_tree_pop(BinaryTree* tree, key_type key){
    // procurar por key
    Node *node = _get_recursive(tree->root, key, tree->cmp_fn);
    if(node == NULL){
        return NULL;
    }
    return _delete_recursive(tree, node);
}

Node *binary_tree_remove_min(BinaryTree* tree){
    Node *node = binary_tree_min(tree);
    if(node == NULL){
        return NULL;
    }
    return _delete_recursive(tree, node);
}

Node *binary_tree_remove_max(BinaryTree* tree){
    Node *node = binary_tree_max(tree);
    if(node == NULL){
        return NULL;
    }
    return _delete_recursive(tree, node);
}

// Destroy a tree
void binary_tree_destroy(BinaryTree *tree) {
    if (tree == NULL) {
        return;
    }
    node_destroy(tree->root);
    free(tree);
}