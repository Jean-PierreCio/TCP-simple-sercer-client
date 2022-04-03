/* Jean-Pierre Ciotta, hw10.c, CS 240, Spring 2022
 * Last updated Feb 7, 2022
 */

/* Add any includes here */

#include "hw10.h"

#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define your functions here */

void create_commit(char *, char *, time_struct_t, commit_t **);
void delete_commit(commit_t **);
int add_commit(commit_t **, commit_t *);
int delete_git_log(commit_t **);
int find_commit(commit_t **, char *);
int find_latest_commits(commit_t *, time_struct_t, commit_t **);
int delete_list(commit_t **);

/*
 * This funcition is very similar to the last funciton to create_commit.
 * The paramaters that are given to us is hash_id, author, time struct, and
 * a commit_t double pointer. the first 3 are nesssesary for creatinga new
 * commit and once you create the new commit you need to have the double
 * pointer point to it.
 */

void create_commit(char *hash_id, char *author, time_struct_t time,
                   commit_t **point_commit) {
  assert(hash_id);
  assert(author);
  assert(time.year > 0);
  assert((time.month > 0) && (time.month <= MONTHS_IN_YEAR));
  assert((time.day > 0) && (time.day <= DAYS_IN_MONTH));
  assert((time.hour >= 0) && (time.hour < HOURS_IN_DAY));
  assert((time.minute >= 0) && (time.minute < MINUTES_IN_HOUR));
  assert((time.second >= 0) && (time.second < SECONDS_IN_MINUTE));
  assert(point_commit);
  assert(*point_commit == NULL);

  commit_t *new_commit = NULL;
  new_commit = malloc(sizeof(commit_t));
  assert(new_commit);

  new_commit->next_commit = NULL;
  new_commit->prev_commit = NULL;

  commit_info_t *new_info = NULL;

  new_info = malloc(sizeof(commit_info_t));
  assert(new_info);
  new_info->hash_id = malloc(strlen(hash_id) + 1);
  strcpy(new_info->hash_id, hash_id);

  new_info->author = malloc(strlen(author) + 1);
  assert(new_info->author);
  strcpy(new_info->author, author);

  new_info->commit_time = time;

  new_commit->commit_info = new_info;

  *point_commit = new_commit;
} /* create_commit() */

/*
 * This function is given a double pointer that it's inner pointer
 * points to a commit_t. This function deletes that commit_t by freeing
 * each commonent of the struct and setting it to NULL.
 */

