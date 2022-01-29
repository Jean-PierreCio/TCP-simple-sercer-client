/* Jean-Pierre Ciotta, hw2.c, CS 240, Spring 2022
 * Last updated Jan 16, 2022
 */

/* Add any includes here */

#include "hw2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Define your functions here */

/* Remember, you don't need a main function!
 * It is provided by hw2_main.c or  hw2_test.o
 */

/*
 * This function calcualtes how many total
 * travelers there were in the given month and year
 */

int num_travel_by_month(char *file_name, int given_month, int given_year) {
  int bad_date = 0;
  int bad_error = 0;
  int elements = 0;
  int total_travelers = 0;
  int travelers = 0;
  int price = 0;
  int month = 0;
  int day = 0;
  int year = 0;
  char f_city[MAX_CITY_LEN] = "";
  char t_city[MAX_CITY_LEN] = "";
  FILE *file_ptr = fopen(file_name, "r");

  if (file_ptr == NULL) {
    return FILE_READ_ERR;
  }
  if ((given_month < 1) || (given_month > 12) || (given_year < 2000) ||
      (given_year > 2022)) {
    bad_date++;
    printf("first bad date\n");
    fclose(file_ptr);
    return BAD_DATE;
  }
  elements = fscanf(file_ptr, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                    &year, f_city, t_city, &travelers, &price);
  if ((elements != 7) && (elements != 0) && (elements != -1)) {
    fclose(file_ptr);

    return BAD_RECORD;
  }
  if ((given_month == month) && (given_year == year)) {
    total_travelers += travelers;
  }
  printf("\nyear: %d month: %d\n", given_year, given_month);
  while ((elements != -1) && (elements != 0)) {
    elements = fscanf(file_ptr, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      bad_error++;
      fclose(file_ptr);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      bad_date++;
      printf("BAD DATE\n");
      fclose(file_ptr);
      return BAD_DATE;
    }

    if ((given_month == month) && (given_year == year) && (elements != -1) &&
        (elements != 0)) {
      total_travelers += travelers;
    }

    // printf("element: %d\n", elements);
    // printf("year: %d month: %d day: %d travelers: %d elements: %d\n", year,
    // month, day, travelers, elements);
  }

  if (bad_error > 0) {
    fclose(file_ptr);
    return BAD_RECORD;
  }

  // if(total_travelers == 0) {
  // return NO_DATA_POINTS;
  //}
  if (bad_date > 0) {
    fclose(file_ptr);
    return BAD_DATE;
  }
  if (total_travelers == 0) {
    fclose(file_ptr);
    return NO_DATA_POINTS;
  }
  fclose(file_ptr);
  return total_travelers;
} /* num_travel_by_month() */

/*
 * This function returns the number of travelers given the destination
 *
 *
 */

int num_travel_by_destination(char *file_name, char *given_to_city) {
  int bad_date = 0;
  int compare = 0;
  int bad_error = 0;
  int elements = 5;
  int total_travelers = 0;
  int travelers = 0;
  int price = 0;
  int month = 1;
  int day = 1;
  int year = 2000;
  char f_city[MAX_CITY_LEN] = "";
  char t_city[MAX_CITY_LEN] = "";

  FILE *file_ptr = fopen(file_name, "r");
  if (file_ptr == NULL) {
    return FILE_READ_ERR;
  }
  while ((elements != 0) && (elements != -1)) {
    elements = fscanf(file_ptr, "%d/%d/%d|%[^|]|%[^|]|%d|%d", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    printf("To city: %s Travelers: %d\n", t_city, travelers);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      bad_error++;
      fclose(file_ptr);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      bad_date++;
      printf("BAD DATE month:%d day:%d year:%d\n", month, day, year);
      fclose(file_ptr);
      return BAD_DATE;
    }
    compare = strcmp(t_city, given_to_city);
    if ((compare == 0) && (elements != 0) && (elements != -1)) {
      total_travelers += travelers;
    }
    // printf("year: %d month: %d day: %d travelers: %d elements: %d
    // to_locaiton: %s\n", year, month, day, travelers, elements, t_city);
  }
  if (total_travelers == 0) {
    fclose(file_ptr);
    return NO_DATA_POINTS;
  }
  fclose(file_ptr);
  printf("Total!%d\n", total_travelers);
  return total_travelers;
} /* num_travel_by_destination() */

/*
 * This function creates a file that shows the total number of passengers
 * with the given month and the total revenue. With that information
 * it reuturns the average price
 */

