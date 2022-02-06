#ifndef HW3_H
#define HW3_H

/* Constant definitions */

#define MAX_RECIPES          (50)
#define MAX_WEATHER_LEN      (15)
#define MAX_FILE_LEN         (50)
#define CODE_LEN              (7)
#define NUM_COLS              (3)

/* Error codes */

#define OK                    (0)
#define FILE_READ_ERR        (-1)
#define FILE_WRITE_ERR       (-2)
#define RECORD_ERROR         (-3)
#define OUT_OF_BOUNDS        (-4)
#define NO_DATA_POINTS       (-5)
#define NO_SUCH_DATA         (-6)
#define BAD_RANGE            (-7)
#define BAD_PERCENTAGE       (-8)
#define BAD_CODE             (-9)
#define BAD_ROW             (-10)

/* Function prototypes */

int read_tables(char *);
int find_cheapest_recipe(void);
int find_cheapest_recipe_by_weather(char *);
int count_recipes_in_price_range(float, float);
int count_num_satisfied_over_percentage(float);
float calculate_recipe_rating(char *);
int calculate_all_ratings(char *);
int write_tables(char *, int, int);

/* Global variables */

extern int g_recipe_count;
extern char g_recipe[MAX_RECIPES][CODE_LEN];
extern char g_weather[MAX_RECIPES][MAX_WEATHER_LEN];
extern int g_review[MAX_RECIPES][NUM_COLS];
extern float g_price[MAX_RECIPES];

#pragma GCC poison access

#endif // HW3_H
