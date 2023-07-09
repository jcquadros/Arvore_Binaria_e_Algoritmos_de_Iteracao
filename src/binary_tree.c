#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "stack.h"

typedef struct Node
{
    key_type key;
    value_type value;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

struct BinaryTree
{
    Node *root;
    cmp_func cmp_fn;
    destroy_key_func destroy_key_fn;
    destroy_value_func destroy_value_fn;
};

// Create a Pair
Pair *_pair_construct(key_type key, value_type value)
{
    Pair *pair = malloc(sizeof(Pair));
    pair->key = key;
    pair->value = value;
    return pair;
}

// Destroy a Pair
void _pair_destroy(Pair *pair, destroy_key_func destroy_key_fn, destroy_value_func destroy_value_fn)
{
    if (pair == NULL)
    {
        return;
    }
    if (destroy_key_fn != NULL)
    {
        destroy_key_fn(pair->key);
    }
    if (destroy_value_fn != NULL)
    {
        destroy_value_fn(pair->value);
    }
    free(pair);
}

// Create a new node
Node *_node_construct(Node *parent, Node *left, Node *right, key_type key, value_type value)
{
    Node *node = malloc(sizeof(Node));
    node->left = left;
    node->right = right;
    node->value = value;
    node->key = key;
    node->parent = parent;
    return node;
}

// Destroy a node
void _node_destroy(Node *node, destroy_key_func destroy_key_fn, destroy_value_func destroy_value_fn)
{
    if (node == NULL)
    {
        return;
    }
    _node_destroy(node->left, destroy_key_fn, destroy_value_fn);
    _node_destroy(node->right, destroy_key_fn, destroy_value_fn);

    if (destroy_key_fn != NULL)
    {
        destroy_key_fn(node->key);
    }
    if (destroy_value_fn != NULL)
    {
        destroy_value_fn(node->value);
    }

    free(node);
}

// Create a new tree
BinaryTree *binary_tree_construct(cmp_func cmp_fn, destroy_key_func destroy_key_fn, destroy_value_func destroy_value_fn)
{
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->cmp_fn = cmp_fn;
    tree->destroy_key_fn = destroy_key_fn;
    tree->destroy_value_fn = destroy_value_fn;
    return tree;
}

Node *_add_recursive(BinaryTree* tree, Node *node, Node *parent, key_type key, value_type value)
{
    if (node == NULL)
    {
        // printf("Construindo um novo nó para a chave %s\n", (char*)key);
        return _node_construct(parent, NULL, NULL, key, value);
    }
    int cmp = tree->cmp_fn(key, node->key);
    if (cmp < 0)
    {
        // printf("Inserindo %s na esquerda de %s\n", (char*)key, (char*)node->key);
        node->left = _add_recursive(tree, node->left, node, key, value);
    }
    else if(cmp > 0)
    {
        // printf("Inserindo %s na direita de %s\n", (char*)key, (char*)node->key);
        node->right = _add_recursive(tree, node->right, node, key, value);
    }else{
        // printf("Atualizando %s\n", (char*)value);
        if(tree->destroy_value_fn != NULL && node->value != NULL){
            tree->destroy_value_fn(node->value);
        }

        if(tree->destroy_key_fn != NULL && node->key != NULL){
            tree->destroy_key_fn(node->key);
        }
        
        node->key = key;
        node->value = value;
    }
    return node;
}

// Add a new node to the tree
void binary_tree_add(BinaryTree *tree, key_type key, value_type value)
{
    tree->root = _add_recursive(tree, tree->root, NULL, key, value);
}

Node *_get_recursive(Node *node, key_type key, cmp_func cmp_fn)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (cmp_fn(key, node->key) == 0)
    {
        return node;
    }
    if (cmp_fn(key, node->key) < 0)
    {
        return _get_recursive(node->left, key, cmp_fn);
    }
    else
    {
        return _get_recursive(node->right, key, cmp_fn);
    }
}

Pair *binary_tree_get(BinaryTree *tree, key_type key)
{
    // recursive
    Node *node = _get_recursive(tree->root, key, tree->cmp_fn);

    if (node == NULL)
    {
        return NULL;
    }

    Pair *p = _pair_construct(node->key, node->value);
    return p;
}

Node *_get_min(Node *node)
{
    if (node->left == NULL)
    {
        return node;
    }
    return _get_min(node->left);
}

Pair *binary_tree_min(BinaryTree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }
    Node *node = _get_min(tree->root);

    if (node == NULL)
    {
        return NULL;
    }

    Pair *p = _pair_construct(node->key, node->value);
    return p;
}

Node *_get_max(Node *node)
{
    if (node->right == NULL)
    {
        return node;
    }
    return _get_max(node->right);
}

Pair *binary_tree_max(BinaryTree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }
    Node *node = _get_max(tree->root);
    if (node == NULL)
    {
        return NULL;
    }
    Pair *p = _pair_construct(node->key, node->value);
    return p;
}

