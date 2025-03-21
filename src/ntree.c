#include "ntree.h"

#include <assert.h>
#include <stdlib.h>

// TODO: gracefully handle assertions

/**
 * @brief Constructs a new ntree_node with the given data
 */
ntree_node *ntree_create_node(int data) {
    ntree_node *new_node = malloc(sizeof(ntree_node));
    assert(new_node != NULL);
    new_node->parent = NULL;
    new_node->child = NULL;
    new_node->sibling = NULL;
    new_node->degree = 0;
    new_node->data = data;

    return new_node;
}

/**
 * @brief Adds a sibling to the elder node's list of siblings
 * @invariant The elder node MUST have a parent
 */
void ntree_insert_sibling(ntree_node *node, ntree_node *elder) {
    assert(node != NULL);
    assert(elder != NULL);
    assert(elder->parent != NULL);

    if (elder->sibling == NULL) {
        elder->sibling = node;
    } else {
        // TODO: store tail pointer to make insertion O(1)
        ntree_node *current_sibling = elder->sibling;
        while (current_sibling->sibling) {
            current_sibling = current_sibling->sibling;
        }
        current_sibling->sibling = node;
    }
    elder->parent->degree++;
}

/**
 * @brief Adds a child to the given parent node. If the child has no children,
 * then its child pointer is updated with the new node. Otherwise, a
 * sibling is added to the current child node.
 */
void ntree_insert_child(ntree_node *node, ntree_node *parent) {
    assert(node != NULL);
    assert(parent != NULL);

    node->parent = parent;
    if (parent->child == NULL) {
        parent->child = node;
        parent->degree = 1;
    } else {
        ntree_insert_sibling(parent->child, node);
    }
}
