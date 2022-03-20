#ifndef HW8_H
#define HW8_H

/* Structure Declarations */

typedef struct app {
  char *author;
  char *category;
  char *name;

  struct app *next_app;
} app_t;

/* Function prototypes */

app_t *add_app_to_head(app_t*, char *, char *, char *);
app_t *remove_app_from_head(app_t *);
app_t *add_app_to_tail(app_t *, char *, char *, char *);
app_t *remove_app_from_tail(app_t *);
int count_apps(app_t *);
app_t *search_by_index(app_t *, int);
app_t *search_by_information(app_t *, char *, char *, char *);
app_t *modify_app_by_index(app_t *, int, char *, char *, char *);
app_t *move_to_tail(app_t *, int);
app_t *interleave_apps(app_t *, app_t *);
void free_app_list(app_t *);

#endif // HW8_H
