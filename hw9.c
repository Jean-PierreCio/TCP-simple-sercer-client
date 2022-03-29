/* Jean-Pierre Ciotta, hw9.c, CS 240, Spring 2022
 * Last updated Mar 29, 2022
 */

/* Add any includes here */

#include "hw9.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define your functions here */

commit_t *create_commit(char *, char *, time_struct_t);
void delete_commit(commit_t *);
int add_commit(commit_t *, commit_t *);
commit_t *remove_commit(commit_t *);
void delete_git_log(commit_t *);
int find_commit(commit_t *, char *, time_struct_t);

/*
 * This function is given the parameters "hash_id, author" and also a time
 * struct. It wants us to malloc to create a brand new node. In the beginging
 * we have to do many asserts to make sure the given data is valid for us to
 * create a brand new node. At the end the nodes points its next and prev
 * to NULL and then returns the node.
 */

commit_t *create_commit(char *hash_id, char *author, time_struct_t time) {
  assert(hash_id);
  assert(author);
  assert(time.year > 0);
  assert(time.month <= MONTHS_IN_YEAR);
  assert(time.month > 0);
  assert(time.day <= DAYS_IN_MONTH);
  assert(time.day > 0);
  assert(time.hour < HOURS_IN_DAY);
  assert(time.hour >= 0);
  assert(time.minute < MINUTES_IN_HOUR);
  assert(time.minute >= 0);
  assert(time.second < SECONDS_IN_MINUTE);
  assert(time.second >= 0);

  commit_t *new_commit = NULL;

  new_commit = malloc(sizeof(commit_t));
  assert(new_commit);

  commit_info_t *new_commit_info = NULL;

  new_commit_info = malloc(sizeof(commit_info_t));
  assert(new_commit_info);

  new_commit_info->hash_id = malloc(strlen(hash_id) + 1);
  assert(new_commit_info->hash_id);
  strcpy(new_commit_info->hash_id, hash_id);

  new_commit_info->author = malloc(strlen(author) + 1);
  assert(new_commit_info->author);
  strcpy(new_commit_info->author, author);

  new_commit_info->commit_time = time;

  new_commit->commit_info = new_commit_info;
  new_commit->next_commit = NULL;
  new_commit->prev_commit = NULL;

  return new_commit;
} /* create_commit() */

/*
 * This funciton is given a pointer to a node and wants us to free all of its
 * memory. We first need to assert that the given node is not NULL and then
 * we are able to just free and set the components to NULL.
 */

void delete_commit(commit_t *delete) {
  assert(delete);
  assert(delete->next_commit == NULL);
  assert(delete->prev_commit == NULL);
  assert(delete->commit_info);

  free(delete->commit_info->hash_id);
  delete->commit_info->hash_id = NULL;

  free(delete->commit_info->author);
  delete->commit_info->author = NULL;

  free(delete->commit_info);
  delete->commit_info = NULL;

  free(delete);
  delete = NULL;
} /* delete_commit() */

/*
 * This function is given two parameters. The first one is a list of commit_t's
 * that is a doubly linked list. The secound parameters is a brand new commit_t
 * and our goal is to put the commit inside the list_commmit so that it is in
 * the right order. I did this by first setting the value of the "IDs" to the
 * total amount of secounds. Once I set all of the values I was able to compare
 * and see if the possition of the commit was valid.
 */

