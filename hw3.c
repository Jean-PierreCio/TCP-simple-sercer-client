/* Name, hw3.c, CS 240, Spring 2022
 * Last updated Jan 19, 2022
 */

/* Add any includes here */

#include "hw3.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define your functions here */

/* Remember, you don't need a main function!
 * It is provided by hw3_main.c or  hw3_test.o
 */

/*
 * Setting up the global variables
 */
int g_recipe_count = 0;
char g_recipe[MAX_RECIPES][CODE_LEN] = {0};
char g_weather[MAX_RECIPES][MAX_WEATHER_LEN] = {0};
int g_review[MAX_RECIPES][NUM_COLS] = {0};
float g_price[MAX_RECIPES] = {0};

/*
 * This function reads all the data in the file and organizes it correctly in
 * the correct arrays that are instansiated above
 */

int read_tables(char *in_file) {
  g_recipe_count = 0;
  char copy[10] = "";
  char val_1 = 'A';
  char val_2 = 'A';
  char val_3 = '1';
  char val_4 = '2';
  char val_5 = '3';
  char val_6 = '4';
  int elements = 5;

  FILE *file_ptr = fopen(in_file, "r");
  if (file_ptr == NULL) {
    return FILE_READ_ERR;
  }

  while ((elements != 0) && (elements != -1)) {
    elements =
        fscanf(file_ptr, "%6[^;];%15[^;];%d;%d;%d;%f\n",
               g_recipe[g_recipe_count], g_weather[g_recipe_count],
               &g_review[g_recipe_count][0], &g_review[g_recipe_count][1],
               &g_review[g_recipe_count][2], &g_price[g_recipe_count]);

    if ((g_recipe_count == 0) && ((elements == 0) || (elements == -1))) {
      fclose(file_ptr);
      return NO_DATA_POINTS;
    }

    if ((elements != 6) && (elements != 0) && (elements != -1)) {
      fclose(file_ptr);

      return RECORD_ERROR;
    }
    strcpy(copy, g_recipe[g_recipe_count]);
    val_1 = copy[0];
    val_2 = copy[1];
    val_3 = copy[2];
    val_4 = copy[3];
    val_5 = copy[4];
    val_6 = copy[5];

    if (((val_1 > 90) || (val_1 < 65)) || ((val_2 > 90) || (val_2 < 65)) ||
        ((val_3 > 57) || (val_3 < 48)) || ((val_4 > 57) || (val_4 < 48)) ||
        ((val_5 > 57) || (val_5 < 48)) || ((val_6 > 57) || (val_6 < 48))) {
      fclose(file_ptr);
      return RECORD_ERROR;
    }
    if (elements == 6) {
      g_recipe_count++;
    }
    if (g_recipe_count > MAX_RECIPES - 1) {
      fclose(file_ptr);
      return OUT_OF_BOUNDS;
    }
  }
  if (g_recipe_count == 0) {
    fclose(file_ptr);
    return NO_DATA_POINTS;
  }
  fclose(file_ptr);
  return g_recipe_count;
} /* read_tables() */

/*
 * This function finds the cheapest flights by comparing it to the rest
 * of the flights
 */

int find_cheapest_recipe(void) {
  float min_price = g_price[0];
  int index = 0;


  if (g_recipe_count == 0) {
    return NO_DATA_POINTS;
  }

  for (int i = 1; i < g_recipe_count; i++) {

    if (g_price[i] < min_price) {

      min_price = g_price[i];
      index = i;
    }

  }
  for (int j = 0; j < g_recipe_count; j++) {
    if (g_price[j] == min_price) {

      return j;
    }
  }
  return index;
} /* find_cheapest_recipe() */

/*
 * This function find the cheapest flights based on the given weather
 */

int find_cheapest_recipe_by_weather(char *given_weather) {
  float min_price = 0;
  int index = 0;
  int compare = 0;
  int start = 0;
  int data = 0;

  if (g_recipe_count == 0) {
    return NO_DATA_POINTS;
  }

  for (int i = 0; i < g_recipe_count; i++) {
    compare = strncmp(g_weather[i], given_weather, 15);

    if ((start == 0) && (compare == 0)) {
      min_price = g_price[i];
      start++;
      data++;
      index = i;

    }
    if ((start > 0) && (g_price[i] < min_price) && (compare == 0)) {

      min_price = g_price[i];
      index = i;
    }

  }

  if (data == 0) {
    return NO_SUCH_DATA;
  }
  return index;
} /* find_cheapest_recipe_by_weather() */

