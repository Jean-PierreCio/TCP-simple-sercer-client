/* Homework 2 Main function
 * CS 240 - Spring 2022
 * Last updated Nov 27, 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw2.h"

/*
 * This function is used to check the input
 */

int clean_stdin() {
  while (getchar() != '\n') {
  }
  return (1);
} /* clean_stdin() */

/*
 * This function is used to run the functions implemented in hw2.c.
 * User input is used to determine which function to run what input
 * is passed to it. Upon completion, the function returns zero.
 */

int main(int argc, char **argv) {
  while (1) {
    printf("====================================================\n");
    printf("Test Menu\n");
    printf("1. num_travel_by_month()\n");
    printf("2. num_travel_by_destination()\n");
    printf("3. monthly_report()\n");
    printf("4. min_max_price()\n");
    printf("5. compare_files()\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    int response = 0;
    int read = 0;
    char c = ' ';

    read = scanf("%d%c", &response, &c);
    while (((read != 2) || (c != '\n')) && clean_stdin()) {
      printf("Wrong input!\n");
      printf("Enter your choice: ");
      read = scanf("%d%c", &response, &c);
    }

    int month = 0;
    int year = 0;
    float avg_revene = 0;
    int total = 0;
    int err_code = 0;
    char input_filename[MAX_FILE_LEN] = "";
    char input_filename1[MAX_FILE_LEN] = "";
    char input_filename2[MAX_FILE_LEN] = "";
    char result_filename[MAX_FILE_LEN] = "";
    char to_city[MAX_CITY_LEN] = "";

    switch (response) {
      case 1:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        printf("Enter month as a number (ex. January -> 1): ");
        read = scanf("%d%c", &month, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter month as a number (ex. January -> 1): ");
          read = scanf("%d%c", &month, &c);
        }
        total = num_travel_by_month(input_filename, month, year);
        if (total >= 0) {
          printf("num_travel_by_month(%s, %d, %d) returned %d\n",
              input_filename, month, year, total);
        }
        else {
          printf("Error! (code %d)\n", total);
        }
        break;

      case 2:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter to city: ");
        scanf("%s", to_city);
        total = num_travel_by_destination(input_filename, to_city);
        if (total >= 0) {
          printf("num_travel_by_destination(%s, %s) returned %d\n",
                  input_filename, to_city, total);
        }
        else {
          printf("Error! (code %d)\n", total);
        }
        break;

      case 3:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter output file name: ");
        scanf("%s", result_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        printf("Enter month as a number (ex. January -> 1): ");
        read = scanf("%d%c", &month, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter month as a number (ex. January -> 1): ");
          read = scanf("%d%c", &month, &c);
        }
        avg_revene = monthly_report(input_filename,
                                    result_filename, month, year);
        if (avg_revene >= 0) {
          printf("monthly_report(%s, %s, %d, %d) returned %.2f\n",
              input_filename, result_filename, month, year, avg_revene);
        }
        else {
          printf("Error! (code %d)\n", (int) avg_revene);
        }
        break;
      case 4:
        printf("Enter input file name: ");
        scanf("%s", input_filename);
        printf("Enter output file name: ");
        scanf("%s", result_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        err_code = min_max_price(input_filename, result_filename, year);
        if (err_code >= 0) {
          printf("min_max_price(%s, %s, %d) returned %d\n"
                 , input_filename, result_filename, year, err_code);
        }
        else {
          printf("Error! (code %d)\n", err_code);
        }
        break;
      case 5:
        printf("Enter 1st input file name: ");
        scanf("%s", input_filename1);
        printf("Enter 2nd input file name: ");
        scanf("%s", input_filename2);
        printf("Enter output file name: ");
        scanf("%s", result_filename);
        printf("Enter year: ");
        read = scanf("%d%c", &year, &c);
        while (((read != 2) || (c != '\n')) && (clean_stdin())) {
          printf("Wrong input!\n");
          printf("Enter year: ");
          read = scanf("%d%c", &year, &c);
        }
        err_code = compare_files(input_filename1, input_filename2,
                                      result_filename, year);
        if (err_code >= 0) {
          printf("compare_price(%s, %s ,%s, %d) returned %d\n"
                 , input_filename1, input_filename2, result_filename
                 , year, err_code);
        }
        else {
          printf("Error! (code %d)\n", err_code);
        }
        break;

      case 6:
        printf("Good Bye :^) \n\n");
        return (0);

      default:
        printf("Invalid choice!\n");
        break;
    }
  }
  return (0);
} /* main() */
