#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

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


// Iterators
struct Iterator {
    Node *node;
};

void _inorder_traversal_recursive(Node *node, Vector *vector){
    if(node == NULL){
        return;
    }
    _inorder_traversal_recursive(node->left, vector);
    vector_push_back(vector, node);
    _inorder_traversal_recursive(node->right, vector);
}

void iterator_inorder_traversal_recursive(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return vector;
    }
    _inorder_traversal_recursive(tree->root, vector);

}
void iterator_inorder_traversal_iterative(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return;
    }

    Stack *stack = stack_construct();
    Node *node = tree->root;
    while (!stack_empty(stack) || node != NULL){
        if(node != NULL){
            stack_push(stack, node);
            node = node->left;
        }else{
            node = stack_pop(stack);
            vector_push_back(vector, node);
            node = node->right;
        }
    }

    stack_destroy(stack);
}

void _preorder_traversal_recursive(Node *node, Vector *vector){
    if(node == NULL){
        return;
    }
    vector_push_back(vector, node);
    _preorder_traversal_recursive(node->left, vector);
    _preorder_traversal_recursive(node->right, vector);
}

void iterator_preorder_traversal_recursive(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return vector;
    }
    _preorder_traversal_recursive(tree->root, vector);
}

void iterator_preorder_traversal_iterative(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return;
    }
    Stack *stack = stack_construct();
    stack_push(stack, tree->root);
    while(!stack_empty(stack)){
        Node *node = stack_pop(stack);
        vector_push_back(vector, node);
        if(node->right != NULL){
            stack_push(stack, node->right);
        }
        if(node->left != NULL){
            stack_push(stack, node->left);
        }
    }
    stack_destroy(stack);
}

void _postorder_traversal_recursive(Node *node, Vector *vector){
    if(node == NULL){
        return;
    }
    _postorder_traversal_recursive(node->left, vector);
    _postorder_traversal_recursive(node->right, vector);
    vector_push_back(vector, node);
}

void iterator_postorder_traversal_recursive(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return vector;
    }
    _postorder_traversal_recursive(tree->root, vector);
}

void iterator_postorder_traversal_iterative(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return;
    }
    Stack *stack = stack_construct();
    Stack *stack_rev = stack_construct();
    while(!stack_empty(stack)){
        Node *node = stack_pop(stack);
        if(node->left != NULL){
            stack_push(stack, node->left);
        }
        if(node->right != NULL){
            stack_push(stack, node->right);
        }
        stack_push(stack_rev, node);
    }

    while(!stack_empty(stack_rev)){
        Node *node = stack_pop(stack_rev);
        vector_push_back(vector, node);
    }

    stack_destroy(stack);
    stack_destroy(stack_rev);
}

void iterator_levelorder_traversal(BinaryTree* tree, Vector *vector){
    if(tree->root == NULL){
        return;
    }
    Queue *queue = queue_construct();
    queue_push(queue, tree->root);
    while(!queue_empty(queue)){
        Node *node = queue_pop(queue);
        vector_push_back(vector, node);
        if(node->left != NULL){
            queue_push(queue, node->left);
        }
        if(node->right != NULL){
            queue_push(queue, node->right);
        }
    }
    queue_destroy(queue);
}

void iterator_destroy(Iterator* iterator){
    free(iterator);
}

