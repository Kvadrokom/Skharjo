#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "stack_header.h"

int    pres(char op1, char op2)
{
    int num1;
    int num2;

    if (op1 == '+' || op1 == '-')
    {
      num1 = 1;
    }
    if (op1 == '/' || op1 == '*')
    {
      num1 = 2;
    }
    if (op1 == '%')
    {
      num1 = 3;
    }
    if (op2 == '+' || op2 == '-')
    {
      num2 = 1;
    }
    if (op2 == '/' || op2 == '*')
    {
      num2 = 2;
    }
    if (op2 == '%')
    {
      num2 = 3;
    }
    if (op2 == '0')
    {
      num2 = -1;
    }
    if (op2 =='(')
    {
      num2 = 0;
    }
    return (num1 > num2);
}

char *make_str_from_int(int num)
{
  char c[40];
  int i;
  int k;
  char *tmp;

  i = 0;
  k = 0;
  while (num > 0)
  {
    c[i] = num % 10 + 48;
    num = num / 10;
    i++;
  }
  tmp = malloc(sizeof(char) * (i + 1));
  while (i > 0)
  {
    tmp[k] = c[i - 1];
    k++;
    i--;
  }
  tmp[k] = '\0';
  return (tmp);
}

char     *do_op_eval(int num1, int num2, char op)
{
    if (op == '+')
    {
        return (make_str_from_int(num2 + num1));
    }
    if (op == '-')
    {
      return (make_str_from_int(num1 - num2));
    }
    if (op == '/')
    {
      return (make_str_from_int(num1 / num2));
    }
    if (op == '*')
    {
      return (make_str_from_int(num1 * num2));
    }
    if (op == '%')
    {
      return (make_str_from_int(num1 % num2));
    }
    return (0);
}

void  ft_putchar(char c)
{
  write (1, &c, 1);
}

void  ft_print_nbr(int nbr)
{
  if (nbr >= 0 && nbr <= 9)
    ft_putchar(nbr + 48);
  else if (nbr < 0)
  {
    nbr = -nbr;
    ft_putchar('-');
    ft_print_nbr(nbr);
  }
  else
  {
    ft_print_nbr(nbr / 10);
    ft_putchar(nbr % 10 + 48);
  }
}

int   is_tab(char c)
{
  if (c == ' ')
  {
    return (1);
  }
  return (0);
}

int   is_digit(char c)
{
  if (c >= '0' && c <= '9')
  {
    return (1);
  }
  return (0);
}

int   is_op(char c)
{
  if (is_digit(c) == 0 && is_tab(c) == 0)
  {
    return (1);
  }
  return (0);
}

void    do_op_par(t_list  **node_int, t_list **node_char)
{

    int     num1;
    int     num2;
    char    op;
    char  *c;

    c = (*node_char)->data;
    op = c[0];
    while ( op != '(')
    {
        num2 = atoi((*node_int)->data);
        ft_pop(node_int);
        num1 = atoi((*node_int)->data);
        ft_pop(node_int);
        ft_push_back(node_int, do_op_eval(num1, num2, op));
        ft_pop(node_char);
        c = (*node_char)->data;
        op = c[0];
    }
    ft_pop(node_char);
}

void  do_op_pres(t_list **list_int, t_list **list_op)
{
  char *c;
  int num2;
  int num1;

  num1 = atoi((*list_int)->data);
  ft_pop(list_int);
  num2 = atoi((*list_int)->data);
  ft_pop(list_int);
  c = (*list_op)->data;
  ft_push_back(list_int,do_op_eval(num2, num1, c[0]));
  ft_pop(list_op);
}

void  do_op(char *op, t_list **list_op, t_list **list_int)
{
  char *a;

  if (op[0] == '(' || !(*list_op))
    ft_push_back(list_op, op);
  else if (op[0] == ')')
    do_op_par(list_int, list_op);
  else 
  {
    a = (*list_op)->data;
    if (pres(op[0], a[0]))
    {
      ft_push_back(list_op, op);
    }
    else
    {
        while (pres(op[0], a[0]) == 0 && (*list_op))
        {
          do_op_pres(list_int, list_op);
          if(*list_op)
          {
              a = (*list_op)->data;
          }
        }
        ft_push_back(list_op, op);
      }
  }
}

int   last_op(t_list **list_int, t_list **list_op)
{
    int     num1;
    int     num2;
    char    op;
    char  *c;

    c = (*list_op)->data;
    op = c[0];
  while (*list_op)
  {
        num2 = atoi((*list_int)->data);
        ft_pop(list_int);
        num1 = atoi((*list_int)->data);
        ft_pop(list_int);
        ft_push_back(list_int, do_op_eval(num1, num2, op));
        ft_pop(list_op);
        if (*list_op)
        {
            c = (*list_op)->data;
            op = c[0];
        }
  }
  return (atoi((*list_int)->data));
}

int   eval_expr(char *c, t_list **list_int, t_list **list_op)
{
  while (*c != 0)
  {
    while (is_tab(*c) && *c != 0)
    {
      c++;
    }
    if (is_digit(*c) && *c != 0)
    {
      ft_push_back(list_int, c);
      while (is_digit(*c) && *c != 0)
            {
              c++;
            }
    }
    if (is_op(*c) && *c != 0)
    {
      do_op(c, list_op, list_int);
    }
    if(*c == 0)
      break;
    c++;
  }
  return (last_op(list_int, list_op));
}

int main(int argc, char **argv)
{
  t_list  *list_int;
  t_list  *list_op;

  list_op = 0;
  list_int = 0;
  if (argc > 1)
  {
      ft_print_nbr(eval_expr(argv[1], &list_int, &list_op));
  }
}