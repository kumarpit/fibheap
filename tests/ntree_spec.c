#include <criterion/criterion.h>

#include "../src/ntree.h"
#include "../src/utils.h"

Test(NaryTree, create) {
    int data = 1;
    ntree_node *root = ntree_create_node(&data);

    cr_assert_eq(1, to_int(root->data));
    cr_assert_eq(0, root->degree);
    cr_assert_eq(NULL, root->parent);
    cr_assert_eq(NULL, root->child);
    cr_assert_eq(NULL, root->sibling);
}

Test(NaryTree, insert_child) {
    int data[3];
    for (int i = 1; i <= 3; i++) {
        data[i - 1] = i;
    }
    ntree_node *root = ntree_create_node(&data[0]);
    ntree_node *child1 = ntree_create_node(&data[1]);
    ntree_node *child2 = ntree_create_node(&data[2]);

    ntree_insert_child(child1, root);
    ntree_insert_child(child2, root);

    cr_assert_eq(2, root->degree);
}

Test(NaryTree, insert_child_complex) {
    int data1[3];
    for (int i = 1; i <= 3; i++) {
        data1[i - 1] = i;
    }
    ntree_node *root1 = ntree_create_node(&data1[0]);
    ntree_node *child1_1 = ntree_create_node(&data1[1]);
    ntree_node *child1_2 = ntree_create_node(&data1[2]);

    ntree_insert_child(child1_1, root1);
    ntree_insert_child(child1_2, root1);

    cr_assert_eq(2, root1->degree);

    int data2[3];
    for (int i = 4; i <= 6; i++) {
        data2[i - 4] = i;
    }
    ntree_node *root2 = ntree_create_node(&data2[0]);
    ntree_node *child2_1 = ntree_create_node(&data2[1]);
    ntree_node *child2_2 = ntree_create_node(&data2[2]);

    ntree_insert_child(child2_1, root2);
    ntree_insert_child(child2_2, root2);

    cr_assert_eq(2, root2->degree);

    ntree_insert_child(root1, root2);

    cr_assert_eq(3, root2->degree);
}

Test(NaryTree, insert_sibling) {
    int data[3];
    for (int i = 1; i <= 3; i++) {
        data[i - 1] = i;
    }
    ntree_node *root = ntree_create_node(&data[0]);
    ntree_node *child1 = ntree_create_node(&data[1]);
    ntree_node *child2 = ntree_create_node(&data[2]);

    ntree_insert_child(child1, root);
    ntree_insert_sibling(child2, child1);

    cr_assert_eq(2, root->degree);
}
