/* Name, hw11.c, CS 240, Spring 2022
 * Last updated Feb 7, 2022
 */

/* Add any includes here */

#include "hw11.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

/* Define your functions here */

tree_node_t *create_node(int);
void insert_node(tree_node_t **, tree_node_t *);
tree_node_t *search_node(tree_node_t *, int);
void delete_tree(tree_node_t **);
int prefix(int *, int, tree_node_t *);
int postfix(int *, int, tree_node_t *);
int indorder(int *, int, tree_node_t *);
int reverse(int *, int, tree_node_t *);
int decode_number(tree_node_t *, int);

/*
 * This function create a new tree node witht he type tree_node_t.
 * The components of the structure are just the hash_id and setting
 * the left node and the right node to NULL. In order to set memory for
 * the node we malloc.
 */

tree_node_t *create_node(int hash_id) {
  assert(hash_id > 0);

  tree_node_t *new_node = NULL;
  new_node = malloc(sizeof(tree_node_t));
  assert(new_node);

  new_node->hash_id = hash_id;

  new_node->left_child_ptr = NULL;
  new_node->right_child_ptr = NULL;

  return new_node;
} /* create_node() */

/*
 * This function recursivly traverses all of the ndoes until it finds the
 * best place for the new_node (secound parameter) to be placed. It does this
 * by check the hash_id of the current node and if the current node is less
 * than the new node then it recursivly calls the root of the one on the right
 * and vice versa.
 */

void insert_node(tree_node_t **root, tree_node_t *new_node) {
  assert(root);
  assert(new_node);
  assert(new_node->left_child_ptr == NULL);
  assert(new_node->right_child_ptr == NULL);

  if ((*root) == NULL) {
    (*root) = new_node;
    return;
  }

  if (new_node->hash_id <= (*root)->hash_id) {
    return insert_node(&((*root)->left_child_ptr), new_node);
  }

  return insert_node(&((*root)->right_child_ptr), new_node);
} /* insert_node() */

/*
 * This function recersivly searches for a node and the base case is
 * if it reaches the end of the tree (tree === NULL) then it just returns
 * NULL. Another base case is if the current node's hash_id is equal to the
 * search hash_id. If they are equal the funciton return the node. In order
 * to search for each node it does it recersivly either going to the left or
 * right depending how large the hash_id is compared to the list.
 */

tree_node_t *search_node(tree_node_t *tree, int hash_id) {
  assert(hash_id > 0);
  if (tree == NULL) {
    return NULL;
  }

  if (tree->hash_id == hash_id) {
    return tree;
  }

  if (tree->hash_id > hash_id) {
    return search_node(tree->left_child_ptr, hash_id);
  }

  return search_node(tree->right_child_ptr, hash_id);
} /* search_node() */

/*
 * This funciton goal is to free all of the tree nodes and it does this
 * recersivly by calling botht he left and right child ptr and then freeing
 * it at the end.
 */

void delete_tree(tree_node_t **root) {
  assert(root);

  if ((*root) == NULL) {
    return;
  }

  if ((*root) != NULL) {
    delete_tree(&((*root)->right_child_ptr));
    delete_tree(&((*root)->left_child_ptr));

    free(*root);
    root = NULL;
  }
} /* delete_tree() */

/*
 * This is the first helper function for the decode funciton. This function
 * decodes a tree using the prefix method. The prefix method is
 * current-left-right. It does this by having a pointer to a int to determine
 * whether to add or subtract the hash_id of the node.
 */

int prefix(int *prev, int cnt, tree_node_t *root) {
  if (root == NULL) {
    return 0;
  }
  cnt = *prev * root->hash_id;
  *prev *= -1;

  cnt += prefix(prev, cnt, root->left_child_ptr);

  cnt += prefix(prev, cnt, root->right_child_ptr);

  return cnt;
} /* prefix() */

/*
 * This is the secound helper function for the decode funciton. This funciton
 * decoeds a tree using the postfix method. The postfix method is
 * left-right-current. It does this by having a pointer to a int to determine
 * whether to add or subtract the hash_id of the node. It transverses this order
 * recursivly as well.
 */

int postfix(int *prev, int cnt, tree_node_t *root) {
  if (root == NULL) {
    return 0;
  }
  cnt = postfix(prev, cnt, root->left_child_ptr);
  cnt += postfix(prev, cnt, root->right_child_ptr);

  cnt += *prev * root->hash_id;
  *prev *= -1;

  return cnt;
} /* postfix() */

/*
 * This is the third helper function for the decode funciton. This funciton
 * decoeds a tree using the inorder method. The postfix method is
 * left-current-right. It does this by having a pointer to a int to determine
 * whether to add or subtract the hash_id of the node. It transverses this order
 * recursivly as well.
 */

int inorder(int *prev, int cnt, tree_node_t *root) {
  if (root == NULL) {
    return 0;
  }

  cnt = inorder(prev, cnt, root->left_child_ptr);

  cnt += *prev * root->hash_id;
  *prev *= -1;

  cnt += inorder(prev, cnt, root->right_child_ptr);

  return cnt;
} /* inorder() */

/*
 * This is the forth helper function for the decode funciton. This funciton
 * decoeds a tree using the reverse method. The postfix method is
 * right-current-left. It does this by having a pointer to a int to determine
 * whether to add or subtract the hash_id of the node. It transverses this order
 * recursivly as well.
 */

int reverse(int *prev, int cnt, tree_node_t *root) {
  if (root == NULL) {
    return 0;
  }

  cnt = reverse(prev, cnt, root->right_child_ptr);

  cnt += *prev * root->hash_id;
  *prev *= -1;

  cnt += reverse(prev, cnt, root->left_child_ptr);

  return cnt;
} /* reverse() */

/*
 * This funciton incorperates the 4 helper funcitons that are listed above.
 * It just individually calls the function depending on the "order" which is
 * the secound parameter. Depending on the order it multiplies the final
 * counter by either 1,2,3, or 4.
 */

int decode_number(tree_node_t *root, int order) {
  assert((order >= 1) && (order <= 4));

  int cnt = 0;
  int prev = 1;
  if (order == PREFIX) {
    cnt = prefix(&prev, cnt, root);
  }

  if (order == POSTFIX) {
    cnt = postfix(&prev, cnt, root);
    cnt *= 2;
  }

  if (order == INORDER) {
    cnt = inorder(&prev, cnt, root);
    cnt *= 3;
  }

  if (order == REVERSE) {
    cnt = reverse(&prev, cnt, root);
    cnt *= 4;
  }

  return cnt;
} /* decode_number() */