int add_commit(commit_t *list_commit, commit_t *new_commit) {
  assert(list_commit);
  assert(new_commit);

  while (1) {
    if (list_commit->prev_commit == NULL) {
      break;
    }
    list_commit = list_commit->prev_commit;
  }

  while (1) {
    if (list_commit->next_commit == NULL) {
      int total_sec = list_commit->commit_info->commit_time.month * 2628288 +
                      list_commit->commit_info->commit_time.day * 86400 +
                      list_commit->commit_info->commit_time.hour * 3600 +
                      list_commit->commit_info->commit_time.minute * 60 +
                      list_commit->commit_info->commit_time.second;
      list_commit->commit_info->commit_time.id = total_sec;

      break;
    }
    int total_sec = list_commit->commit_info->commit_time.month * 2628288 +
                    list_commit->commit_info->commit_time.day * 86400 +
                    list_commit->commit_info->commit_time.hour * 3600 +
                    list_commit->commit_info->commit_time.minute * 60 +
                    list_commit->commit_info->commit_time.second;
    list_commit->commit_info->commit_time.id = total_sec;
    list_commit = list_commit->next_commit;
  }
  while (1) {
    if (list_commit->prev_commit == NULL) {
      break;
    }
    list_commit = list_commit->prev_commit;
  }
  int new_sec = new_commit->commit_info->commit_time.month * 2628288 +
                new_commit->commit_info->commit_time.day * 86400 +
                new_commit->commit_info->commit_time.hour * 3600 +
                new_commit->commit_info->commit_time.minute * 60 +
                new_commit->commit_info->commit_time.second;

  new_commit->commit_info->commit_time.id = new_sec;
  int pos = 1;
  while (1) {
    if (list_commit == NULL) {
      break;
    }
    if ((new_sec == list_commit->commit_info->commit_time.id) &&
        (new_commit->commit_info->commit_time.year ==
         list_commit->commit_info->commit_time.year)) {
      return TIME_ERROR;
    }
    if ((list_commit->next_commit == NULL) &&
        (list_commit->prev_commit == NULL)) {
      if ((list_commit->commit_info->commit_time.id > new_sec) &&
          (list_commit->commit_info->commit_time.year >=
           new_commit->commit_info->commit_time.year)) {
        list_commit->prev_commit = new_commit;
        new_commit->prev_commit = NULL;
        new_commit->next_commit = list_commit;
        return pos;
      } 
      else {
        list_commit->next_commit = new_commit;
        new_commit->next_commit = NULL;
        new_commit->prev_commit = list_commit;
      }
      pos++;
      return pos;
    }

    if ((list_commit->commit_info->commit_time.id > new_sec) &&
        (list_commit->commit_info->commit_time.year >=
         new_commit->commit_info->commit_time.year) &&
        (pos == 1)) {
      new_commit->prev_commit = NULL;
      new_commit->next_commit = list_commit;
      list_commit->prev_commit = new_commit;
      return pos;
    }

    if ((list_commit->commit_info->commit_time.id < new_sec) &&
        (list_commit->next_commit == NULL) &&
        (new_commit->commit_info->commit_time.year >=
         list_commit->commit_info->commit_time.year)) {
      list_commit->next_commit = new_commit;
      new_commit->next_commit = NULL;
      new_commit->prev_commit = list_commit;
      pos++;
      return pos;
    }

    if ((list_commit->commit_info->commit_time.id > new_sec) &&
        (list_commit->next_commit == NULL) &&
        (new_commit->commit_info->commit_time.year <=
         list_commit->commit_info->commit_time.year)) {
      commit_t *prev_list = list_commit->prev_commit;

      list_commit->prev_commit = NULL;
      prev_list->next_commit = NULL;
      new_commit->next_commit = list_commit;
      new_commit->prev_commit = prev_list;
      list_commit->prev_commit = new_commit;
      prev_list->next_commit = new_commit;
      return pos;
    }

    if ((list_commit->commit_info->commit_time.id < new_sec) &&
        (list_commit->commit_info->commit_time.year <=
         new_commit->commit_info->commit_time.year) &&
        (list_commit->next_commit->commit_info->commit_time.id > new_sec) &&
        (new_commit->commit_info->commit_time.year <=
         list_commit->next_commit->commit_info->commit_time.year)) {
      commit_t *rest_list = list_commit->next_commit;

      list_commit->next_commit = NULL;
      rest_list->prev_commit = NULL;
      list_commit->next_commit = new_commit;
      new_commit->next_commit = rest_list;
      new_commit->prev_commit = list_commit;
      rest_list->prev_commit = new_commit;
      pos++;
      return pos;
    }
    list_commit = list_commit->next_commit;
    pos++;
  }
  return pos;
} /* add_commit() */

/*
 * This function just gives us a pointer of list of commits in a double linked
 * list. They want us to just remove the commit that is pointed without it
 * being feed. Once it is removed the funciton returns the head of the updated
 * list of commits.
 */