float monthly_report(char *in_file, char *out_file, int given_month,
                     int given_year) {
  float average_price = 0.0;
  int elements = 5;
  int total_travelers = 0;
  int travelers = 0;
  int total_rev = 0;
  int price = 0;
  int month = 5;
  int day = 5;
  int year = 2000;
  char f_city[MAX_CITY_LEN] = "";
  char t_city[MAX_CITY_LEN] = "";

  FILE *file_ptr1 = fopen(in_file, "r");
  FILE *file_ptr2 = fopen(out_file, "w");
  if (file_ptr1 == NULL) {
    fclose(file_ptr2);
    return FILE_READ_ERR;
  }
  if ((given_month < 1) || (given_month > 12) || (given_year < 2000) ||
      (given_year > 2022)) {
    fclose(file_ptr1);
    fclose(file_ptr2);
    return BAD_DATE;
  }
  while ((elements != 0) && (elements != -1)) {
    elements = fscanf(file_ptr1, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    // printf("year: %d month: %d day: %d travelers: %d price: %d\n", year,
    // month, day, travelers, price);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      fclose(file_ptr1);
      fclose(file_ptr2);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      // printf("BAD DATE month:%d day:%d year:%d\n", month, day, year);
      fclose(file_ptr1);
      fclose(file_ptr2);
      return BAD_DATE;
    }
    if ((month == given_month) && (year == given_year) && (elements != -1) &&
        (elements != 0)) {
      total_travelers += travelers;
      total_rev += price * travelers;
    }
  }
  if (total_travelers == 0) {
    fclose(file_ptr1);
    fclose(file_ptr2);
    return NO_DATA_POINTS;
  }
  average_price = ((float)total_rev / (float)total_travelers) * 1.0;
  if (file_ptr2 == NULL) {
    fclose(file_ptr1);
    return FILE_WRITE_ERR;
  }
  fprintf(file_ptr2,
          "The total revenue for Month %d and Year %d is %d.\nThe total number "
          "of passengers for Month %d and Year %d is %d.",
          given_month, given_year, total_rev, given_month, given_year,
          total_travelers);
  fclose(file_ptr1);
  fclose(file_ptr2);
  printf("Average!%f\n", average_price);
  return average_price;
} /* monthly_report() */

/*
 * This sorts through the file to check the min and max price of flights
 * of the given year. It then writes to a file to show the information
 */

int min_max_price(char *in_file, char *out_file, int given_year) {
  int min_price = 0;
  int max_price = 0;
  int elements = 5;
  int cnt = 0;
  int travelers = 0;
  int price = 0;
  int month = 5;
  int day = 5;
  int year = 2000;
  char f_city[MAX_CITY_LEN] = "";
  char t_city[MAX_CITY_LEN] = "";

  FILE *file_ptr1 = fopen(in_file, "r");
  FILE *file_ptr2 = fopen(out_file, "w");
  if (file_ptr1 == NULL) {
    fclose(file_ptr2);
    return FILE_READ_ERR;
  }
  if ((given_year < 2000) || (given_year > 2022)) {
    fclose(file_ptr1);
    fclose(file_ptr2);
    return BAD_DATE;
  }
  while ((elements != 0) && (elements != -1)) {
    elements = fscanf(file_ptr1, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    printf("year: %d month: %d day: %d travelers: %d price: %d\n", year, month,
           day, travelers, price);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      fclose(file_ptr1);
      fclose(file_ptr2);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      // printf("BAD DATE month:%d day:%d year:%d\n", month, day, year);
      fclose(file_ptr1);
      fclose(file_ptr2);
      return BAD_DATE;
    }
    if ((year == given_year) && (elements != -1) && (elements != 0) &&
        (cnt == 0)) {
      min_price = price;
      max_price = price;
      cnt++;
    }
    else if ((year == given_year) && (elements != -1) && (elements != 0) &&
               (cnt > 0)) {
      if (price > max_price) {
        max_price = price;
      }
      if (price < min_price) {
        min_price = price;
      }
    }
  }
  if ((max_price == 0) && (min_price == 0)) {
    fclose(file_ptr1);
    fclose(file_ptr2);
    return NO_DATA_POINTS;
  }
  if (file_ptr2 == NULL) {
    fclose(file_ptr1);
    return FILE_WRITE_ERR;
  }
  fprintf(file_ptr2,
          "The minimum price of a plane ticket in Year %d is %d.\nThe maximum "
          "price of a plane ticket in Year %d is %d.",
          given_year, min_price, given_year, max_price);
  fclose(file_ptr1);
  fclose(file_ptr2);
  // printf("MIN: %d MAX: %d\n", min_price, max_price);
  return OK;
} /* min_max_price() */

/*
 * This compares two differnt files and sees if the total travelers or
 * total revenue is the same or which one is greater. Once it knows which one
 * is greater it writes to a file to show if they are the same or different.
 */

