//
// Created by kalu on 11/27/19.
//

#include "avl_tree.h"

avlnode *avl_addifnotin(avlnode *tree_root, char str[], uint pos, uint len) {
    avlnode *added;
    if (tree_root->str == NULL) {
        tree_root->str = malloc(len + 1);
        tree_root->left_child = (avlnode *) malloc(sizeof(avlnode));
        tree_root->right_child = (avlnode *) malloc(sizeof(avlnode));

        tree_root->height=0;
        strcpy(tree_root->str, str);
        tree_root->len = len;
        tree_root->pos = pos;

    } else if (strcmp(str, tree_root->str) > 0) {
        //add on right subtree
        tree_root->right_child = avl_addifnotin(tree_root->right_child, str, pos, len);
        tree_root->height = max(tree_root->left_child->height, tree_root->right_child->height);

    } else if (strcmp(str, tree_root->str) < 0) {
        //add on left subtree
        tree_root->left_child = avl_addifnotin(tree_root->left_child, str, pos, len);
    }else if(strcmp(tree_root->str, str)==0)
        return tree_root;

    tree_root = balancenode(tree_root);
    updateheight(tree_root);
    return tree_root;
}

avlnode *create_avl() {
    return (avlnode *) malloc(sizeof(avlnode));
}


avlnode *balancenode(avlnode *subroot) {
    avlnode *new_subroot;
    if (node_weight(subroot) <= -2) {
        // Left Heavy
        if (node_weight(subroot->left_child) > 0)
            new_subroot = avl_rotate_lr(subroot);
        else
            new_subroot = avl_rotate_ll(subroot);

    } else if (node_weight(subroot)  >= 2) {
        // Right Heavy
        if (node_weight(subroot->right_child) > 0)
            new_subroot = avl_rotate_rr(subroot);
        else
            new_subroot = avl_rotate_rl(subroot);
    } else {
        // This subroot is balanced, no change.
        new_subroot = subroot;
    }

    return new_subroot;
}

int node_weight(avlnode *node){
    return node->right_child->height-node->left_child->height;
}

void updateheight(avlnode *node){
    node -> height = max(node->right_child->height,node->left_child->height)+1;
}


// ---- Rotations ----

avlnode *avl_rotate_lr(avlnode *node) {

    avlnode *c = node;
    avlnode *a = c->left_child;
    avlnode *b = a->right_child;

    //step 1, move b between c and a
    a->right_child = b->left_child;
    c->left_child = b;
    b->left_child = a;

    //step 2, let b be the root
    c->left_child = b->right_child;
    b->right_child = c;

    updateheight(a);
    updateheight(c);
    updateheight(b);

    return (b);
}

avlnode *avl_rotate_ll(avlnode *node) {
    avlnode *c = node;
    avlnode *b = c->left_child;

    c->left_child = b->right_child;
    b->right_child = c;

    updateheight(c);
    updateheight(b);

    return (b);
}

avlnode *avl_rotate_rr(avlnode *node) {
    avlnode *a = node;
    avlnode *b = a->right_child;

    a->right_child = b->left_child;
    b->left_child = a;

    updateheight(a);
    updateheight(b);

    return (b);
}

avlnode *avl_rotate_rl(avlnode *node) {
    avlnode *a = node;
    avlnode *c = a->right_child;
    avlnode *b = c->left_child;

    c->left_child = b->right_child;
    b->right_child = c;
    a->right_child = b;

    a->right_child = b->left_child;
    b->left_child = a;

    updateheight(a);
    updateheight(c);
    updateheight(b);

    return (b);
}