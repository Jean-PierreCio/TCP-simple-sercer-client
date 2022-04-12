#ifndef HW11_H
#define HW11_H

/* Constant definitions */

#define PREFIX        (1)
#define POSTFIX       (2)
#define INORDER       (3)
#define REVERSE       (4)
#define MAX_NODE_SIZE (20)

/* Structure Definitions */

typedef struct tree_node {
  int hash_id;

  struct tree_node *left_child_ptr;
  struct tree_node *right_child_ptr;
} tree_node_t;

/* Function prototypes */

tree_node_t *create_node(int);
void insert_node(tree_node_t **, tree_node_t *);
tree_node_t *search_node(tree_node_t *, int);
void delete_tree(tree_node_t **);
int decode_number(tree_node_t *, int);

#endif // HW11_H
