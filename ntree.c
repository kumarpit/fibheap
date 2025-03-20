#include <stdlib.h>
#include <assert.h>
#include "ntree.h"


// TODO: gracefully handle assertions 

/**
* @brief Constructs a new ntree_node with the given data
*/
ntree_node *ntree_create_node(int data) {
    ntree_node *new_node = malloc(sizeof(ntree_node));
    assert(new_node != NULL);
    new_node->child = NULL;
    new_node->sibling = NULL;
    new_node->degree = 0;
    new_node->data = data;
} 

/**
* @brief Adds a sibling to the given node's list of siblings
*/
ntree_node *ntree_insert_sibling(ntree_node *node, int data) {
    assert(node != NULL);
    ntree_node *new_sibling = ntree_create_node(data);
    if (node->sibling == NULL) {
        node->sibling = new_sibling;
    } else {
        ntree_node *current_sibling = node->sibling;
        while (current_sibling->sibling) {
            current_sibling = current_sibling->sibling;
        }
        current_sibling->sibling = new_sibling;
    }

    return new_sibling;
}

/**
* @brief Adds a child to the given node. If the child has no children,
* then its child pointer is updated with a new node. Otherwise, a
* sibling is added to the current child node.
*/
ntree_node *ntree_insert_child(ntree_node *node, int data) {
    assert(node != NULL);
    ntree_node *child;
    if (node->child == NULL) {
        ntree_node *new_child = ntree_create_node(data);
        node->child = new_child;
        child = new_child;
    } else {
        child = ntree_insert_sibling(node->child, data);
    }

    node->degree++;
    return child;
}