int compare_files(char *in_file_1, char *in_file_2, char *out_file,
                  int given_year) {
  int total_travelers_1 = 0;
  int total_travelers_2 = 0;
  int total_revenue_1 = 0;
  int total_revenue_2 = 0;
  int elements = 5;
  int travelers = 0;
  int price = 0;
  int month = 5;
  int day = 5;
  int year = 2000;
  char f_city[MAX_CITY_LEN] = "";
  char t_city[MAX_CITY_LEN] = "";

  FILE *file_ptr_1 = fopen(in_file_1, "r");
  FILE *file_ptr_2 = fopen(in_file_2, "r");
  FILE *file_ptr_3 = fopen(out_file, "w");

  if (file_ptr_1 == NULL) {
    if (file_ptr_2 == NULL) {
      fclose(file_ptr_3);
      return FILE_READ_ERR;
    }
    fclose(file_ptr_2);
    fclose(file_ptr_3);
    return FILE_READ_ERR;
  }
  if (file_ptr_2 == NULL) {
    fclose(file_ptr_1);
    fclose(file_ptr_3);
    return FILE_READ_ERR;
  }

  if ((given_year < 2000) || (given_year > 2022)) {
    fclose(file_ptr_1);
    fclose(file_ptr_2);
    fclose(file_ptr_3);
    return BAD_DATE;
  }
  // first file
  while ((elements != 0) && (elements != -1)) {
    elements = fscanf(file_ptr_1, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    // printf("1. year: %d month: %d day: %d travelers: %d price: %d\n", year,
    // month, day, travelers, price);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      fclose(file_ptr_1);
      fclose(file_ptr_2);
      fclose(file_ptr_3);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      printf("BAD DATE month:%d day:%d year:%d\n", month, day, year);
      fclose(file_ptr_1);
      fclose(file_ptr_2);
      fclose(file_ptr_3);
      return BAD_DATE;
    }
    if ((year == given_year) && (elements != -1) && (elements != 0)) {
      total_travelers_1 += travelers;
      total_revenue_1 += travelers * price;
    }
  }
  // secound file
  elements = 5;
  while ((elements != 0) && (elements != -1)) {
    elements = fscanf(file_ptr_2, "%d/%d/%d|%[^|]|%[^|]|%d|%d\n", &month, &day,
                      &year, f_city, t_city, &travelers, &price);
    // printf("2. year: %d month: %d day: %d travelers: %d price: %d\n", year,
    // month, day, travelers, price);
    if ((elements != 7) && (elements != 0) && (elements != -1)) {
      fclose(file_ptr_1);
      fclose(file_ptr_2);
      fclose(file_ptr_3);
      return BAD_RECORD;
    }
    if ((month < 1) || (month > 12) || (year < 2000) || (year > 2022) ||
        (day < 1) || (day > 31)) {
      // printf("BAD DATE month:%d day:%d year:%d\n", month, day, year);
      fclose(file_ptr_1);
      fclose(file_ptr_2);
      fclose(file_ptr_3);
      return BAD_DATE;
    }
    if ((year == given_year) && (elements != -1) && (elements != 0)) {
      total_travelers_2 += travelers;
      total_revenue_2 += travelers * price;
    }
  }
  if ((total_travelers_1 == 0) || (total_travelers_2 == 0)) {
    fclose(file_ptr_1);
    fclose(file_ptr_2);
    fclose(file_ptr_3);
    return NO_DATA_POINTS;
  }
  if (file_ptr_3 == NULL) {
    fclose(file_ptr_1);
    fclose(file_ptr_2);
    return FILE_WRITE_ERR;
  }
  // first statement
  if (total_travelers_1 == total_travelers_2) {
    fprintf(file_ptr_3, "%s and %s have the same tickets sold in Year %d.\n",
            in_file_1, in_file_2, given_year);
  }
  else if (total_travelers_1 > total_travelers_2) {
    fprintf(file_ptr_3, "%s has more tickets sold by %d than %s in Year %d.\n",
            in_file_1, (total_travelers_1 - total_travelers_2), in_file_2,
            given_year);
  }
  else {
    fprintf(file_ptr_3, "%s has more tickets sold by %d than %s in Year %d.\n",
            in_file_2, (total_travelers_2 - total_travelers_1), in_file_1,
            given_year);
  }
  // secound statement
  if (total_revenue_1 == total_revenue_2) {
    fprintf(file_ptr_3, "%s and %s have the same revenue sold in Year %d.\n",
            in_file_1, in_file_2, given_year);
  }  
  else if (total_travelers_1 > total_travelers_2) {
    fprintf(file_ptr_3, "%s has more revenue sold by %d than %s in Year %d.\n",
            in_file_1, (total_revenue_1 - total_revenue_2), in_file_2,
            given_year);
  } 
  else {
    fprintf(file_ptr_3, "%s has more revenue sold by %d than %s in Year %d.\n",
            in_file_2, (total_revenue_2 - total_revenue_1), in_file_1,
            given_year);
  }
  fclose(file_ptr_1);
  fclose(file_ptr_2);
  fclose(file_ptr_3);

  return OK;
} /* compare_files() */
