/* Jean-Pierre Ciotta, hw12.c, CS 24000, Spring 2022
 * Last updated Jan 24, 2022
 */

/* Add any includes here */

#include "hw12.h"

#include <assert.h>
#include <malloc.h>
#include <string.h>

/* Define your functions here */

/*
 * This function is given a double void pointer to set to the new cpu_t struct.
 * It first creates the cpu_t struct by using the given parameters to it. It
 * is very similar to previous assignment of mallocing data.
 */

void create_cpu_data(void **node_ptr, const char *model,
                     const char *manufacturer, int speed, int cores) {
  assert(node_ptr);
  assert(*node_ptr == NULL);
  assert(model);
  assert(manufacturer);
  assert(speed);
  assert(cores);

  cpu_t *new_cpu = NULL;

  new_cpu = malloc(sizeof(cpu_t));
  assert(new_cpu);

  new_cpu->model = malloc(strlen(model) + 1);
  assert(new_cpu->model);
  strcpy(new_cpu->model, model);

  new_cpu->manufacturer = malloc(strlen(manufacturer) + 1);
  assert(new_cpu->manufacturer);
  strcpy(new_cpu->manufacturer, manufacturer);

  new_cpu->speed = speed;
  new_cpu->cores = cores;

  *node_ptr = new_cpu;

} /* create_cpu_data() */

/*
 * This function is only given one parametetr "point". Point is a double
 * void pointer that points to a struct of already allocated memory. The
 * goal of delte_cpu is to dealocate that memory.
 */

void delete_cpu_data(void **point) {
  assert(point);
  assert(*point);

  void *new = *point;
  cpu_t *del = NULL;
  del = (struct cpu_s *)new;

  free(del->model);
  del->model = NULL;

  free(del->manufacturer);
  del->manufacturer = NULL;

  free(del);
  del = NULL;

} /* delete_cpu_data() */

/*
 * This function compares the two pointers whic are voids.
 * in order to use themw e have to cast it to a cpu_t struct
 * once we have casted both of the parameters we just mulitply
 * the struct componet of the speed and cores and compare them.
 */

int compare_cpu_data(void *varg1, void *varg2) {
  assert(varg1);
  assert(varg2);

  cpu_t *arg1 = (struct cpu_s *)varg1;
  cpu_t *arg2 = (struct cpu_s *)varg2;

  int val1 = arg1->speed * arg1->cores;
  int val2 = arg2->speed * arg2->cores;

  if (val1 == val2) {
    return 0;
  }

  if (val1 > val2) {
    return 1;
  }
  return -1;
} /* compare_cpu_data() */

/*
 * This funciton is almost exact as the first one excapt we are dealing with a
 * different struct.  We have to malloc all of the pointer of chars to the new
 * memoery data struct. Once we allocated everything we set the void_ptr to
 * the new struct.
 */

void create_memory_data(void **void_ptr, const char *model,
                        const char *manufacturer, int size, int speed,
                        int ddr_gen) {
  assert(void_ptr);
  assert(*void_ptr == NULL);
  assert(model);
  assert(manufacturer);
  assert(size);
  assert(speed);
  assert(ddr_gen);

  memory_t *mem = NULL;

  mem = malloc(sizeof(memory_t));
  assert(mem);

  mem->model = malloc(strlen(model) + 1);
  assert(mem->model);
  strcpy(mem->model, model);

  mem->manufacturer = malloc(strlen(manufacturer) + 1);
  assert(mem->manufacturer);
  strcpy(mem->manufacturer, manufacturer);

  mem->size = size;
  mem->speed = speed;
  mem->ddr_gen = ddr_gen;

  *void_ptr = mem;
} /* create_memory_data() */

/*
 * This funciton is very similar to the secound function. Instead we
 * handle the memory struct memroy_t. We just free all of its componets
 * and set it to NULL.
 */

void delete_memory_data(void **void_ptr) {
  assert(void_ptr);
  assert(*void_ptr);

  void *new_ptr = *void_ptr;
  memory_t *del = (struct memory_s *)new_ptr;

  free(del->model);
  del->model = NULL;

  free(del->manufacturer);
  del->manufacturer = NULL;

  free(del);
  del = NULL;
} /* delete_memory_data() */

/*
 * This function is very similar to the third function. Instead we compare
 * the model and manufacture of the memroy_t type. This compares the ASCI
 * values of the strings themselves. And they are equal then they comapre
 * the ASCI values of the manufacturer.
 */

int compare_memory_data(void *varg1, void *varg2) {
  assert(varg1);
  assert(varg2);

  memory_t *arg1 = (struct memory_s *)varg1;
  memory_t *arg2 = (struct memory_s *)varg2;

  int val1 = strcmp(arg1->model, arg2->model);
  int val2 = strcmp(arg1->manufacturer, arg2->manufacturer);

  if (val1 == 0) {
    if (val2 > 0) {
      return 1;
    }
    return -1;
  }
  if (val1 > 0) {
    return 1;
  }
  return -1;
} /* compare_memory_data() */

