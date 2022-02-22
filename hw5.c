/* Jean-Pierre Ciotta, hw5.c, CS 240, Spring 2022
 * Last updated Feb 19, 2022
 */

/* Add any includes here */

#include "hw5.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define your functions here */

teaching_assistant_t read_teaching_assistant(FILE *, int);
int write_teaching_assistant(FILE *, teaching_assistant_t, int);
float compute_percent_by_male(FILE *);
float compute_percent_by_type(FILE *, enum type_t);
float average_rating_by_type(FILE *, enum type_t);
int find_teaching_assistant_by_id(FILE *, int);
int find_teaching_assistant_by_name(FILE *, char *, char *);
int update_teaching_assistant_rating(FILE *, int, float);
int book_office_hours(FILE *, int, int, int);

/*
 * This funciton is for assertion check of first name. Just checks if the
 * string isn't null
 */

bool teaching_assistant_first_name_check(char *first_name_check) {
  return (*first_name_check != '\0');
} /* teaching_assistant_first_name_check() */

/*
 * This funciton is for assertion check of last name. Just cheks if the
 * string ins't null
 */

bool teaching_assistant_last_name_check(char *last_name_check) {
  return (*last_name_check != '\0');
} /* teaching_assistant_last_name_check() */

/*
 * This funciton is for assertion check of id number. Just cheks if the
 * parameter int id_number is greater than 0.
 */

bool teaching_assistant_id_number_check(int id_number) {
  return (id_number > 0);
} /* teaching_assistant_id_number_check() */

/*
 * This function is for assertion check of rating. Just checks if the
 * parameter flaot rating_check is greater than 0.
 */

bool teaching_assistant_rating_check(float rating_check) {
  return (rating_check > 0);
} /* teaching_assistant_rating_check() */

/*
 * This function is for assertion check of gender. Just checks if the
 * parameter enum tyep_t gender_check is the values of the ENUM.
 */

bool teaching_assistant_gender_check(teaching_assistant_t gender_check) {
  return ((gender_check.gender >= FEMALE) && (gender_check.gender <= OTHER));
} /* teaching_assistant_gender_check() */

/*
 * This function is for assertion check of type. Just checks if the
 * parameter enum tyep_t type_check is the values of the ENUM.
 */

bool teaching_assistant_type_check(enum type_t type_check) {
  return ((type_check >= UTA) && (type_check <= COORDINATOR));
} /* teaching_assistant_type_check() */

/*
 * This function is for assertion check of calendar. Just iterates of all
 * values in calendar array and making sure that it is either an A or B.
 */

bool teaching_assistant_calendar_check(teaching_assistant_t calendar_check) {
  for (int i = 0; i < N_DAYS; i++) {
    for (int j = 0; j < N_HOURS; j++) {
      if ((calendar_check.calendar[i][j] != 'A') &&
          (calendar_check.calendar[i][j] != 'B')) {
        return false;
      }
    }
  }
  return true;
} /* teaching_assistant_calendar_check() */

/* Remember, you don't need a main function!
 * It is provided by hw5_main.c or  hw5_test.o
 */

/*
 * This function reads a file that contains all the information for a teaching
 * assistant in binary. It's job is go to the position in the secound parameter
 * and then read that one teaching assisant and returning a typedef.
 */

teaching_assistant_t read_teaching_assistant(FILE *file_ptr, int record_num) {
  assert(file_ptr != NULL);
  assert(record_num >= 0);
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  if (size / sizeof(teaching_assistant_t) < record_num) {
    return BAD_TA;
  }
  fseek(file_ptr, record_num * sizeof(teaching_assistant_t), SEEK_SET);
  teaching_assistant_t read = BAD_TA;
  int elements = fread(&read, sizeof(read), 1, file_ptr);
  if (elements != 1) {
    return BAD_TA;
  }

  return read;
} /* read_teaching_assistant() */

/*
 * This function is very similar to read_teaching_assistant() except
 * it writes to the file. First it makes sure that teh secound parameter
 * is valid by using the above functions for assertion checks. Then it goes
 * the the third parameter position to write to the file adn add the new
 * teaching assistnat to the file
 */

int write_teaching_assistant(FILE *file_ptr, teaching_assistant_t write,
                             int record_num) {
  assert(file_ptr != NULL);
  assert(record_num >= 0);
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  if (size / sizeof(teaching_assistant_t) < record_num) {
    return WRITE_ERROR;
  }

  assert(teaching_assistant_first_name_check(write.first_name));
  assert(teaching_assistant_last_name_check(write.last_name));
  assert(teaching_assistant_id_number_check(write.id_number));
  assert(teaching_assistant_gender_check(write));
  assert(teaching_assistant_type_check(write.type));
  assert(teaching_assistant_rating_check(write.rating));
  assert(teaching_assistant_calendar_check(write));

  fseek(file_ptr, record_num * sizeof(write), SEEK_SET);
  int elements = fwrite(&write, 1, sizeof(write), file_ptr);
  if (elements != 128) {
    return WRITE_ERROR;
  }

  return OK;
} /* write_teaching_assistant() */

/*
 * This function goes into the file to see all teaching asistants.
 * It only finds the percentage of male teaching assistants. So
 * we use the read_teaching_assitant so we can see all teaching
 * assistant.
 */

