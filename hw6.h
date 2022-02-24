#ifndef HW6_H
#define HW6_H

/* Constant definitions */

#define MAX_FILE_LEN       (50)
#define MAX_APPLICATIONS   (50)
#define MAX_NAME_LEN       (50)

typedef struct application {
  char app_name[MAX_NAME_LEN];
  char app_developer[MAX_NAME_LEN];
  char app_category[MAX_NAME_LEN];
  float app_rating;
} application_t;

/* Error codes */

#define READ_ERROR         (-1)
#define BAD_RECORD         (-2)
#define OUT_OF_BOUNDS      (-3)
#define NO_APPLICATIONS    (-4)

/* Function prototypes */

int read_applications(char *);
int find_applications(char *, char *, char *, float);

/* Global variables */

extern int g_application_count;
extern application_t g_application_array[MAX_APPLICATIONS];

#endif // HW6_H