void delete_commit(commit_t **point_commit) {
  assert(point_commit);
  assert(*point_commit);
  assert((*point_commit)->next_commit == NULL);
  assert((*point_commit)->prev_commit == NULL);
  assert((*point_commit)->commit_info);

  commit_t *delete = *point_commit;

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
 * This funciton is given a git_log which is a double pointer with a list of
 * commit_t in a doubly linked list and the secound parameter is a new commit_t
 * the goal of the function is to perfectly fit the new_commit into the git_log
 * so that the order stays perfect. There are many cercomstances for this and
 * the funciton makes sure it fits perfectly.
 */

int add_commit(commit_t **git_log, commit_t *new_commit) {
  assert(git_log);
  assert(*git_log);
  assert(new_commit);

  while (1) {
    if ((*git_log)->prev_commit == NULL) {
      break;
    }
    *git_log = (*git_log)->prev_commit;
  }
  int total_sec = 0;
  while (1) {
    if ((*git_log)->next_commit == NULL) {
      total_sec = (*git_log)->commit_info->commit_time.month * 2628288 +
                  (*git_log)->commit_info->commit_time.day * 86400 +
                  (*git_log)->commit_info->commit_time.hour * 3600 +
                  (*git_log)->commit_info->commit_time.minute * 60 +
                  (*git_log)->commit_info->commit_time.second;
      (*git_log)->commit_info->commit_time.id = total_sec;

      break;
    }
    total_sec = (*git_log)->commit_info->commit_time.month * 2628288 +
                (*git_log)->commit_info->commit_time.day * 86400 +
                (*git_log)->commit_info->commit_time.hour * 3600 +
                (*git_log)->commit_info->commit_time.minute * 60 +
                (*git_log)->commit_info->commit_time.second;
    (*git_log)->commit_info->commit_time.id = total_sec;
    *git_log = (*git_log)->next_commit;
  }
  while (1) {
    if ((*git_log)->prev_commit == NULL) {
      break;
    }
    *git_log = (*git_log)->prev_commit;
  }
  int new_sec = new_commit->commit_info->commit_time.month * 2628288 +
                new_commit->commit_info->commit_time.day * 86400 +
                new_commit->commit_info->commit_time.hour * 3600 +
                new_commit->commit_info->commit_time.minute * 60 +
                new_commit->commit_info->commit_time.second;

  new_commit->commit_info->commit_time.id = new_sec;
  int pos = 1;
  while (1) {
    if ((*git_log) == NULL) {
      break;
    }
    if ((new_sec == (*git_log)->commit_info->commit_time.id) &&
        (new_commit->commit_info->commit_time.year ==
         (*git_log)->commit_info->commit_time.year)) {
      return TIME_ERROR;
    }
    if (((*git_log)->next_commit == NULL) &&
        ((*git_log)->prev_commit == NULL)) {
      if (((*git_log)->commit_info->commit_time.id > new_sec) &&
          ((*git_log)->commit_info->commit_time.year >=
           new_commit->commit_info->commit_time.year)) {
        (*git_log)->prev_commit = new_commit;
        new_commit->prev_commit = NULL;
        new_commit->next_commit = *git_log;
        return pos;
      } 
      else {
        (*git_log)->next_commit = new_commit;
        new_commit->next_commit = NULL;
        new_commit->prev_commit = *git_log;
      }
      pos++;
      return pos;
    }

    if (((*git_log)->commit_info->commit_time.id > new_sec) &&
        ((*git_log)->commit_info->commit_time.year >=
         new_commit->commit_info->commit_time.year) &&
        (pos == 1)) {
      new_commit->prev_commit = NULL;
      new_commit->next_commit = *git_log;
      (*git_log)->prev_commit = new_commit;
      return pos;
    }

    if (((*git_log)->commit_info->commit_time.id < new_sec) &&
        ((*git_log)->next_commit == NULL) &&
        (new_commit->commit_info->commit_time.year >=
         (*git_log)->commit_info->commit_time.year)) {
      (*git_log)->next_commit = new_commit;
      new_commit->next_commit = NULL;
      new_commit->prev_commit = *git_log;
      pos++;
      return pos;
    }

    if (((*git_log)->commit_info->commit_time.id > new_sec) &&
        ((*git_log)->next_commit == NULL) &&
        (new_commit->commit_info->commit_time.year <=
         (*git_log)->commit_info->commit_time.year)) {
      commit_t *prev_list = (*git_log)->prev_commit;

      (*git_log)->prev_commit = NULL;
      prev_list->next_commit = NULL;
      new_commit->next_commit = *git_log;
      new_commit->prev_commit = prev_list;
      (*git_log)->prev_commit = new_commit;
      prev_list->next_commit = new_commit;
      return pos;
    }

    if (((*git_log)->commit_info->commit_time.id < new_sec) &&
        ((*git_log)->commit_info->commit_time.year <=
         new_commit->commit_info->commit_time.year) &&
        ((*git_log)->next_commit->commit_info->commit_time.id > new_sec) &&
        (new_commit->commit_info->commit_time.year <=
         (*git_log)->next_commit->commit_info->commit_time.year)) {
      commit_t *rest_list = (*git_log)->next_commit;

      (*git_log)->next_commit = NULL;
      rest_list->prev_commit = NULL;
      (*git_log)->next_commit = new_commit;
      new_commit->next_commit = rest_list;
      new_commit->prev_commit = *git_log;
      rest_list->prev_commit = new_commit;
      pos++;
      return pos;
    }
    *git_log = (*git_log)->next_commit;
    pos++;
  }
  return pos;
} /* add_commit() */

/*
 * This function dealocates all internal data for each commit and all the
 * commits in the git log. It reuses the function already writen at the top of
 * the program "delete_commit" so there is no repeated lines of code.
 */

int delete_git_log(commit_t **git_log) {
  assert(git_log);

  if (*git_log == NULL) {
    return 0;
  }
  while (1) {
    if ((*git_log)->prev_commit == NULL) {
      break;
    }
    *git_log = (*git_log)->prev_commit;
  }
  if (((*git_log)->prev_commit == NULL) && ((*git_log)->next_commit == NULL)) {
    delete_commit(git_log);
    return 1;
  }

  commit_t *find_commit = (*git_log)->next_commit;
  int del = 0;
  int end = 0;
  while (*git_log != NULL) {
    (*git_log)->next_commit = NULL;
    (*git_log)->prev_commit = NULL;
    delete_commit(git_log);
    del++;
    if (end == 1) {
      return del;
    }
    *git_log = find_commit;
    if (find_commit != NULL) {
      find_commit = find_commit->next_commit;
    } 
    else {
      end++;
    }
  }
  return del;
} /* delete_git_log() */

/*
 * This function is given two paramaters. The first is a double pointer to a
 * doubly linked list. The secound parameter is the hash_id. This funciton
 * uses a while loop to check if the one of the commit_t in the *git_log
 * paramater is the same and returns the position it was found. Other wise
 * returns COMMIT_NOT_FOUND.
 */

int find_commit(commit_t **git_log, char *hash_id) {
  assert(git_log);
  assert(*git_log);
  assert(hash_id);

  while (1) {
    if ((*git_log)->prev_commit == NULL) {
      break;
    }
    *git_log = (*git_log)->prev_commit;
  }

  int pos = 1;
  while (*git_log != NULL) {
    int str_val = strcmp((*git_log)->commit_info->hash_id, hash_id);
    if (str_val == 0) {
      return pos;
    }
    *git_log = (*git_log)->next_commit;
    pos++;
  }
  git_log = NULL;
  return COMMIT_NOT_FOUND;
} /* find_commit() */

/*
 * This function finds commits after the given time_struct and creates
 * a brand new list with the double pointer "new_log". It finds where
 * the rest of the commits are by comparing the IDs. It iterates through
 * all commits using a while loop.
 */

int find_latest_commits(commit_t *git_log, time_struct_t time,
                        commit_t **new_log) {
  assert(git_log);
  assert(new_log);
  assert(*new_log == NULL);
  assert(time.year > 0);
  assert((time.month <= MONTHS_IN_YEAR) && (time.month > 0));
  assert((time.day <= DAYS_IN_MONTH) && (time.day > 0));
  assert((time.hour < HOURS_IN_DAY) && (time.hour >= 0));
  assert((time.minute < MINUTES_IN_HOUR) && (time.minute >= 0));
  assert((time.second < SECONDS_IN_MINUTE) && (time.second >= 0));

  while (1) {
    if (git_log->prev_commit == NULL) {
      break;
    }
    git_log = git_log->prev_commit;
  }
  int new_sec = time.month * 2628288 + time.day * 86400 + time.hour * 3600 +
                time.minute * 60 + time.second;
  int total_sec = 0;
  while (1) {
    if (git_log->next_commit == NULL) {
      total_sec = git_log->commit_info->commit_time.month * 2628288 +
                  git_log->commit_info->commit_time.day * 86400 +
                  git_log->commit_info->commit_time.hour * 3600 +
                  git_log->commit_info->commit_time.minute * 60 +
                  git_log->commit_info->commit_time.second;
      git_log->commit_info->commit_time.id = total_sec;

      break;
    }

    total_sec = git_log->commit_info->commit_time.month * 2628288 +
                git_log->commit_info->commit_time.day * 86400 +
                git_log->commit_info->commit_time.hour * 3600 +
                git_log->commit_info->commit_time.minute * 60 +
                git_log->commit_info->commit_time.second;
    git_log->commit_info->commit_time.id = total_sec;
    git_log = git_log->next_commit;
  }

  while (1) {
    if (git_log->prev_commit == NULL) {
      break;
    }
    git_log = git_log->prev_commit;
  }

  while (git_log != NULL) {
    printf("Current time: %d current year: %d| compare_time: %d "
           "compare_year:%d \n",
           git_log->commit_info->commit_time.id,
           git_log->commit_info->commit_time.year, new_sec, time.year);

    if (git_log->commit_info->commit_time.id > new_sec) {
      printf("IM IN\n");
      commit_t *new_list = git_log;
      git_log = git_log->prev_commit;
      git_log->next_commit = NULL;
      new_list->prev_commit = NULL;
      git_log = new_list;
      int amount = 1;
      commit_t *search = new_list;
      while (1) {
        if (search->next_commit == NULL) {
          printf("amount:%d\n", amount);
          return amount;
        }
        search = search->next_commit;
        amount++;
      }
    }
    git_log = git_log->next_commit;
  }
  *new_log = NULL;
  new_log = NULL;
  return COMMIT_NOT_FOUND;
} /* find_latest_commits() */

/*
 * This funciton only dalocates all the nodes in a git_log.
 * The only way for this to work is to create a new commit_t
 * by pointing it to the dereference double pointer.
 */

int delete_list(commit_t **git_log) {
  assert(git_log);
  assert(*git_log);
  commit_t *temp = *git_log;
  int del = 0;
  while (temp != NULL) {
    commit_t *next_commit = temp->next_commit;
    free(temp);
    temp = NULL;
    del++;
    temp = next_commit;
  }

  return del;
} /* delete_list() */
