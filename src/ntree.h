/**
 * \file
 * \brief Defines the interface to a n-ary tree structure
 */

#ifndef NTREE_H
#define NTREE_H

/**
 * @brief Represents a n-ary tree node. The node supports an arbitrary
 * number of children per node by storing as a linked list of siblings.
 * Thus, the `child` pointer points to the first of the children,
 * while the other children are stored as siblings within the first
 * child. ntree nodes support storing ints.
 */
typedef struct ntree_node {
    int data;
    int degree;  // in other words, the number of children
    struct ntree_node *parent;
    struct ntree_node *child;
    struct ntree_node *sibling;
} ntree_node;

ntree_node *ntree_create_node(int);
void ntree_insert_sibling(ntree_node *node, ntree_node *elder);
void ntree_insert_child(ntree_node *node, ntree_node *parent);

#endif