/*
 * This function creates a node based on the given parameters and once created
 * is set the the double void pointer.  The struct node contains a lot of
 * function pointers that point to the previous function already initialized.
 */

void create_node(struct node **void_ptr, void *data, void (*print)(void *),
                 void (*delete)(void **), int (*compare)(void *, void *)) {
  assert(void_ptr);
  assert(*void_ptr == NULL);
  assert(data);
  assert(print);
  assert(delete);
  assert(compare);

  struct node *new = *void_ptr;

  new = malloc(sizeof(struct node));
  assert(new);

  new->left = NULL;
  new->right = NULL;

  new->data = data;

  new->print = print;
  new->delete = delete;
  new->compare = compare;

  *void_ptr = new;
} /* create_node() */

/*
 * This function calles the funciton pointer of node called
 * delete which just frees all of the componets of hte struct
 * and then later we just free the node itself.
 */

void delete_node(struct node **node) {
  assert(node);
  assert(*node);
  assert((*node)->left == NULL);
  assert((*node)->right == NULL);

  struct node *del = *node;

  del->delete(&(del->data));

  free(*node);
  *node = NULL;
} /* delete_node() */

/*
 * This funciton works recursivly. Its goals is to find a spot for
 * the new node to be plaecd based on the compare function. Since the data
 * component of the struct node could either be from memory or cpu we have a
 * pointer to the compare function and recursivly go through the whole tree
 * and place the new node in the right place.
 */

void insert_node(struct node **root, struct node *new) {
  assert(root);
  assert(new);

  if (*root == NULL) {
    *root = new;
  }
  else if ((*root)->compare(((*root)->data), new->data) >= 0) {
    insert_node(&((*root)->left), new);
  }
  else if ((*root)->compare(((*root)->data), new->data) < 0) {
    insert_node(&((*root)->right), new);
  }
} /* insert_node() */

/*
 * This funciton goal is to set a new double pointer pointing to a array list of
 * nodes that are all the same as the given parameter "data" additionally it
 * changes the pointer value based on how many nodes it finds.
 */
void search_copies(struct node *root, void *data, int *dup) {


  if (root == NULL) {
    
  }
  else if (root->compare((root->data), data) == 0) {
    *dup = *dup + 1;
    search_copies(root->left, data, dup);
  }
  else if (root->compare(root->data, data) > 0) {
    search_copies(root->left, data, dup);
  }
  else if (root->compare(root->data, data) < 0) {
    search_copies(root->right, data, dup);
  }


}
void fill_array(struct node *root, struct node **array_of_dups, void *data, int *pos) {
  printf("RECURSION**\n");
  if (root == NULL) {
    
  }
  else if (root->compare((root->data), data) == 0) {
    //*(arrayof_dups + *pos) = root;
    array_of_dups[*pos] = root;
    fill_array(root->left, array_of_dups, data, pos);
    *pos = *pos + 1;
    //(*pos)++;
    printf("ARRAY UPDATED***********\n");
  }
  else if (root->compare(root->data, data) > 0) {
    fill_array(root->left, array_of_dups, data, pos);
  }
  else if (root->compare(root->data, data) < 0) {
    fill_array(root->right, array_of_dups, data, pos);
  }

}

struct node **find_nodes(struct node *root, void *data, int *dup) {
  assert(root);
  assert(data);
  assert(dup);
  *dup = 0;
  search_copies(root, data, dup);
  if (*dup == 0) {
    printf("NULLL\n");
    return NULL;
  }
  printf("NUMBER OF DUPLICATES: %d\n", *dup);
  struct node **array_of_dups = NULL;
  //printf("TEST:1\n");
  array_of_dups = malloc(sizeof(struct node *) * (*dup));
  //printf("Test:2\n");
  int x = 0;
  int *pos = &x;
  //*pos = 0;
  //printf("Test:3\n");

  fill_array(root, array_of_dups, data, pos);
  //printf("Test:4\n");

  return array_of_dups;
  //return NULL;
} /* find_nodes() */

/*
 * This funciton goal is to remove all of the nodes of the given root tree
 * It reuses the funciton pointers delete in order to go through all of the
 * values. There are two parameters for this.
 */

void remove_node(struct node **root, struct node *rem) {
  assert(root);
  assert(rem);

} /* remove_node() */

/*
 * This function is givena double pointer root. It recursivly go through all
 * of the nodes and frees them by reusing hte fucniton delete_node. Once it
 * reaches the base case it is finished.
 */

void delete_tree(struct node **root) {
  assert(root);

  if (*root == NULL) {
    root = NULL;
    return;
  }

  if ((*root) != NULL) {
    delete_tree(&((*root)->right));
    delete_tree(&((*root)->left));
    delete_node(root);
  }

} /* delete_tree() */

/* Remember, you don't need a main function!
 * it is provided by hw12_main.c or hw12_test.o
 */
