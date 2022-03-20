/* Jean-Pierre Ciotta, hw8.c, CS 240, Spring 2022
 * Last updated Feb 1, 2022
 */

/* Add any includes here */

#include "hw8.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

/* Define your functions here */

/*
 * This fuction first assertes if the given parameters aren't null.
 * The whole purpos of it is adding a brand new app_t structure to
 * the head of the given linked list.
 */

app_t *add_app_to_head(app_t *head_app, char *author, char *category,
                       char *name) {
  assert(author);
  assert(category);
  assert(name);
  app_t *new_app = NULL;

  new_app = malloc(sizeof(app_t));
  assert(new_app);

  new_app->author = malloc(strlen(author) + 1);
  assert(new_app->author);
  strcpy(new_app->author, author);

  new_app->category = malloc(strlen(category) + 1);
  assert(new_app->category);
  strcpy(new_app->category, category);

  new_app->name = malloc(strlen(name) + 1);
  assert(new_app->name);
  strcpy(new_app->name, name);

  if (head_app == NULL) {
    new_app->next_app = NULL;
    return new_app;
  }

  new_app->next_app = head_app;
  return new_app;
} /* add_app_to_head() */

/*
 * This function is only given a linked list and removes the head app from
 * the list and sets the new app. You have to free each component of the struct
 * and then have to set each component of the struct to NULL.
 */

app_t *remove_app_from_head(app_t *remove) {
  if (remove == NULL) {
    return NULL;
  }

  if (remove->next_app == NULL) {
    free(remove->author);
    free(remove->category);
    free(remove->name);
    free(remove);

    remove->author = NULL;
    remove->category = NULL;
    remove->name = NULL;
    remove = NULL;

    return NULL;
  }
  app_t *new_head = NULL;
  new_head = remove->next_app;

  free(remove->author);
  free(remove->category);
  free(remove->name);
  free(remove);

  remove->author = NULL;
  remove->category = NULL;
  remove->name = NULL;
  remove = NULL;

  return new_head;
} /* remove_app_from_head() */

/*
 * This function first asserts if the given parameters aren't NULL. Then it
 * creates a new app_t structue and add it to the tail of the given linked list
 * by transversing the whole list until it is at the end. We found out were
 * the tail is using a while loop.
 */

app_t *add_app_to_tail(app_t *head_app, char *author, char *category,
                       char *name) {
  assert(author);
  assert(category);
  assert(name);

  app_t *tail_app = NULL;

  tail_app = malloc(sizeof(app_t));
  assert(tail_app);

  tail_app->author = malloc(strlen(author) + 1);
  assert(tail_app->author);
  strcpy(tail_app->author, author);

  tail_app->category = malloc(strlen(category) + 1);
  assert(tail_app->category);
  strcpy(tail_app->category, category);

  tail_app->name = malloc(strlen(name) + 1);
  assert(tail_app->name);
  strcpy(tail_app->name, name);

  if (head_app == NULL) {
    tail_app->next_app = NULL;
    return tail_app;
  }

  app_t *back_app = head_app;
  app_t *front_app = head_app->next_app;
  while (1) {
    if (front_app->next_app == NULL) {
      back_app->next_app->next_app = tail_app;
      tail_app->next_app = NULL;
      break;
    }
    back_app = back_app->next_app;
    front_app = front_app->next_app;
  }
  return head_app;
} /* add_app_to_tail() */

/*
 * This function just gives the linked list as the parameter. It first checks
 * if the linked list is not NULL and if it is NULL it returns NULL. Then it
 * goes to the tail of the app and removes it and sets the new Tail to point
 * to NULL.
 */

app_t *remove_app_from_tail(app_t *head_app) {
  if (head_app == NULL) {
    return NULL;
  }
  if (head_app->next_app == NULL) {
    free(head_app->author);
    free(head_app->category);
    free(head_app->name);
    free(head_app);

    head_app->author = NULL;
    head_app->category = NULL;
    head_app->name = NULL;
    head_app = NULL;

    return NULL;
  }

  app_t *new_tail = head_app;
  app_t *old_tail = head_app->next_app;
  app_t *find_app = head_app->next_app->next_app;

  while (1) {
    if (find_app == NULL) {
      free(old_tail->author);
      free(old_tail->category);
      free(old_tail->name);
      free(old_tail);

      old_tail->author = NULL;
      old_tail->category = NULL;
      old_tail->name = NULL;
      old_tail = NULL;

      new_tail->next_app = NULL;
      break;
    }
    old_tail = old_tail->next_app;
    new_tail = new_tail->next_app;
    find_app = find_app->next_app;
  }

  return head_app;
} /* remove_app_from_tail() */