/*
 * It counts how many recipes are int he given price range
 */

int count_recipes_in_price_range(float lower_bound, float upper_bound) {
  int total = 0;


  if (upper_bound < lower_bound) {
    return BAD_RANGE;
  }
  if (g_recipe_count == 0) {
    return NO_DATA_POINTS;
  }

  for (int i = 0; i < g_recipe_count; i++) {
    if ((g_price[i] > lower_bound) && (g_price[i] < upper_bound)) {
      total++;
    }
  }
  if (total == 0) {
    return NO_SUCH_DATA;
  }
  return total;
} /* count_recipes_in_price_range() */

/*
 * This function totals how many satisfied costomers are there that are over
 * the given percentage
 */

int count_num_satisfied_over_percentage(float given_percentage) {
  float total = 0;
  int num = 0;

  float current_percentage = 0.0;
  if (g_recipe_count == 0) {
    return NO_DATA_POINTS;
  }
  if ((given_percentage < 0) || (given_percentage > 1)) {
    return BAD_PERCENTAGE;
  }
  for (int i = 0; i < g_recipe_count; i++) {
    total = g_review[i][0] + g_review[i][1] + g_review[i][2];

    current_percentage = g_review[i][0] / total;


    if (current_percentage > given_percentage) {
      num++;
    }
  }
  if (num == 0) {
    return NO_SUCH_DATA;
  }

  return num;
} /* count_num_satisfied_over_percentage() */

/*
 * This funciton calculates the recipe rating witht he given recipe code
 */

float calculate_recipe_rating(char *given_code) {
  char val_1 = 'A';
  char val_2 = 'A';
  char val_3 = '1';
  char val_4 = '2';
  char val_5 = '3';
  char val_6 = '4';
  int compare = 0;

  if (g_recipe_count == 0) {
    return NO_DATA_POINTS;
  }
  val_1 = given_code[0];
  val_2 = given_code[1];
  val_3 = given_code[2];
  val_4 = given_code[3];
  val_5 = given_code[4];
  val_6 = given_code[5];

  if (((val_1 > 90) || (val_1 < 65)) || ((val_2 > 90) || (val_2 < 65)) ||
        ((val_3 > 57) || (val_3 < 48)) || ((val_4 > 57) || (val_4 < 48)) ||
        ((val_5 > 57) || (val_5 < 48)) || ((val_6 > 57) || (val_6 < 48))) {
    return BAD_CODE;
  }

  for (int i = 0; i < g_recipe_count; i++) {
    compare = strncmp(given_code, g_recipe[i], 7);
    if (compare == 0) {
      return (((g_review[i][0] + g_review[i][2]) * 1.0) /
              (g_review[i][1] * 1.0) * 10.0);
    }
  }

  return NO_SUCH_DATA;

} /* calculate_recipe_rating() */

/*
 * This funciton calcuates all ratings of the recipes with the given formula
 */

int calculate_all_ratings(char *out_file) {
  float rating = 0.0;
  FILE *file_ptr = fopen(out_file, "w");

  if (file_ptr == NULL) {
    return FILE_WRITE_ERR;
  }
  if (g_recipe_count == 0) {
    fclose(file_ptr);
    return NO_DATA_POINTS;
  }

  for (int i = 0; i < g_recipe_count; i++) {
    rating = (((g_review[i][0] + g_review[i][2]) * 1.0) /
              (g_review[i][1] * 1.0) * 10.0);

    fprintf(file_ptr, "%s:  %.2f\n", g_recipe[i], rating);
  }

  fclose(file_ptr);
  return OK;

} /* calculate_all_ratings() */

/*
 * This function writes all the data that is given to us into a file
 */

int write_tables(char *out_file, int start_row, int end_row) {

  FILE *file_ptr = fopen(out_file, "w");

  if (file_ptr == NULL) {
    return FILE_WRITE_ERR;
  }
  if (g_recipe_count == 0) {
    fclose(file_ptr);
    return NO_DATA_POINTS;
  }
  if ((start_row < 0) || (end_row >= g_recipe_count) || (end_row < start_row)) {
    fclose(file_ptr);
    return BAD_ROW;
  }

  for (int i = start_row; i <= end_row; i++) {
    fprintf(file_ptr, "%s,%s,%d,%d,%d,%.2f\n", g_recipe[i], g_weather[i],
            g_review[i][0], g_review[i][1], g_review[i][2], g_price[i]);
  }

  fclose(file_ptr);
  return OK;
} /* write_tables() */
