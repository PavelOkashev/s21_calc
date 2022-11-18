#include "c_calc.h"

void cos_func(tokens **head, tokens **stek) {
  (*head)->n_token = cosl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void sin_func(tokens **head, tokens **stek) {
  (*head)->n_token = sinl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void tan_func(tokens **head, tokens **stek) {
  (*head)->n_token = tanl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void acos_func(tokens **head, tokens **stek) {
  (*head)->n_token = acosl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void asin_func(tokens **head, tokens **stek) {
  (*head)->n_token = asinl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void atan_func(tokens **head, tokens **stek) {
  (*head)->n_token = atanl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void sqrt_func(tokens **head, tokens **stek) {
  (*head)->n_token = sqrtl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void ln_func(tokens **head, tokens **stek) {
  (*head)->n_token = logl((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void log_func(tokens **head, tokens **stek) {
  (*head)->n_token = log10l((*head)->n_token);
  tokens *next = (*stek)->next;
  free(*stek);
  *stek = next;
}

void mod_func(tokens **head, tokens **stek) {
  (*head)->next->n_token = fmodl((*head)->next->n_token, (*head)->n_token);
  tokens *next_h = (*head)->next;
  free(*head);
  *head = next_h;
  tokens *next_s = (*stek)->next;
  free(*stek);
  *stek = next_s;
}

void degree_func(tokens **head, tokens **stek) {
  (*head)->next->n_token = powl((*head)->next->n_token, (*head)->n_token);
  tokens *next_h = (*head)->next;
  free(*head);
  *head = next_h;
  tokens *next_s = (*stek)->next;
  free(*stek);
  *stek = next_s;
}

void division_func(tokens **head, tokens **stek) {
  (*head)->next->n_token /= (*head)->n_token;
  tokens *next_h = (*head)->next;
  free(*head);
  *head = next_h;
  tokens *next_s = (*stek)->next;
  free(*stek);
  *stek = next_s;
}

void multiplicat_func(tokens **head, tokens **stek) {
  (*head)->next->n_token *= (*head)->n_token;
  tokens *next_h = (*head)->next;
  free(*head);
  *head = next_h;
  tokens *next_s = (*stek)->next;
  free(*stek);
  *stek = next_s;
}

void plus_func(tokens **head, tokens **stek) {
  if ((*stek)->type) {
    (*head)->n_token =
        (*head)->n_token < 0 ? (*head)->n_token * -1 : (*head)->n_token;
    tokens *next = (*stek)->next;
    free(*stek);
    *stek = next;
  } else {
    (*head)->next->n_token += (*head)->n_token;
    tokens *next_h = (*head)->next;
    free(*head);
    *head = next_h;
    tokens *next_s = (*stek)->next;
    free(*stek);
    *stek = next_s;
  }
}

void minus_func(tokens **head, tokens **stek) {
  if ((*stek)->type) {
    (*head)->n_token = 0 - (*head)->n_token;
    tokens *next = (*stek)->next;
    free(*stek);
    *stek = next;
  } else {
    (*head)->next->n_token -= (*head)->n_token;
    tokens *next_h = (*head)->next;
    free(*head);
    *head = next_h;
    tokens *next_s = (*stek)->next;
    free(*stek);
    *stek = next_s;
  }
}

void priority_calculating(tokens **stek, tokens **head, int priority) {
  if (*stek && (*stek)->priority >= priority) {
    switch ((int)(*stek)->n_token) {
    case '-':
      minus_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case '+':
      plus_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case '*':
      multiplicat_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case '/':
      division_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case '^':
      if ((*stek)->priority > priority) {
        degree_func(head, stek);
        priority_calculating(stek, head, priority);
      }
      break;
    case 'm':
      mod_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 's':
      sin_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'c':
      cos_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 't':
      tan_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'S':
      asin_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'C':
      acos_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'T':
      atan_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'q':
      sqrt_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'l':
      ln_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    case 'L':
      log_func(head, stek);
      priority_calculating(stek, head, priority);
      break;
    }
  }
}

void bracket_calculating(tokens **head, tokens **stek) {
  calculating_steck_remainder(&(*stek)->next, head);
  tokens *new_s = (*stek)->next->next;
  free((*stek)->next);
  free(*stek);
  *stek = new_s;
}

void calculating_steck_remainder(tokens **stek, tokens **head) {
  if (*stek && (*stek)->n_token != '(') {
    switch ((int)(*stek)->n_token) {
    case '-':
      minus_func(head, stek);
      break;
    case '+':
      plus_func(head, stek);
      break;
    case '*':
      multiplicat_func(head, stek);
      break;
    case '/':
      division_func(head, stek);
      break;
    case '^':
      degree_func(head, stek);
      break;
    case 'm':
      mod_func(head, stek);
      break;
    case 's':
      sin_func(head, stek);
      break;
    case 'c':
      cos_func(head, stek);
      break;
    case 't':
      tan_func(head, stek);
      break;
    case 'S':
      asin_func(head, stek);
      break;
    case 'C':
      acos_func(head, stek);
      break;
    case 'T':
      atan_func(head, stek);
      break;
    case 'q':
      sqrt_func(head, stek);
      break;
    case 'l':
      ln_func(head, stek);
      break;
    case 'L':
      log_func(head, stek);
      break;
    }
    calculating_steck_remainder(stek, head);
  }
}

void calculating(tokens **head, tokens **stek) {
  if ((*stek)->n_token == ')') {
    bracket_calculating(head, stek);
  } else if ((*stek)->n_token != '(') {
    priority_calculating(&(*stek)->next, head, (*stek)->priority);
  }
}

int priority_and_type(char **token, tokens **stek) {
  tokens *new_s = add_list_past(*stek);
  int res = 0;
  if (new_s) {
    res = 1;
    *stek = new_s;
    (*stek)->n_token = **token;
    if (**token == '-' || **token == '+') {
      (*stek)->type = *(*token - 1) == '(' ? 1 : 0;
      (*stek)->priority = (*stek)->type == 1 ? 5 : 2;
    } else if (**token == '^') {
      (*stek)->priority = 4;
      (*stek)->type =
          (*stek)->next && (*stek)->next->n_token == **token ? 1 : 0;
    } else if (**token == '*' || **token == '/' || **token == 'm') {
      (*stek)->priority = 3;
      (*stek)->type = 0;
    } else if (**token == '(' || **token == ')') {
      (*stek)->priority = 1;
      (*stek)->type = 0;
    } else {
      (*stek)->priority = 5;
      (*stek)->type = 1;
    }
  }
  return res;
}

int operation_valid(char **line, tokens **stek) {
  int res = 0;
  if (**line) {
    res = priority_and_type(line, stek);
    *line += 1;
  }
  return res;
}

void recourse_transfer(char *line, tokens **head, tokens **stek, int *res) {
  if (*line) {
    *res = opn_transfer(line, head, stek);
  } else {
    calculating_steck_remainder(stek, head);
  }
}

void past_dot_determine(long double *head) {
  if (*head > 1) {
    *head *= 0.1;
    past_dot_determine(head);
  }
}

void number_determine(char **line, long double *head) {
  if (**line >= '0' && **line <= '9') {
    *head *= 10;
    *head += **line - '0';
    *line += 1;
    number_determine(line, head);
  }
}

int nod_valid(char **line, tokens **head) {
  int res = 0;
  if (**line >= '0' && **line <= '9') {
    tokens *new_h = add_list_past(*head);
    if (new_h) {
      res = 1;
      *head = new_h;
      long double pre_dot = 0;
      number_determine(line, &pre_dot);
      (*head)->n_token = pre_dot;
      if (**line == '.') {
        long double past_dot = 0;
        *line += 1;
        number_determine(line, &past_dot);
        past_dot_determine(&past_dot);
        (*head)->n_token += past_dot;
      }
    }
  }
  return res;
}

int opn_transfer(char *line, tokens **head, tokens **stek) {
  int res = 0;
  if (nod_valid(&line, head)) {
    res = 1;
    recourse_transfer(line, head, stek, &res);
  } else if (operation_valid(&line, stek)) {
    res = 1;
    calculating(head, stek);
    recourse_transfer(line, head, stek, &res);
  }
  return res;
}

long double standart_calc(char *line) {
  long double result = 0;
  tokens *stek = 0;
  tokens *head = 0;
  if (opn_transfer(line, &head, &stek)) {
    result = head->n_token;
  }
  free(head);
  return result;
}

tokens *add_list_past(tokens *head) {
  tokens *tmp = create_list();
  tmp->next = head;
  return tmp;
}

tokens *create_list() {
  tokens *tmp = NULL;
  tmp = (tokens *)calloc(1, sizeof(tokens));
  return tmp;
}