float compute_percent_by_male(FILE *file_ptr) {
  assert(file_ptr != NULL);

  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  float men = 0.0;
  float total = 0.0;
  for (int i = 0; i < elements; i++) {
    teaching_assistant_t male = read_teaching_assistant(file_ptr, i);
    if (male.gender == MALE) {
      men++;
    }
    total++;
  }
  if (men == 0) {
    return NO_SUCH_TA;
  }
  return men / total;
} /* compute_percent_by_male() */

/*
 * This function is very similar to computer_percent_by_male()
 * except it computes the percent of type. Agian we just read
 * all teaching assistants in the file
 */

float compute_percent_by_type(FILE *file_ptr, enum type_t job) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_type_check(job));
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  float num = 0.0;
  float total = 0.0;

  for (int i = 0; i < elements; i++) {
    teaching_assistant_t type = read_teaching_assistant(file_ptr, i);
    if (type.type == job) {
      num++;
    }
    total++;
  }
  if (num == 0) {
    return NO_SUCH_TA;
  }
  return num / total;
} /* compute_percent_by_type() */

/*
 * This function calculates the average rating by type. So we
 * still iterate through all teaching assitants and check if the
 * type matches the parmeter given of the enum type_t job and then adds
 * each rating to get a total and divides by the total matches to get the
 * average.
 */

float average_rating_by_type(FILE *file_ptr, enum type_t job) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_type_check(job));
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  float average = 0.0;
  float total = 0.0;
  for (int i = 0; i < elements; i++) {
    teaching_assistant_t type = read_teaching_assistant(file_ptr, i);
    if (type.type == job) {
      average += type.rating;
      total++;
    }
  }
  if (total == 0) {
    return NO_SUCH_TA;
  }
  average = average / total;
  return average;
} /* average_rating_by_type() */

/*
 * This function iterates through every teaching assistant in the file
 * until it finds one with the same id_num that is given in the paremeter
 * then it just returns the position where it found it.
 */

int find_teaching_assistant_by_id(FILE *file_ptr, int id_num) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_id_number_check(id_num));
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  for (int i = 0; i < elements; i++) {
    teaching_assistant_t id = read_teaching_assistant(file_ptr, i);
    if (id.id_number == id_num) {
      return i;
    }

  }

  return NO_SUCH_TA;
} /* find_teaching_assistant_by_id() */

/*
 * This function iterates through all teaching assistants in the file and
 * then checks if they have the same first_name and last_name and once
 * it finds the position where it found the first teaching assistant with the
 * same name it will return that position.
 */

int find_teaching_assistant_by_name(FILE *file_ptr, char *first_name,
                                    char *last_name) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_first_name_check(first_name));
  assert(teaching_assistant_last_name_check(last_name));
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  for (int i = 0; i < elements; i++) {
    teaching_assistant_t name = read_teaching_assistant(file_ptr, i);
    int first = strcmp(name.first_name, first_name);
    int last = strcmp(name.last_name, last_name);
    if ((first == 0) && (last == 0)) {
      return i;
    }

  }

  return NO_SUCH_TA;
} /* find_teaching_assistant_by_name() */

/*
 * This function updates the file of teaching assistants. It first asserts that
 * the file is not NULL and teh id_num adn rating is valid. Then it iterates
 * through all teaching assistants to check if it has the same id_num and
 * once it finds the same id_num then it replaces the original rating for
 * that teaching assistant with the new rating in the parameter. It does that
 * by using the write_teaching_assistant() funciton to overwrite the original
 * teacing assistant with the new one.
 */

int update_teaching_assistant_rating(FILE *file_ptr, int id_num, float rating) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_id_number_check(id_num));
  assert(teaching_assistant_rating_check(rating));
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  for (int i = 0; i < elements; i++) {
    teaching_assistant_t replace = read_teaching_assistant(file_ptr, i);
    if (replace.id_number == id_num) {
      replace.rating = rating;
      write_teaching_assistant(file_ptr, replace, i);
      return OK;
    }

  }

  return NO_SUCH_TA;
} /* update_teaching_assistant_rating() */

/*
 * This funciton acts like a receptionist. It first asserts that all the
 * parameters are valid. Then we iterate throught all the teaching assistants
 * until one teachin assistant has the same id number as the given parameter
 * then it checks the booking of that teaching assitant by seeing the calandar
 * array of the given day and time. If it is alrady booked then it returns
 * UNAVAILABLE and if they are free it reserves the office hours making them
 * booked for that time.
 */

int book_office_hours(FILE *file_ptr, int id_num, int day, int time) {
  assert(file_ptr != NULL);
  assert(teaching_assistant_id_number_check(id_num));
  if ((day < 1) || (day > 5)) {
    return BAD_TIME;
  }
  if ((time < 8) || (time > 21)) {
    return BAD_TIME;
  }
  fseek(file_ptr, 0, SEEK_END);
  int size = ftell(file_ptr);
  int elements = size / sizeof(teaching_assistant_t);

  for (int i = 0; i < elements; i++) {
    teaching_assistant_t office_hours = read_teaching_assistant(file_ptr, i);
    if (office_hours.id_number == id_num) {
      printf("OFFICE on day:%d hour:%d : %c\n", day, time,
             office_hours.calendar[day - 1][time - 8]);
      if (office_hours.calendar[day - 1][time - 8] == 'B') {
        return UNAVAILABLE;
      }
      office_hours.calendar[day - 1][time - 8] = 'B';
      write_teaching_assistant(file_ptr, office_hours, i);
      return OK;
    }
  }

  return NO_SUCH_TA;
} /* book_office_hours() */