commit_t *remove_commit(commit_t *remove_commit) {
  if (remove_commit == NULL) {
    return NULL;
  }
  if ((remove_commit->prev_commit == NULL) &&
      (remove_commit->next_commit == NULL)) {
    return NULL;
  }
  if (remove_commit->prev_commit == NULL) {
    commit_t *list_commit = remove_commit->next_commit;
    list_commit->prev_commit = NULL;
    remove_commit->next_commit = NULL;
    return list_commit;
  }

  if (remove_commit->next_commit == NULL) {
    commit_t *list_commit = remove_commit->prev_commit;

    remove_commit->prev_commit = NULL;

    list_commit->next_commit = NULL;
    while (1) {
      if (list_commit->prev_commit == NULL) {
        break;
      }
      list_commit = list_commit->prev_commit;
    }
    return list_commit;
  }

  commit_t *prev_list = remove_commit->prev_commit;
  commit_t *next_list = remove_commit->next_commit;

  remove_commit->next_commit = NULL;
  remove_commit->prev_commit = NULL;

  prev_list->next_commit = next_list;
  next_list->prev_commit = prev_list;

  while (1) {
    if (prev_list->prev_commit == NULL) {
      break;
    }
    prev_list = prev_list->prev_commit;
  }
  return prev_list;
} /* remove_commit() */

/*
 * This function is given a list of commits. Its goal is to get rid of all the
 * commits. In order to make this easier I reused the function I already
 * created called delete_commit().
 */

void delete_git_log(commit_t *list_commit) {
  assert(list_commit);
  while (1) {
    if (list_commit->prev_commit == NULL) {
      break;
    }
    list_commit = list_commit->prev_commit;
  }
  if ((list_commit->prev_commit == NULL) &&
      (list_commit->next_commit == NULL)) {
    delete_commit(list_commit);
    return;
  }

  commit_t *find_commit = list_commit->next_commit;

  int end = 0;
  while (list_commit != NULL) {
    list_commit->next_commit = NULL;
    list_commit->prev_commit = NULL;
    delete_commit(list_commit);
    if (end == 1) {
      break;
    }
    list_commit = find_commit;
    if (find_commit != NULL) {
      find_commit = find_commit->next_commit;
    } 
    else {
      end++;
    }
  }

} /* delete_git_log() */

/*
 * This function is given the parameters list_commit, hash_id, and time.
 * the list_commit is a list of commits in a doubly linked list. It tries
 * to find a commit in the list of commits with the givin hash ID and same
 * time and date. Once it finds the commit it returns the position where it
 * found it.
 */

int find_commit(commit_t *list_commit, char *hash_id, time_struct_t time) {
  assert(list_commit);
  assert(hash_id);
  assert(time.year > 0);
  assert((time.month <= MONTHS_IN_YEAR) && (time.month > 0));
  assert((time.day <= DAYS_IN_MONTH) && (time.day > 0));
  assert((time.hour < HOURS_IN_DAY) && (time.hour >= 0));
  assert((time.minute < MINUTES_IN_HOUR) && (time.minute >= 0));
  assert((time.second < SECONDS_IN_MINUTE) && (time.second >= 0));

  while (1) {
    if (list_commit->prev_commit == NULL) {
      break;
    }
    list_commit = list_commit->prev_commit;
  }

  int new_sec = time.month * 2628288 + time.day * 86400 + time.hour * 3600 +
                time.minute * 60 + time.second;
  while (1) {
    if (list_commit->next_commit == NULL) {
      int total_sec = list_commit->commit_info->commit_time.month * 2628288 +
                      list_commit->commit_info->commit_time.day * 86400 +
                      list_commit->commit_info->commit_time.hour * 3600 +
                      list_commit->commit_info->commit_time.minute * 60 +
                      list_commit->commit_info->commit_time.second;
      list_commit->commit_info->commit_time.id = total_sec;

      break;
    }
    int total_sec = list_commit->commit_info->commit_time.month * 2628288 +
                    list_commit->commit_info->commit_time.day * 86400 +
                    list_commit->commit_info->commit_time.hour * 3600 +
                    list_commit->commit_info->commit_time.minute * 60 +
                    list_commit->commit_info->commit_time.second;
    list_commit->commit_info->commit_time.id = total_sec;
    list_commit = list_commit->next_commit;
  }

  while (1) {
    if (list_commit->prev_commit == NULL) {
      break;
    }
    list_commit = list_commit->prev_commit;
  }

  int pos = 1;
  while (list_commit != NULL) {
    int str_val = strcmp(list_commit->commit_info->hash_id, hash_id);
    if ((str_val == 0) &&
        (new_sec == list_commit->commit_info->commit_time.id) &&
        (list_commit->commit_info->commit_time.year == time.year)) {
      return pos;
    }
    list_commit = list_commit->next_commit;
    pos++;
  }

  return COMMIT_NOT_FOUND;
} /* find_commit() */