void _transplant(BinaryTree *tree, Node *u, Node *v)
{
    if (u->parent == NULL)
    {
        tree->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    if (v != NULL)
    {
        v->parent = u->parent;
    }
}

Node *_delete_recursive(BinaryTree *tree, Node *node)
{
    // caso 1 : nao tem o filho da esquerda ou nenhum filho
    if (node->left == NULL)
    {
        _transplant(tree, node, node->right);
        // caso 2 : nao tem o filho da direita
    }
    else if (node->right == NULL)
    {
        _transplant(tree, node, node->left);
        // caso 3 : tem os dois filhos
    }
    else
    {
        Node *successor = _get_min(node->right);
        // caso 3.1 : sucessor nao eh filho direito de node entao eu faco a substicuicao para que seja o filho direito
        if (successor->parent != node)
        {
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

Pair *binary_tree_remove(BinaryTree *tree, key_type key)
{
    // procurar por key
    Node *node = _get_recursive(tree->root, key, tree->cmp_fn);
    if (node == NULL)
    {
        return NULL;
    }
    Node *removed = _delete_recursive(tree, node);
    if (removed == NULL)
    {
        return NULL;
    }
    Pair *p = _pair_construct(removed->key, removed->value);
    free(removed);
    return p;
}

Pair *binary_tree_pop_min(BinaryTree *tree)
{
    if(tree->root == NULL)
    {
        return NULL;
    }
    Node *node = _get_min(tree->root);
    if (node == NULL)
    {
        return NULL;
    }
    node = _delete_recursive(tree, node);
    if (node == NULL)
    {
        return NULL;
    }
    Pair *p = _pair_construct(node->key, node->value);
    free(node);
    return p;
}

Pair *binary_tree_pop_max(BinaryTree *tree)
{
    if(tree->root == NULL)
    {
        return NULL;
    }
    Node *node = _get_max(tree->root);
    if (node == NULL)
    {
        return NULL;
    }
    node = _delete_recursive(tree, node);
    if (node == NULL)
    {
        return NULL;
    }
    Pair *p = _pair_construct(node->key, node->value);
    free(node);
    return p;
}

// Destroy a tree
void binary_tree_destroy(BinaryTree *tree)
{
    if (tree == NULL)
    {
        return;
    }
    _node_destroy(tree->root, tree->destroy_key_fn, tree->destroy_value_fn);
    free(tree);
}

void _inorder_traversal_recursive(Node *node, Vector *vector)
{
    if (node == NULL)
    {
        return;
    }
    _inorder_traversal_recursive(node->left, vector);
    vector_push_back(vector, _pair_construct(node->key, node->value));
    _inorder_traversal_recursive(node->right, vector);
}

Vector *inorder_traversal_recursive(BinaryTree *tree)
{
    Vector *vector = vector_create();
    _inorder_traversal_recursive(tree->root, vector);
    return vector;
}
Vector *inorder_traversal_iterative(BinaryTree *tree)
{
    Vector *vector = vector_create();
    Stack *stack = stack_construct();
    Node *node = tree->root;

    while (!stack_empty(stack) || node != NULL)
    {
        if (node != NULL)
        {
            stack_push(stack, node);
            node = node->left;
        }
        else
        {
            node = stack_pop(stack);
            vector_push_back(vector, _pair_construct(node->key, node->value));
            node = node->right;
        }
    }

    stack_destroy(stack);
    return vector;
}

void _preorder_traversal_recursive(Node *node, Vector *vector)
{
    if (node == NULL)
    {
        return;
    }
    vector_push_back(vector, _pair_construct(node->key, node->value));
    _preorder_traversal_recursive(node->left, vector);
    _preorder_traversal_recursive(node->right, vector);
}

Vector *preorder_traversal_recursive(BinaryTree *tree)
{
    Vector *vector = vector_create();
    _preorder_traversal_recursive(tree->root, vector);
    return vector;
}

Vector *preorder_traversal_iterative(BinaryTree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }

    Vector *vector = vector_create();
    Stack *stack = stack_construct();
    stack_push(stack, tree->root);

    while (!stack_empty(stack))
    {
        Node *node = stack_pop(stack);
        vector_push_back(vector, _pair_construct(node->key, node->value));
        if (node->right != NULL)
        {
            stack_push(stack, node->right);
        }
        if (node->left != NULL)
        {
            stack_push(stack, node->left);
        }
    }
    stack_destroy(stack);
    return vector;
}

void _postorder_traversal_recursive(Node *node, Vector *vector)
{
    if (node == NULL)
    {
        return;
    }
    _postorder_traversal_recursive(node->left, vector);
    _postorder_traversal_recursive(node->right, vector);
    vector_push_back(vector, _pair_construct(node->key, node->value));
}

Vector *postorder_traversal_recursive(BinaryTree *tree)
{
    Vector *vector = vector_create();
    _postorder_traversal_recursive(tree->root, vector);
    return vector;
}

Vector *postorder_traversal_iterative(BinaryTree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }
    Vector *vector = vector_create();
    Stack *stack = stack_construct();
    Stack *stack_rev = stack_construct();
    stack_push(stack, tree->root);
    while (!stack_empty(stack))
    {
        Node *node = stack_pop(stack);

        if (node->left != NULL)
        {
            stack_push(stack, node->left);
        }
        if (node->right != NULL)
        {
            stack_push(stack, node->right);
        }

        stack_push(stack_rev, node);
    }

    while (!stack_empty(stack_rev))
    {
        Node *node = stack_pop(stack_rev);
        vector_push_back(vector, _pair_construct(node->key, node->value));
    }

    stack_destroy(stack);
    stack_destroy(stack_rev);
    return vector;
}

Vector *levelorder_traversal(BinaryTree *tree)
{
    if (tree->root == NULL)
    {
        return NULL;
    }
    Vector *vector = vector_create();
    Queue *queue = queue_construct();
    queue_push(queue, tree->root);
    while (!queue_empty(queue))
    {
        Node *node = queue_pop(queue);
        vector_push_back(vector, _pair_construct(node->key, node->value));
        if (node->left != NULL)
        {
            queue_push(queue, node->left);
        }
        if (node->right != NULL)
        {
            queue_push(queue, node->right);
        }
    }
    queue_destroy(queue);
    return vector;
}
