#include <criterion/criterion.h>

#include "../src/ntree.h"

Test(NaryTree, create) {
    ntree_node *root = ntree_create_node(1);

    cr_assert_eq(1, root->data);
    cr_assert_eq(0, root->degree);
    cr_assert_eq(NULL, root->parent);
    cr_assert_eq(NULL, root->child);
    cr_assert_eq(NULL, root->sibling);
}

Test(NaryTree, insert_child) {
    ntree_node *root = ntree_create_node(1);
    ntree_node *child1 = ntree_create_node(2);
    ntree_node *child2 = ntree_create_node(3);

    ntree_insert_child(child1, root);
    ntree_insert_child(child2, root);

    cr_assert_eq(2, root->degree);
}

Test(NaryTree, insert_sibling) {
    ntree_node *root = ntree_create_node(1);
    ntree_node *child1 = ntree_create_node(2);
    ntree_node *child2 = ntree_create_node(3);

    ntree_insert_child(child1, root);
    ntree_insert_sibling(child2, child1);

    cr_assert_eq(2, root->degree);
}
