#ifndef HW12_H
#define HW12_H

#define CPU     (1)
#define MEMORY  (2)

/* Generic node structure */

struct node {
  struct node *left;
  struct node *right;
  void *data;
  void (*print)(void *);
  void (*delete)(void **);
  int (*compare)(void *, void *);
};

typedef struct cpu_s {
  char *model;
  char *manufacturer;
  int speed;
  int cores;
} cpu_t;

typedef struct memory_s {
  char *model;
  char *manufacturer;
  int size;
  int speed;
  int ddr_gen;
} memory_t;

/*
 * Functions of the Tree
 */

void print_tree(struct node *);
void delete_tree(struct node **);

/*
 * Functions of the Tree-nodes
 */

void print_node(struct node *);
void create_node(struct node **, void *, void (*)(void*),
                 void (*)(void **), int (*)(void *, void *));
void delete_node(struct node **);
void insert_node(struct node **, struct node *);
void remove_node(struct node **, struct node *);
struct node **find_nodes(struct node *, void *, int *);

/*
 * Functions for accessing/manipulating node-data
 */

/* data access/manipulation functions for cpu structure */

void print_cpu_data(void *);
void create_cpu_data(void **, const char *,
                     const char *, int, int);
void delete_cpu_data(void **);
int  compare_cpu_data(void *, void *);

/* data access/manipulation functions for memory structure */

void print_memory_data(void *);
void create_memory_data(void **, const char *,
                        const char *, int, int, int);
void delete_memory_data(void **);
int  compare_memory_data(void *, void *);

#endif // HW12_H
