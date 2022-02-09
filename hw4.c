/* Jean-Pierre Ciotta, hw4.c, CS 24000, Spring 2022
 * Last updated Feb 8, 2022
 */

/* Add any includes here */

#include "hw4.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Define any global variables here */

/* Define your functions here */

/*
 * just adds the two structures
 */

complex_t add_complex(complex_t arg1, complex_t arg2) {
  double add_x = arg1.x + arg2.x;
  double add_y = arg1.y + arg2.y;
  complex_t add = {add_x, add_y};
  return add;
} /* add_complex() */

/*
 * converst the two values of the struct to negative values
 */

complex_t neg_complex(complex_t arg) {
  double neg_x = arg.x * -1;
  double neg_y = arg.y * -1;
  complex_t neg = {neg_x, neg_y};
  return neg;
} /* neg_complex() */

/*
 * subtracts the secound argument from the first
 */

complex_t sub_complex(complex_t arg1, complex_t arg2) {
  complex_t sub = add_complex(arg1, neg_complex(arg2));
  return sub;
} /* sub_complex() */

/*
 * takes the dot product of the two vectors
 */

double dot_complex(complex_t arg1, complex_t arg2) {
  double dot_x = (arg1.x * arg2.x);
  double dot_y = (arg1.y * arg2.y);

  return dot_x + dot_y;
} /* dot_complex() */

/*
 * takes the inverse of both values
 */

complex_t inv_complex(complex_t arg) {
  double top_x = arg.x;
  double bottom_x = (arg.x * arg.x) + (arg.y * arg.y);
  double top_y = arg.y * -1;
  double bottom_y = bottom_x;

  complex_t inv = {(top_x / bottom_x), (top_y / bottom_y)};
  return inv;
} /* inv_complex() */

/*
 * This function returns the product of the two complex argumetns
 */

complex_t mul_complex(complex_t arg1, complex_t arg2) {
  double x_1 = arg1.x;
  double x_2 = arg2.x;
  double y_1 = arg1.y;
  double y_2 = arg2.y;

  complex_t mul = {((x_1 * x_2) - (y_1 * y_2)), ((x_1 * y_2) + (y_1 * x_2))};
  return mul;
} /* mul_complex() */

/*
 * complex division of first adn secound document
 */

complex_t div_complex(complex_t arg1, complex_t arg2) {
  complex_t div = mul_complex(arg1, inv_complex(arg2));
  return div;
} /* div_complex() */

/*
 * takes the complex exponent of the two values
 */

complex_t exp_complex(complex_t arg) {
  double x = exp(arg.x) * cos(arg.y);
  double y = exp(arg.x) * sin(arg.y);

  complex_t exp = {x, y};
  return exp;
} /* exp_complex() */

/*
 * replicate the madelbrot equation
 */

int mandelbrot(complex_t arg) {
  int cnt = 0;
  double len = 0.0;
  complex_t z = {0.0, 0.0};

  while (cnt < MAX_MANDELBROT) {
    z = mul_complex(z, z);
    z = add_complex(z, arg);
    len = dot_complex(z, z);
    cnt++;
    if (len > 4) {
      return cnt;
    }
  }
  return cnt;
} /* mandelbrot() */
