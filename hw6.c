/* Jean-Pierre Ciotta, hw6.c, CS 240, Spring 2022
 * Last updated Jan 19, 2022
 */

/* Add any includes here */

#include "hw6.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Setting up global Variables */

int g_application_count = 0;
application_t g_application_array[MAX_APPLICATIONS] = {0};

/* Define your functions here */

/*
 * This function reads from a file containing applications. It first determines
 * if there are no applications by examining the whole file using fseek and
 * seeing if there is data. If there is data it reads the data using
 * fscanf and puts all the structs read into an array with only
 * 50 elements allowed to be read.
 */

int read_applications(char *file) {
  assert(file);
  FILE *file_ptr = fopen(file, "r");
  if (file_ptr == NULL) {
    return READ_ERROR;
  }

  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  if (size == 0) {
    fclose(file_ptr);
    return NO_APPLICATIONS;
  }

  application_t read = {0};
  fseek(file_ptr, 0, SEEK_SET);
  int elements = 4;
  while (1) {
    elements = fscanf(file_ptr, "%49[^|]|%49[^|]|%49[^|]|%f\n", read.app_name,
                      read.app_developer, read.app_category, &read.app_rating);

    if (elements == EOF) {
      fclose(file_ptr);
      return g_application_count;
    }
    g_application_count++;
    if (g_application_count > MAX_APPLICATIONS) {
      fclose(file_ptr);
      return OUT_OF_BOUNDS;
    }
    if (elements == 4) {
      g_application_array[g_application_count - 1] = read;
    }
    else {
      fclose(file_ptr);
      return BAD_RECORD;
    }
  }

  fclose(file_ptr);
  return g_application_count;
} /* read_applications() */

/*
 * This function checks if the first two strings are a substring of the
 * applications app_name and app_developer name. It then checks if the
 * app_category is exactly the same of the same application being read.
 * and checks if the app_rating is less or equal the applicaiton app_rating.
 * if all of these conditions are true it records that it is a valid
 * applicaitons and at the end of the progrom it returns how many valid
 * applications there are in the array that match with the paremeters.
 */

int find_applications(char *app_name, char *app_developer, char *app_category,
                      float app_rating) {
  assert(app_name);
  assert(app_developer);
  assert(app_category);
  assert(app_rating >= 0);

  if (g_application_count == 0) {
    return NO_APPLICATIONS;
  }
  int cnt = 0;
  for (int i = 0; i < g_application_count; i++) {
    bool name_valid = false;
    bool developer_valid = false;
    bool category_valid = false;
    bool rating_valid = false;

    char *name_sub = "";
    char *developer_sub = "";
    name_sub = strstr(g_application_array[i].app_name, app_name);
    if (name_sub) {
      name_valid = true;
    }
    developer_sub = strstr(g_application_array[i].app_developer, app_developer);
    if (developer_sub) {
      developer_valid = true;
    }
    if (strcmp(g_application_array[i].app_category, app_category) == 0) {
      category_valid = true;
    }
    if (g_application_array[i].app_rating > app_rating) {
      rating_valid = true;
    }
    if (name_valid && developer_valid && category_valid && rating_valid) {
      cnt++;
    }
  }

  return cnt;
} /* find_applications() */
