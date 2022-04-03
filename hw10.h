#ifndef HW10_H
#define HW10_H

/* Constant definitions */

#define MONTHS_IN_YEAR    (12)
#define DAYS_IN_MONTH     (31)
#define HOURS_IN_DAY      (24)
#define MINUTES_IN_HOUR   (60)
#define SECONDS_IN_MINUTE (60)

/* Error codes */

#define COMMIT_NOT_FOUND (-1)
#define TIME_ERROR       (-2)

/* Structure Definitions */

typedef struct time_struct {
  int id;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
} time_struct_t;

typedef struct commit_info {
  char           *hash_id;
  char           *author;
  time_struct_t  commit_time;
} commit_info_t;

typedef struct commit {
  struct commit_info   *commit_info;
  struct commit        *next_commit;
  struct commit        *prev_commit;
} commit_t;

/* Function prototypes */

void create_commit(char *, char *, time_struct_t, commit_t **);
void delete_commit(commit_t **);
int add_commit(commit_t **, commit_t *);
int delete_git_log(commit_t **);
int find_commit(commit_t **, char *);
int find_latest_commits(commit_t *, time_struct_t, commit_t **);
int delete_list(commit_t **);

#endif // HW10_H
