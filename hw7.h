#ifndef HW7_H
#define HW7_H

/* Constant definitions */

#define MAX_FILE_LEN       (50)
#define MAX_APPLICATIONS   (50)
#define MAX_NAME_LEN       (50)

typedef struct application {
  char app_name[MAX_NAME_LEN];
  char app_developer[MAX_NAME_LEN];
  char app_category[MAX_NAME_LEN];
  float app_rating;

  struct application *next_developer_ptr;
  struct application *next_category_ptr;
} application_t;

/* Error codes */

#define APPLICATION_FOUND       (0)
#define NON_READABLE_FILE      (-1)
#define BAD_RECORD             (-2)
#define OUT_OF_BOUNDS          (-3)
#define NO_APPLICATIONS        (-4)
#define APPLICATION_NOT_FOUND  (-5)

/* Function prototypes */

int read_applications(char *);
void link_applications();
int find_application_with_category(int, char *);
int count_category_links(int);
int find_applications_by_rating(float, int *);

/* Global variables */

extern int g_application_count;
extern application_t g_application_array[MAX_APPLICATIONS];

#endif // HW7_H