/*
 * All this funciton does it counts how many apps there are in the given
 * Linked list. It does this by using a while loop and tranversing the
 * linked list.
 */

int count_apps(app_t *head_app) {
  if (head_app == NULL) {
    return 0;
  }

  int cnt = 0;
  while (1) {
    if (head_app == NULL) {
      break;
    }
    head_app = head_app->next_app;
    cnt++;
  }
  return cnt;
} /* count_apps() */

/*
 * This funciton traverses a linked list until it reaches the given index.
 * To go the given index I used a while loop and then I just return the app_t
 * at the given index.
 */

app_t *search_by_index(app_t *head_app, int index) {
  assert(index > 0);

  for (int i = 1; i <= index; i++) {
    if (head_app == NULL) {
      return NULL;
    }
    if (i == index) {
      break;
    }
    head_app = head_app->next_app;
  }
  return head_app;
} /* search_by_index() */

/*
 * This function is given a linked list and the componets of the structor:
 * author, category, and name. It first asserts if the compontes of the
 * structuor are not NULL. Then I wrote a while loop that transversis the
 * whole list until it finds an app_t with the exact same compontes of
 * the parameter. If it can't find a app_t with the same componets it just
 * returns NULL.
 */

app_t *search_by_information(app_t *head_app, char *author, char *category,
                             char *name) {
  assert(author);
  assert(category);
  assert(name);

  while (1) {
    if (head_app == NULL) {
      break;
    }
    int auth_val = strcmp(author, head_app->author);
    int cat_val = strcmp(category, head_app->category);
    int name_val = strcmp(name, head_app->name);

    if ((auth_val == 0) && (cat_val == 0) && (name_val == 0)) {
      return head_app;
    }
    head_app = head_app->next_app;
  }
  return NULL;
} /* search_by_information() */

/*
 * This funciton modifies the app at the given index with the given parameters.
 * It first goes to the app_t at the given index and then frees all the
 * compontes and remallocs it with the given components.
 */

app_t *modify_app_by_index(app_t *head_app, int index, char *author,
                           char *category, char *name) {
  assert(index > 0);
  assert(author);
  assert(category);
  assert(name);

  for (int i = 1; i <= index; i++) {
    if (head_app == NULL) {
      return NULL;
    }
    if (i == index) {
      break;
    }
    head_app = head_app->next_app;
  }
  printf("made it passed the for loop\n");
  free(head_app->author);
  free(head_app->category);
  free(head_app->name);

  head_app->author = malloc(strlen(author) + 1);
  assert(head_app->author);
  strcpy(head_app->author, author);

  head_app->category = malloc(strlen(category) + 1);
  assert(head_app->category);
  strcpy(head_app->category, category);

  head_app->name = malloc(strlen(name) + 1);
  assert(head_app->name);
  strcpy(head_app->name, name);

  return head_app;
} /* modify_app_by_index() */

/*
 * This funciton moves the head of the linked list to the tail until the new
 * head reaches to the Nth positon of the original linked list. It basically
 * shifts all of the nodes to the right of the original list until it hist the
 * Nth node.
 */

