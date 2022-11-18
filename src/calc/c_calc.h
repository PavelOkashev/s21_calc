#ifndef SRC_CALC_C_CALC_H_
#define SRC_CALC_C_CALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tk {
  long double n_token;
  int type;
  int priority;
  struct tk *next;
} tokens;

tokens *create_list();

tokens *add_list_past(tokens *head);

long double standart_calc(char *line);

int opn_transfer(char *line, tokens **head, tokens **stek);

int nod_valid(char **line, tokens **head);

void number_determine(char **line, long double *head);

void past_dot_determine(long double *head);

void recourse_transfer(char *line, tokens **head, tokens **stek, int *res);

void calculating_steck_remainder(tokens **stek, tokens **head);

int operation_valid(char **line, tokens **stek);

int priority_and_type(char **token, tokens **stek);

void calculating(tokens **head, tokens **stek);

void bracket_calculating(tokens **head, tokens **stek);

void priority_calculating(tokens **stek, tokens **head, int priority);

void minus_func(tokens **head, tokens **stek);

void plus_func(tokens **head, tokens **stek);

void multiplicat_func(tokens **head, tokens **stek);

void division_func(tokens **head, tokens **stek);

void degree_func(tokens **head, tokens **stek);

void mod_func(tokens **head, tokens **stek);

void log_func(tokens **head, tokens **stek);

void ln_func(tokens **head, tokens **stek);

void sqrt_func(tokens **head, tokens **stek);

void atan_func(tokens **head, tokens **stek);

void asin_func(tokens **head, tokens **stek);

void acos_func(tokens **head, tokens **stek);

void tan_func(tokens **head, tokens **stek);

void sin_func(tokens **head, tokens **stek);

void cos_func(tokens **head, tokens **stek);

#endif // SRC_CALC_C_CALC_H_
