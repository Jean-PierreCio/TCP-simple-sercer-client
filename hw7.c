/* Jean-Pierre Ciotta, hw7.c, CS 240, Spring 2022
 * Last updated Mar 1, 2022
 */

/* Add any includes here */

#include "hw7.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Setting up global Variables */

int g_application_count = 0;
application_t g_application_array[MAX_APPLICATIONS] = {};

/* Define your functions here */

int read_applications(char *);
void link_applications();
int find_application_with_category(int, char *);
int count_category_links(int);
int find_applications_by_rating(float rating, int * applications_array);

/*
 * This function read applications from the given first parameter file.
 * It looks through the file and gets 4 elements from it spliting it up
 * by three strings and a float and it puts all of those values in a
 * struct that is later added to the arrary of structs.
 */

int read_applications(char *file) {
  assert(file);
  FILE *file_ptr = fopen(file, "r");
  if (file_ptr == NULL) {
    return NON_READABLE_FILE;
  }

  while (g_application_count < MAX_FILE_LEN) {
    application_t val = {};
    val.next_developer_ptr = NULL;
    val.next_category_ptr = NULL;
    int elements =
        fscanf(file_ptr, "%49[^|]|%49[^|]|%49[^|]|%f\n", val.app_name,
               val.app_developer, val.app_category, &val.app_rating);
    if ((elements == EOF) && (g_application_count == 0)) {
      fclose(file_ptr);
      file_ptr = NULL;
      return NO_APPLICATIONS;
    }
    if (elements == EOF) {
      fclose(file_ptr);
      file_ptr = NULL;
      return g_application_count;
    }

    if (elements != 4) {
      fclose(file_ptr);
      file_ptr = NULL;
      return BAD_RECORD;
    }
    g_application_array[g_application_count] = val;
    g_application_count++;
    if (g_application_count >= MAX_FILE_LEN) {
      fclose(file_ptr);
      file_ptr = NULL;
      return OUT_OF_BOUNDS;
    }
  }

  fclose(file_ptr);
  file_ptr = NULL;
  return g_application_count;
} /* read_applications() */

/*
 * This function links goes through all the structures in the global array
 * g_applicatoin_array[]. It starts at the first element and checks if any
 * other applications in the array have the same developer name and if they do
 * then they are linked together by the first struct pointing to the other. It
 * repeats this agian if the applicaiton are in the same category.
 */

void link_applications() {
  for (int i = 0; i < g_application_count; i++) {
    for (int j = i + 1; j < g_application_count; j++) {
      if (strcmp(g_application_array[j].app_developer,
                 g_application_array[i].app_developer) == 0) {
        g_application_array[i].next_developer_ptr = &g_application_array[j];
        break;
      }
    }
  }
  for (int i = 0; i < g_application_count; i++) {
    for (int j = i + 1; j < g_application_count; j++) {
      if (strcmp(g_application_array[j].app_category,
                 g_application_array[i].app_category) == 0) {
        g_application_array[i].next_category_ptr = &g_application_array[j];
        break;
      }
    }
  }
} /* link_applications() */

/*
 * This funciton parses through a linked list and checks if the given
 * category that is in the parameter is the same as teh linked list is being
 * parsed through. Once it find an applicaiton of the developer linked list
 * witht he same given_category then it returns APPLICATION_FOUND and if
 * it never finds one then it returns APPLICATION_NOT_FOUND.
 */

int find_application_with_category(int num, char *given_category) {
  assert((num >= 0) && (num < g_application_count));
  assert(given_category);

  application_t *app = g_application_array[num].next_developer_ptr;
  while (app != NULL) {
    if (strcmp(app->app_category, given_category) == 0) {
      return APPLICATION_FOUND;
    }
    app = app->next_developer_ptr;
  }
  return APPLICATION_NOT_FOUND;
} /* find_application_with_category() */

/*
 * This function counts how many category links there are in the next
 * category_ptr linked list. It incremetns the int variable cnt for
 * every link and then returns cnt;
 */

int count_category_links(int num) {
  assert((num >= 0) && (num < g_application_count));
  application_t *app = g_application_array[num].next_category_ptr;
  int cnt = 0;
  while (app != NULL) {
    app = app->next_category_ptr;
    cnt++;
  }
  return cnt;

} /* count_category_links() */

/*
 * This function goes through the g_application_array[] array and checks
 * if the given rating is less then the g_application_array[] element rating.
 * if the applicaiton_array[] elements is greater then the given rating then it
 * will increment the cnt variable and put the locaiton where the applicaiton
 * has a higher riating in the given applications_arry in the parameter.
 */

int find_applications_by_rating(float rating, int *applications_array) {
  assert(rating >= 0);
  assert(applications_array != NULL);

  int cnt = 0;
  for (int i = 0; i < g_application_count; i++) {
    if (g_application_array[i].app_rating > rating) {
      applications_array[cnt] = i;
      cnt++;
    }
  }
  if (cnt == 0) {
    return 0;
  }
  return cnt;

} /* find_applications_by_rating() */