app_t *move_to_tail(app_t *head_app, int n) {
  assert(n > 0);
  int total = 0;
  app_t *cnt_app = head_app;
  while (1) {
    if (cnt_app == NULL) {
      break;
    }
    cnt_app = cnt_app->next_app;
    total++;
  }
  assert(n <= total);
  if (total == 1) {
    return head_app;
  }
  for (int i = 1; i <= n; i++) {
    app_t *temp_app = NULL;

    temp_app = malloc(sizeof(app_t));
    assert(temp_app);

    temp_app->author = malloc(strlen(head_app->author) + 1);
    assert(temp_app->author);
    strcpy(temp_app->author, head_app->author);

    temp_app->category = malloc(strlen(head_app->category) + 1);
    assert(temp_app->category);
    strcpy(temp_app->category, head_app->category);

    temp_app->name = malloc(strlen(head_app->name) + 1);
    assert(temp_app->name);
    strcpy(temp_app->name, head_app->name);

    app_t *old_head = head_app;
    head_app = head_app->next_app;

    free(old_head->author);
    free(old_head->category);
    free(old_head->name);
    free(old_head);

    old_head->author = NULL;
    old_head->category = NULL;
    old_head->name = NULL;
    old_head = NULL;

    app_t *tail_app = head_app;
    app_t *search_app = head_app->next_app;
    while (1) {
      if (search_app == NULL) {
        tail_app->next_app = temp_app;
        temp_app->next_app = NULL;
        break;
      }
      tail_app = tail_app->next_app;
      search_app = search_app->next_app;
    }
  }
  return head_app;
} /* move_to_tail() */

/*
 * This function is given two seperate linked lists. It fist checks which
 * linked list is the largest or if they are the same size. Starting with
 * the largest size linked list it interleaves app from the fitst one to the
 * secound one until the secound one runs out of apps and just leaves the rest
 * of the list to be the rest of the first_input. I did this by finding out
 * which linked list was the biggest with a while loop and then using a for
 * until the size of the smaller linked list that interleaves apps and sets
 * the pointer of the next app to the rest of the first apps.
 */

app_t *interleave_apps(app_t *first_input, app_t *secound_input) {

  assert(first_input);
  assert(secound_input);
  app_t *first_holder = first_input;
  app_t *secound_holder = secound_input;
  int first_cnt = 0;
  int secound_cnt = 0;

  app_t *first_app = NULL;
  app_t *secound_app = NULL;
  while (1) {
    if ((first_input == NULL) && (secound_input == NULL)) {
      first_app = first_holder;
      secound_app = secound_holder;
      break;
    }
    if ((first_input == NULL) && (secound_input != NULL)) {
      first_app = secound_holder;
      secound_app = first_holder;
      while (1) {
        secound_input = secound_input->next_app;
        if (secound_input == NULL) {
          break;
        }
        first_cnt++;
      }
      break;
    }
    if ((first_input != NULL) && (secound_input == NULL)) {
      first_app = first_holder;
      secound_app = secound_holder;
      while (1) {
        first_input = first_input->next_app;
        if (first_input == NULL) {
          break;
        }
        first_cnt++;
      }
      break;
    }

    first_input = first_input->next_app;
    secound_input = secound_input->next_app;
    first_cnt++;
    secound_cnt++;
  }
  printf("first: %d secound: %d \n", first_cnt, secound_cnt);

  app_t *head_app = first_app;
  app_t *first_rest = NULL;
  app_t *secound_rest = NULL;
  for (int i = 1; i <= secound_cnt; i++) {
    first_rest = first_app->next_app;
    secound_rest = secound_app->next_app;
    first_app->next_app = NULL;
    secound_app->next_app = NULL;
    first_app->next_app = secound_app;
    secound_app->next_app = first_rest;
    if (i != secound_cnt) {
      first_app = first_app->next_app->next_app;
      secound_app = secound_rest;
    }
  }
  return head_app;
} /* interleave_apps() */

/*
 * This function just frees all of the apps of the linked list given in the
 * parameter. It does this by using the free comand and setting all the
 * componets to NULL.
 */

void free_app_list(app_t *given_app) {

  int cnt = 1;
  app_t *test = given_app;
  while (1) {
    if (test->next_app == NULL) {
      break;
    }
    test = test->next_app;
    cnt++;
  }

  printf("total number of nodes: %d\n", cnt);

  app_t *temp_app = given_app;
  given_app = given_app->next_app;
  int count = 0;
  while (1) {
    if (temp_app == NULL) {
      break;
    }
    printf("freeing memory\n");
    free(temp_app->author);
    free(temp_app->category);
    free(temp_app->name);
    free(temp_app);

    temp_app->author = NULL;
    temp_app->category = NULL;
    temp_app->name = NULL;
    temp_app = NULL;

    if ((count > 0) || (cnt == 1)) {
      break;
    }

    if (given_app == NULL) {
      count++;
    }

    temp_app = given_app;
    given_app = given_app->next_app;
    if (given_app == NULL) {
      count++;
    }
  }
} /* free_app_list() */
